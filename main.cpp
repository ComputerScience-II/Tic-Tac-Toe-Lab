#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

char selections[] = {'1','2','3','4','5','6','7','8','9'};
char turn = 'X';
char choice;
bool gameEnd = false;
int scoreX = 0;
int scoreO = 0;
int scoreTie = 0;

bool checkWin() {

    int winningCombinations[8][3] = {{0,1,2}, {3,4,5}, {6,7,8},{0,3,6}, {1,4,7}, {2,5,8},{0,4,8}, {2,4,6}};

    for (int i = 0; i < 8; i++) {

        if (selections[winningCombinations[i][0]] == turn && selections[winningCombinations[i][1]] == turn && selections[winningCombinations[i][2]] == turn) {

            return true;
        }
    }
    return false;
}

bool checkTie() {

    for (int i = 0; i < 9; i++) {
        if (selections[i] != 'X' && selections[i] != 'O') return false;
    }
    return true;

}

void resetGame() {

    for (int i = 0; i < 9; i++) selections[i] = '1' + i;
    turn = 'X';
    gameEnd = false;

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

    selections[0]='X a 3';
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
    


}

int main() {

    testCases();

    resetGame();

    string playerX, playerO;

    cout << "Enter name for Player X: ";
    getline(cin, playerX);

    cout << "Enter name for Player O: ";
    getline(cin, playerO);

    ifstream xfile(playerX + "--scores.txt");
    if (xfile) xfile >> scoreX;
    xfile.close();

    ifstream ofile(playerO + "--scores.txt");
    if (ofile) ofile >> scoreO;
    ofile.close();

    ifstream dfile("draws.txt");
    if (dfile) dfile >> scoreTie;
    dfile.close();

    char continueGame = 'y';

    while (continueGame == 'y' || continueGame == 'Y') {

        resetGame();

        while (!gameEnd) {

            for (int i = 0; i < 9; i++) {

                cout << selections[i];
                if (i % 3 != 2) cout << " | ";
                else if (i != 8) cout << "\n---------\n";
                else cout << "\n\n";
            }

            cout << "Player " << turn << ", enter a digit: ";
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

           if (checkWin()) {
                if (turn == 'X') {
                    cout << "Player " << playerX << " wins!\n";
                    scoreX++;
                }       
                
            else {
                cout << "Player " << playerO << " wins!\n";
                scoreO++;
            }

            gameEnd = true;

            } 

            else {
                if (checkTie()) {

                    cout << "Game has ended in a tie.\n";
                    scoreTie++;
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
        }

        cout << "\n--- Stats ---\n";

        cout << playerX << " (X) Wins: " << scoreX << "\n";
        cout << playerO << " (O) Wins: " << scoreO << "\n";
        cout << "Draws: " << scoreTie << "\n";

        ofstream xFile(playerX + "-results.txt"); xFile << scoreX; xFile.close();

        ofstream ofile(playerO + "-results.txt"); ofile << scoreO; ofile.close();

        ofstream dFile("draws.txt"); dFile << scoreTie; dFile.close();

        cout << "Do you want to play another game? (y/n): ";

        cin >> continueGame;

        while (cin.fail() || (continueGame != 'y' && continueGame != 'Y' && continueGame != 'n' && continueGame != 'N')){

            cin.clear();            

            cin.ignore(500, '\n');     

            cout << "Invalid input. Please enter y or n: ";

            cin >> continueGame;   
        }

    }

    cout << "Thanks for playing\n";
    return 0;
}
