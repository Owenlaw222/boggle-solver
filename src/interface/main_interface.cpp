#include "main_interface.hpp"

#include <algorithm>
#include <iostream>
#include <string>

Main_Interface::Main_Interface(int* argc, char*** argv, Board* board_ptr) : m_board_ptr(board_ptr)
{
    // Initialize GTK
    gtk_init(argc, argv);

    // Initialize starting screen
    Initialize_Window();
    Initialize_Input_Screen();

    // Show all elements
    gtk_widget_show_all(m_window_ptr);

    // Start loop
    gtk_main();
}

void Main_Interface::Initialize_Window()
{
    // Create window
    m_window_ptr = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Set window properties
    gtk_window_set_title(GTK_WINDOW(m_window_ptr), "Boggle Solver");
    gtk_window_set_default_size(GTK_WINDOW(m_window_ptr), 750, 750);
    gtk_window_set_position(GTK_WINDOW(m_window_ptr), GTK_WIN_POS_CENTER);

    // Setup close button
    g_signal_connect(m_window_ptr, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void Main_Interface::Initialize_Input_Screen()
{
    // Create widgets
    m_input_screen_frame_ptr = gtk_aspect_frame_new("", 0.5, 0.5, (double)m_board_ptr->Get_Board_Size() / (double)(m_board_ptr->Get_Board_Size() + 1), gtk_false());
    m_input_grid_ptr = gtk_grid_new();
    m_randomize_button_ptr = gtk_button_new_with_label("Randomize!");
    m_solve_button_ptr = gtk_button_new_with_label("Solve!");

    // Disable solve button
    gtk_widget_set_sensitive(m_solve_button_ptr, gtk_false());

    // Set margin around frame
    gtk_container_set_border_width(GTK_CONTAINER(m_input_screen_frame_ptr), 10);

    // Set input grid properties
    gtk_grid_set_row_spacing(GTK_GRID(m_input_grid_ptr), 5.0);
    gtk_grid_set_column_spacing(GTK_GRID(m_input_grid_ptr), 5.0);
    gtk_grid_set_row_homogeneous(GTK_GRID(m_input_grid_ptr), gtk_true());
    gtk_grid_set_column_homogeneous(GTK_GRID(m_input_grid_ptr), gtk_true());

    // Create font attributes
    PangoAttrList* font_attribute_list = pango_attr_list_new();
    PangoAttribute* font_size_attribute = pango_attr_size_new_absolute(PANGO_SCALE * 40.0);
    pango_attr_list_insert(font_attribute_list, font_size_attribute);

    // Add text input boxes to grid
    m_entry_box_ptrs.resize(m_board_ptr->Get_Board_Size());
    for (uint8_t x = 0; x < m_board_ptr->Get_Board_Size(); x++)
    {
        m_entry_box_ptrs[x].resize(m_board_ptr->Get_Board_Size());
        for (uint8_t y = 0; y < m_board_ptr->Get_Board_Size(); y++)
        {
            // Create entry box
            m_entry_box_ptrs[x][y] = gtk_entry_new();

            gtk_entry_set_alignment(GTK_ENTRY(m_entry_box_ptrs[x][y]), 0.5);                  // Center text in entry box
            gtk_entry_set_attributes(GTK_ENTRY(m_entry_box_ptrs[x][y]), font_attribute_list); // Apply font attributes to entry box

            // Allocate structure to pass to callback
            Input_Box_Callback_Data* input_box_callback_data_ptr = (Input_Box_Callback_Data*)malloc(sizeof(Input_Box_Callback_Data));
            input_box_callback_data_ptr->interface = this;
            input_box_callback_data_ptr->x_position = x;
            input_box_callback_data_ptr->y_position = y;

            // Add entry box to grid
            gtk_grid_attach(GTK_GRID(m_input_grid_ptr), m_entry_box_ptrs[x][y], x * 2, y * 2, 2, 2);

            // Setup changed and destroyed callbacks
            g_signal_connect(GTK_EDITABLE(m_entry_box_ptrs[x][y]), "changed", G_CALLBACK(On_Input_Changed), (gpointer)input_box_callback_data_ptr);
        }
    }

    // Add randomize and solve button to grid
    gtk_grid_attach(GTK_GRID(m_input_grid_ptr), m_randomize_button_ptr, 0, m_board_ptr->Get_Board_Size() * 2, m_board_ptr->Get_Board_Size() * 2, 1);
    gtk_grid_attach(GTK_GRID(m_input_grid_ptr), m_solve_button_ptr, 0, m_board_ptr->Get_Board_Size() * 2 + 1, m_board_ptr->Get_Board_Size() * 2, 1);

    // Setup randomize callback
    g_signal_connect(m_randomize_button_ptr, "clicked", G_CALLBACK(On_Randomized_Clicked), this);

    // Add grid to frame and the frame to the window
    gtk_container_add(GTK_CONTAINER(m_input_screen_frame_ptr), m_input_grid_ptr);
    gtk_container_add(GTK_CONTAINER(m_window_ptr), m_input_screen_frame_ptr);
}

bool Main_Interface::Is_String_Valid(const char* input, uint8_t board_size)
{
    if (board_size == 4)
    {
        // const char* valid_strings[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "V", "W", "Z", "Y", "Z", "QU"};
        const char* valid_strings[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Q"};

        for (uint8_t i = 0; i < 26; i++)
        {
            if (strcmp(input, valid_strings[i]) == 0)
            {
                return true;
            }
        }
    }
    else
    {
        // const char* valid_strings[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "QU", "IN", "TH", "ER", "HE", "AN"};
        const char* valid_strings[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Q", "I", "T", "E", "H", "A"};

        for (uint8_t i = 0; i < 31; i++)
        {
            if (strcmp(input, valid_strings[i]) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

void Main_Interface::Check_Inputs(Main_Interface* interface)
{
    interface->m_are_inputs_valid = true;

    // Loop through cells
    for (uint8_t x = 0; x < interface->m_board_ptr->Get_Board_Size(); x++)
    {
        for (uint8_t y = 0; y < interface->m_board_ptr->Get_Board_Size(); y++)
        {
            // Test whether or not the input at cell x, y is valid
            interface->m_are_inputs_valid &= Is_String_Valid(interface->m_board_ptr->Get_Board_Cell(x, y).c_str(), interface->m_board_ptr->Get_Board_Size());
        }
    }
}

void Main_Interface::On_Input_Changed(GtkWidget* self, gpointer user_data)
{
    // Get input box text and data
    Input_Box_Callback_Data* input_box_callback_data_ptr = (Input_Box_Callback_Data*)user_data;
    std::string input_text = gtk_entry_get_text(GTK_ENTRY(self));

    // Convert input text to upper case
    std::transform(input_text.begin(), input_text.end(), input_text.begin(), ::toupper);

    // Remove added letter if it is not valid
    if (!Is_String_Valid(input_text.c_str(), input_box_callback_data_ptr->interface->m_board_ptr->Get_Board_Size()) && input_text != "" && input_text != "Q")
    {
        input_text.pop_back();
    }

    // Update text with processed text
    gtk_entry_set_text(GTK_ENTRY(self), input_text.c_str());

    // Set board cell to text
    input_box_callback_data_ptr->interface->m_board_ptr->Set_Board_Cell(input_box_callback_data_ptr->x_position, input_box_callback_data_ptr->y_position, input_text);

    // Enable / disable solve button
    Check_Inputs(input_box_callback_data_ptr->interface);
    gtk_widget_set_sensitive(input_box_callback_data_ptr->interface->m_solve_button_ptr, (gboolean)input_box_callback_data_ptr->interface->m_are_inputs_valid);
}

void Main_Interface::On_Randomized_Clicked(GtkWidget* self, gpointer user_data)
{
    // Silence -Wunused-parameter (parameter is needed in callback signature)
    (void)self;

    // Cast pointer to interface
    Main_Interface* interface_ptr = (Main_Interface*)user_data;

    // Randomize board
    interface_ptr->m_board_ptr->Randomize();

    // Update text input boxes
    for (uint8_t x = 0; x < interface_ptr->m_board_ptr->Get_Board_Size(); x++)
    {
        for (uint8_t y = 0; y < interface_ptr->m_board_ptr->Get_Board_Size(); y++)
        {
            std::string cell_value = interface_ptr->m_board_ptr->Get_Board_Cell(x, y);

            gtk_entry_set_text(GTK_ENTRY(interface_ptr->m_entry_box_ptrs[x][y]), cell_value.c_str());
        }
    }

    // Enable / disable solve button
    Check_Inputs(interface_ptr);
    gtk_widget_set_sensitive(interface_ptr->m_solve_button_ptr, (gboolean)interface_ptr->m_are_inputs_valid);
}