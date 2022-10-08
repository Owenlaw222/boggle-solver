#include "interface/main_interface.hpp"

#include <cstring>
#include <iostream>


int main(int argc, char* argv[])
{
    Board board(5);
    Solver solver(&board, "../words/collins-scrabble-words-2019.txt", 3, 100);
    Main_Interface main_interface(&argc, &argv, &board);

    return 0;
}