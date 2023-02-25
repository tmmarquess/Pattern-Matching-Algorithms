cases = int(input())

for i in range(cases):
    uses = int(input())
    itens = []
    for j in range(uses):
        string = input().split()
        if string[1] == "chirrin":
            itens.append(string[0])
        elif string[1] == "chirrion":
            try:
                itens.remove(string[0])
            except ValueError:
                pass
    itens.sort()
    print("TOTAL")
    for item in itens:
        print(item)
