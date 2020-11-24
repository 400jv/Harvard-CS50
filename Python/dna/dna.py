from sys import argv
from cs50 import get_string
import csv

if len(argv) != 3:
    print("Error!")
    exit(1)

database = open(argv[1], 'r')
strandDna = open(argv[2], 'r').read()
strands = []
users = {}
finalStrands = []

for index, r in enumerate(database):
    if index == 0:
        strands = [strand for strand in r.strip().split(',')][1:]
    else:
        curr_row = r.strip().split(',')
        users[curr_row[0]] = [int(x) for x in curr_row[1:]]

for strand in strands:
    i = strandMax = curMax = 0

    while i < len(strandDna):
        cur_window = strandDna[i:i+len(strand)]
        if cur_window == strand:
            curMax += 1
            strandMax = max(strandMax, curMax)
            i += len(strand)
        else:
            curMax = 0
            i += 1

    finalStrands.append(strandMax)

for name, data in users.items():
    if data == finalStrands:
        print(name)
        exit(0)

print("No match")

database.close()
