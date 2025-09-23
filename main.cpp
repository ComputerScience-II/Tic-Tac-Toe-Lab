#include <iostream>
#include <fstream>
using namespace std;

char selections[] = {'1','2','3','4','5','6','7','8','9'};
char turn = 'X';
int choice;
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

        if (selections[i] != 'X' && selections[i] != 'O') {

            return false;
        }
    }

    return true;

}

void resetGame() {

    for (int i = 0; i < 9; i++) {

        selections[i] = '1' + i;

    }

    turn = 'X';

    gameEnd = false;

}



int main() {

    string playerX, playerO;

    cout << "Enter name for Player X: ";

    getline(cin, playerX);

    cout << "Enter name for Player O: ";

    getline(cin, playerO);


    ifstream inX(playerX + "-results.txt");

    if (inX) inX >> scoreX;

    inX.close();

    ifstream inO(playerO + "-results.txt");

    if (inO) inO >> scoreO;

    inO.close();

    ifstream inD("draws.txt");

    if (inD) inD >> scoreTie;
    
    inD.close();


    while (!gameEnd) {

        for (int i = 0; i < 9; i++) {

            cout << selections[i];

            if (i % 3 != 2) cout << " | ";

            else if (i != 8) cout << "\n---------\n";

            else cout << "\n";

        }

        cout << "Player " << turn << ", enter a digit: ";

        cin >> choice;

        if(cin.fail() || choice < 1 || choice > 9) {

            cin.clear();
            cin.ignore(500, '\n');
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;

        }

        if (selections[choice - 1] == 'X' || selections[choice - 1] == 'O') {

            cout << "This slot has already been filled. Choose another.\n";

        }

        selections[choice - 1] = turn;

        if (checkWin()) {

            cout << "Player " << turn << " wins!\n";
            gameEnd = true;
            cout << "Game over!\n";

        } 

        else if (checkTie()) {

            cout << "Game has ended in a tie.\n";
            gameEnd = true;
            cout << "Game over\n";

        } 

        else {

            turn = (turn == 'X') ? 'O' : 'X';
            
        }
    }
}
