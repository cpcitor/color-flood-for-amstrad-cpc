#include "../widget_base.h"
#include "platform.h"

void generic_draw( char *decorator, ui_element_t *element )
{
        fprintf( stderr, "DOT: elem_%p [label=\"%s%s\"];\n", element, decorator, element->text );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbour_up );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbour_down );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbour_left );
        fprintf( stderr, "DOT: elem_%p -> elem_%p;\n", element, element->neighbour_right );
}

void labelDraw( ui_element_t *element )
{
        generic_draw( "", element );
}

void radioButtonDraw( ui_element_t *element )
{
        generic_draw( "(*) ", element );
}

void checkBoxDraw( ui_element_t *element )
{
        generic_draw( "[x] ", element );
}
