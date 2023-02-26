word_count = int(input())

word_list = []
for i in range(word_count):
    word_list.append(input())

biggest_pattern_found = ""
biggest_pattern_size = 0

beggining = 0
end = 1

while end <= len(word_list[0]):
    pattern_not_found = False
    sliced_string = word_list[0][beggining:end]

    for i in range(1, word_count):
        if sliced_string not in word_list[i]:
            pattern_not_found = True
            break

    if pattern_not_found:
        beggining += 1
        end = beggining + 1
    elif biggest_pattern_size < len(sliced_string):
        biggest_pattern_found = sliced_string
        biggest_pattern_size = len(sliced_string)
    end += 1

print(biggest_pattern_found)
