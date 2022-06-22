#include "board.hpp"

#include <memory>
#include <set>
#include <string>


class Solver
{
private:
    std::shared_ptr<Board> m_board_ptr;

    std::string m_word_list_path;

    std::vector<std::string> m_word_list;
    std::set<std::string> m_found_words;
    std::vector<std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>> m_solutions;

    unsigned int m_min_word_length;
    unsigned int m_max_word_length;

private:
    void Load_Word_List();

    std::pair<int, int> Find_Range(std::pair<int, int> previous_range, char character_to_compare, unsigned int character_index);
    void Solve_From_Cell(unsigned int cell_x, unsigned int cell_y);

public:
    Solver(std::shared_ptr<Board> board_ptr, std::string word_list_path, unsigned int min_word_length, unsigned int max_word_length);

public:
    std::vector<std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>> Get_Solutions();
};