#include "interface.hpp"
#include "solver.hpp"


int main()
{
    std::shared_ptr<Board> board_ptr = std::make_shared<Board>(5);
    board_ptr->Randomize();

    Interface interface = Interface(board_ptr);
    //  interface.Get_User_Board_Input(0, 0);

    Solver solver(board_ptr, "../words/collins-scrabble-words-2019.txt", 3, 25);
    interface.Main_Interface(solver.Get_Solutions());

    return 0;
}