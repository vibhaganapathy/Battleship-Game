/**
 * Copyright 2025 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;

void test_position();
void test_ship();
void test_player();
void test_project_setup();
void test_game();
void fileCheck();
void testDefaultConstructor();
void testNonDefaultConstructor1();
void testNonDefaultConstructor2();


void startTests() {
    test_project_setup();
    test_position();
    test_ship();
    test_player();
    test_game();
    fileCheck();
    testDefaultConstructor();
    testNonDefaultConstructor1();
    testNonDefaultConstructor2();
    
    return;
}

void test_position() {
    Position start_pos;
    Position end_pos;
    
    start_pos.set_row(4);
    start_pos.set_col(5);
    cout << "\nTesting Position::set_row() and Position::set_col()\n";
    cout << "start_pos, expected output: (5,F) actual output: " << start_pos << endl;
    
    ifstream input_file;
    input_file.open("grid1.txt");
    if (input_file.good()) {

        start_pos.read(input_file);

        input_file >> end_pos;

        cout << "\nTesting Position::read()\n";
        cout << "start_pos, expected output: (8,B) actual output: " << start_pos << endl;
        cout << "end_pos, expected output: (8,C) actual output: " << end_pos << endl;
    }
    else {
        cout << "\nError opening grid1.txt\n";
    }
  
    return;
}

void test_ship() {
    cout << "\nTesting ship()\n";
    cout << "\nTesting ship() default constructor\n";
    Ship ship1;
    cout << "Expected: (1, A), Actual: " << ship1.get_start() << endl;
    cout << "Expected: (1, A), Actual: " << ship1.get_end() << endl;
    cout << "Expected: 0, Actual: " << ship1.get_size() << endl;
    cout << "Expected: 1, Actual: " << ship1.is_horizontal() << endl;
    cout << "Expected: 0, Actual: " << ship1.has_position(Position(4, 5)) << endl;
    ship1.hit();
    cout << "Expected: 1, Actual: " << ship1.has_sunk() << endl;
    cout << endl;
    cout << "\nTesting ship() nondefault constructor\n";
    Ship ship2(Position(3, 3), Position(4, 3));
    cout << "Expected: (4, D), Actual: " << ship2.get_start() << endl;
    cout << "Expected: (5, D), Actual: " << ship2.get_end() << endl;
    cout << "Expected: 2, Actual: " << ship2.get_size() << endl;
    cout << "Expected: 0, Actual: " << ship2.is_horizontal() << endl;
    cout << "Expected: 0, Actual: " << ship2.has_position(Position(4, 5)) << endl;
    ship2.hit();
    cout << "Expected: 0, Actual: " << ship2.has_sunk() << endl;
    
    cout << "\nTesting get_start()\n";
    Ship ship3(Position(4, 7), Position(5, 7));
    Ship ship4(Position(2, 2), Position(2, 6));
    cout << "Expected: (5, H), Actual: " << ship3.get_start() << endl;
    cout << "Expected: (3, D), Actual: " << ship4.get_start() << endl;
    cout << endl;
    
    cout << "\nTesting get_end()\n";
    cout << "Expected: (6, H), Actual: " << ship3.get_end() << endl;
    cout << "Expected: (3, G), Actual: " << ship4.get_end() << endl;
    cout << endl;
    
    cout << "\nTesting get_size()\n";
    cout << "Expected: 2, Actual: " << ship3.get_size() << endl;
    cout << "Expected: 5, Actual: " << ship4.get_size() << endl;
    cout << endl;
    
    cout << "\nTesting is_horizontal()\n";
    cout << "Expected: 0, Actual: " << ship3.is_horizontal() << endl;
    cout << "Expected: 1, Actual: " << ship4.is_horizontal() << endl;
    cout << endl;
    
    cout << "\nTesting has_position(Position pos)\n";
    Ship horiz1(Position(2,1), Position(2,4));
    cout << horiz1.has_position(Position(2,1)) << endl;
    cout << horiz1.has_position(Position(2,4)) << endl;
    cout << horiz1.has_position(Position(2,2)) << endl;
    cout << horiz1.has_position(Position(1,2)) << endl;
    cout << horiz1.has_position(Position(2,5)) << endl;
    Ship horiz2(Position(5,6), Position(5,3));
    cout << horiz2.has_position(Position(5,3)) << endl;
    cout << horiz2.has_position(Position(5,6)) << endl;
    cout << horiz2.has_position(Position(5,4)) << endl;
    cout << horiz2.has_position(Position(4,4)) << endl;
    Ship vert1(Position(1,5), Position(4,5));
    cout << vert1.has_position(Position(1,5)) << endl;
    cout << vert1.has_position(Position(4,5)) << endl;
    cout << vert1.has_position(Position(2,5)) << endl;
    cout << vert1.has_position(Position(2,4)) << endl;
    Ship vert2(Position(6,2), Position(3,2));
    cout << vert2.has_position(Position(5,2)) << endl;
    cout << vert2.has_position(Position(2,2)) << endl;
    cout << endl;
    
    cout << "\nTesting has_sunk()\n";
    cout << ship3.has_sunk() << endl;
    cout << ship4.has_sunk() << endl;
    cout << endl;
    
    return;
}

void test_player() {
    cout << "\nTesting Player()\n";
    Player player1;
    Player player2;

    Player player3("Vibha");
    Player player4("Bob");
    
    cout << "\n Testing get_name \n";
    cout << player1.get_name() << endl;
    cout << player2.get_name() << endl;
    cout << player3.get_name() << endl;
    cout << player4.get_name() << endl;
    cout << endl;
    
    cout << "\n Testing get_num_ships() \n";
    cout << player1.get_num_ships() << endl;
    cout << player2.get_num_ships() << endl;
    cout << player3.get_num_ships() << endl;
    cout << player4.get_num_ships() << endl;
    
    cout << "\n Testing get_remaining_ships() \n";
    cout << player1.get_remaining_ships() << endl;
    cout << player2.get_remaining_ships() << endl;
    cout << player3.get_remaining_ships() << endl;
    cout << player4.get_remaining_ships() << endl;
    
    cout << "\n Testing get_grid_at(Position pos) \n";
    cout << player1.get_grid_at(3, 5) << endl;
    cout << player2.get_grid_at(5, 7) << endl;
    cout << player3.get_grid_at(2, 2) << endl;
    cout << player4.get_grid_at(1, 7) << endl;
    
    cout << "\n Testing get_guess_grid_at(Position pos) \n";
    cout << player1.get_guess_grid_at(2, 6) << endl;
    cout << player2.get_guess_grid_at(5, 5) << endl;
    cout << player3.get_guess_grid_at(3, 3) << endl;
    cout << player4.get_guess_grid_at(1, 7) << endl;
    
    Position start;
    Position end;
    Position start1(0, 0);
    Position end1(0, 2);
    Position start2('1', 'A');
    Position end2('3', 'A');
    
    cout << "\n Testing add_ship()\n\n";
    player1.add_ship(Ship());
    player1.print_grid();
    Ship s1(Position(0, 0), Position(0, 1));
    player2.add_ship(s1);
    player1.add_ship(Ship(start, end2));
    player1.print_grid();
    player2.add_ship(Ship(start2, end));
    player2.print_grid();
    player3.add_ship(Ship(start1, end1));
    player3.print_grid();
    player3.add_ship(Ship(start2, end2));
    player3.print_grid();
    player4.add_ship(Ship(start, end2));
    player4.print_grid();
    cout << endl;
    
    cout << "\nTesting attack 1 \n";
    Player defender("P2");
    defender.add_ship(Ship(Position(0,0), Position(0,1)));
    cout << "Before attack, remaining ships: " << defender.get_remaining_ships() << endl;
    Player attacker("P1");
    attacker.attack(defender, Position(0,0));
    cout << "After 1st hit, remaining ships: " << defender.get_remaining_ships() << endl;
    attacker.attack(defender, Position(0,1));
    cout << "After 2nd hit, remaining ships: " << defender.get_remaining_ships() << endl;
    cout << "\nGrids after sinking one ship:\n";
    cout << "P1 guess grid:\n";
    attacker.print_guess_grid();
    cout << "P2 actual grid:\n";
    defender.print_grid();

    cout << "\nTesting attack 2 (duplicate shot same cell)\n";
    Player other("Bob");
    other.add_ship(Ship(Position(1,0), Position(1,1)));
    Player you("Vibha");
    cout << "Before attack, Bob remaining: " << other.get_remaining_ships() << endl;
    you.attack(other, Position(1,0));
    cout << "After 1st hit, Bob remaining: " << other.get_remaining_ships() << endl;
    you.attack(other, Position(1,0));
    cout << "After duplicate hit, Bob remaining: " << other.get_remaining_ships() << endl;
    cout << "Vibha's guess grid:\n";
    you.print_guess_grid();
    cout << "Bob's actual grid:\n";
    other.print_grid();

    return;
    
}

void test_game() {
    Game game;
    
    Player p1;
    Player p2;
    Player p3("Vibha");
    Player p4("Bob");
    
    string empty = "";
    string valid = "8a";
    string invalid = "90210";
    
    Game game1(p1, empty, p2, valid);
    Game game2(p1, empty, p2, invalid);
    Game game3(p1, invalid, p2, valid);
    Game game4(p3, empty, p2, valid);
    Game game5(p3, empty, p4, empty);
    
    cout << "\n Testing get_p1() and get_p2()\n";
    Game g(p3, "grid1.txt", p4, "grid2.txt");
    cout << "Expected: " << p3.get_name() << ", Actual: "  << g.get_p1().get_name() << endl;
    cout << "Expected: " << p4.get_name() << ", Actual: "  << g.get_p2().get_name() << endl;

    cout << "\n Testing get_move('player_name')\n";
    cout << "Expected: Vibha, enter your move: , Actual: " << game1.get_move("Vibha") << endl;
    cout << endl;
    
    cout << "\n Testing check_valid_move()\n";
    game1.check_valid_move("abcdef");
    game2.check_valid_move("1a");
    game1.check_valid_move("3a");
    
    return;
}

void test_project_setup() {
    // open file to verify setup
    ifstream ins;
    ins.open("grid1.txt");

    // check for fail state
    if (ins.fail()) {
        cout << "Project was not created correctly." << endl;
        cout << "Text files are not in the correct folder." << endl;
        cout << "Check the project specification "
            << "for how to set up your project." << endl;
    }
    else {
        cout << "Project set up correctly, file opened." << endl;
    }

    return;
}


void fileCheck() {
    ifstream ins;
    ins.open("grid1.txt");
    
    if (ins.fail()) {
        cout << "Could not open grid1.txt" << endl;
        
        ofstream outs;
        outs.open("crazyfilename");
        outs << "find the file named crazyfilename in windows explorer or finder";
        outs.close();
    }
    else {
        cout << "Success! Text files are in the right directory." << endl;
    }
    ins.close();
}

void testDefaultConstructor() {
    Position p;

    cout << "Expected: (1,A)  Actual: " << p << endl;

    if (p.get_row() != 0 || p.get_col() != 0)
        cout << "Default constructor has failed.\n";
    else
        cout << "Default constructor is correct.\n";
}

void testNonDefaultConstructor1() {
    Position p1(4, 2);
    cout << "Input: (4,2)  Expected: (5,C)  Actual: " << p1 << endl;

    Position p2(-3, -1);
    cout << "Input: (-3,-1)  Expected: (1,A)  Actual: " << p2 << endl;

    Position p3(20, 15);
    cout << "Input: (20,15)  Expected: (8,H)  Actual: " << p3 << endl;

    if (p1.get_row() == 4 && p1.get_col() == 2 && p2.get_row() == 0 &&
        p2.get_col() == 0 && p3.get_row() == 7 && p3.get_col() == 7)
        cout << "\nNon-default constructor correct.\n";
    else
        cout << "\nNon-default constructor incorrect.\n";
}

void testNonDefaultConstructor2() {
    Position p1('3', 'B');
    cout << "Input: ('3','B')  Expected: (3,B)  Actual: " << p1 << endl;

    Position p2('4', 'c');
    cout << "Input: ('4','c')  Expected: (4,C)  Actual: " << p2 << endl;

    Position p3('9', 'Z');
    cout << "Input: ('9','Z')  Expected: (8,H)  Actual: " << p3 << endl;

    if (p1.get_row() == 2 && p1.get_col() == 1 && p2.get_row() == 3 &&
        p2.get_col() == 2 && p3.get_row() == 7 && p3.get_col() == 7)
        cout << "\nNon-default constructor correct.\n";
    else
        cout << "\nNon-default constructor incorrect.\n";
}
