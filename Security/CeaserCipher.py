alphabet = [str(chr(i)) for i in range(97, 123)]  # small letters
#alphabet.extend([str(chr(i)) for i in range(65, 91)]) #extending my list to add capital letters
#alphabet.append(' ')
alphabet_length = len(alphabet)


def ceaser_cipher(word=None, key=None):
    # if the user didn't fill the parameters of the function the function will ask for input
    if word is None:
        word = str(input('Enter the word\n'))
    if key is None:
        key = int(input('Enter the key\n'))
    # adding ',' between every character then splitting using this ',' to create list
    word_list = ','.join(word).split(',')
    word_length = len(word_list)
    cipher = ''
    for i in range(word_length):
        '''concatenating every character to cipher by getting every character from word_list and getting the index of 
        that character from alphabet length and also adding the key and making mod operation to get the new character 
        '''
        cipher += alphabet[(alphabet.index(word_list[i]) + key) % alphabet_length]
    return cipher


def decryption(word=None):
    if word is None:
        word = str(input('Enter the word\n'))
    word_list = ','.join(word).split(',')
    word_length = len(word_list)
    decryption_possibilities = []
    for i in range(1, alphabet_length + 1):
        decrypted_word = '' # to avoid concatenating on old values
        for j in range(word_length):
            # making a reverse operation which is subtracting every possible key
            decrypted_word += alphabet[(alphabet.index(word_list[j]) - i) % alphabet_length]
        decryption_possibilities.append(decrypted_word)  # appending all posibilities
    return decryption_possibilities


cipher = ceaser_cipher('hazem', 4)

print('Encrypted: ', cipher)
print('Decrypted: ', decryption(cipher))

