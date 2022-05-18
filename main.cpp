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
    
    char Playerchoice;
    int ThemeChoice;
    printMenuScreen();
    Playerchoice = getInputCharacter();
    bool checkRetry;
    if(Playerchoice == 'p' || Playerchoice == 'P')
    {
        do{
        
        srand((int)time(0));
        string vocabularyFile;
        printModeScreen();
        Playerchoice = getInputCharacter();
        switch(Playerchoice){
        case '1':{
            printDiffScreen();
            Playerchoice = getInputCharacter();
            switch(Playerchoice){
                case '1':{
                vocabularyFile = "data/Animal - Easy.txt";
                break;
                }
                case '2':{
                vocabularyFile = "data/Animal - Hard.txt";
                break;
                }
            }
            break;
            }
        case '2':{
            printDiffScreen();
            Playerchoice = getInputCharacter();
            switch(Playerchoice){
                case '1':{
                vocabularyFile = "data/Household - Easy.txt";
                break;
                }
                case '2':{
                vocabularyFile = "data/Household - Hard.txt";
                break;
                }
            }
            break;
            }
        case '3':{
            printDiffScreen();
            Playerchoice = getInputCharacter();
            switch(Playerchoice){
                case '1':{
                vocabularyFile = "data/Job - Easy.txt";
                break;
                }
                case '2':{
                vocabularyFile = "data/Job - Hard.txt";
                break;
                }
            }
            break;
            }
        case '4':{
            printDiffScreen();
            Playerchoice = getInputCharacter();
            switch(Playerchoice){
                case '1':{
                vocabularyFile = "data/Vehicle - Easy.txt";
                break;
                }
                case '2':{
                vocabularyFile = "data/Vehicle - Hard.txt";
                break;
                }
            }
            break;
            }
        case '5':{
                printDiffScreen();
                Playerchoice = getInputCharacter();
                switch(Playerchoice){
                    case '1':{
                    vocabularyFile = "data/Random - Easy.txt";
                    break;
                    }
                    case '2':{
                    vocabularyFile = "data/Random - Hard.txt";
                    break;
                    }
                }
                break;
            }
        break;
        }
        vector<string> wordList;

        try {
            wordList = readWordListFromFile(vocabularyFile);
        } catch (domain_error) {
            cout << endl << "Error: in reading vocabulary file: " << vocabularyFile << endl;
            return 1;
        }

        int index = generateRandomNumber(0, wordList.size()-1);

        string word = chooseWordFromList(wordList, index);

        if (word.empty()) {
            cout << "Error: Coud not choose a random word." << endl;
            return 1;
        }

        string secretWord = generateHiddenCharacters(word);
        int incorrectGuess = 0;
        string correctChars = "";
        string incorrectChars = "";

            do {
                printPlayingScreen(word, secretWord, correctChars, incorrectGuess, incorrectChars);
                char ch = getInputCharacter();
                processData(ch, word, secretWord,
                            correctChars, incorrectGuess, incorrectChars);

            } while (secretWord != word && incorrectGuess != MAX_MISTAKES-1);

            playAnimation(word, secretWord, correctChars, incorrectGuess, incorrectChars);
            printRetryScreen();
            char retry = getInputCharacter();
            checkRetry=askRetry(retry);
        }while(checkRetry);
        
    }
    return 0;
}
//g++ hangman.cpp draw.cpp main.cpp -o hangman