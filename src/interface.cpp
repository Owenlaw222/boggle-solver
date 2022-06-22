#include "interface.hpp"

#include <algorithm>
#include <iostream>


Interface::Interface(std::shared_ptr<Board> board_ptr) : m_board_ptr(board_ptr)
{
    initscr();
    curs_set(1);
    keypad(stdscr, TRUE);

    Draw_Board(0, 0);
}

Interface::~Interface()
{
    endwin();
}

void Interface::Draw_Board(unsigned int board_x, unsigned int board_y)
{
    for (unsigned int i = 0; i <= m_board_ptr->Get_Board_Size(); i++)
    {
        move(board_y, board_x + i * 6);
        vline(ACS_VLINE, m_board_ptr->Get_Board_Size() * 4);
    }

    for (unsigned int i = 0; i <= m_board_ptr->Get_Board_Size(); i++)
    {
        move(board_y + i * 4, board_x);
        hline(ACS_HLINE, m_board_ptr->Get_Board_Size() * 6 + 1);
    }

    for (unsigned int x = 0; x < m_board_ptr->Get_Board_Size(); x++)
    {
        for (unsigned int y = 0; y < m_board_ptr->Get_Board_Size(); y++)
        {
            move(board_y + y * 4 + 2, board_x + x * 6 + 3);
            printw(m_board_ptr->Get_Board_Cell(x, y).c_str());
        }
    }

    refresh();
}

void Interface::Draw_Board_Path(unsigned int board_x, unsigned int board_y, std::vector<std::pair<unsigned int, unsigned int>> path)
{
    for (unsigned int i = 0; i <= m_board_ptr->Get_Board_Size(); i++)
    {
        move(board_y, board_x + i * 4);
        vline(ACS_VLINE, m_board_ptr->Get_Board_Size() * 4);
    }

    for (unsigned int i = 0; i <= m_board_ptr->Get_Board_Size(); i++)
    {
        move(board_y + i * 4, board_x);
        hline(ACS_HLINE, m_board_ptr->Get_Board_Size() * 4 + 1);
    }

    for (unsigned int x = 0; x < m_board_ptr->Get_Board_Size(); x++)
    {
        for (unsigned int y = 0; y < m_board_ptr->Get_Board_Size(); y++)
        {
            if (std::find(path.begin(), path.end(), std::pair<unsigned int, unsigned int>(x, y)) != path.end())
            {
                attrset(A_STANDOUT | A_BOLD);
            }

            move(board_y + y * 4 + 2, board_x + x * 4 + 2);
            printw(m_board_ptr->Get_Board_Cell(x, y).c_str());

            attrset(A_NORMAL);
        }
    }

    attrset(A_STANDOUT);
    for (unsigned int i = 0; i < path.size(); i++)
    {
        if (i != 0)
        {
            move((board_y + path[i].second * 4 + 2) - (path[i].second - path[i - 1].second), (board_x + path[i].first * 4 + 2) - (path[i].first - path[i - 1].first));
            printw(" ");
            move((board_y + path[i].second * 4 + 2) - ((path[i].second - path[i - 1].second) * 2), (board_x + path[i].first * 4 + 2) - ((path[i].first - path[i - 1].first) * 2));
            printw(" ");
        }
        if (i != path.size() - 1)
        {
            move((board_y + path[i].second * 4 + 2) - (path[i].second - path[i + 1].second), (board_x + path[i].first * 4 + 2) - (path[i].first - path[i + 1].first));
            printw(" ");
            move((board_y + path[i].second * 4 + 2) - ((path[i].second - path[i + 1].second) * 2), (board_x + path[i].first * 4 + 2) - ((path[i].first - path[i + 1].first) * 2));
            printw(" ");
        }
    }
    attrset(A_NORMAL);

    refresh();
}

void Interface::Main_Interface(std::vector<std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>> solutions)
{
    clear();

    curs_set(0);

    int selected_word = 0;
    int scroll = 0;


    std::sort(solutions.begin(), solutions.end(),
              [](const std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>& first, const std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>& second) { return first.first.compare(second.first) < 0; });

    std::stable_sort(solutions.begin(), solutions.end(),
                     [](const std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>& first, const std::pair<std::string, std::vector<std::pair<unsigned int, unsigned int>>>& second)
                     { return first.first.size() > second.first.size(); });

    while (true)
    {
        clear();

        for (int i = scroll; i < std::min((int)solutions.size(), LINES + (int)scroll); i++)
        {
            if (selected_word == i)
            {
                attrset(A_STANDOUT);
            }

            move(i - scroll, 0);
            printw(solutions[i].first.c_str());

            attrset(A_NORMAL);
        }

        Draw_Board_Path(30, 0, solutions[selected_word].second);

        refresh();

        move(100, 100);

        int input = getch();

        switch (input)
        {
            case KEY_UP:
                if (selected_word != 0)
                {
                    selected_word--;
                }
                if (selected_word - scroll == 0 && selected_word != 0)
                {
                    scroll--;
                }
                break;
            case KEY_DOWN:
                if ((long unsigned int)selected_word != solutions.size() - 1)
                {
                    selected_word++;
                }
                if (selected_word - scroll == LINES - 1)
                {
                    scroll++;
                }
                break;
        }

        move(100, 100);
    }
}

void Interface::Get_User_Board_Input(unsigned int x, unsigned int y)
{
    unsigned int x_position = 0;
    unsigned int y_position = 0;

    bool exit = false;

    while (!exit)
    {
        move(y + y_position * 4 + 2, x + x_position * 6 + 3);

        int input = getch();

        switch (input)
        {
            case KEY_UP:
                if (y_position != 0)
                {
                    y_position--;
                }
                break;
            case KEY_DOWN:
                if (y_position != m_board_ptr->Get_Board_Size() - 1)
                {
                    y_position++;
                }
                break;
            case KEY_LEFT:
                if (x_position != 0)
                {
                    x_position--;
                }
                break;
            case KEY_RIGHT:
                if (x_position != m_board_ptr->Get_Board_Size() - 1)
                {
                    x_position++;
                }
                break;
            case '\n':
                exit = m_board_ptr->All_Cells_Entered();
                break;
            default:
                m_board_ptr->Set_Board_Cell(x_position, y_position, std::string(1, toupper(input)));
                break;
        }

        clear();
        Draw_Board(0, 0);
    }
}

void Interface::Close()
{
    endwin();
}