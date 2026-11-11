from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

from .report import build_report
from .runner import discover_tasks, run_lab


LAB_DIR_RE = re.compile(r"^lab_(\d+)_(\d+)$")


def repo_root() -> Path:
    return Path(__file__).resolve().parents[2]


def find_labs(root: Path, only: list[str] | None) -> list[Path]:
    if only:
        paths = []
        for name in only:
            p = root / name
            if not p.is_dir():
                print(f"ERROR: lab directory not found: {p}", file=sys.stderr)
                sys.exit(1)
            paths.append(p)
        return paths

    labs = []
    for p in sorted(root.iterdir()):
        if p.is_dir() and LAB_DIR_RE.match(p.name) and (p / "lab.json").is_file():
            labs.append(p)
    return labs


def process_lab(lab_dir: Path, root: Path, check_only: bool) -> bool:
    if not discover_tasks(lab_dir):
        print(f"SKIP {lab_dir.name}: no task_*.json")
        return True

    ok, results = run_lab(lab_dir)
    if not ok:
        for r in results:
            if not r.ok:
                print(f"FAIL {lab_dir.name} task {r.task_number}: {r.error}", file=sys.stderr)
        return False

    if check_only:
        print(f"OK {lab_dir.name}: all tasks passed")
        return True

    report = build_report(lab_dir, root, results)
    out = lab_dir / "REPORT.md"
    changed = (not out.exists()) or out.read_text(encoding="utf-8") != report
    out.write_text(report, encoding="utf-8")
    status = "UPDATED" if changed else "UNCHANGED"
    print(f"{status} {lab_dir.name}/REPORT.md")
    return True


def main() -> None:
    parser = argparse.ArgumentParser(description="Compile, test, and render lab reports.")
    parser.add_argument(
        "--lab",
        action="append",
        dest="labs",
        help="Process only this lab directory (e.g. lab_1_19). Can be repeated.",
    )
    parser.add_argument(
        "--check",
        action="store_true",
        help="Only compile and test; do not write REPORT.md",
    )
    args = parser.parse_args()
    root = repo_root()
    labs = find_labs(root, args.labs)
    if not labs:
        print("No lab directories found.", file=sys.stderr)
        sys.exit(0)

    success = True
    for lab in labs:
        if not process_lab(lab, root, args.check):
            success = False

    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()
