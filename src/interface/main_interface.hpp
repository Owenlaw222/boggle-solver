#pragma once

#include "../solver/board.hpp"
#include <gtk/gtk.h>
#include <vector>

class Main_Interface
{
private:
    struct Input_Box_Callback_Data
    {
        Main_Interface* interface;

        uint8_t x_position;
        uint8_t y_position;
    };

private:
    bool m_are_inputs_valid = false;
    Board* m_board_ptr;

    GtkWidget* m_window_ptr;

    // Input screen widgets
    GtkWidget* m_input_screen_frame_ptr;
    GtkWidget* m_input_grid_ptr;
    GtkWidget* m_randomize_button_ptr;
    GtkWidget* m_solve_button_ptr;
    std::vector<std::vector<GtkWidget*>> m_entry_box_ptrs;

private:
    void Initialize_Window();
    void Initialize_Input_Screen();

    static bool Is_String_Valid(const char* input, uint8_t board_size);
    static void Check_Inputs(Main_Interface* interface);

    static void On_Input_Changed(GtkWidget* self, gpointer user_data);
    static void On_Randomized_Clicked(GtkWidget* self, gpointer user_data);

public:
    Main_Interface(int* argc, char*** argv, Board* board_ptr);
};