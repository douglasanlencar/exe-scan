# Dizionario

GPL-3.0-or-later **KDE/Qt 6** port of the abandoned Windows .NET 2.0 Italian–Chinese
image dictionary (`Dizionario.exe`, 《意汉词典》图片版, 2008).

The original author is deceased and the WinForms app was never published as free
software. This project reimplements the viewer so the Chinese–Italian community
can keep using the page scans on modern Linux desktops (target: **Fedora + KDE Plasma 6**).

## What it does

- Opens a folder of dictionary page images (`headword.jpg`, …)
- **查询** search jumps to the first page whose filename is ≥ the query (same rule as the original EXE)
- **上一页 / 下一页** flip through pages
- Fit-to-width image viewer with Ctrl+scroll zoom

Dictionary images are a separate data set from the GPL application.

## Build (Fedora / Plasma 6)

```bash
sudo dnf install cmake gcc-c++ qt6-qtbase-devel
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

On Ubuntu 24.04+ / Debian:

```bash
sudo apt install cmake g++ qt6-base-dev
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Install (optional):

```bash
sudo cmake --install build
```

## Install from RPM (Fedora)

Build the package on Fedora:

```bash
sudo dnf install rpm-build rpmdevtools rsync cmake gcc-c++ qt6-qtbase-devel
./packaging/build-rpm.sh
sudo dnf install ./dist/KDE-Dictionary-v1.0.0/packages/kde-dictionary-1.0.0.rpm
```

Then put dictionary scans here (recommended system path):

```bash
sudo mkdir -p /usr/share/dizionario/jpg
sudo cp -r /path/to/your/images/* /usr/share/dizionario/jpg/
dizionario
```

Or per-user:

```bash
mkdir -p ~/.local/share/dizionario/jpg
cp -r /path/to/your/images/* ~/.local/share/dizionario/jpg/
```

You can also choose a folder in the app: **File → Open Image Folder…**
(select the folder that contains the `.jpg` files, not a single image).

## Run

The app looks for a `jpg` folder in this order (first match wins):

1. Next to the program — `<exe>/jpg/` (same layout as the original Windows app)
2. Current working directory — `./jpg/`
3. `~/.local/share/dizionario/jpg/`
4. `/usr/local/share/dizionario/jpg/`
5. `/usr/share/dizionario/jpg/`

Portable layout example:

```text
build/
  dizionario
  jpg/
    ambrosiano.jpg
    linea.jpg
    …
```

Then start with no arguments:

```bash
./build/dizionario
```

You can still pass a folder explicitly, or use **File → Open Image Folder…** / **Find Default Image Folder**.

Small placeholder pages for smoke-testing search live in `data/sample-jpg/`:

```bash
./build/dizionario data/sample-jpg
# try searching: like   → opens linea.jpg
```

`data/original-page-keys.txt` lists the headwords embedded in the original EXE (for reference only; the live index always comes from your image filenames).

## Keyboard

| Key | Action |
|-----|--------|
| Enter | Search |
| ← / → | Previous / next page |
| Ctrl+scroll | Zoom |

## License

Program code: [GPL-3.0-or-later](LICENSE).

Page scan images from the original distribution remain under whatever terms they were shared with; this port does not claim to relicense them. Bundle or redistribute those files only if you have the right to do so.
