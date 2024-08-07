#include <iostream>
#include <vector>
#include <array>

using namespace std;

void DisplayGame(vector<string> gameTable) {
    int xValue = 0;
    string xLine = "";

    for (int i = 0; i < gameTable.size(); i++) {
        xValue++;
        string inCurrentValue;

        if (gameTable[i] == "NULL") {
            inCurrentValue = " ";
        } else if (gameTable[i] == "false") {
            inCurrentValue = "O";
        } else if (gameTable[i] == "true") {
            inCurrentValue = "X";
        }

        if (xValue != 3) {
            xLine += inCurrentValue + " | ";
        } else {
            xLine += inCurrentValue + " \n";
            cout << xLine;
            xLine = "";
            xValue = 0;
        }
    }
}

bool CheckForTableError(vector<string> gameTable, string Entry) {
    bool CheckedValue = false;
    if (gameTable[stoi(Entry)-1] == "NULL") {
        CheckedValue = true;
    }
    return CheckedValue;
}

vector<string> UpdateGameTable(vector<string> gameTable, string PlayerMoved, string Position) {
    int tableIndex = stoi(Position)-1;

    if (PlayerMoved == "one") {
        gameTable[tableIndex] = "true";
    } else {
        gameTable[tableIndex] = "false";
    }

    return gameTable;
}

string GameProcessEnd(vector<string> gameTable) {
    string PlayerFinish = "NULL";

    for (int i = 0; i < gameTable.size(); i++) {
        // Vertical Check
        if (i+1 <= 3) {
            if (gameTable[i] != "NULL") {
                string f = gameTable[i];

                if (gameTable[i+3] == f && gameTable[i+6] == f) {
                    PlayerFinish = f;
                }
            }
        }

        // Horizontal Check
        vector<int> horizontalValues = {1,4,7};
        bool horCheck = false;
        for (int v = 0; v < horizontalValues.size(); v++) {
            if (i == horizontalValues[v]) {
                horCheck = true;
            }
        }

        if (horCheck) {
            string f = gameTable[i];
            if (gameTable[i+1] == f && gameTable[i+2] == f) {
                PlayerFinish = f;
            }
        }

        // Diagonal Check
        
        if (gameTable[0] == gameTable[4] && gameTable[0] == gameTable[8]) {PlayerFinish = gameTable[0];}
        if (gameTable[2] == gameTable[4] && gameTable[2] == gameTable[2+4]) {PlayerFinish = gameTable[2];}

    }

    if (PlayerFinish == "true") {
        PlayerFinish = "One";
    } else if (PlayerFinish == "false") {
        PlayerFinish = "Two";
    }

    return PlayerFinish;
}

int main() {
    bool GameRunning = true;
    string GameMode = "TwoPlayer";
    
    vector<string> gameTable = {
        "NULL","NULL","NULL",
        "NULL","NULL","NULL",
        "NULL","NULL","NULL"
    };
    while (GameRunning) {
        if (GameMode == "TwoPlayer") {
            string pO;
            string pT;
            
            bool checked = false;
            while (!checked) {
                cout << "Player One (X) Move (1-9, left-right): ";
                cin >> pO;
                bool checked = CheckForTableError(gameTable, pO);
                if (checked) {
                    break;
                } else {
                    cout << "\nError: Already Taken\n";
                }
            }
            gameTable = UpdateGameTable(gameTable, "one", pO);

            cout << "\n";
            DisplayGame(gameTable);
            cout << "\n";

            string GameProcessed = GameProcessEnd(gameTable);
            if (GameProcessed != "NULL") {
                cout << "Player " << GameProcessed << " Wins\n";
                break;
            }

            checked = false;
            while (!checked) {
                cout << "Player Two (O) Move (1-9, left-right): ";
                cin >> pT;
                bool checked = CheckForTableError(gameTable, pT);
                if (checked) {
                    break;
                } else {
                    cout << "\nError: Already Taken\n";
                }
            }
            gameTable = UpdateGameTable(gameTable, "two", pT);

            cout << "\n";
            DisplayGame(gameTable);
            cout << "\n";

            GameProcessed = GameProcessEnd(gameTable);
            if (GameProcessed != "NULL") {
                cout << "Player " << GameProcessed << " Wins\n";
                break;
            }
        }
    }
    return 0;
}

// if you reading this, this has bad code but this is one of my first actual projects in c++