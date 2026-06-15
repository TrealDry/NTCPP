# created by gemini ai

import argparse
from pathlib import Path
import shutil
import sys

def move_audio_files(source_audio_dir: str, source_no_ext_dir: str):
    # Текущая директория, где лежит скрипт
    script_dir = Path(__file__).resolve().parent

    # Целевая директория: ./../assets/sounds
    target_dir = (script_dir / ".." / "assets" / "sounds").resolve()

    # Создаем целевую папку, если она еще не существует
    target_dir.mkdir(parents=True, exist_ok=True)
    print(f"Целевая папка: {target_dir}\n")

    path_audio = Path(source_audio_dir)
    path_no_ext = Path(source_no_ext_dir)

    # Проверка на существование указанных папок
    if not path_audio.exists() or not path_audio.is_dir():
        print(
            f"Ошибка: Папка с аудио не найдена по пути {path_audio}",
            file=sys.stderr,
        )
        return
    if not path_no_ext.exists() or not path_no_ext.is_dir():
        print(
            f"Ошибка: Папка с файлами без расширения не найдена по пути {path_no_ext}",
            file=sys.stderr,
        )
        return

    # 1. Обработка первой папки (.wav и .ogg)
    print("Перемещение .wav и .ogg файлов...")
    valid_extensions = {".wav", ".ogg"}
    for file_path in path_audio.iterdir():
        if file_path.is_file() and file_path.suffix.lower() in valid_extensions:
            dest_path = target_dir / file_path.name
            shutil.copy2(str(file_path), str(dest_path))
            print(f"Перемещен: {file_path.name} -> {dest_path}")

    print("-" * 30)

    # 2. Обработка второй папки (файлы без расширения)
    print("Перемещение файлов без расширения с добавлением .ogg...")
    for file_path in path_no_ext.iterdir():
        # Проверяем, что это файл и у него нет расширения
        if file_path.is_file() and file_path.suffix == "":
            # Формируем новое имя с добавлением .ogg
            new_name = f"{file_path.name}.ogg"
            dest_path = target_dir / new_name
            shutil.copy2(str(file_path), str(dest_path))
            print(f"Перемещен и переименован: {file_path.name} -> {new_name}")


if __name__ == "__main__":
    # Настройка аргументов командной строки
    parser = argparse.ArgumentParser(
        description="Скрипт для перемещения и переименования аудиофайлов."
    )
    parser.add_argument(
        "audio_dir", help="Путь к папке с файлами .wav и .ogg"
    )
    parser.add_argument(
        "no_ext_dir", help="Путь к папке с файлами без расширения"
    )

    args = parser.parse_args()

    move_audio_files(args.audio_dir, args.no_ext_dir)
    print("\nРабота скрипта завершена!")