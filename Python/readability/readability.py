from cs50 import get_string

text = get_string("Text: ")

letters = word = sentences = 0
for i in text:
    if i.isalpha():
        letters += 1

    if i == ' ':
        word += 1

    if i in ['.',  '?', '!']:
        sentences += 1

word += 1

average_L = (letters * 100.0) / word
average_S = (sentences * 100.0) / word

grade = int(((0.0588 * average_L) - (0.296 * average_S) - 15.8) + 0.5)

if grade >= 16:
    print("Grade 16+")

elif grade < 1:
    print("Before Grade 1")

else:
    print(f"Grade {grade}")

