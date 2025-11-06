from PIL import Image
import sys
import numpy as np

if len(sys.argv) < 2:
    print("usage: python3 image_assembler.py <image>")
    sys.exit(1)

image_path = sys.argv[1]
print("opening file")

# >>>>>> EDIT THESE TO MATCH YOUR otter.h <<<<<<
X_RES = 200
Y_RES = 200
# >>>>>> REPLACE THESE VALUES <<<<<<

img = Image.open(image_path).convert("RGB").resize((X_RES, Y_RES))
data = np.array(img)

def rgb_to_332(r, g, b):
    r = (r >> 5) & 0b111
    g = (g >> 5) & 0b111
    b = (b >> 6) & 0b11
    return (r << 5) | (g << 2) | b

pixels = []
for row in range(Y_RES):
    for col in range(X_RES):
        r, g, b = data[row, col]
        pixels.append(rgb_to_332(r, g, b))

# Write human-readable hex values
with open("data.txt", "w") as f:
    for i, p in enumerate(pixels):
        f.write(f"0x{p:02X}, ")
        if (i + 1) % X_RES == 0:
            f.write("\n")

# ✅ Write raw binary for direct inclusion in firmware
with open("image.bin", "wb") as f:
    f.write(bytearray(pixels))

print("done!")
print("data.txt → readable array")
print("image.bin → raw framebuffer data")
