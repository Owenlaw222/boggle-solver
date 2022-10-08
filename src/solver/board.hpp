#pragma once

#include <string>
#include <vector>


class Board
{
private:
    unsigned int m_board_size;

private:
    std::vector<std::vector<std::string>> m_cell_values;

public:
    Board(unsigned int size);

public:
    void Randomize();
    void Set_Board_Cell(unsigned int x, unsigned int y, std::string value);

    unsigned int Get_Board_Size();
    bool All_Cells_Entered();
    std::string Get_Board_Cell(unsigned int x, unsigned int y);
};