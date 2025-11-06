#!/usr/bin/env python3

X_RES = 200
Y_RES = 200

# This must match your image in init.s
BIN_FILE = "../image_assmblr/image.bin"

with open(BIN_FILE, "rb") as f:
    data = f.read()

assert len(data) == X_RES * Y_RES, f"Expected {X_RES*Y_RES} bytes, got {len(data)}"

# Convert RGB(3-3-2) to 24-bit RGB
def expand(pixel):
    r = (pixel >> 5) & 0b111
    g = (pixel >> 2) & 0b111
    b = pixel & 0b11
    # expand to 8-bit ranges:
    r = int(r * (255/7))
    g = int(g * (255/7))
    b = int(b * (255/3))
    return r, g, b

with open("image.ppm", "w") as out:
    out.write("P3\n")
    out.write(f"{X_RES} {Y_RES}\n")
    out.write("255\n")

    for i in range(len(data)):
        r, g, b = expand(data[i])
        out.write(f"{r} {g} {b}\n")

print("Saved output as image.ppm (portable pixmap).")
print(" Convert to PNG using:   convert image.ppm image.png")
