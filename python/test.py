def iterate_string():
    word = "Hello"
    for c in word:
        print (c)

    for index, char in enumerate(word):
        print("Index: {0} has value: {1}".format(index, char))

#iterate_string()

def formated_string():
    a = 10
    b = 5

    inputs = f"Comparing {a} and {b}"
    print(inputs)

#formated_string()