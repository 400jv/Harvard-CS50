from cs50 import get_int

def get_height():
    height = 0
    while height <= 0 or height > 8:
        height = get_int("Height: ")

    return height


height = get_height()

for i in range(0, height):
    for l in range(1, height - i):
        print(" ", end="")

    for j in range(0, i +1):
        print("#", end="")

    print("  ", end="")

    for j in range(0, i +1):
        print("#", end="")
    print()

