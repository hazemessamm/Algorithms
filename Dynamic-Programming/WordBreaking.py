def WordBreaking(listOfWords, String):
    if String == '""' or String == "''": #if the string is empty then it will print yes
        print("\n"+"Yes")
        return
    dictOfWords = dict() #dictionary that will store all the words from the list
    for i in range(len(listOfWords)): 
        dictOfWords[listOfWords[i]] = i #Storing words in the Dict
    partsOfString = str() #Variable to collect characters
    collectingString = str() #Variable to collect the strings
    for i in range(len(String)-1,-1,-1): #the loop started backwards to avoid one character problem
                                        #like ice will take the i in ice and leave ice with only 'ce' which is wrong
        partsOfString = String[i] + partsOfString #collecting the characters
        if partsOfString in dictOfWords: #check if the collected characters is stored in the Dict or Not
            collectingString = collectingString + partsOfString #if it's stored then store them in the collectingString variable
            partsOfString = str() #Re-initialize partsOfString variable to store new characters
    if len(collectingString) == len(String): #check if the length of the collectedString equal to the actual string
        print("\n"+"Yes")
    else:
        print("\n"+"No")



String = str(input())
listOfWords = ['i', 'like', 'sam', 'sung', 'samsung', 'mobile', 'ice', 
  'cream', 'icecream', 'and','man','go', 'mango']

WordBreaking(listOfWords, String)
