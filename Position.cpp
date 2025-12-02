/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Vibha Ganapathy
 * vibhagan
 *
 * Project 4: Battleship
 *
 * Position function for the Battleship Game
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    row = 0;
    col = 0;
}

Position::Position(int row_in, int col_in) {
    row = check_range(row_in);
    col = check_range(col_in);
}

Position::Position(char row_in, char col_in) {
    int r = 0;
    if (row_in >= '1' && row_in <= ('0' + MAX_GRID_SIZE)) {
        r = (row_in - '1');
    }
    int c = toupper(col_in) - 'A';
    row = check_range(r);
    col = check_range(c);
}

int Position::get_row() {
    return row;
}

void Position::set_row(int row_in) {
    row = check_range(row_in);
    return;
}

int Position::get_col() {
    return col;
}

void Position::set_col(int col_in) {
    col = check_range(col_in);
    return;
}

void Position::write(ostream &os) {
    os << '(' << (row + 1) << ',' << char('A' + col) << ')';
    return;
}

int Position::check_range(int val) {
    if (val < 0) {
        return 0;
    }
    if (val >= MAX_GRID_SIZE) {
        return MAX_GRID_SIZE - 1;
    }
    return val;
}

void Position::read(istream& is) {
    char trash = 't';
    int row_in = 0;
    char col_in = 'c';

    is >> row_in >> col_in;

    if (is.fail()) {
        is.clear();
        is >> trash >> row_in >> trash >> col_in >> trash;
    }

    int row1 = row_in - 1;
    int col1 = toupper(col_in) - 'A';

    row = check_range(row1);
    col = check_range(col1);


    return;
}

// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}

