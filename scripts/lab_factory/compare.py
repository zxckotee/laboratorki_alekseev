from __future__ import annotations

import re


def normalize_output(text: str) -> str:
    text = text.replace("\r\n", "\n").replace("\r", "\n")
    lines = [ln.rstrip() for ln in text.split("\n")]
    while lines and lines[-1] == "":
        lines.pop()
    return "\n".join(lines)


def outputs_match(actual: str, expected: str, mode: str) -> tuple[bool, str]:
    if mode == "exact":
        ok = actual == expected
    elif mode == "ignore_trailing_ws":
        ok = actual.rstrip() == expected.rstrip()
    elif mode == "normalize":
        ok = normalize_output(actual) == normalize_output(expected)
    else:
        raise ValueError(f"Unknown compare mode: {mode}")
    if ok:
        return True, ""
    return False, (
        f"expected ({mode}):\n{repr(expected)}\n"
        f"actual ({mode}):\n{repr(actual)}"
    )


def match_any(actual: str, expected, mode: str) -> tuple[bool, str]:
    if isinstance(expected, list):
        errors = []
        for item in expected:
            ok, err = outputs_match(actual, item, mode)
            if ok:
                return True, ""
            errors.append(err)
        return False, "No alternative matched:\n" + "\n---\n".join(errors)
    return outputs_match(actual, expected, mode)
