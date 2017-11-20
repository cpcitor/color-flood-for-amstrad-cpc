#include "../widget_base.h"
#include "platform.h"

void cf_platform_prepare_for_config_screen()
{
}

void draw_window( char *title, uint8_t top, uint8_t height, uint8_t left, uint8_t width )
{
        ( void ) title;
        ( void ) top;
        ( void ) height;
        ( void ) left;
        ( void ) width;
}

void generic_draw( const char *const decorator, const ui_element_t *const element )
{
        fprintf( stderr, "\nDOT: elem_%p [label=\"%s%s\", pos=\"%d,%d!\"];\n",
                 element, decorator, element->text, element->x, element->y );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbours[neighbour_up] );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbours[neighbour_down] );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbours[neighbour_left] );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbours[neighbour_right] );
}

void radioButtonDraw( const ui_element_t *const element )
{
        generic_draw( "(*) ", element );
}

void checkBoxDraw( const ui_element_t *const element )
{
        generic_draw( "[x] ", element );
}

/*void textInputDraw( const ui_element_t *const element )
{
        generic_draw( "INPUT ", element );
        }*/

void buttonDraw( const ui_element_t *const element )
{
        generic_draw( "BUTTON ", element );
}

void gui_loop( ui_element_t *first_selected_element )
{
        ( void ) first_selected_element;
}


void radioButtonAction( ui_element_t *source )
{
        ( void ) source;
}

void checkBoxAction( ui_element_t *source )
{
        ( void ) source;
}

void buttonAction( ui_element_t *source )
{
        ( void ) source;
}
