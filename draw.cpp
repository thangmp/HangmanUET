#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "hangman.h"

using std::string;
using std::endl;
using std::cout;

const int MAX_MISTAKES = 8;

string getDrawing(const int i)
{
    static int LEN = 8;
    static string FIGURES[] = {
                "   -------------    \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |                \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |                \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |           |    \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|    \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |                \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |          /     \n"
                "   |     \n"
                " -----   \n",
                "   -------------    \n"
                "   |           |    \n"
                "   |           O    \n"
                "   |          /|\\  \n"
                "   |          / \\  \n"
                "   |     \n"
                " -----   \n",
    };
    return FIGURES[i % LEN];
}

string getNextHangman()
{
    static int LEN = 4;
    static string FIGURES[] = {
          "   ------------+    \n"
          "   |          /     \n"
          "   |         O      \n"
          "   |        /|\\    \n"
          "   |        / \\    \n"
          "   |        \n"
          " -----      \n" ,
          "   ------------+     \n"
          "   |           |     \n"
          "   |           O     \n"
          "   |          /|\\   \n"
          "   |          / \\   \n"
          "   |        \n"
          " -----      \n",
          "   ------------+      \n"
          "   |            \\    \n"
          "   |            O     \n"
          "   |           /|\\   \n"
          "   |           / \\   \n"
          "   |      \n"
          " -----    \n",
          "   ------------+     \n"
          "   |           |     \n"
          "   |           O     \n"
          "   |          /|\\   \n"
          "   |          / \\   \n"
          "   |        \n"
          " -----      \n",
          };
    static int i = 0;
    i = (i + 1) % LEN;

    return FIGURES[i];
}

string getNextStandingman()
{
    static int LEN = 8;
    static string FIGURES[] = {
          "     O     \n"
          "    /|\\   \n"
          "    | |    \n",
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n",
          "   __O__   \n"
          "     |     \n"
          "    / \\   \n",
          "    \\O/   \n"
          "     |     \n"
          "    / \\   \n",
          "   __O__   \n"
          "     |     \n"
          "    / \\   \n",
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "    O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "      O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          "     O     \n"
          "    /|\\   \n"
          "    / \\   \n" ,
          };
    static int i = 0;
    i = (i + 1) % LEN;

    return FIGURES[i];
}

void clearScreen()
{
#ifdef __WIN32__
    system("cls");
#else
    for (int i = 0; i < 30; i++) cout << endl;
#endif
}

void printStats(const string& word, const string& secretWord,
                 const string& correctChars,
                 const int incorrectGuess, const string& incorrectChars)
{
        cout << "Current word: " << secretWord;
        cout << endl << "Correct guesses: " << correctChars;
        cout << "    " << "Incorrect guesses: " << incorrectChars;

        if (secretWord == word) {
            cout << endl << "Well done :D   The word is: " << word << endl;
        } else if (incorrectGuess == MAX_MISTAKES-1) {
            cout << endl << "You lose :(   The word is: " << word << endl;
        } else {
            cout << endl << "Choose a character: ";
        }
}

void printPlayingScreen(const string& word, const string& secretWord,
                 const string& correctChars,
                 const int incorrectGuess, const string& incorrectChars)
{
    clearScreen();

    cout << getDrawing(incorrectGuess);
    printStats(word, secretWord, correctChars, incorrectGuess, incorrectChars);

}



void playAnimation(const string& word, const string& secretWord,
                 const string& correctChars,
                 const int incorrectGuess, const string& incorrectChars)
{
    clearScreen();   
    for (int i = 0; i < 21; ++i) {
        if (secretWord == word) {
            cout << getNextStandingman();
        } else if (incorrectGuess == MAX_MISTAKES-1) {
            cout << getNextHangman();
        }
        printStats(word, secretWord, correctChars, incorrectGuess, incorrectChars);

        std::this_thread::sleep_for (std::chrono::milliseconds(1000/2));
        clearScreen();
    }
}

void printMenuScreen()
{
    cout << "PLAYER MODE:TYPE P" << endl;
    cout << "BOT MODE:TYPE B" << endl;
    cout << "EXIT:TYPE E" << endl;
}

void printModeScreen()
{
    for (int i = 0; i < 30; ++i) cout << endl;
    cout << "Please choose your theme:" << endl;
    cout << "Animal:1" << endl;
    cout << "Household:2" << endl;
    cout << "Job:3" << endl;
    cout << "Vehicle:4" << endl;
    cout << "Random:5" << endl;
}
void printRetryScreen()
{
    for (int i = 0; i < 30; ++i) cout << endl;
    cout << "Do you want to play again(y/n)" << endl;
}

void printDiffScreen()
{
    for (int i = 0; i < 30; ++i) cout << endl;
    cout << "Easymode:1" << endl;
    cout << "Hardmode:2" << endl;
}

