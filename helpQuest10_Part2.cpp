#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class MineSweeper {
public:
    int size;
    int mines;
    int flags;
    std::vector<std::vector<char>> board;
    std::vector<std::vector<bool>> revealed;


    MineSweeper(int size, int mines, int flags) : size(size), mines(mines), flags(mines) {
        initializeBoard();
        placeMines();
        initializeRevealed();
    }

    void initializeBoard() {
        board.resize(size, std::vector<char>(size, 'c'));
    }

    void placeMines() {
        std::srand(std::time(0));
        for (int i = 0; i < mines; ++i) {
            int row = std::rand() % size;
            int col = std::rand() % size;
            while (board[row][col] == 'M') {
                row = std::rand() % size;
                col = std::rand() % size;
            }
            board[row][col] = 'M';
        }
    }

    void initializeRevealed() {
        revealed.resize(size, std::vector<bool>(size, false));
    }

    void displayBoard() {
        std::cout << "  ";
        for (int i = 0; i < size; ++i) {
            std::cout << char('A' + i) << " ";
        }
        std::cout << std::endl;

        for (int i = 0; i < size; ++i) {
            std::cout << char('A' + i) << " ";
            for (int j = 0; j < size; ++j) {
                if (revealed[i][j]) {
                    std::cout << board[i][j] << " ";
                }
                else {
                    std::cout << 'c' << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void revealLocation(int row, int col) {
        if (revealed[row][col]) {
            std::cout << "Location already revealed." << std::endl;
            return;
        }

        revealed[row][col] = true;

        if (board[row][col] == 'M') {
            gameOver();
            return;
        }
        else {
            board[row][col] = char('0' + countMinesAround(row, col));
        }
    }

    void flagLocation(int row, int col) {
        if (flags > 0 && board[row][col] == 'c') {
            board[row][col] = 'F';
            flags--;
        }
        else {
            std::cout << "Invalid flagging operation. Check if the location is covered and you have available flags." << std::endl;
        }
    }

    int countMinesAround(int row, int col) {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i;
                int newCol = col + j;

                if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
                    if (board[newRow][newCol] == 'M') {
                        count++;
                    }
                }
            }
        }
        return count;
    }

    void gameOver() {
        std::cout << "Game Over! Mines were at the following locations:" << std::endl;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == 'M') {
                    std::cout << char('A' + i) << char('A' + j) << " ";
                }
            }
        }

        std::cout << std::endl;

        std::cout << "Press any key to exit..." << std::endl;
        char dummy;
        std::cin >> dummy; // Wait for user input

        exit(0); // Close the program
    }


    void resetGame() {
        flags = mines;
        initializeBoard();
        placeMines();
        initializeRevealed();
        std::cout << "Choose a field size:" << std::endl;
    }
};

int main() {
    MineSweeper game(0, 0,0);  // Create an initial game instance

    while (true) {
        int choice;
        std::cout << "1. 10-by-10 (12 mines)" << std::endl;
        std::cout << "2. 15-by-15 (18 mines)" << std::endl;
        std::cout << "3. 20-by-20 (24 mines)" << std::endl;
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

       
        int size, mines, flags;

        switch (choice) {
        case 1:
            size = 10;
            mines = 12;
            flags = 12;
            break;
        case 2:
            size = 15;
            mines = 18;
            flags = 18;
            break;
        case 3:
            size = 20;
            mines = 24;
            flags = 24;

            break;
        default:
            std::cerr << "Invalid choice. Exiting." << std::endl;
            return 1;
        }

        game = MineSweeper(size, mines, flags);

        game.displayBoard();

        while (true) {
            char move[3];
            std::cout << "\nEnter your move (e.g., A1R or ABF): ";
            std::cin >> move;

            if (move[2] == 'R') {
                game.revealLocation(move[0] - 'A', move[1] - 'A');
            }
            else if (move[2] == 'F') {
                game.flagLocation(move[0] - 'A', move[1] - 'A');
            }
            else {
                std::cout << "Invalid command. Please enter 'R' for reveal or 'F' for flag." << std::endl;
                continue;
            }

            game.displayBoard();
        }
    }

    return 0;
}
