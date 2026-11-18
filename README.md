# lineparse — Patchcheck patch-validation target

This repository is an independent patch-validation target for [Patchcheck](https://github.com/amirhoseinshayan/patchcheck). It is a harmless fixture for framework self-tests (NOT a real vulnerability).

## Layout

- `src/` — the target source (base version on `main`).
- `configs/lineparse-argv.json` — Patchcheck configuration (build, tests, oracles).
- `corpus/lineparse/` — test inputs; `oracles/lineparse/` — independent reference behaviour.
- `.github/workflows/patchcheck.yml` — the CI pipeline.

## Patch evaluation

Every pull request against `main` is evaluated by the pipeline: the base
version and the PR head are both built (Release and Sanitized, ELF Linux
x86_64) and run on the same valid / boundary / invalid / error-causing inputs
inside an isolated container with resource limits. Findings are compared to
independent oracles, correlated with the diff, and the verdict is one of the
spec codes:

| code | meaning |
|---|---|
| 0 | PASS |
| 10 | VULN_REMAINS / NEW_ISSUE |
| 20 | FUNC_REGRESSION |
| 30 | BUILD_OR_CONFIG_ERROR |
| 40 | INCONCLUSIVE |

The verdict comes from execution evidence, never from the branch name, PR
title or any pre-defined result.

## Run independently

```bash
python3 -m venv .venv && .venv/bin/pip install patchcheck  # or: git clone https://github.com/amirhoseinshayan/patchcheck.git && .venv/bin/python patchcheck/ci/bootstrap.py
docker build --platform linux/amd64 -t patchcheck-framework:1.0 -f environment/Dockerfile .  # from the Patchcheck clone
.venv/bin/patchcheck run configs/lineparse-argv.json --base main --candidate <branch-or-sha> --out artifacts/result
```

For an unseen patch handed over as a diff:
```bash
.venv/bin/patchcheck run configs/lineparse-argv.json --patch /path/to/patch.diff --out artifacts/result
```

## Fixture note

This target is a **harmless fixture**: it exercises the framework mechanics
and always ends INCONCLUSIVE (40). A green verdict here never confirms a real
security fix.

See `oracles/lineparse/SPEC.md` for the independent reference behaviour.
