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
                = {{"U", "S", "E", "N", "S", "S"}, {"U", "O", "T", "O", "N", "W"}, {"P", "C", "E", "I", "T", "S"}, {"M", "T", "E", "T", "T", "O"}, {"G", "E", "W", "N", "E", "H"}, {"E", "C", "C", "N", "S", "T"}, {"E", "E", "E", "E", "A", "A"},
                   {"D", "N", "O", "W", "H", "H"}, {"N", "M", "E", "N", "A", "G"}, {"A", "E", "M", "E", "E", "E"}, {"E", "M", "G", "A", "U", "E"}, {"R", "L", "H", "N", "D", "O"}, {"R", "I", "S", "P", "Y", "Y"}, {"F", "S", "I", "R", "A", "A"},
                   {"N", "N", "E", "N", "A", "D"}, {"O", "O", "O", "T", "U", "T"}, {"L", "O", "H", "D", "R", "H"}, {"E", "L", "P", "T", "S", "I"}, {"S", "E", "I", "I", "L", "T"}, {"K", "S", "F", "F", "A", "P"}, {"H", "N", "T", "D", "O", "D"},
                   {"W", "R", "O", "G", "R", "V"}, {"B", "X", "J", "K", "Z", "B"}, {"R", "A", "S", "A", "F", "A"}, {"I", "A", "H", "E", "T", "Q"}};

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
            char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

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