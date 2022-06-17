/* main.cpp
    Program 3 CS141:
    Wordle Reload is a game that allows you to guess either a 3 letter word or 5 letter word.
    You have a set amount of time to guess a word.  At the conlusion of game play
    you will be provided stats on your overall game play.

    Author: George Fashho
    Date: 2/27/2022
    Class: CS 141, Spring 2022, UIC
    System: Windows 10 - CLion

*/

#include <iostream>   // For Input and Output
#include <utility>
#include <vector>     // For vectors
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement used to validate file open
#include <cctype>     // Allows using the tolower() function
#include <ctime>      // Timer functions
#include <string.h>   // Manipulate strings
#include <cmath>      // round() function

using namespace std;

//binary search function to check if the word inputted by the user is in the dictionary
int binarySearchString(string searchWord, vector<string> dictionary) {
    int mid;
    int low;
    int high;

    low = 0;
    high = dictionary.size() - 1;

    while (high >= low) {
        mid = (high + low) / 2;
        int searchResult = searchWord.compare(dictionary[mid]);
        if (searchResult == 0) {
            return mid;
        } else if (searchResult < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1; // not found
}


//boolean using binary search function to return if the word is in the dictionary or not
bool checkExists(string userInput, vector<string> dictionary) {

    int result = binarySearchString(userInput, dictionary);
    if (result == -1) {
        return false;
    } else {
        return true;
    }
}


//function used to seperate 3 letter words from 5 letter words and then read them into the correct dictionary
void readWordsIntoDictionary(vector<string> &dictionaryThree, vector<string> &dictionaryFive) {
    // Read in dictionary into dictionary vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open("wordlewords.txt");       // Open dictionary file
    assert(inStream.fail() == false);     // Ensure file open worked

    dictionaryThree.clear();
    dictionaryFive.clear();

    // Keep repeating while input from the file yields a word
    string newWord;
    vector<char> lengthTest(newWord.length());

    // Store a single input word
    while (inStream >> newWord) {           // While there is another word to be read
        //checks if the length of a word is 3 letters long or 5 letters long
        if (newWord.length() == 3) {
            dictionaryThree.push_back(newWord);

        } else if (newWord.length() == 5) {
            dictionaryFive.push_back(newWord);
        }
    }

    // Close the dictionary file
    inStream.close();
}


//function used to display the games instructions
void gameDisplayInstructions() {
    cout << "Program 3: Wordle Reload \n"
         << "CS 141, Spring 2022, UIC \n"
         << " \n"
         << "The objective of this game is to guess the randomly selected \n"
         << "word within a given number of attempts. You can select either \n"
         << "a three or five word board. \n"
         << "At the conlusion of the game, stats will be displayed.  \n"
         << "Indicators will be given if characters of the user entered \n"
         << "word are reflected in the guessed word. \n"
         << "  - If the character is in the correct position, the character \n"
         << "    will display as an uppercase value.\n"
         << "  - If the character is within the random word, the character \n"
         << "    will display as a lowercase value.\n"
         << "  - If you enter a character that is not in the word, an asterisk '*' \n"
         << "    will display."
         << " \n"
         << endl;
}//end displayWelcomeMessage()


//function to display rules when player chooses menu option 1
void gameRulesThree(){
    cout << "To get started, enter your first 3 letter word. \n " <<
         "You have 4 attempts to guess the random word. \n " <<
         "The timer will start after your first word entry.\n" <<
         "Try to guess the word within 20 seconds.\n";

}//end of game rules 3


//function to display rules when player chooses menu option 2
void gameRulesFive(){

    cout << "To get started, enter your first 5 letter word. \n " <<
         "You have 6 attempts to guess the random word. \n " <<
         "The timer will start after your first word entry.\n" <<
         "Try to guess the word within 40 seconds.\n";

}//end of game rules 5


//function used to display the 3 character word board
char displayBoardThree(char board[4][3]) {

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            if ((board[row][col]) != ' ') {
                cout << "[ " << board[row][col] << " ]";
            }
        }
        //checking if the board space is empty and if it is then a new line is added
        if ((board[row][0] && board[row][1] && board[row][2] != ' ')) {
            cout << "\n";
        }
    }
}


//function used to display the 5 character word board
char displayBoardFive(char board[6][5]) {

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 5; col++) {
            if ((board[row][col]) != ' ') {
                cout << "[ " << board[row][col] << " ]";
            }
        }
        //checking if the board space is empty and if it is then a new line is added
        if ((board[row][0] && board[row][1] && board[row][2] != ' ')) {
            cout << "\n";
        }
    }
}


