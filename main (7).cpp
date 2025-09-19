#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

const int SIZE = 5;  // Board size (5x5 for simplicity)

class Board {
private:
    vector<vector<char>> grid;
public:
    Board() {
        grid.resize(SIZE, vector<char>(SIZE, '~')); // ~ = water
    }

    void display(bool hideShips = false) {
        cout << "  ";
        for (int i = 0; i < SIZE; i++) cout << i << " ";
        cout << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << i << " ";
            for (int j = 0; j < SIZE; j++) {
                if (hideShips && grid[i][j] == 'S')
                    cout << "~ ";
                else
                    cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool placeShip(int x, int y) {
        if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && grid[x][y] == '~') {
            grid[x][y] = 'S'; // Ship
            return true;
        }
        return false;
    }

    bool attack(int x, int y) {
        if (x >= 0 && x < SIZE && y >= 0 && y < SIZE) {
            if (grid[x][y] == 'S') {
                grid[x][y] = 'X'; // Hit
                return true;
            } else if (grid[x][y] == '~') {
                grid[x][y] = 'O'; // Miss
            }
        }
        return false;
    }

    bool allShipsSunk() {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (grid[i][j] == 'S')
                    return false;
        return true;
    }
};

class Game {
private:
    Board playerBoard, aiBoard;
public:
    Game() {
        srand(time(0));
        // Place random ships for AI
        for (int i = 0; i < 3; i++) {
            int x, y;
            do {
                x = rand() % SIZE;
                y = rand() % SIZE;
            } while (!aiBoard.placeShip(x, y));
        }
        // Place random ships for Player (you can replace with manual placement)
        for (int i = 0; i < 3; i++) {
            int x, y;
            do {
                x = rand() % SIZE;
                y = rand() % SIZE;
            } while (!playerBoard.placeShip(x, y));
        }
    }

    void start() {
        cout << "=== Battleship Game ===\n";
        while (true) {
            cout << "\nYour Board:\n";
            playerBoard.display();
            cout << "\nEnemy Board:\n";
            aiBoard.display(true);

            int x, y;
            cout << "Enter attack coordinates (row col): ";
            cin >> x >> y;
            if (aiBoard.attack(x, y))
                cout << "Hit!\n";
            else
                cout << "Miss!\n";

            if (aiBoard.allShipsSunk()) {
                cout << "You win!\n";
                break;
            }

            // AI random attack
            x = rand() % SIZE;
            y = rand() % SIZE;
            cout << "Enemy attacks (" << x << "," << y << ")...\n";
            if (playerBoard.attack(x, y))
                cout << "Your ship was hit!\n";
            else
                cout << "Enemy missed!\n";

            if (playerBoard.allShipsSunk()) {
                cout << "You lose!\n";
                break;
            }
        }
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}