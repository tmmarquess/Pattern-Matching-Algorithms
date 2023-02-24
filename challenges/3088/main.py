import re

regex = re.compile("\s+[,|\.]")

while True:
    try:
        string = input()
    except EOFError:
        exit(0)
    i = 0
    for match in regex.finditer(string):
        index = match.span()[0]
        string = string[: index - i] + string[index + 1 - i :]
        i += 1
    print(string)
