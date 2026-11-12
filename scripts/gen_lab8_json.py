#!/usr/bin/env python3
"""Generate task JSON with captured stdout for lab_8_* folders."""
import json
import subprocess
import tempfile
from pathlib import Path

CONDITIONS = {
    ("lab_8_6", 1): "Задан массив вещественных X(n): сумма положительных; произведение на нечётных индексах во 2-й половине; объединение с Y(m) в Z (отриц., нули, положит.); удаление максимума из Z.",
    ("lab_8_6", 2): "X — числа без цифры 0, Y — составные; массив Z; 5 наибольших нечётных в Z; сортировка X, Y, Z.",
    ("lab_8_6", 3): "Удалить последнюю группу убывающих нечётных чисел.",
    ("lab_8_6", 4): "Упорядочить по возрастанию суммы цифр элементы между последним палиндромом и первым простым.",
    ("lab_8_19", 1): "Произведение кратных 7; количество между первым и последним чётным; Y из первых k положительных; удалить из X элемент, ближайший к среднему.",
    ("lab_8_19", 2): "X в пятеричной, Y в шестеричной записи → Z в десятичной; пять наибольших с нечётной суммой цифр.",
    ("lab_8_19", 3): "Удалить группу простых минимальной длины с убывающими цифрами.",
    ("lab_8_19", 4): "Упорядочить по убыванию суммы цифр между последним и предпоследним палиндромами.",
}

STDIN = {
    ("lab_8_6", 1): "4\n1\n-2\n3\n-1\n2\n0\n5\n",
    ("lab_8_6", 2): "3\n12\n21\n103\n3\n4\n6\n9\n",
    ("lab_8_6", 3): "4\n9\n7\n5\n10\n",
    ("lab_8_6", 4): "5\n4\n11\n6\n5\n7\n",
    ("lab_8_19", 1): "5\n7\n14\n3\n8\n4\n2\n",
    ("lab_8_19", 2): "2\n23\n10\n2\n15\n14\n",
    ("lab_8_19", 3): "4\n13\n31\n2\n5\n",
    ("lab_8_19", 4): "6\n1\n121\n13\n5\n22\n3\n",
}


def main() -> None:
    root = Path(__file__).resolve().parents[1]
    for key, stdin in STDIN.items():
        lab_name, task_no = key
        lab = root / lab_name
        src = lab / f"task_{task_no:02d}.c"
        meta = {
            "task_number": task_no,
            "condition": CONDITIONS[key],
            "source": f"task_{task_no:02d}.c",
            "stdin": stdin,
            "compare": "normalize",
            "compile_flags": ["-std=c11", "-Wall", "-Wextra", "-lm"],
        }
        with tempfile.TemporaryDirectory() as tmp:
            binp = Path(tmp) / "a.out"
            flags = meta["compile_flags"]
            libs = [f for f in flags if f.startswith("-l")]
            cflags = [f for f in flags if not f.startswith("-l")]
            subprocess.run(["gcc", *cflags, str(src), "-o", str(binp), *libs], check=True)
            r = subprocess.run([str(binp)], input=stdin, capture_output=True, text=True, check=True)
            meta["expected_stdout"] = r.stdout
        (lab / f"task_{task_no:02d}.json").write_text(
            json.dumps(meta, ensure_ascii=False, indent=2) + "\n",
            encoding="utf-8",
        )
        print("OK", lab_name, task_no)


if __name__ == "__main__":
    main()
