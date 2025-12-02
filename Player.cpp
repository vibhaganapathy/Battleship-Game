/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Vibha Ganapathy
 * vibhagan
 *
 * Project 4: Battleship
 *
 * Player represents a player in the Battleship game
 */

#include <fstream>

#include "Player.h"


Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

void Player::init_grid() {
    int i;
    for (i = 0; i < MAX_GRID_SIZE; ++i) {
        int x;
        for(x = 0; x < MAX_GRID_SIZE; ++x) {
            grid[i][x] = EMPTY_LETTER;
            guess_grid[i][x] = EMPTY_LETTER;
        }
    }
    return;
}

string Player::get_name() {
    return name;
}

int Player::get_num_ships() {
    return num_ships;
}

int Player::get_remaining_ships() {
    return remaining_ships;
}

char Player::get_grid_at(int row, int col) {
    return grid[row][col];
}

char Player::get_guess_grid_at(int row, int col) {
    return guess_grid[row][col];
}

void Player::add_ship(Ship ship) {
    if (num_ships == MAX_NUM_SHIPS) {
        return;
    }
    
    ships[num_ships] = ship;
    num_ships += 1;
    remaining_ships += 1;
    
    Position start = ship.get_start();
    Position middle;
    Position end = ship.get_end();
    
    grid[start.get_row()][start.get_col()] = SHIP_LETTER;
    grid[end.get_row()][end.get_col()] = SHIP_LETTER;
    
    if (ship.is_horizontal()) {
        middle.set_row(start.get_row());
        int i;
        for (i = 0; i < MAX_GRID_SIZE; ++i) {
            middle.set_col(i);
            if (ship.has_position(middle)) {
                grid[middle.get_row()][middle.get_col()] = SHIP_LETTER;
            }
        }
    }
    else {
        middle.set_col(start.get_col());
        int j;
        for (j = 0; j < MAX_GRID_SIZE; ++j) {
            middle.set_row(j);
            if (ship.has_position(middle)) {
                grid[middle.get_row()][middle.get_col()] = SHIP_LETTER;
            }
        }
    }
    return;
}

void Player::attack(Player &opponent, Position pos) {
    int row = pos.get_row();
    int col = pos.get_col();
    
    char grid1 = opponent.get_grid_at(row, col);
    if (grid1 == SHIP_LETTER) {
        int g;
        for (g = 0; g < opponent.num_ships; ++g) {
            if (opponent.ships[g].has_position(pos)) {
                opponent.ships[g].hit();
                opponent.grid[row][col] = HIT_LETTER;
                guess_grid[row][col] = HIT_LETTER;
                cout << name << " " << pos << " hit" << endl;
                
                if (opponent.ships[g].has_sunk()) {
                    opponent.remaining_ships -= 1;
                    announce_ship_sunk(opponent.ships[g].get_size());
                }
            }
        }
    }
    if (grid1 == EMPTY_LETTER || grid1 == MISS_LETTER) {
        opponent.grid[row][col] = MISS_LETTER;
        guess_grid[row][col] = MISS_LETTER;
        cout << name << " " << pos << " miss" << endl;
    }
    return;
}

void Player::announce_ship_sunk(int size) {
    string type;
    
    string types[] = {"Destroyer", "Submarine", "Battleship", "Carrier"};
    int h;
    for (h = 0; h < 4; ++h) {
        if (h == size - 2) {
            type = types[h];
        }
    }
    
    cout << "Congratulations " << name << "! You sunk a " << type << endl;
    return;
}

bool Player::load_grid_file(string filename) {
    ifstream infile;
    infile.open(filename);
    
    Position start;
    Position end;
    
    if (infile.fail()) {
        return false;
    }
    while (infile >> start >> end) {
        add_ship(Ship(start, end));
    }
    return true;
}

bool Player::destroyed() {
    if (remaining_ships == 0) {
        return true;
    }
    return false;
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_guess_grid() {
    ::print_grid(guess_grid);
}
