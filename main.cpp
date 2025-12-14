#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

const int TOTAL_SLOTS = 9;

bool moveValid = false;

char selections[TOTAL_SLOTS] = {'1','2','3','4','5','6','7','8','9'};

const int WINNING_COMBOS[8][3] = {{0,1,2}, {3,4,5}, {6,7,8},{0,3,6}, {1,4,7}, {2,5,8},{0,4,8}, {2,4,6}};

char turn = 'X';

bool gameEnd = false;

char choice;

int battleRound = 0;

int randomEventCounter = 0;

int wallet = 0;

struct Entity {

    string name; 

    string type; 

    char symbol;

    int health;

    int attack;

    int defense;

    bool isFinalBoss;
};


vector<Entity> enemies {

    {"Goblin", "Monster", 'G', 0, 0, 0,false},

    {"Orc", "Monster", 'O', 0, 0, 0, false},

    {"Giant", "Monster", 'T', 0, 0, 0, false},

    {"Necromancer", "BossRoom Guard", 'N', 0, 0, 0, false},

    {"Dragon", "Final Boss", 'D', 0, 0, 0, true}
};

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

        if (selections[i] >= '1' && selections[i] <= '9') return false;

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

void StatsSetter(Entity &entity, string archetype) {

    if(archetype == "Paladin" || archetype == "paladin") {

        entity.health = 250;

        entity.attack = 50;

        entity.defense = 20;

    }

    else if(archetype == "Alchemist" || archetype == "alchemist") {

        entity.health = 250;

        entity.attack = 30;

        entity.defense = 50;

    }

    else if (archetype == "Monster") {

        entity.health = 100;

        entity.attack = 30;

        entity.defense = 30;

    }

    else if (archetype == "BossRoom Guard") {

        entity.health = 200;

        entity.attack = 50;

        entity.defense = 35;

    }

    else if (archetype == "Final Boss") {

        entity.health = 300;

        entity.attack = 40;

        entity.defense = 40;

    }

}

int EntityBattle(Entity &player, Entity &enemy) {
    
    resetGame();

    turn = player.symbol;

    while (player.health > 0 && enemy.health > 0) {

        displayBoard();

        if (turn == player.symbol) {

            if (checkTie()) {

                cout << "\nThis round ended in a tie. No damage dealt to anyone.\n";
                resetGame();
                turn = player.symbol;
                continue;
            }

            cout << "\n\n" << player.name << "'s turn. Enter a slot number 1-9: \n\n";
            char choice;
            cin >> choice;

            if (cin.fail() || choice < '1' || choice > '9') {
                cin.clear(); cin.ignore(50000, '\n');
                cout << "\n\nInvalid input! Try again.\n\n";
                continue;
            }

            int idx = choice - '0' - 1;
            if (selections[idx] == player.symbol || selections[idx] == enemy.symbol) {
                cout << "\n\nSlot full! Choose another.\n\n";
                continue;
            }

            selections[idx] = player.symbol;
        }
        else {
            vector<int> freeSlots;
            for (int i = 0; i < 9; i++) {
                if (selections[i] != player.symbol && selections[i] != enemy.symbol) {
                    freeSlots.push_back(i);
                }
            }

            if (!freeSlots.empty()) {
                int move = freeSlots[rand() % freeSlots.size()];
                selections[move] = enemy.symbol;
                cout << enemy.name << " placed its symbol in slot " << move + 1 << ".\n\n";
            }
        }

        int result = 0;

        if (checkWin()) {
            result = (turn == player.symbol) ? 1 : -1;
        } 
        else if (checkTie()) {
            cout << "\n\nThis round ended in a tie. No damage dealt.\n\n";
            resetGame();
            turn = player.symbol;
            continue;
        }

        if (result != 0) {

            int damage = 0;

            if (result == 1) {

                damage = player.attack - enemy.defense;
                if (damage < 0) damage = 0;
                enemy.health -= damage;
                cout << "\n\n" << player.name << " wins the round and deals " << damage << " damage to " << enemy.name << ".\n\n";
            } 
            else if (result == -1) {
                int enemyAttack = enemy.attack;
                int enemyDef = enemy.defense;

                // Unique abilities
                if (enemy.name == "Goblin") {
                    if (rand() % 100 < 20) {

                        cout << "\n\nGoblin uses dodge! You take no damage this round.\n\n";
                        enemyAttack = 0;

                    }
                } 
                else if (enemy.name == "Orc") {

                    if (rand() % 100 < 25) {

                        enemyAttack *= 2;

                        cout << "\n\nOrc goes berserk and his attack is doubled!\n\n";

                    }
                } 
                else if (enemy.name == "Giant") 
                {
                    if (rand() % 100 < 15) {

                        enemyAttack += 20;

                        cout << "\n\nGiant crushes you and his attack increases by 20\n\n";
                    }
                } 
                else if (enemy.name == "Necromancer") {

                    if (rand() % 100 < 30) {

                        enemy.health += 15;
                        cout << "\n\nNecromancer heals 15 HP!\n\n";

                    }
                } 
                else if (enemy.name == "Dragon") {

                    int ability = rand() % 3;

                    if (ability == 0) {

                        enemyAttack += 25;
                        cout << "\n\nDragon uses fire breath and his overall damage has increases\n\n";

                    } 
                    else if (ability == 1) {

                        enemyDef += 20;
                        cout << "\n\nDragon uses scale armor and his defense increases by 20\n\n";
                    } 
                    else if (ability == 2) {
                        cout << "\n\nDragon flaps its wings and you lose your turn\n\n";
                        turn = enemy.symbol;
                    }
                }

                damage = enemyAttack - player.defense;
                if (damage < 0) damage = 0;
                player.health -= damage;

                if (enemy.name != "Dragon" || (enemy.name == "Dragon" && damage > 0))

                    cout << "\n\n" << enemy.name << " wins the round and deals " << damage << " damage to " << player.name << ".\n\n";
            }

            if (player.health > 0 && enemy.health > 0) {
                resetGame();
                turn = player.symbol;
            }
        } 
        else {

            if (turn == player.symbol) {

                turn = enemy.symbol;
            }
            else {
                turn = player.symbol;
            }
        }
    }

    if (player.health > 0) {
        return 1;
    }
    else{
        return -1;

    }
}



