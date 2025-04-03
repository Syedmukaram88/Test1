def sorted_anagram(word):
    return "".join(sorted(word))  # Sort letters to form an anagram pattern

# Input from user
input_str = input("Enter a string: ")

# Create arrays
letters = list(input_str.replace(" ", ""))  # Array of letters (excluding spaces)
words = input_str.split()  # Array of words

# Convert each word into its sorted anagram form
anagram_words = [sorted_anagram(word) for word in words]

# Print results
print("Original words:", words)
print("Anagram transformed words:", anagram_words)
print("Letter array:", letters)
print("Word array:", words)
