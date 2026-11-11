from __future__ import annotations

import json
from pathlib import Path

from .runner import TaskRunResult


TITLE_STYLES = """<style>
  @media print {
    @page {
      size: A4;
      margin: 20mm 15mm 20mm 20mm;
    }
    .gost-page-break {
      page-break-after: always !important;
      break-after: page !important;
    }
  }
  body, html {
    margin: 0;
    padding: 0;
    font-family: "Times New Roman", Times, serif;
    font-size: 14pt;
    line-height: 1.5;
    color: #000;
  }
  .gost-center { text-align: center; }
  .gost-bold { font-weight: bold; }
  .gost-uppercase { text-transform: uppercase; }
  .space-vedomstvo { margin-bottom: 20mm; }
  .space-kafedra { margin-bottom: 30mm; }
  .space-tema { margin-bottom: 35mm; }
  .gost-signatures-block {
    margin-left: 105mm;
    text-align: left;
    line-height: 1.7;
  }
  .gost-footer-city { margin-top: 45mm; }
</style>
"""


def _load_defaults(repo_root: Path) -> dict:
    path = repo_root / "config" / "defaults.json"
    if path.is_file():
        return json.loads(path.read_text(encoding="utf-8"))
    return {}


def _merge_lab_meta(lab_dir: Path, repo_root: Path) -> dict:
    defaults = _load_defaults(repo_root)
    meta = json.loads((lab_dir / "lab.json").read_text(encoding="utf-8"))
    student = {**defaults.get("student", {}), **meta.get("student", {})}
    reviewer = {**defaults.get("reviewer", {}), **meta.get("reviewer", {})}
    meta.setdefault("variant", defaults.get("variant", 19))
    meta.setdefault("department", defaults.get("department", ""))
    meta.setdefault("city", defaults.get("city", "Краснодар"))
    meta.setdefault("year", defaults.get("year", 2026))
    meta.setdefault("discipline", defaults.get("discipline", ""))
    meta["student"] = student
    meta["reviewer"] = reviewer
    return meta


def _initials(full_name: str) -> str:
    parts = full_name.split()
    if len(parts) >= 3:
        return f"{parts[1][0]}. {parts[2][0]}. {parts[0]}"
    if len(parts) == 2:
        return f"{parts[1][0]}. {parts[0]}"
    return full_name


def render_title_page(meta: dict) -> str:
    student = meta["student"]
    reviewer = meta["reviewer"]
    fio_short = _initials(student.get("full_name", ""))
    lab_no = meta.get("lab_number", "?")
    theme = meta.get("report_theme") or f"Лабораторная работа {lab_no}"
    lab_title = meta.get("lab_title", "")
    discipline = meta.get("discipline", "")
    group = student.get("group", "")
    year = meta.get("year", 2026)
    city = meta.get("city", "Краснодар")
    department = meta.get("department", "")

    return f"""{TITLE_STYLES}
<div class="gost-page-break">

  <div class="gost-center gost-uppercase space-vedomstvo">
    Министерство науки и высшего образования <br>Российской Федерации<br>
    Федеральное государственное бюджетное образовательное<br> учреждение
    высшего образования<br>
    <span class="gost-bold">«КУБАНСКИЙ ГОСУДАРСТВЕННЫЙ УНИВЕРСИТЕТ»</span>
  </div>

  <div class="gost-center space-kafedra">
    {department}
  </div>

  <div class="gost-center gost-uppercase gost-bold" style="margin-bottom: 15mm;">
    Лабораторная работа №{lab_no}<br>
    <span style="font-weight: normal; text-transform: none;">по дисциплине: «{discipline}»</span>
  </div>

  <div class="gost-center space-tema">
    на тему: <span class="gost-bold">«{lab_title}»</span><br>
    <span style="font-weight: normal;">Вариант {meta.get("variant", 19)}</span>
  </div>

  <div class="gost-signatures-block">
    <strong>Выполнил:</strong><br>
    Студент группы {group}<br>
    ___________ / {fio_short}<br>
    «___» _________ {year} г.<br><br>
    <strong>Проверил:</strong><br>
    {reviewer.get("title", "")}<br>
    ___________ / {reviewer.get("name", "")}<br>
    «___» _________ {year} г.
  </div>

  <div class="gost-center gost-footer-city">
    {city}, {year}
  </div>

</div>

<!-- -->

## {theme}

Вариант **{meta.get("variant", 19)}**. {student.get("faculty", "")}, {student.get("specialty", "")}.

"""


def _read_explanation(lab_dir: Path, task_no: int) -> str:
    md = lab_dir / f"task_{task_no:02d}.md"
    if md.is_file():
        return md.read_text(encoding="utf-8").strip()
    return ""


def render_task_section(
    lab_dir: Path, task_meta: dict, run: TaskRunResult
) -> str:
    task_no = int(task_meta["task_number"])
    condition = task_meta.get("condition", "").strip()
    source = lab_dir / task_meta["source"]
    code = source.read_text(encoding="utf-8").strip() if source.is_file() else ""
    stdin = task_meta.get("stdin", "")
    stdout = run.stdout if run.ok else task_meta.get("expected_stdout", "")

    explanation = _read_explanation(lab_dir, task_no)
    expl_block = f"\n\n{explanation}\n" if explanation else ""

    return f"""### Задача №{task_no}

**Условие.** {condition}
{expl_block}
**Код (`{task_meta["source"]}`):**

```c
{code}
```

**Ввод:**

```
{stdin.rstrip()}
```

**Вывод:**

```
{stdout.rstrip() if isinstance(stdout, str) else stdout}
```

"""


def build_report(
    lab_dir: Path,
    repo_root: Path,
    results: list[TaskRunResult],
) -> str:
    meta = _merge_lab_meta(lab_dir, repo_root)
    tasks: dict[int, dict] = {}
    for p in sorted(lab_dir.glob("task_*.json")):
        data = json.loads(p.read_text(encoding="utf-8"))
        tasks[int(data["task_number"])] = data
    run_map = {r.task_number: r for r in results}

    parts = [render_title_page(meta)]
    for task_no in sorted(tasks.keys()):
        parts.append(render_task_section(lab_dir, tasks[task_no], run_map[task_no]))
    return "\n".join(parts).rstrip() + "\n"
