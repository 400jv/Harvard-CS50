import cs50
from sys import argv

if len(argv) != 2:
    print('Usage: python roster.py [name of the house]')
    exit(1)

database = cs50.SQL("sqlite:///students.db")
numberOfRows = database.execute(
    'SELECT * FROM students WHERE house = ? ORDER BY last, first',
    argv[-1]
)

for row in numberOfRows:
    print(row['first'] + '' + (row['middle'] + ' ' if row['middle'] else '') + row['last'] + ', born', str(row['birth']))
