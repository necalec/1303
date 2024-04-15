#include <iostream>
#include <vector>
#include <cstdlib>
#include <Windows.h>

using namespace std;

class GameOfLife {
private:
    int rows;
    int cols;
    vector<vector<bool>> board;

public:
    GameOfLife(int rows, int cols) : rows(rows), cols(cols), board(rows, vector<bool>(cols, false)) {}

    void randomize() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                board[i][j] = rand() % 2 == 1;
            }
        }
    }

    void draw() {
        system("cls");

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << (board[i][j] ? 'Я' : ' ');
            }
            cout << endl;
        }
    }

    void update() {
        vector<vector<bool>> new_board(rows, vector<bool>(cols, false));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int neighbors = count_neighbors(i, j);

                if (board[i][j]) {
                    new_board[i][j] = (neighbors == 2 || neighbors == 3);
                }
                else {
                    new_board[i][j] = (neighbors == 3);
                }
            }
        }

        board = new_board;
    }

private:
    int count_neighbors(int i, int j) {
        int neighbors = 0;
        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue;
                int ni = i + di;
                int nj = j + dj;
                if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && board[ni][nj]) {
                    ++neighbors;
                }
            }
        }
        return neighbors;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    const int rows = 20;
    const int cols = 60;

    GameOfLife game(rows, cols);

    game.randomize();

    for (int generation = 0; generation < 100; ++generation) {
        game.draw();
        Sleep(200);
        game.update();
    }

    return 0;
}



