#include <iostream>
#include "hangman.h"

using std::string;
using std::vector;
using std::ifstream;
using std::domain_error;
using std::cin;

// Function 1: Generate a random integer number between min and max.
int generateRandomNumber(const int min, const int max)
{
    //srand((int)time(0)); // It is a bug if putting this line here.
    return rand() % (max - min + 1) + min;
}

vector<string> readWordListFromFile(const string& filePath)
{
    // Your code here
    vector<string> v;
    ifstream f_in(filePath);
    string word;
    while(f_in >> word)
    {
        v.push_back(word);
    }
    return v;
}

// Function 2: Check if a character is in a string or not.
bool isCharInWord(const char ch, const string& word)
{
    // Your code here
    for(int i=0;i<word.size();i++)
    {
        if(word[i]==ch) return true;
    }
    return false;
}

// Function 3: Return a lowercase word in a certain position of a list.
string chooseWordFromList(const vector<string>& wordList, int index)
{
    // Your code here
    string word= wordList[index];
    for(int i=0;i<word.length();i++)
    {
        word[i]= tolower(word[i]);
    }
    return word;
}

// return user's input
char getInputCharacter() {
    // your code here
    char input;
    cin >> input;
    return input;
}

// Function 4: Update the secret word if the character ch is in the answer word.
void updateSecretWord(string& secretWord, const char ch, const string& word)
{
    // Your code here
    for(int i=0;i<word.size();i++)
    {
        if(word[i]==ch) secretWord[i]=ch;
    }
}

// Function 5 + 6 +7: processData
// If ch in word:
//     update secretWord
//     update correctChars
// Else:
//     update incorrectGuess
//     update incorrectChars

// Function 5: this function is used to update correctChars and incorrectChars
void updateEnteredChars(const char ch, string& chars){
    // Your code here
    chars = chars + " " + ch;
}

// Function 6: Update incorrectGuess
void updateIncorrectGuess(int& incorrectGuess){
    // Your code here
    incorrectGuess++;
}

// Function 7: processData
void processData(const char ch, const string& word,
                string& secretWord,
                string& correctChars,
                int& incorrectGuess, string& incorrectChars)
{
    // Your code here
    if(isCharInWord(ch,word))
    {
        updateSecretWord(secretWord,ch,word);
        updateEnteredChars(ch,correctChars);
    }else{
        updateIncorrectGuess(incorrectGuess);
        updateEnteredChars(ch,incorrectChars);
    }
}

// Function 8: Based on secretWord's length, generate hidden characters in form of "---"
string generateHiddenCharacters(string secretWord){
    // Your code here
    for(int i=0;i<secretWord.size();i++)
    {
        secretWord[i]='_';
    }
    return secretWord;
}

bool askRetry(char answer)
{
    if(answer=='y' || answer == 'Y') return true;
    else return false;
}
