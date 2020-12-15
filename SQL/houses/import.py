import cs50
import csv
from sys import argv

if len(argv) != 2:
    print('Usage: python import.py csvname')
    exit(1)

database = cs50.SQL("sqlite:///students.db")

with open(argv[-1], "r") as characters:
    reader = csv.DictReader(characters)

    for row in reader:
        name = row['name'].split()
        first = name[0]
        middle = name[1] if len(name) == 3 else None
        last = name[-1]

        house = row['house']
        birth = row['birth']

        database.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)

print('Done')
