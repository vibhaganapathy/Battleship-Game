/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Vibha Ganapathy
 * vibhagan
 *
 * Project 4: Battleship
 *
 * Game represents the gameplay of the Battleship game
 */

#include <fstream>

#include "Game.h"


Game::Game() {
    p1 = Player();
    p2 = Player();
}

Game::Game(Player player1, string grid1, Player player2, string grid2) {
    p1 = player1;
    p2 = player2;
    bool win1 = false;
    bool win2 = false;
    if (grid1 != "") {
        win1 = p1.load_grid_file(grid1);
    }
    if (grid1 == "" || !win1) {
        cout << "Generating random grid for " << p1.get_name() << endl;
        generate_random_grid(p1);
    }
    if (grid2 != "") {
        win2 = p2.load_grid_file(grid2);
    }
    if (grid2 == "" || !win2) {
        cout << "Generating random grid for " << p2.get_name() << endl;
        generate_random_grid(p2);
    }
}

Player Game::get_p1() {
    return p1;
}

Player Game::get_p2() {
    return p2;
}

string Game::get_move(string player_name) {
    string move;
    cout << player_name << " enter your move: " << endl;
    cin >> move;
    cout << endl;
    return move;
}

bool Game::check_valid_move(string move) {
    string row_nums = "12345678";
    string col_letters = "ABCDEFGH";
    
    bool valid1 = false;
    bool valid2 = false;
    
    if (move.length() != 2) {
        cout << p1.get_name() << " you entered an invalid input" << endl;
        return false;
    }
    else {
        int b;
        for (b = 0; b < 8; ++b) {
            if (move.at(0) == row_nums.at(b)) {
                valid1 = true;
            }
        }
        int c;
        for (c = 0; c < 8; ++c) {
            if (toupper(move.at(1)) == col_letters.at(c)) {
                valid2 = true;
            }
        }
        if (!valid1 || !valid2) {
            cout << p1.get_name() << " you entered an invalid position" << endl;
            return false;
        }
    }
    return true;
}

void Game::start(char difficulty, int max_num_rounds) {
    int rounds = 0;

    while (rounds < max_num_rounds && !p1.destroyed() && !p2.destroyed()) {
        string move = get_move(p1.get_name());
        while (!check_valid_move(move)) {
            move = get_move(p1.get_name());
        }
        Position attack(move[0], move[1]);
        p1.attack(p2, attack);
        
        if (!p2.destroyed()) {
            opponent_make_move(difficulty);
        }
        
        cout << "\n\nYour grid\n";
        p1.print_grid();
        cout << p2.get_name() << "'s grid\n";
        p1.print_guess_grid();
        
        ++rounds;
    }

    string winner = "no one";
    if (p1.destroyed() && !p2.destroyed()) {
        winner = p2.get_name();
    }
    else if (p2.destroyed() && !p1.destroyed()) {
        winner = p1.get_name();
    }
    cout << "\nGame over, winner is " << winner << " in " << rounds << " rounds" << endl;

}

// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

