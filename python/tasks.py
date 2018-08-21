import re


def remove_chars(sentence):
    # Return sentence without first and last character
    return sentence[1:-1]


# assert remove_chars("country") == "ountr", "Failed test case"
# assert remove_chars("Tieto") == "iet", "Failed test case"


def return_half(sentence):
    # Return half of the string
    half = len(sentence) // 2
    return sentence[:half]


# assert return_half("Tieto") == "Ti", "Wrong."
# assert return_half("Work") == "Wo", "Wrong."
# assert return_half("Academy") == "Aca", "Wrong."


def append_to_string(sentence):
    # If length of string is > 5 then append "World"
    # Otherwise, push "Welcome" to the front
    if len(sentence) >= 5:
        sentence = sentence + " World"
    else:
        sentence = "Welcome, " + sentence
    return sentence


# assert append_to_string("Hello") == "Hello World", "Wrong"
# assert append_to_string("Hi") == "Welcome, Hi", "Wrong"

def alphabetical_order(sentence_1, sentence_2):
    if (sentence_1 > sentence_2):
        return sentence_2
    else:
        return sentence_1


# print(alphabetical_order("AA", "aa"))

def filter_list(my_list):
    # Create a new list based on the old list with ints only
    my_list = [element for element in my_list if type(element) is int]
    return my_list


# assert filter_list([1, 5, 'A', 30, 'Hello', 50, 2.75]) == [1, 5, 30, 50], "Bad filtering"

def who_likes_it(list_of_likes):
    if not list_of_likes:
        return "no one likes this"
    else:
        names = list_of_likes[0].split(", ")
        names_len = len(names)

        if names_len == 0:
            return "no one likes this"
        elif names_len == 1:
            return f'{names[0]} likes this'
        elif names_len == 2:
            return f'{names[0]} and {names[1]} like this'
        elif names_len == 3:
            return f'{names[0]}, {names[1]} and {names[2]} like this'
        else:
            return f'{names[0]}, {names[1]} and {str(names_len - 2)} others like this'


# assert who_likes_it([]) == "no one likes this", "Wrong like count!"
# assert who_likes_it(["Ryszard"]) == "Ryszard likes this", "Wrong like count!"
# assert who_likes_it(["Marcin, Michal"]) == "Marcin and Michal like this", "Wrong like count!"
# assert who_likes_it(["Edyta, Igor, Kamil"]) == "Edyta, Igor and Kamil like this", "Wrong like count!"
# assert who_likes_it(["Michal, Maciej, Bartosz, Przemek"]) == "Michal, Maciej and 2 others like this", "Wrong like count!"


def count_duplicates(sentence, how_many_times):
    '''
     Function checks how many times a letter is present in a string.
     Return only those letters.
     See test cases for examples
     '''

    # Get duplicated letters, number of occurance is given by argument
    duplicates = [letter for letter in sentence if sentence.count(letter) == how_many_times]
    single_duplicates = []
    # Get unique letters while keeping the order of letters
    for letter in duplicates:
        if letter not in single_duplicates:
            single_duplicates.append(letter)

    # Return string concatenated from duplicated letters
    return ''.join(single_duplicates)

# assert count_duplicates("aabcdddee", 2) == "ae", "Failed to count!" # only 'a' end 'e' were present 2 times.
# assert count_duplicates("indivisibility", 6) == "i", "Failed to count!"
# assert count_duplicates("Karima", 1) == "Krim", "Failed to count!"

def reorder_substrings(sentence):
    '''
        Your task is to sort a given string. Each word in the String will contain a single number.
        This number is the position the word should have in the result.
        Note: Numbers can be from 1 to 9. So 1 will be the first word (not 0).
        '''
    # Split input string into words separated by spaces
    sentence = sentence.split(" ")
    # Create empty list for word from input string
    sentence_sorted = [""] * len(sentence)

    # For each word in the sentence
    for word in sentence:
        # Check every letter of the word
        for letter in word:
            # If letter is digit save it as index of a list
            if letter.isdigit():
                index = int (letter) - 1 # First word should be on index 0
        # Insert word at proper index
        sentence_sorted[index] = word

    # Return sorted list as string
    return ' '.join(sentence_sorted)

#assert reorder_substrings("is2 Thi1s T4est 3a") == "Thi1s is2 3a T4est", "Failed!"

def create_dictionary():
    names = {"Michal": 0, "Marcin": 1, "Ryszard": 2}
    print(names)
    names.pop("Ryszard", None);
    print(names)
    if "Edyta" in names:
        names["Edyta"] += 3
    else:
        names["Edyta"] = 3
    print(names)

# create_dictionary()

# Write a Python program to count the occurrences of each word in a given sentence.
def word_counter(sentence):
    words = {}
    sentence = sentence.split(" ")
    for word in sentence:
        if word not in words:
            words[word] = sentence.count(word)

    print(words)
    return words


answer = {"Ala": 2, "ma": 2, "kota.": 1, "psa.": 1}
# assert word_counter("Ala ma kota. Ala ma psa.") == answer

# Write a Python program to count the occurrences of each word in a given sentence.
def word_counter_2(sentence):
    words = {}
    sentence = list(sentence)
    string = ""

    for letter in sentence:
        if letter.isalnum() or letter.isspace():
            string += letter
        else:
            string += " " + letter

    string = string.split(" ")
    for word in string:
        if word not in words:
            words[word] = string.count(word)

    return words

# answer = {"Ala": 2, "ma": 2, "kota": 1, "psa": 1, ".": 2}
# assert word_counter_2("Ala ma kota. Ala ma psa.") == answer


def validatePIN(PIN):
    # ATM machines allow 4 digit PIN codes and PIN must contain only digits.
    # Validate if input is correct
    if len(PIN) == 4 and re.match(r"\d{4}", PIN):
        return True
    return False


# assert validatePIN("1234") == True, "Wrong validation!"
# assert validatePIN("12345") == False, "Wrong validation!"
# assert validatePIN("a234") == False, "Wrong validation!"


def validate_input(word):
    # Write a simple regex to validate a username. Allowed characters are:
    # lowercase letters, numbers, underscore
    # Length should be between 5 and 20 characters (both included).
    pattern = re.compile(r'[0-9_a-z]{5,20}')

    if re.match(pattern, word) is None:
        return False
    else:
        return True

# assert validate_input("Summer Academmy") == False, "Bad validation!"
# assert validate_input("Summer_Academmy") == False, "Bad validation!"
# assert validate_input("summer_academmy") == True, "Bad validation!"

