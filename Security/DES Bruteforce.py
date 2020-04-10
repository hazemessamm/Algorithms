from Crypto.Cipher import DES

key = b'66666666'

word = b'hazem   ' #the word should be 8 bytes so length("hazem") = 5 so there are 3 extra spaces to make the word = 8 bytes

encoding = 'UTF-8'

cipher = DES.new(key, DES.MODE_ECB)

encrypted_word = cipher.encrypt(word)

decrypted_word = cipher.decrypt(encrypted_word)

guess_key = ''


for i in range(10):
    for j in range(10):
        for k in range(10):
            for l in range(10):
                for m in range(10):
                    for n in range(10):
                        for o in range(10):
                            for p in range(10):
                                guess_key = bytes(str(i)+str(j)+str(k)+str(l)+str(m)+str(n)+str(o)+str(p), encoding)
                                decrypted_guess = DES.new(guess_key, DES.MODE_ECB).decrypt(encrypted_word)
                                if decrypted_guess == decrypted_word:
                                    print(decrypted_guess.decode(encoding), guess_key)
                                    break
