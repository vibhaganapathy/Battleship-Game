/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Vibha Ganapathy
 * vibhagan
 *
 * Project 4: Battleship
 *
 * Ship fucntion for the Battleship game
 */

#include <cmath>

#include "Ship.h"


Ship::Ship() {
    start.set_row(0);
    start.set_col(0);
    end.set_row(0);
    end.set_col(0);
    size = 0;
    num_hits = 0;
}

Ship::Ship(Position start_in, Position end_in) {
    start = start_in;
    end = end_in;
    num_hits = 0;
    
    if (is_horizontal()) {
        size = abs(start.get_col() - end.get_col()) + 1;
    }
    else {
        size = abs(start.get_row() - end.get_row()) + 1;
    }
}

Position Ship::get_start() {
    return start;
}

Position Ship::get_end() {
    return end;
}

int Ship::get_size() {
    return size;
}

bool Ship::is_horizontal() {
    if (start.get_row() != end.get_row()) {
        if (start.get_col() == end.get_col()) {
            return false;
        }
    }
    return true;
}

bool Ship::has_position(Position pos) {
    int pos_row = pos.get_row();
    int pos_col = pos.get_col();
    int start_row = start.get_row();
    int start_col = start.get_col();
    int end_row = end.get_row();
    int end_col = end.get_col();
    
    if (is_horizontal() && start_row == pos_row) {
        if (start_col <= end_col) {
            if (pos_col >= start_col && pos_col <= end_col) {
                return true;
            }
            else {
                return false;
            }
            }
        else if (start_col >= end_col) {
            if (pos_col >= end_col && pos_col <= start_col) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    else if (!is_horizontal() && start_col == pos_col) {
        if (start_row <= end_row) {
            if (pos_row >= start_row && pos_row <= end_row) {
                return true;
            }
            else {
                return false;
            }
            }
        else if (start_row >= end_row) {
            if (pos_row >= end_row && pos_row <= start_row) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

void Ship::hit() {
    if (num_hits < size) {
        num_hits += 1;
    }
    return;
}

bool Ship::has_sunk() {
    return num_hits == size;
}
