# created by claude ai

import json
import re
import shutil
import sys
from pathlib import Path

# ── Импорт конвертера ────────────────────────────────────────────────────────
# png_to_qoi.py должен лежать рядом со скриптом или быть в PYTHONPATH
try:
    from png_to_qoi import png_to_qoi
except ImportError:
    print("[ERROR] Не удалось импортировать png_to_qoi. "
          "Убедитесь, что png_to_qoi.py лежит рядом со скриптом.")
    sys.exit(1)


# ── Пути ────────────────────────────────────────────────────────────────────
SCRIPT_DIR   = Path(__file__).resolve().parent          # {project}/scripts/
PROJECT_DIR  = SCRIPT_DIR.parent                        # {project}/
SOURCE_DIR   = PROJECT_DIR / "assets" / "textures_src"  # ← исходники здесь
OUTPUT_DIR   = PROJECT_DIR / "assets" / "textures"      # ← результат сюда

# Если хочешь передать SOURCE_DIR аргументом командной строки:
#   python conv_textures.py /path/to/source
if len(sys.argv) > 1:
    SOURCE_DIR = Path(sys.argv[1]).resolve()


def slim_json(data: dict) -> dict:
    """Оставляет только {frames: {sprite: {x, y, w, h}}}."""
    slim = {}
    for sprite_name, sprite_data in data.get("frames", {}).items():
        frame = sprite_data.get("frame", {})
        slim[sprite_name] = {
            "x": frame.get("x", 0),
            "y": frame.get("y", 0),
            "w": frame.get("w", 0),
            "h": frame.get("h", 0),
        }
    return {"frames": slim}


def find_texture_pairs(source_dir: Path) -> list[tuple[Path, Path]]:
    """
    Ищет пары (texture-N.png, texture-N.json), сортирует по N.
    Возвращает [(png_path, json_path), ...].
    """
    pattern = re.compile(r"^texture-(\d+)\.png$", re.IGNORECASE)
    pairs: list[tuple[int, Path, Path]] = []

    for png_file in source_dir.iterdir():
        m = pattern.match(png_file.name)
        if not m:
            continue
        index   = int(m.group(1))
        json_file = source_dir / f"texture-{m.group(1)}.json"
        if not json_file.exists():
            print(f"[WARN] Нет JSON для {png_file.name}, пропуск.")
            continue
        pairs.append((index, png_file, json_file))

    pairs.sort(key=lambda t: t[0])
    return [(p, j) for _, p, j in pairs]


def main() -> None:
    if not SOURCE_DIR.exists():
        print(f"[ERROR] Папка с исходниками не найдена: {SOURCE_DIR}")
        sys.exit(1)

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    print(f"Исходники : {SOURCE_DIR}")
    print(f"Результат : {OUTPUT_DIR}\n")

    pairs = find_texture_pairs(SOURCE_DIR)
    if not pairs:
        print("[ERROR] Не найдено ни одной пары texture-N.png + texture-N.json")
        sys.exit(1)

    for seq, (png_path, json_path) in enumerate(pairs, start=0):
        tag = f"{seq:03d}"  # "001", "002", ...

        # ── 1. PNG → QOI ────────────────────────────────────────────────────
        qoi_out = OUTPUT_DIR / f"{tag}.qoi"
        try:
            png_to_qoi(str(png_path), str(qoi_out))
            print(f"[{tag}] PNG  → QOI : {png_path.name} → {qoi_out.name}")
        except Exception as exc:
            print(f"[{tag}] [ERROR] Конвертация PNG провалилась: {exc}")
            continue

        # ── 2. JSON: обрезаем и сохраняем ───────────────────────────────────
        json_out = OUTPUT_DIR / f"{tag}.json"
        try:
            with open(json_path, encoding="utf-8") as fh:
                raw = json.load(fh)
            slim = slim_json(raw)
            with open(json_out, "w", encoding="utf-8") as fh:
                json.dump(slim, fh, ensure_ascii=False, indent=2)
            print(f"[{tag}] JSON → slim: {json_path.name} → {json_out.name}")
        except Exception as exc:
            print(f"[{tag}] [ERROR] Обработка JSON провалилась: {exc}")
            continue

    print(f"\nГотово. Обработано пар: {len(pairs)}")


if __name__ == "__main__":
    main()