void shopMenu(Entity &player) {

    char itemChoice;
    bool shopping = true;

    while(shopping) {

        cout << "\nWelcome to the dungeon shop! Each item costs 10 coins.\n";

        cout << "\n\nCurrent Wallet:\n\n " << wallet;

        cout << "1. Attack Potion (+10 Attack)\n";
        cout << "2. Health Potion (+20 Health)\n";
        cout << "3. Defense Potion (+10 Defense)\n";
        cout << "4. Exit Shop\n";
        cout << "\n\nEnter your choice: \n\n";
        cin >> itemChoice;

        if(itemChoice == '1') {

            if(wallet >= 10) { player.attack += 10; wallet -= 10; cout << "\n\nAttack increased! New attack: " << player.attack << "\n"; }
            else cout << "\n\nNot enough coins!\n";

        } 
        else if(itemChoice == '2') {

            if(wallet >= 10) { player.health += 20; wallet -= 10; cout << "\n\nHealth increased! New health: " << player.health << "\n"; }
            else cout << "\n\nNot enough coins!\n";
        } 

        else if(itemChoice == '3') {

            if(wallet >= 10) { 

                player.defense += 10; wallet -= 10; cout << "\n\nDefense increased! New defense: " << player.defense << "\n"; 
            }

            else cout << "\n\nNot enough coins!\n";
        } 

        else if(itemChoice == '4') {

            shopping = false;

        } 

        else {
            cout << "\n\nInvalid choice.\n";
        }
    }
}



