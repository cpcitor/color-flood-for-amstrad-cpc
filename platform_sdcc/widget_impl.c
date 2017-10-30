#include "../widget_base.h"
#include "platform.h"

void labelDraw( ui_element_t *element )
{
        fw_txt_set_cursor( element->x, element->y );
        cfwi_txt_str0_output( element->text );
}

void radioButtonDraw( ui_element_t *element )
{
        fw_txt_set_cursor( element->x, element->y );
        cfwi_txt_str0_output( "* " );
        cfwi_txt_str0_output( element->text );
}

void checkBoxDraw( ui_element_t *element )
{
        fw_txt_set_cursor( element->x, element->y );
        cfwi_txt_str0_output( "* " );
        cfwi_txt_str0_output( element->text );
}
