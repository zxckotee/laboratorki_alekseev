from __future__ import annotations

import json
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path

from .compare import match_any


@dataclass
class TaskRunResult:
    task_number: int
    source: str
    ok: bool
    stdout: str
    stderr: str
    error: str | None = None


def _compile(c_src: Path, out_bin: Path, flags: list[str]) -> subprocess.CompletedProcess:
    libs = [f for f in flags if f.startswith("-l")]
    cflags = [f for f in flags if not f.startswith("-l")]
    cmd = ["gcc", *cflags, str(c_src), "-o", str(out_bin), *libs]
    return subprocess.run(cmd, capture_output=True, text=True, timeout=60)


def run_task(lab_dir: Path, task_meta: dict) -> TaskRunResult:
    task_no = int(task_meta["task_number"])
    source_name = task_meta["source"]
    c_src = lab_dir / source_name
    flags = task_meta.get("compile_flags", ["-std=c11", "-Wall", "-lm"])
    timeout = float(task_meta.get("timeout_sec", 5))
    compare = task_meta.get("compare", "normalize")

    if not c_src.is_file():
        return TaskRunResult(
            task_number=task_no,
            source=source_name,
            ok=False,
            stdout="",
            stderr="",
            error=f"Missing source file: {c_src}",
        )

    with tempfile.TemporaryDirectory() as tmp:
        binary = Path(tmp) / "a.out"
        comp = _compile(c_src, binary, flags)
        if comp.returncode != 0:
            return TaskRunResult(
                task_number=task_no,
                source=source_name,
                ok=False,
                stdout="",
                stderr=comp.stderr,
                error=f"gcc failed with code {comp.returncode}",
            )

        try:
            proc = subprocess.run(
                [str(binary)],
                input=task_meta.get("stdin", ""),
                capture_output=True,
                text=True,
                timeout=timeout,
            )
        except subprocess.TimeoutExpired:
            return TaskRunResult(
                task_number=task_no,
                source=source_name,
                ok=False,
                stdout="",
                stderr="",
                error=f"Timeout after {timeout}s",
            )

        if proc.returncode != 0:
            return TaskRunResult(
                task_number=task_no,
                source=source_name,
                ok=False,
                stdout=proc.stdout,
                stderr=proc.stderr,
                error=f"Program exited with code {proc.returncode}",
            )

        ok, err = match_any(
            proc.stdout, task_meta["expected_stdout"], compare
        )
        if not ok:
            return TaskRunResult(
                task_number=task_no,
                source=source_name,
                ok=False,
                stdout=proc.stdout,
                stderr=proc.stderr,
                error=err,
            )

        return TaskRunResult(
            task_number=task_no,
            source=source_name,
            ok=True,
            stdout=proc.stdout,
            stderr=proc.stderr,
            error=None,
        )


def discover_tasks(lab_dir: Path) -> list[dict]:
    tasks: list[dict] = []
    for path in sorted(lab_dir.glob("task_*.json")):
        data = json.loads(path.read_text(encoding="utf-8"))
        tasks.append(data)
    tasks.sort(key=lambda t: int(t["task_number"]))
    return tasks


def run_lab(lab_dir: Path) -> tuple[bool, list[TaskRunResult]]:
    results = [run_task(lab_dir, meta) for meta in discover_tasks(lab_dir)]
    return all(r.ok for r in results), results