void campaignMode() {

    Entity player;

    char continueStatus = 'y';
    char shopChoice = 'y';

    cout << "----welcome to campaign mode----\n\n\n";

    cout << "Enter your character's name:\n\n";

    cin >> player.name;

    cout << "Choose your archetype (paladin/alchemist): \n\n";

    cin >> player.type;

    while(player.type != "Paladin" && player.type != "paladin" && player.type != "Alchemist" && player.type != "alchemist") {

        cout << "Invalid archetype. Please choose either paladin or alchemist: \n\n";
        cin >> player.type;
    }

    cout << "Choose your character symbol: \n\n";

    cin >> player.symbol;

    while (!characterChecker(player.symbol)) {

        cout << "Invalid character. Please choose a valid character symbol:\n\n";
        cin >> player.symbol;
    }

    StatsSetter(player, player.type);

    cout << "\n\n-------------------------------\n\n";

    cout << "Your character " << player.name << " has been created with the following stats:\n\n";
    cout << "Health: " << player.health << "\n";
    cout << "Attack: " << player.attack << "\n";
    cout << "Defense: " << player.defense << "\n";

    cout << "\n\nWould you like to begin your campaign? (y/n): \n\n";

    cin >> continueStatus;

    if(continueStatus != 'y' && continueStatus != 'Y') {

        cout << "\n\nExiting campaign mode. Returning to main menu.\n\n";
        return;
    }

    cout << "\n\nLet the campaign begin\n\n";
    cout << "-------------------------------\n\n";

    cout << "You enter the dark dungeon, ready to face whatever challenges lie ahead.\n";
    cout << "\n\nYour first opponent approaches, a goblin\n\n";

    Entity enemy1 = enemies[0];
    StatsSetter(enemy1, enemy1.type);
    int battleResult = EntityBattle(player, enemy1);

    if(battleResult == -1) {

        cout << "\n\nYou have been defeated by the goblin. Game over.\n";
        return;
    }

    cout << "\n\nYou have defeated the goblin\n";
    wallet += 10;
    cout << "You have earned 10 coins. Current wallet: " << wallet << "\n";

    cout << "\nAfter the fight, you see two paths ahead:\n";
    cout << "1. Take the left path (+10 attack)\n";
    cout << "2. Take the right path (+10 defense)\n";
    cout << "3. Rest and recover (no stat change)\n";
    int choice;
    cin >> choice;

    if(choice == 1) {

        player.attack += 10;
        cout << "Your attack increased. New attack: " << player.attack << "\n";
    }

    else if(choice == 2) {

        player.defense += 10;
        cout << "Your defense increased. New defense: " << player.defense << "\n";
    }

    else {

        cout << "You rest and prepare for the next challenge.\n";
    }

    cout << "\nYou notice a shop nearby. Would you like to open it? (y/n): ";

    cin >> shopChoice;

    if(shopChoice == 'y' || shopChoice == 'Y') {

        shopMenu(player);
    }

    cout << "\n\nAs you venture further, an orc blocks your path\n\n";
    Entity enemy2 = enemies[1];
    StatsSetter(enemy2, enemy2.type);
    battleResult = EntityBattle(player, enemy2);

    if(battleResult == -1) {

        cout << "\n\nYou have been defeated by the orc. Game over.\n";
        return;
    }

    cout << "\n\nYou defeated the orc. You may proceed deeper into the dungeon\n";

    cout << "\nBefore continuing, you find a fork in the path:\n";
    cout << "1. Explore the forest (+10 health)\n";
    cout << "2. Climb the hill (+10 attack)\n";
    cout << "3. Take a short rest (no change)\n";
    cin >> choice;

    if(choice == 1) {

        player.health += 10;
        cout << "Health increased. New health: " << player.health << "\n";
    }

    else if(choice == 2) {

        player.attack += 10;
        cout << "Attack increased. New attack: " << player.attack << "\n";
    }

    else {

        cout << "You take a short rest\n";
    }

    cout << "You see a shop nearby. Would you like to open it? (y/n): ";
    cin >> shopChoice;

    if(shopChoice == 'y' || shopChoice == 'Y') {

        shopMenu(player);
    }

    cout << "\n\nA giant appears in your path\n\n";

    Entity enemy3 = enemies[2];

    StatsSetter(enemy3, enemy3.type);
    battleResult = EntityBattle(player, enemy3);

    if(battleResult == -1) {

        cout << "\n\nYou have been defeated by the giant. Game over.\n";
        return;
    }

    cout << "\n\nYou bravely defeat the giant\n";

    cout << "\nYou find a cave with two options:\n";
    cout << "1. Enter the cave (+20 attack)\n";
    cout << "2. Continue up the mountain (+10 defense)\n";
    cin >> choice;

    if(choice == 1) {

        player.attack += 20;
        cout << "Attack increased. New attack: " << player.attack << "\n";
    }

    else if(choice == 2) {

        player.defense += 10;
        cout << "Defense increased. New defense: " << player.defense << "\n";
    }

    cout << "Shop nearby? (y/n): ";
    cin >> shopChoice;
    if(shopChoice == 'y' || shopChoice == 'Y') {

        shopMenu(player);
    }

    cout << "\n\nThe necromancer guards the boss room\n\n";

    Entity enemy4 = enemies[3];
    StatsSetter(enemy4, enemy4.type);
    battleResult = EntityBattle(player, enemy4);

    if(battleResult == -1) {

        cout << "\n\nYou have been defeated by the necromancer. Game over.\n\n";
        return;
    }

    cout << "\n\nYou defeated the necromancer. Enter the boss room?\n";
    
    cout << "1. Enter cautiously\n2. Charge in bravely (+10 attack)\n";

    cin >> choice;

    if(choice == 2) {

        player.attack += 10;
        cout << "Attack increased. New attack: " << player.attack << "\n";
    }

    cout << "\n\nYou face the dragon\n\n";

    Entity enemy5 = enemies[4];
    StatsSetter(enemy5, enemy5.type);
    battleResult = EntityBattle(player, enemy5);

    if(battleResult == -1) {

        cout << "\n\nYou have been defeated by the dragon. Game over.\n\n";
        return;
    }

    cout << "\n\nCongratulations. You have defeated the dragon and completed the campaign mode\n";
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

    cout << "3. Campaign Mode\n";

    cin >> gameMode;
    



    if (gameMode == '1') {

        normalGame();

    }

    else if (gameMode == '2') {

        battleMode();

    }

    else if (gameMode == '3') {

        campaignMode();

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