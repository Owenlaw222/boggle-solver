#include "interface/main_interface.hpp"

#include <cstring>
#include <iostream>


int main(int argc, char* argv[])
{
    Board board(5);
    Main_Interface main_interface(&argc, &argv, &board);

    return 0;
}