int main() {

    //setting srand to 1
    srand(1);

    //declaring string vectors dictionaries
    vector<string> dictionaryThree;
    vector<string> dictionaryFive;

    //writing the words from the txt file into the dictionaries
    readWordsIntoDictionary(dictionaryThree, dictionaryFive);

    //finding the length of the dictionaries
    int dictSizeThree = dictionaryThree.size();
    int dictSizeFive = dictionaryFive.size();

    //boolean function to keep loop running
    bool gameplay = true;

    //declaring multiple string and int
    string wordThree,wordFive,DictWordThree,DictWordFive;
    gameDisplayInstructions();
    int Wins,CurrentStreak,runs,longestStreak = 0;
    int menuOption,TotalTime,AvgTime;


    //while loop used to run the game and keep looping until menu option = 3
    while (gameplay == true) {

        int attempts = 0;
        int secondsElapsed = 0;

        //printing the menu options
        cout << "Select a menu option: \n"
             << "1. To play Wordle Reload 3 letter play \n"
             << "2. To play Wordle Reload 5 letter play \n"
             << "3. Exit the program \n"
             << "Your choice --> \n";
        cin >> (menuOption);

        //checking if an input is an integer or not
        if (!cin) {
            cin.clear();
            cin.ignore();
            continue;
        }
        //starting the timer
        time_t startTime = time(nullptr);
        if (menuOption == 1) {

            bool checkWin = false;
            int wordThreeLocation;
            //getting a random number
            wordThreeLocation = rand() % dictSizeThree;
            //getting a random word from the dictionary
            DictWordThree = dictionaryThree[wordThreeLocation];

            //outputting the rules for the game
            gameRulesThree();

            char board[4][3] = {
                    {' ', ' ', ' '},
                    {' ', ' ', ' '},
                    {' ', ' ', ' '},
                    {' ', ' ', ' '},

            };

            //for loop that runs 4 times to take 4 user inputs
            for (int row = 0; row < 5; row++) {
                attempts = attempts + 1;
                //ending for loop if user uses all their attempts
                if (attempts > 4) {
                    cout << "Maximum amount of attempts have been reached. Try again.\n";
                    CurrentStreak = 0;
                    runs++;
                    continue;
                }

                //getting the users input
                cout << "Please enter word --> \n";
                cin >> wordThree;

                //checking if user input is indeed 3 characters long
                if (wordThree.length() > 3 || wordThree.length() < 3) {

                    int temp = row;
                    cout << "Invalid word entry - please enter a word that is 3 characters long.\n";
                    row = temp - 1;
                    if (attempts != 0) {
                        int tempAttempts = attempts;
                        attempts = tempAttempts - 1;
                    }

                    continue;
                }

                //converting the inputted word into lowercase letters to be able to compare it the
                //dictionary words
                for (int x = 0; x < 3; x++) {
                    wordThree[x] = tolower(wordThree[x]);
                }

                /*if the boolean comes back as false when comparing the word to a dictionary word then the
                following message is outputted and the for loop continues*/
                if (!checkExists(wordThree, dictionaryThree)) {
                    cout << "Not a playable word, please select another word. " << endl;
                    int tempRow = row;
                    row = tempRow - 1;
                    if (attempts != 0) {
                        int tempAttempts = attempts;
                        attempts = tempAttempts - 1;
                    }
                    continue;
                }

                //checking the amount of time passed
                secondsElapsed = difftime(time(nullptr), startTime);

                //if the amount of time passed is over 20 seconds the game ends and the user needs to pick another
                //menu option
                if (secondsElapsed > 20) {
                    cout << "Your time has expired.  Try again.\n"
                            "  - You are " << (secondsElapsed - 20) << " seconds over the 20 second time limit.";
                    continue;
                }

                //checking if the inputted word is equal to the random dictionary word
                if (wordThree == DictWordThree) {
                    checkWin = true;

                }

                /*checking each letter in the inputted word,
                 *if the letter is in the same position as the random word it is displayed on the
                 * board as a capital letter
                 *if a letter is in the dictionary word but not the same position then it is displayed
                 * on the board as lowercase*/

                for (int col = 0; col < 3; col++) {
                    if (wordThree.at(col) == DictWordThree.at(col)) {
                        board[row][col] = toupper(wordThree[col]);

                    } else if (wordThree[col] == DictWordThree[0] || wordThree[col] == DictWordThree[1] ||
                               wordThree[col] == DictWordThree[2]) {
                        board[row][col] = wordThree[col];
                    } else {
                        board[row][col] = '*';
                    }
                }

                //displaying the board
                displayBoardThree(board);

                //checking for a win
                if (checkWin == true) {

                    secondsElapsed = difftime(time(nullptr), startTime);

                    cout << "Nice Work!  You guessed the correct word\n"
                         << "- You completed the board in:" << secondsElapsed << " seconds. \n" <<
                         "  - It took you " << attempts << "/4 attempts.";

                    Wins++;
                    TotalTime = TotalTime + secondsElapsed;
                    CurrentStreak++;
                    runs++;

                    if (longestStreak < CurrentStreak) {
                        longestStreak = CurrentStreak;
                    }
                    break;
                }
            }
        }

        else if (menuOption == 2) {

            bool checkWin = false;
            int wordFiveLocation;

            //getting a random number
            wordFiveLocation = rand() % dictSizeFive;
            //getting a random word from the dictionary
            DictWordFive = dictionaryFive[wordFiveLocation];

            //outputting the rules for the game
            gameRulesFive();

            char boardFive[6][5] = {
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},

            };

            //for loop that runs 6 times to take 6 user inputs
            for (int row = 0; row < 7; row++) {
                attempts = attempts + 1;
                //ending for loop if user uses all their attempts
                if (attempts > 6) {
                    cout << "Maximum amount of attempts have been reached. Try again.\n";
                    CurrentStreak = 0;
                    runs++;
                    continue;
                }

                //getting the users input
                cout << "Please enter word --> \n";
                cin >> wordFive;

                /*converting the inputted word into lowercase letters to be able to compare it the
                dictionary words*/
                for (int x = 0; x < 5; x++) {
                    wordFive[x] = tolower(wordFive[x]);
                }

                //checking if user input is indeed 5 characters long
                if (wordFive.length() > 5 || wordFive.length() < 5) {
                    int temp = row;
                    cout << "Invalid word entry - please enter a word that is 5 characters long.\n";
                    row = temp - 1;
                    if (attempts != 0) {
                        int tempAttempts = attempts;
                        attempts = tempAttempts - 1;
                    }
                    continue;
                }

                //if the boolean comes back as false when comparing the word to a dictionary word then the
                //following message is outputted and the for loop continues
                if (!checkExists(wordFive, dictionaryFive)) {
                    cout << "Not a playable word, please select another word. " << endl;
                    int tempRow = row;
                    row = tempRow - 1;
                    if (attempts != 0) {
                        int tempAttempts = attempts;
                        attempts = tempAttempts - 1;
                    }
                    continue;
                }

                //checking the amount of time passed
                secondsElapsed = difftime(time(nullptr), startTime);

                /*if the amount of time passed is over 40 seconds the game ends and the user needs to pick another
                menu option*/
                if (secondsElapsed > 40) {
                    cout << "Your time has expired.  Try again.\n"
                            "  - You are " << (secondsElapsed - 40) << " seconds over the 40 second time limit.";
                    continue;
                }

                //checking if the inputted word is equal to the random dictionary word
                if (wordFive == DictWordFive) {
                    checkWin = true;
                }

                /*checking each letter in the inputted word,
                 *if the letter is in the same position as the random word it is displayed on the
                 * board as a capital letter
                 *if a letter is in the dictionary word but not the same position then it is displayed
                 * on the board as lowercase*/

                for (int col = 0; col < 5; col++) {
                    if (wordFive.at(col) == DictWordFive.at(col)) {
                        boardFive[row][col] = toupper(wordFive[col]);

                    } else if (wordFive[col] == DictWordFive[0] || wordFive[col] == DictWordFive[1] ||
                               wordFive[col] == DictWordFive[2] || wordFive[col] == DictWordFive[3] ||
                               wordFive[col] == DictWordFive[4]) {
                        boardFive[row][col] = wordFive[col];
                    } else {
                        boardFive[row][col] = '*';
                    }
                }

                //displaying the board
                displayBoardFive(boardFive);

                //checking for a win
                if (checkWin == true) {

                    secondsElapsed = difftime(time(nullptr), startTime);

                    cout << "Nice Work!  You guessed the correct word\n"
                         << "- You completed the board in: " << secondsElapsed << " seconds. \n" <<
                         "  - It took you " << attempts << "/6 attempts.";

                    TotalTime = TotalTime + secondsElapsed;
                    Wins++;
                    CurrentStreak++;
                    runs++;
                    if (longestStreak < CurrentStreak) {
                        longestStreak = CurrentStreak;
                    }
                    break;
                }
            }
        }
        else if (menuOption == 3) {

            //ending while loop if user inputs 3
            gameplay = false;

            //calculating the average time for the user to get the correct answer
            if (Wins != 0) {
                AvgTime = round(TotalTime / Wins);
            }

            //if statement to check if the user had any wins or not and diplaying the correct scoreboard
            if (longestStreak > 0) {
                cout << "Overall Stats:\n"
                        "  - You guessed: " << Wins << "\n"
                        "  - Your longest streak is: " << longestStreak << "\n"
                        "  - Average word completion time: "
                        << AvgTime << "\n"
                        "Exiting program";
            } else {
                cout << "Overall Stats:\n"
                        "  - You guessed: " << Wins << "\n"
                        "  - Your longest streak is: 0\n"
                        "  - Average word completion time: N/A\n"
                        "Exiting program";
            }
        }
    }

    return 0;
}//end  of main
