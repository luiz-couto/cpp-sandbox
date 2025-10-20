#include <iostream>
#include <random>

#define ALPHABET_NUM_OF_CHARS 26
#define BOARD_SIZE_N 10
#define BOARD_SIZE_M 10


char generateRandomASCCharacter() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, ALPHABET_NUM_OF_CHARS);

    int randomNum = dist(mt);
    char letter = 'A' + randomNum;

    return letter;
}

void printBoard(int* board, int n, int m) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

char* createBoard() {
    char board[BOARD_SIZE_N][BOARD_SIZE_M] = {};

    for (int i=0; i<BOARD_SIZE_N; i++) {
        for (int j=0; j<BOARD_SIZE_M; j++) {
            board[i][j] = generateRandomASCCharacter();
        }
    }

    return board;
}

int main() {
    return 0;
}