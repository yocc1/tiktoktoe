#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Display the game board
void displayBoard(const vector<char>& board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << board[i] << " ";
        if ((i + 1) % 3 == 0 && i != 8)
            cout << "\n---|---|---\n";
        else if (i != 8)
            cout << "|";
    }
    cout << "\n\n";
}

// Check for a winner or a draw
bool checkWinner(const vector<char>& board, char currentPlayer) {
    // Winning combinations
    int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };
    for (auto& combo : winCombos) {
        if (board[combo[0]] == currentPlayer && board[combo[1]] == currentPlayer && board[combo[2]] == currentPlayer)
            return true;
    }
    return false;
}

bool isDraw(const vector<char>& board) {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') return false;
    }
    return true;
}

// Get and validate user input
int getUserInput(const vector<char>& board) {
    int position;
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> position;
        if (cin.fail() || position < 1 || position > 9 || board[position - 1] == 'X' || board[position - 1] == 'O') {
            cout << "Invalid input. Please try again.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        } else {
            break;
        }
    }
    return position - 1;
}

// Main game loop
void playGame() {
    vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char currentPlayer = 'X';
    bool gameRunning = true;

    while (gameRunning) {
        displayBoard(board);
        cout << "Player " << currentPlayer << "'s turn.\n";
        
        int move = getUserInput(board);
        board[move] = currentPlayer;

        if (checkWinner(board, currentPlayer)) {
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            gameRunning = false;
        } else if (isDraw(board)) {
            displayBoard(board);
            cout << "It's a draw!\n";
            gameRunning = false;
        } else {
            // Switch players
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    char playAgain;
    do {
        cout << "Welcome to Tic-Tac-Toe!\n";
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    cout << "Thanks for playing!\n";
    return 0;
}
