#include "../widget_base.h"
#include "platform.h"

void cf_platform_prepare_for_config_screen()
{
}

void draw_window( char *title, uint8_t top, uint8_t height, uint8_t left, uint8_t width )
{
}

void generic_draw( char *decorator, ui_element_t *element )
{
        fprintf( stderr, "\nDOT: elem_%p [label=\"%s%s\", pos=\"%d,%d!\"];\n",
                 element, decorator, element->text, element->x, element->y );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbours[neighbour_up] );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbours[neighbour_down] );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbours[neighbour_left] );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbours[neighbour_right] );
}

void radioButtonDraw( ui_element_t *element )
{
        generic_draw( "(*) ", element );
}

void checkBoxDraw( ui_element_t *element )
{
        generic_draw( "[x] ", element );
}

void textInputDraw( ui_element_t *element )
{
        generic_draw( "INPUT ", element );
}

void buttonDraw( ui_element_t *element )
{
        generic_draw( "BUTTON ", element );
}

void gui_loop( ui_element_t *first_selected_element )
{
}
