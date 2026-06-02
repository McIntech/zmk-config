# Contributing

Thank you for contributing to this project. Please follow the conventions below.

## Local setup

```bash
git clone git@github.com:<owner>/<repo>.git
cd <repo>
# install dependencies for your stack
# Node:    yarn install      | pnpm install     | npm ci
# Ruby:    bundle install
# Python:  pip install -r requirements.txt
# .NET:    dotnet restore
```

Copy `.env.example` to `.env` and fill in the required values.

## Branch model

This project uses a two-branch model. There is no `main` branch.

| Branch       | Purpose                                                                  |
| ------------ | ------------------------------------------------------------------------ |
| `develop`    | Active development — all feature and fix branches merge here first.      |
| `production` | Deployed to production — release-ready code only, merged from `develop`. |

Workflow:

1. Branch off `develop`:
   - Features: `feature/<short-name>`
   - Fixes: `fix/<short-name>`
   - Chores: `chore/<short-name>`
2. Open a Pull Request into `develop`.
3. When `develop` is stable and verified, open a PR `develop → production`.
4. Merging into `production` triggers the production deploy.

## Commit messages — Conventional Commits

Every commit message must follow [Conventional Commits](https://www.conventionalcommits.org/):

| Type        | Use for                                 |
| ----------- | --------------------------------------- |
| `feat:`     | A new feature                           |
| `fix:`      | A bug fix                               |
| `docs:`     | Documentation only                      |
| `refactor:` | Code change that is not a feat or a fix |
| `test:`     | Adding or correcting tests              |
| `chore:`    | Tooling, build, or maintenance          |
| `perf:`     | Performance improvement                 |
| `style:`    | Formatting, whitespace, no logic change |

Example: `feat(invoices): add CFDI 4.0 stamping endpoint`

## Code review policy

- Every PR requires **at least 1 approval** before merging.
- All CI checks must pass (`tests`, `lint`, `build`, `typecheck` where applicable).
- Resolve all review comments before merging.
- Squash-merge is preferred to keep history readable.

## Language policy

- **Code, comments, identifiers, commit messages, documentation, config:** English.
- **User-facing app text** (UI strings, labels, messages displayed to end users): Spanish (Mexico) by default.

## Reporting issues

Use the issue templates under `.github/ISSUE_TEMPLATE/` (Bug report or Feature request).
