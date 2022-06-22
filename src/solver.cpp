#include "solver.hpp"

#include <cmath>
#include <fstream>
#include <iostream>


Solver::Solver(std::shared_ptr<Board> board_ptr, std::string word_list_path, int min_word_length, int max_word_length) : m_board_ptr(board_ptr), m_word_list_path(word_list_path), m_min_word_length(min_word_length), m_max_word_length(max_word_length)
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
            m_word_list.push_back(current_line);
        }

        file.close();
    }
    else
    {
        std::cerr << "Failed to open word list file";
        exit(EXIT_FAILURE);
    }
}

std::pair<int, int> Solver::Find_Range(std::pair<int, int> previous_range, char character_to_compare, unsigned int character_index)
{
    std::pair<int, int> range = {-1, -1};

    int low_index = previous_range.first;
    int high_index = previous_range.second;
    while (low_index <= high_index)
    {
        int middle = std::floor((high_index + low_index) / 2.0);

        if (character_index >= m_word_list[middle].size() || character_to_compare > m_word_list[middle].at(character_index))
        {
            low_index = middle + 1;
            continue;
        }
        else if (character_to_compare < m_word_list[middle].at(character_index))
        {
            high_index = middle - 1;
            continue;
        }
        else if (low_index != middle)
        {
            high_index = middle;
            continue;
        }
        else
        {
            range.first = middle;
            break;
        }
    }

    low_index = previous_range.first;
    high_index = previous_range.second;
    while (low_index <= high_index)
    {
        int middle = std::ceil((high_index + low_index) / 2.0);

        if (character_index >= m_word_list[middle].size() || character_to_compare > m_word_list[middle].at(character_index))
        {
            low_index = middle + 1;
            continue;
        }
        else if (character_to_compare < m_word_list[middle].at(character_index))
        {
            high_index = middle - 1;
            continue;
        }
        else if (high_index != middle)
        {
            low_index = middle;
            continue;
        }
        else
        {
            range.second = middle;
            break;
        }
    }

    return range;
}

void Solver::Solve_From_Cell(unsigned int cell_x, unsigned int cell_y)
{
    std::pair<int, int> offsets[8] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    std::string current_word = m_board_ptr->Get_Board_Cell(cell_x, cell_y);
    std::vector<unsigned int> direction_stack = {0};
    std::vector<std::pair<int, int>> search_range_stack = {Find_Range({0, m_word_list.size() - 1}, *m_board_ptr->Get_Board_Cell(cell_x, cell_y).c_str(), 0)};
    std::vector<std::vector<bool>> cells_visited(m_board_ptr->Get_Board_Size(), std::vector<bool>(m_board_ptr->Get_Board_Size(), false));

    if (search_range_stack.back().first == -1 || search_range_stack.back().second == -1)
    {
        return;
    }

    int current_x = cell_x;
    int current_y = cell_y;

    while (direction_stack[0] != 8)
    {
        if ((int)current_word.size() == m_max_word_length || direction_stack.back() == 8)
        {
            cells_visited[current_x][current_y] = false;

            current_word.pop_back();
            direction_stack.pop_back();
            search_range_stack.pop_back();

            current_x -= offsets[direction_stack.back()].first;
            current_y -= offsets[direction_stack.back()].second;

            direction_stack.back()++;
            continue;
        }

        std::pair<int, int> offset = offsets[direction_stack.back()];

        int offset_current_x = current_x + offset.first;
        int offset_current_y = current_y + offset.second;

        if (offset_current_x < 0 || offset_current_y < 0 || offset_current_x >= (int)m_board_ptr->Get_Board_Size() || offset_current_y >= (int)m_board_ptr->Get_Board_Size() || cells_visited[offset_current_x][offset_current_y])
        {
            direction_stack.back()++;
            continue;
        }

        char offset_cell_char = *m_board_ptr->Get_Board_Cell(offset_current_x, offset_current_y).c_str();

        std::pair<int, int> range = Find_Range(search_range_stack.back(), offset_cell_char, current_word.size());
        if (range.first == -1 || range.second == -1)
        {
            direction_stack.back()++;
            continue;
        }
        else
        {
            cells_visited[current_x][current_y] = true;

            current_x = offset_current_x;
            current_y = offset_current_y;

            current_word.push_back(offset_cell_char);
            direction_stack.push_back(0);
            search_range_stack.push_back(range);

            if ((int)current_word.size() >= m_min_word_length && m_found_words.find(current_word) == m_found_words.end())
            {
                for (int i = range.first; i <= range.second; i++)
                {
                    if (m_word_list[i] == current_word)
                    {
                        m_found_words.insert(current_word);

                        std::vector<std::pair<unsigned int, unsigned int>> path = {{cell_x, cell_y}};
                        for (unsigned int i = 0; i < direction_stack.size() - 1; i++)
                        {
                            path.push_back({path.back().first + offsets[direction_stack[i]].first, path.back().second + offsets[direction_stack[i]].second});
                        }

                        m_solutions.push_back({current_word, path});
                        break;
                    }
                }
            }
        }
    }
}

std::vector<std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>> Solver::Get_Solutions()
{
    return m_solutions;
}