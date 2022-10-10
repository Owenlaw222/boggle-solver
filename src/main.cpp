#include "interface/main_interface.hpp"

#include <cstring>
#include <iostream>

int main(int argc, char* argv[])
{
    Board* board_ptr = new Board(4);
    Main_Interface main_interface(&argc, &argv, &board_ptr);

    free(board_ptr);

    return 0;
}