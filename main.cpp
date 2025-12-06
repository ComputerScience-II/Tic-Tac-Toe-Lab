#include <iostream>
#include <cassert>
using namespace std;

const int TOTAL_SLOTS = 9;

bool moveValid = false;

char selections[TOTAL_SLOTS] = {'1','2','3','4','5','6','7','8','9'};

const int WINNING_COMBOS[8][3] = {{0,1,2}, {3,4,5}, {6,7,8},{0,3,6}, {1,4,7}, {2,5,8},{0,4,8}, {2,4,6}};

char turn = 'X';

bool gameEnd = false;

char choice;

void randomEarthquake(){

    int a = rand() % 9;
    int b = rand() % 9;

    cout << "A sudden earthquake has shaken up the whole board! The following slots have been swapped " << a + 1 << " and " << b + 1 << " !\n";

    char x = selections[a];

    selections[a] = selections[b];

    selections[b] = x;
}

void snakeAttack() {

    int f[9];

    int count = 0;

    for(int i = 0; i < 9; i++) {

        if(selections[i] == 'X' || selections[i] == 'O') {
            f[count++] = i;

        }
    }

    if(count == 0) {
        return;
    }

    int attackTarget = f[rand() % count];

    cout << "A snake suddenly spits its venom on slot " << attackTarget + 1 << " and destroyed the input there.\n";

    selections[attackTarget] = '1' + attackTarget;

}

void luckyLanding() {

    int e[9], count = 0;

    for(int i = 0; i < 9; i++) {

        if(selections[i] >= '1' && selections[i] <= '9') {
            e[count++] = i;
        }
    }

    if(count == 0) {

        return;
    }

    int luckyLanding = e[ rand() % count];

    cout << "Someone just got a lucky landing, slot " << luckyLanding + 1 << " is now marked as " << turn << ".\n";

    selections[luckyLanding] = turn;

}

void randomOperator() {

    int chanceOfAnyHappening = rand() % 100;

    if (chanceOfAnyHappening >= 20) {

        return;
    }

    int r = rand() % 100;

    if( r < 10) {

        randomEarthquake();
    }

    r = rand() % 100;

    if (r < 10) {
        
        snakeAttack();     
    }

    r = rand() % 100;

    if (r < 10){

        luckyLanding();

    } 


}
bool checkWin() {


    for (int i = 0; i < 8; i++) {

        if (selections[WINNING_COMBOS[i][0]] == turn && selections[WINNING_COMBOS[i][1]] == turn && selections[WINNING_COMBOS[i][2]] == turn) {
            return true;
        }
    }
    return false;
}

bool checkTie() {

    for (int i = 0; i < TOTAL_SLOTS; i++) {

        if (selections[i] != 'X' && selections[i] != 'O') return false;
    }
    return true;

}

void resetGame() {

    for (int i = 0; i < TOTAL_SLOTS; i++) selections[i] = '1' + i;
    turn = 'X';
    gameEnd = false;

}



