# created by gemini ai

import struct
import zlib

def png_to_qoi(png_path, qoi_path):
    # 1. Читаем и парсим структуру PNG
    with open(png_path, 'rb') as f:
        png_bytes = f.read()

    if png_bytes[:8] != b'\x89PNG\r\n\x1a\n':
        raise ValueError("Файл не является корректным PNG")

    idx = 8
    chunks = []
    while idx < len(png_bytes):
        length, chunk_type = struct.unpack('>I4s', png_bytes[idx:idx+8])
        idx += 8
        chunk_data = png_bytes[idx:idx+length]
        idx += length + 4  # Пропускаем CRC
        chunks.append((chunk_type, chunk_data))
        if chunk_type == b'IEND':
            break

    ihdr = [c[1] for c in chunks if c[0] == b'IHDR'][0]
    width, height, bit_depth, color_type, _, _, interlace_method = struct.unpack('>IIBBBBB', ihdr)

    if bit_depth != 8:
        raise ValueError("Поддерживается только 8-битная глубина цвета.")
    if interlace_method != 0:
        raise ValueError("Чересстрочный PNG (Interlacing) не поддерживается.")
    if color_type not in (2, 6):
        raise ValueError("Поддерживаются только Truecolor PNG (RGB или RGBA).")

    # Декомпрессия пикселей из IDAT чанков
    idat = b''.join([c[1] for c in chunks if c[0] == b'IDAT'])
    decompressed = zlib.decompress(idat)

    bpp = 3 if color_type == 2 else 4
    stride = width * bpp
    pixels = bytearray(height * stride)

    # Функция восстановления для Paeth-фильтра PNG
    def paeth_predictor(a, b, c):
        p = a + b - c
        pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
        if pa <= pb and pa <= pc: return a
        if pb <= pc: return b
        return c

    # Размаскирование (Unfiltering) сканлайнов PNG
    decomp_idx = 0
    for y in range(height):
        filter_type = decompressed[decomp_idx]
        decomp_idx += 1
        scanline = decompressed[decomp_idx:decomp_idx+stride]
        decomp_idx += stride

        row_offset = y * stride
        prev_row_offset = (y - 1) * stride

        for x in range(stride):
            raw = scanline[x]
            up = pixels[prev_row_offset + x] if y > 0 else 0
            sub = pixels[row_offset + x - bpp] if x >= bpp else 0
            corner = pixels[prev_row_offset + x - bpp] if (y > 0 and x >= bpp) else 0

            if filter_type == 0:   recon = raw
            elif filter_type == 1: recon = raw + sub
            elif filter_type == 2: recon = raw + up
            elif filter_type == 3: recon = raw + (sub + up) // 2
            elif filter_type == 4: recon = raw + paeth_predictor(sub, up, corner)
            else: raise ValueError(f"Неизвестный фильтр PNG: {filter_type}")

            pixels[row_offset + x] = recon & 0xFF

    # 2. Кодирование сырых пикселей в формат QOI
    header = struct.pack('>4sIIBB', b'qoif', width, height, bpp, 0)
    qoi_bytes = bytearray(header)

    index = [[0, 0, 0, 0] for _ in range(64)]
    prev_r, prev_g, prev_b, prev_a = 0, 0, 0, 255
    run = 0
    pixel_count = width * height

    for i in range(pixel_count):
        p_idx = i * bpp
        r = pixels[p_idx]
        g = pixels[p_idx+1]
        b = pixels[p_idx+2]
        a = pixels[p_idx+3] if bpp == 4 else 255

        if r == prev_r and g == prev_g and b == prev_b and a == prev_a:
            run += 1
            if run == 62:
                qoi_bytes.append(0xc0 | (run - 1))
                run = 0
        else:
            if run > 0:
                qoi_bytes.append(0xc0 | (run - 1))
                run = 0

            index_pos = (r * 3 + g * 5 + b * 7 + a * 11) % 64
            if index[index_pos] == [r, g, b, a]:
                qoi_bytes.append(index_pos)
            else:
                index[index_pos] = [r, g, b, a]

                if a == prev_a:
                    dr_s = (r - prev_r) & 0xFF
                    dg_s = (g - prev_g) & 0xFF
                    db_s = (b - prev_b) & 0xFF
                    if dr_s >= 128: dr_s -= 256
                    if dg_s >= 128: dg_s -= 256
                    if db_s >= 128: db_s -= 256

                    dr_dg = (dr_s - dg_s) & 0xFF
                    db_dg = (db_s - dg_s) & 0xFF
                    if dr_dg >= 128: dr_dg -= 256
                    if db_dg >= 128: db_dg -= 256

                    if -2 <= dr_s <= 1 and -2 <= dg_s <= 1 and -2 <= db_s <= 1:
                        qoi_bytes.append(0x40 | ((dr_s + 2) << 4) | ((dg_s + 2) << 2) | (db_s + 2))
                    elif -32 <= dg_s <= 31 and -8 <= dr_dg <= 7 and -8 <= db_dg <= 7:
                        qoi_bytes.append(0x80 | (dg_s + 32))
                        qoi_bytes.append(((dr_dg + 8) << 4) | (db_dg + 8))
                    else:
                        qoi_bytes.append(0xfe)
                        qoi_bytes.extend([r, g, b])
                else:
                    qoi_bytes.append(0xff)
                    qoi_bytes.extend([r, g, b, a])

            prev_r, prev_g, prev_b, prev_a = r, g, b, a

    if run > 0:
        qoi_bytes.append(0xc0 | (run - 1))

    # Конечный маркер QOI
    qoi_bytes.extend(b'\x00\x00\x00\x00\x00\x00\x00\x01')

    with open(qoi_path, 'wb') as f:
        f.write(qoi_bytes)
    print(f"Успешно конвертировано: {qoi_path}")

# Пример вызова:
# png_to_qoi("image.png", "image.qoi")