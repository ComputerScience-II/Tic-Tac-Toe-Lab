#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int main() {

    char selections[] = {'1',2,'3','4','5','6','7','8','9'};

    char turn = 'X';

    int choice;

    bool end = false;


    while(!end) {

        for( int i = 0; i < 9; i++) {

            cout << selections[i];

        if (i % 3 != 2){

            cout << " | ";

        }
        else if (i != 8) {
        
            cout << "\n---------\n";
        
        }
        else {

            cout << "\n";

        }

    }

    cout << "Player " << turn << " , enter a digit: ";

    cin >> choice;


    if (choice < 1 || choice > 9) {

        cout << "Please chooose a digit that falls inside the tic tac toe grid.";
    }

    if (selections[choice - 1] == 'X' || selections[choice - 1] == 'O') {

        cout << "This slot has already been filled please choose another digit.";

    }

    selections[choice - 1] = turn;


        return 0;
    }

    int combinations [8][3] = { {0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6} };

    bool ifWin = false;

    


}

