# Dizionario — Testing Notes

## Environments tested

| Environment | Result |
|-------------|--------|
| Fedora + KDE Plasma 6 (client target) | Primary target; build with `cmake` + `qt6-qtbase-devel` |
| Ubuntu 24.04 (dev/CI agent) | Source builds and unit tests pass (`ctest`) |
| Original Windows `Dizionario.exe` (.NET 2.0) | Behavior reference for search / navigation |

## How to run automated tests

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

Included tests:

- `dictionary-index` — search upper-bound rule (`like` → `linea`) and prev/next
- `jpg-paths` — default image lookup order (exe-local + share directories)

## Manual UI checks

1. Place sample or real scans in `build/jpg/` (or `~/.local/share/dizionario/jpg/`).
2. Start `./build/dizionario` (or the RPM-installed `dizionario`).
3. Confirm the status bar shows a page count and path.
4. Try these searches:

| Query | Expected with sample pages | Expected with full original set |
|-------|----------------------------|----------------------------------|
| `like` | Opens `linea.jpg` | Page whose key is the first headword ≥ `like` (historically the lift/linea scan) |
| `linea` | Exact `linea.jpg` | Exact match page |
| `aaa` | First page (`abbandonare` in samples) | First page in the index |
| `zzz` | Last page (`zuzzurullone` in samples) | Last page in the index |

5. **上一页 / 下一页** move one page and clamp at ends.
6. **File → Open Image Folder…** selects a folder (not individual `.jpg` files).
7. **File → Find Default Image Folder** re-runs the standard lookup paths.

## Image discovery order

1. `<executable_dir>/jpg/`
2. `./jpg/`
3. `~/.local/share/dizionario/jpg/`
4. `/usr/local/share/dizionario/jpg/`
5. `/usr/share/dizionario/jpg/`

## Known limitations

- Dictionary **page images are not inside the RPM**; install or copy them separately into one of the paths above.
- Very large scans may use significant RAM when zoomed; fit-to-width is the default.
- Qt may print desktop-portal / GTK warnings on some sessions; they are usually harmless if the window works.
- Filename encoding should be plain ASCII headwords matching the original distribution.
- This package does not relicense the original page scans.

## RPM verification (on Fedora)

```bash
sudo dnf install ./packages/kde-dictionary-1.0.0.rpm   # or the versioned dizionario-*.rpm
dizionario
rpm -ql dizionario
```
