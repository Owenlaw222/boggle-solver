#pragma once


#include "board.hpp"

#include <memory>
#include <ncurses.h>
#include <string>

class Interface
{
private:
    std::shared_ptr<Board> m_board_ptr;

private:
    void Draw_Board(unsigned int board_x, unsigned int board_y);
    void Draw_Board_Path(unsigned int board_x, unsigned int board_y, std::vector<std::pair<unsigned int, unsigned int>> path);

public:
    Interface(std::shared_ptr<Board> board_ptr);
    ~Interface();

public:
    void Get_User_Board_Input(unsigned int x, unsigned int y);
    void Main_Interface(std::vector<std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>> solutions);
    void Close();
};