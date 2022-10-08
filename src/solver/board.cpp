#include "board.hpp"

#include <algorithm>
#include <array>
#include <iostream>


Board::Board(unsigned int size) : m_board_size(size)
{
    srand(time(NULL));

    m_cell_values.clear();

    m_cell_values.resize(size);

    for (unsigned int i = 0; i < size; i++)
    {
        m_cell_values[i].resize(size);

        for (unsigned int j = 0; j < size; j++)
        {
            m_cell_values[i][j] = "\0";
        }
    }
}

void Board::Randomize()
{
    switch (m_board_size)
    {
        case 5:
        {
            std::vector<std::array<std::string, 6>> die
                = {{"A", "A", "A", "F", "R", "S"}, {"A", "A", "E", "E", "E", "E"}, {"A", "A", "F", "I", "R", "S"}, {"A", "D", "E", "N", "N", "N"}, {"A", "E", "E", "E", "E", "M"}, {"A", "E", "E", "G", "M", "U"}, {"A", "E", "G", "M", "N", "N"},
                   {"A", "F", "I", "R", "S", "Y"}, {"B", "B", "J", "K", "X", "Z"}, {"C", "C", "E", "N", "S", "T"}, {"E", "I", "I", "L", "S", "T"}, {"C", "E", "I", "P", "S", "T"}, {"D", "D", "H", "N", "O", "T"}, {"D", "H", "H", "L", "O", "R"},
                   {"D", "H", "H", "N", "O", "W"}, {"D", "H", "L", "N", "O", "R"}, {"E", "I", "I", "I", "T", "T"}, {"E", "I", "L", "P", "S", "T"}, {"E", "M", "O", "T", "T", "T"}, {"E", "N", "S", "S", "S", "U"}, {"1", "2", "3", "4", "5", "6"},
                   {"G", "O", "R", "R", "V", "W"}, {"I", "P", "R", "S", "Y", "Y"}, {"N", "O", "O", "T", "U", "W"}, {"O", "O", "O", "T", "T", "U"}};

            std::random_shuffle(die.begin(), die.end());

            for (unsigned int i = 0; i < m_board_size; i++)
            {
                for (unsigned int j = 0; j < m_board_size; j++)
                {
                    m_cell_values[i][j] = die[i * 5 + j][rand() % 6];
                }
            }
            break;
        }
        default:
        {
            char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1'};

            for (unsigned int i = 0; i < m_board_size; i++)
            {
                for (unsigned int j = 0; j < m_board_size; j++)
                {
                    m_cell_values[i][j] = letters[rand() % 26];
                }
            }

            break;
        }
    }
}

void Board::Set_Board_Cell(unsigned int x, unsigned int y, std::string value)
{
    m_cell_values[x][y] = value;
}

unsigned int Board::Get_Board_Size()
{
    return m_board_size;
}

bool Board::All_Cells_Entered()
{
    bool all_cells_entered = true;

    for (unsigned int x = 0; x < m_board_size; x++)
    {
        for (unsigned int y = 0; y < m_board_size; y++)
        {
            if (m_cell_values[x][y] == "\0")
            {
                all_cells_entered = false;
            }
        }
    }

    return all_cells_entered;
}

std::string Board::Get_Board_Cell(unsigned int x, unsigned int y)
{
    if (x < m_board_size && y < m_board_size)
    {
        return m_cell_values[x][y];
    }
    else
    {
        std::cerr << "Cannot access cell outside of bounds";
        exit(EXIT_FAILURE);
    }
}