from cs50 import get_float

dollars = cents = 0
while (dollars <= 0):
    dollars = get_float("Change owed: ")

dollars = round(dollars * 100)

while (dollars != 0):
    if (dollars >= 25):
        dollars = dollars - 25
        cents += 1

    elif (dollars >= 10):
        dollars = dollars - 10
        cents += 1

    elif (dollars >= 5):
        dollars = dollars - 5
        cents += 1

    elif (dollars >= 1):
        dollars = dollars - 1
        cents += 1

print(cents)
