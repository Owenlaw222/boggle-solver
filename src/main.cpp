#include "interface.hpp"
#include "solver.hpp"

#include <cstring>
#include <iostream>


int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "\nNo arguments passed to program. Pass -h for usage.\n\n";
        return 0;
    }

    int min_word_len = 0;
    int max_word_len = -1;
    int board_size = -1;
    bool enable_random_gen = false;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0)
        {
            std::cout << "\nUsage: Boggle-Solver -s <size> [OPTIONS]\n"
                      << "Usage: Boggle-Solver {-h | --help}\n\n"
                      << "Option            Long option            Meaning\n"
                      << "-h                --help                 Show this help text\n"
                      << "-l <min> <max>    --length <min> <max>   The minimum and maximum word length to find\n"
                      << "-r                --randomize            Provide an already shuffled board\n"
                      << "-s <size>         --size <size>          The size of the boggle board. Must be larger then zero.\n\n";
            return 0;
        }
        else if (strcmp("-l", argv[i]) == 0 || strcmp("--length", argv[i]) == 0)
        {
            i++;
            if (i >= argc)
            {
                std::cout << "\nArgument {-l | --length} must be followed by two integers.\n\n";
                return 0;
            }
            else
            {
                min_word_len = atoi(argv[i]);
            }

            i++;
            if (i >= argc)
            {
                std::cout << "\nArgument {-l | --length} must be followed by two integers.\n\n";
                return 0;
            }
            else
            {
                max_word_len = atoi(argv[i]);
            }
        }
        else if (strcmp("-r", argv[i]) == 0 || strcmp("--randomize", argv[i]) == 0)
        {
            enable_random_gen = true;
        }
        else if (strcmp("-s", argv[i]) == 0 || strcmp("--size", argv[i]) == 0)
        {
            i++;
            if (i >= argc)
            {
                std::cout << "\nArgument {-s | --size} must be followed by a integer higher then one.\n\n";
                return 0;
            }
            else
            {
                board_size = atoi(argv[i]);

                if (max_word_len == -1)
                {
                    max_word_len = board_size * board_size;
                }
            }
        }
        else
        {
            std::cout << "\nInvalid argument '" << argv[i] << "'\n\n";
            return 0;
        }
    }

    if (board_size < 2)
    {
        std::cout << "\nInvalid board size. Argument {-s | --size} must be followed by a integer higher then one.\n\n";
        return 0;
    }

    std::shared_ptr<Board> board_ptr = std::make_shared<Board>(board_size);
    if (enable_random_gen)
    {
        board_ptr->Randomize();
    }

    Interface interface = Interface(board_ptr);
    interface.Get_User_Board_Input(0, 0);

    Solver solver(board_ptr, "../words/collins-scrabble-words-2019.txt", min_word_len, max_word_len);
    interface.Main_Interface(solver.Get_Solutions());

    return 0;
}