bool characterChecker(char a) { 

    if ((a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z') || (a == '?' ) || (a == '!') || (a == '*') || (a == '~') || (a == '#') || (a == '$') || (a == '%')) {

        return true;
    }

    if(a == 'X' || a == 'O' || a == 'x' || a == 'o') {

        cout << "Character cannot be X or O. Please choose another character.\n";

        return false;
    }


    return false;
}

void displayBoard() {

    for (int i = 0; i < 9; i++) {

        cout << selections[i];

        if (i % 3 != 2) cout << " | ";

        else if (i != 8) cout << "\n---------\n";

        else cout << "\n\n";
    }

}

void normalGame() {

    resetGame();

    string playerX, playerO;

    cout << "Enter name for Player X: \n";

    cin >> playerX;

    cout << "Enter name for Player O:\n ";

    cin >> playerO;

    char continueGame = 'y';

    while (continueGame == 'y' || continueGame == 'Y') {

        resetGame();

        while (!gameEnd) {

            displayBoard();

            string playername;

            if (turn == 'X') {

                playername = playerX;
            } 
            else {
                playername = playerO;
            }

            cout << "Player " << playername << ", enter a digit: \n";

            cin >> choice;

            if (cin.fail() || choice < '1' || choice > '9') {

                cin.clear();
                cin.ignore(50000, '\n');
                cout << "Invalid input! Enter a single digit between 1-9.\n";
                continue;
            }

            int a = choice - '0' - 1;

            if (selections[a] == 'X' || selections[a] == 'O') {

                cout << "This slot is already full!!.\n";

                continue;
            }

            

            selections[a] = turn;

            randomOperator();

           if (checkWin()) {

                displayBoard();

                if (turn == 'X') {

                    cout << "Player " << playerX << " wins!\n";
                }       
                
                else {
                cout << "Player " << playerO << " wins!\n";

            }

            gameEnd = true;

            } 

            else if (checkTie()) {

                    displayBoard();

                    cout << "Game has ended in a tie.\n";

                    gameEnd = true;

                } 
            else {

                if (turn == 'X') {
                        
                    turn = 'O';
                } 
                else {
                     turn = 'X';
                    }
                }
            }

        cout << "Do you want to play another round of this gamemode? (y/n): \n";

        cin >> continueGame;

        cin.ignore(500, '\n');

        }



}



bool isAdjacent(int slot1, int slot2) {

    if (slot1 < 0 || slot1 > 8 || slot2 < 0 || slot2 > 8) {

        return false;
    }

    if(slot1 == slot2 - 1 && slot1 % 3 != 2) {

        return true;
    }

    if(slot1 == slot2 + 1 && slot1 % 3 != 0) {

        return true;
    }

    if(slot1 - slot2 == 3) {

        return true;
    }

    if(slot2 - slot1 == 3) {

        return true;
    }

    return false;
}

void battleMode() {

    resetGame();

    string playerX, playerO;
    char char1, char2;
    string archetype1, archetype2;

    cout << "Enter name for Player X: \n";

    cin >> playerX;

    cout << "Enter name for Player O: \n";

    cin >> playerO;
    
    cout << "Player " << playerX << ", choose your character symbol: \n";

    cin >> char1;

    while (!characterChecker(char1)) {

        cout << "Invalid character! Please choose a valid character symbol:\n ";

        cin >> char1;

    }

    cout << "Player " << playerO << ", choose your character symbol:\n ";

    cin >> char2;

    while (!characterChecker(char2)) {

        cout << "Invalid character! Please choose a valid character symbol: \n";

        cin >> char2;

    }

    cout << playerX << " choose an archetype between Paladin and Alchemist\n";

    cin >> archetype1;

    while(archetype1 != "paladin" && archetype1 != "Paladin" && archetype1 != "alchemist" && archetype1 != "Alchemist") {

        cout << "Invalid archetype! Please choose either Paladin or Alchemist: \n";

        cin >> archetype1;

    }

    cout << playerO << " choose an archetype between Paladin and Alchemist\n";

    cin >> archetype2;

    while(archetype2 != "paladin" && archetype2 != "Paladin" && archetype2 != "alchemist" && archetype2 != "Alchemist") {

        cout << "Invalid archetype! Please choose either Paladin or Alchemist: \n";

        cin >> archetype2;

    }

    turn = char1;

    string currentArchetype;
    string currentChar;

    while(gameEnd == false) {

        displayBoard();
        
        if (turn == char1) {

            currentChar = playerX;
            currentArchetype = archetype1;
        }

        else {

            currentChar = playerO;
            currentArchetype = archetype2;
        }

        cout << "Player " << currentChar << " (" << turn << "), choose a move: \n";

        cout << "1. Regular Move\n";
        cout << "2. Special Move\n";
        
        int moveChoice;

        cin >> moveChoice;

        if(moveChoice == 1) {
            
            cout << "Enter a slot number 1-9: ";
            
            cin >> choice;

        
            if (cin.fail() || choice < '1' || choice > '9') {
                    cin.clear(); cin.ignore(50000, '\n');
                    cout << "Invalid input!\n";
                    continue;
            }

            int a = choice - '0' - 1;

            if (selections[a] == char1 || selections[a] == char2) {

                cout << "This slot is already full!!.\n";

                continue;

            }

            selections[a] = turn;

            randomOperator();

            if(checkWin()) {

                displayBoard();

                cout << "Player " << currentChar << " wins!\n";

                gameEnd = true;

            }

            else if (checkTie()) {

                displayBoard();

                cout << "Game has ended in a tie.\n";

                gameEnd = true;

            }

            else {

                if (turn == char1) {

                    turn = char2;
                } 
                else {
                    turn = char1;
                }
            }

        }

        else if (moveChoice == 2) {

            

            if((currentArchetype == "Alchemist") || (currentArchetype == "alchemist")) {

                int boardCounter = 0;

                for(int i = 0; i < 9; i++) {

                    if(selections[i] == char1 || selections[i] == char2) {

                        boardCounter++;
                    }
                }

                if(boardCounter < 2) {

                    cout << "Not enough pieces on board to perform special move yet.\n";

                    continue;
                    
                }

                cout << "Enter the slot numbers of the pieces you want to swap: \n";

                int slot1, slot2;

                cin >> slot1 >> slot2;

                slot1 -= 1;
                slot2 -= 1;

                if(slot1 < 0 || slot1 > 8 || slot2 < 0 || slot2 > 8) {

                    cout << "Invalid slot numbers!\n";

                }
                if(slot1 == slot2) {

                    cout << "Cannot swap the same slot!\n";

                }

                if( selections[slot1] >= '1' && selections[slot1] <= '9') {

                    cout << "There is no piece to swap in slot " << slot1 + 1 << ".\n";

                    continue;

                }

                if( selections[slot2] >= '1' && selections[slot2] <= '9') {

                    cout << "There is no piece to swap in slot " << slot2 + 1 << ".\n";

                    continue;

                }

                char aTemp = selections[slot1];

                selections[slot1] = selections[slot2];

                selections[slot2] = aTemp;

                moveValid = true;

                randomOperator();
            }

            else if((currentArchetype == "Paladin") || (currentArchetype == "paladin")) {

               int boardCounter = 0;
               int slotFrom, slotTo;

                for(int i = 0; i < 9; i++) {

                    if(selections[i] == char1 || selections[i] == char2) {

                        boardCounter++;
                    }
                }

                if (boardCounter < 1) {

                    cout << "Not enough pieces on board to perform special move yet.\n";

                    continue;
                    
                }

                cout << "Enter the slot number of the piece you want to move:\n ";

                cin >> slotFrom;

                slotFrom -= 1;

                if(slotFrom < 0 || slotFrom > 8) {

                    cout << "Invalid slot number!\n";

                }

                if ( selections[slotFrom] != char1 && selections[slotFrom] != char2) {

                    cout << "there are no pieces to move here\n";

                }

                if (selections[slotFrom] >= '1' && selections[slotFrom] <= '9') {

                    cout << "That slot is empty you can only move actual pieces.\n";
                    continue;

                }

                cout << "Enter the slot number you want to move to:\n ";

                cin >> slotTo;

                slotTo -= 1;

                if (slotTo < 0 || slotTo > 8 || selections[slotTo] == char1 || selections[slotTo] == char2) {

                        cout << "Invalid or occupied slots.\n";

                }

                if(!isAdjacent(slotFrom, slotTo)) {

                    cout << "Slots are not adjacent!\n";
                    continue;

                }

                selections[slotTo] = selections[slotFrom];

                selections[slotFrom] = '1' + slotFrom;

                moveValid = true;

                randomOperator();

               
            }

            else {

                cout << "Invalid choice!\n";
            }

           
        }

        if(moveValid) {

            if (checkWin()) {

                displayBoard();

                cout << "Player " << currentChar << " wins!\n";

                gameEnd = true;

            }

            else if (checkTie()) {

                displayBoard();

                cout << "Game has ended in a tie.\n";

                gameEnd = true;

            }

            else {

                if (turn == char1) {

                    turn = char2;
                } 
                else {
                    turn = char1;
                }
            }
        }   

    }

}



void testCases() {

    selections[0]='X'; 
    selections[1]='X'; 
    selections[2]='X';
    selections[3]='O'; 
    selections[4]='O'; 
    selections[5]='5';
    selections[6]='6'; 
    selections[7]='7'; 
    selections[8]='8';

    turn = 'X';

    assert(checkWin() == true);

    selections[0]='1'; 
    selections[1]='2'; 
    selections[2]='3';

    selections[3]='X'; 
    selections[4]='X'; 
    selections[5]='X';
    selections[6]='O'; 
    selections[7]='O'; 
    selections[8]='9';

    turn = 'X';
    assert(checkWin() == true);

    selections[0]='O'; 
    selections[1]='2'; 
    selections[2]='3';
    selections[3]='O';
    selections[4]='5'; 
    selections[5]='6';
    selections[6]='O'; 
    selections[7]='8'; 
    selections[8]='9';

    turn = 'O';
    assert(checkWin() == true);

    selections[0]='X'; 
    selections[1]='2'; 
    selections[2]='3';
    selections[3]='4'; 
    selections[4]='X'; 
    selections[5]='6';
    selections[6]='7'; 
    selections[7]='8'; 
    selections[8]='X';

    turn = 'X';
    assert(checkWin() == true);

    selections[0]='1'; 
    selections[1]='2'; 
    selections[2]='O';
    selections[3]='4'; 
    selections[4]='O'; 
    selections[5]='6';
    selections[6]='O'; 
    selections[7]='8'; 
    selections[8]='9';

    turn = 'O';
    assert(checkWin() == true);

    selections[0]='X'; 
    selections[1]='O'; 
    selections[2]='X';
    selections[3]='O'; 
    selections[4]='X'; 
    selections[5]='O';
    selections[6]='O'; 
    selections[7]='X';
    selections[8]='9';

    turn = 'X';
    assert(checkWin() == false);
    assert(checkTie() == false);

    selections[0]='X'; 
    selections[1]='O'; 
    selections[2]='X';
    selections[3]='O'; 
    selections[4]='X'; 
    selections[5]='O';
    selections[6]='O';
    selections[7]='X'; 
    selections[8]='O';

    turn = 'X';
    assert(checkWin() == false);
    assert(checkTie() == true);

    selections[0]='1'; 
    selections[1]='2'; 
    selections[2]='3';
    selections[3]='4'; 
    selections[4]='X';
    selections[5]='6';
    selections[6]='7'; 
    selections[7]='8';
    selections[8]='9';

    turn = 'X';
    assert(checkWin() == false);
    assert(checkTie() == false);

    selections[0]='X';
    selections[1]='O'; 
    selections[2]='X';
    selections[3]='4'; 
    selections[4]='X';
    selections[5]='6';
    selections[6]='7'; 
    selections[7]='8';
    selections[8]='9';

    turn = 'X';
    assert(checkWin() == false);
    assert(checkTie() == false);

    assert(isAdjacent(0,1) == true);

    assert(isAdjacent(0,3) == true);

    assert(isAdjacent(1,2) == true);

    selections[0]='X';
    selections[1]='O';
    selections[2]='X';
    selections[3]='4';
    selections[4]='X';
    selections[5]='6';
    selections[6]='7';
    selections[7]='8';
    selections[8]='9';

    assert(isAdjacent(0,2) == false);
    assert(isAdjacent(0,4) == false);


}

int main() {

    testCases();

    char gameMode;

    char choice = 'y';

    while (choice != 'n' && choice != 'N') {

    cout << "-----TIC TAC TOE-----\n";

    cout << "Select Game Mode:\n";

    cout << "1. Normal Game\n";

    cout << "2. Battle Mode\n";

    cin >> gameMode;
    



    if (gameMode == '1') {

        normalGame();

    }

    else if (gameMode == '2') {

        battleMode();

    }

    else {

        cout << "Invalid game mode selected!\n";

    }

    cout << "Do you want to go back to the main menu? (y/n): \n";

    cin >> choice;

    while(cin.fail() || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')){

        cin.clear();            

        cin.ignore(500, '\n');     

        cout << "Invalid input. Please enter y or n:\n ";

        cin >> choice;   

    }

    cin.ignore(500, '\n');

    }

    cout << "Thank you for playing Tic Tac Toe!\n";

    cin.ignore(500, '\n');

    return 0;
}