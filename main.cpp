#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <algorithm>

#include "hangman.h"
#include "draw.h"

int main()
{
    srand((int)time(0));
    string vocabularyFile = "data/Ogden_Picturable_200.txt";
    vector<string> wordList;
    try {
        wordList = readWordListFromFile(vocabularyFile);
    } catch (domain_error) {
        cout << endl << "Error: in reading vocabulary file: " << vocabularyFile << endl;
        return 1;
    }
    int index = generateRandomNumber(0, wordList.size()-1);
    string word = chooseWordFromList(wordList, index);
    /*char a;
    cin >> a;
    //cout<<index << " " << word;
    //return 0;*/
    if (word.empty()) {
        cout << "Error: Coud not choose a random word." << endl;
        return 1;
    }
    string secretWord = generateHiddenCharacters(word);

    int incorrectGuess = 0;
    string correctChars = "";
    string incorrectChars = "";

    printScreen(word, secretWord, correctChars, incorrectGuess, incorrectChars);

    do {
        char ch = getInputCharacter();
        processData(ch, word, secretWord,
                    correctChars, incorrectGuess, incorrectChars);

        printScreen(word, secretWord, correctChars, incorrectGuess, incorrectChars);

    } while (secretWord != word && incorrectGuess != MAX_MISTAKES-1);

    playAnimation(word, secretWord, correctChars, incorrectGuess, incorrectChars);

    return 0;
}
