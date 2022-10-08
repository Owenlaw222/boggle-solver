#include "board.hpp"

#include <set>
#include <string>

class Solver
{
public:
    struct Solution
    {
        std::string word;

        std::vector<unsigned int> x_positions;
        std::vector<unsigned int> y_positions;
    };

private:
    Board* m_board_ptr;

    std::string m_word_list_path;

    std::vector<std::string> m_word_list;
    std::set<std::string> m_found_words;
    std::vector<Solution> m_solutions;

private:
    void Load_Word_List();

    std::pair<int, int> Find_Range(std::pair<int, int> previous_range, char character_to_compare, unsigned int character_index);
    void Solve_From_Cell(unsigned int cell_x, unsigned int cell_y);

public:
    Solver(Board* board_ptr, std::string word_list_path);

public:
    std::vector<Solution> Get_Solutions();
};