#include "solver.hpp"

#include <fstream>
#include <iostream>


Solver::Solver(std::shared_ptr<Board> board_ptr, std::string word_list_path, unsigned int min_word_length, unsigned int max_word_length)
    : m_board_ptr(board_ptr), m_word_list_path(word_list_path), m_min_word_length(min_word_length), m_max_word_length(max_word_length)
{
    Load_Word_List();

    for (unsigned int x = 0; x < m_board_ptr->Get_Board_Size(); x++)
    {
        for (unsigned int y = 0; y < m_board_ptr->Get_Board_Size(); y++)
        {
            Solve_From_Cell(x, y);
        }
    }
}

void Solver::Load_Word_List()
{
    m_word_list.clear();

    std::fstream file(m_word_list_path, std::ios::in);

    if (file.is_open())
    {
        std::string current_line;

        while (getline(file, current_line))
        {
            m_word_list.insert(current_line);
        }

        file.close();
    }
    else
    {
        std::cerr << "Failed to open word list file";
        exit(EXIT_FAILURE);
    }
}

void Solver::Solve_From_Cell(unsigned int cell_x, unsigned int cell_y)
{
    std::pair<int, int> offsets[8] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    std::string current_word = m_board_ptr->Get_Board_Cell(cell_x, cell_y);
    std::vector<unsigned int> direction_stack = {0};
    std::vector<std::vector<bool>> cells_visited(m_board_ptr->Get_Board_Size(), std::vector<bool>(m_board_ptr->Get_Board_Size(), false));

    int current_x = cell_x;
    int current_y = cell_y;

    while (direction_stack.size() != 0 && direction_stack[0] != 8)
    {
        if (direction_stack.size() == m_max_word_length || direction_stack.back() == 8)
        {
            cells_visited[current_x][current_y] = false;

            direction_stack.pop_back();
            current_word.pop_back();

            current_x -= offsets[direction_stack.back()].first;
            current_y -= offsets[direction_stack.back()].second;

            direction_stack.back()++;

            continue;
        }

        int temp_x = current_x + offsets[direction_stack.back()].first;
        int temp_y = current_y + offsets[direction_stack.back()].second;

        if (temp_x < 0 || temp_y < 0 || temp_x > m_board_ptr->Get_Board_Size() - 1 || temp_y > m_board_ptr->Get_Board_Size() - 1 || cells_visited[temp_x][temp_y])
        {
            direction_stack.back()++;

            continue;
        }

        cells_visited[current_x][current_y] = true;

        current_x = temp_x;
        current_y = temp_y;

        direction_stack.push_back(0);
        current_word.push_back(*m_board_ptr->Get_Board_Cell(current_x, current_y).c_str());

        if (current_word.length() >= m_min_word_length && m_word_list.find(current_word) != m_word_list.end() && m_found_words.find(current_word) == m_found_words.end())
        {
            m_found_words.insert(current_word);

            std::vector<std::pair<unsigned int, unsigned int>> path = {{cell_x, cell_y}};
            for (unsigned int i = 0; i < direction_stack.size() - 1; i++)
            {
                path.push_back({path.back().first + offsets[direction_stack[i]].first, path.back().second + offsets[direction_stack[i]].second});
            }

            m_solutions.push_back({current_word, path});
        }
    }
}

std::vector<std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>> Solver::Get_Solutions()
{
    return m_solutions;
}