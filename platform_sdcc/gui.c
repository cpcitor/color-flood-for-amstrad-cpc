#include "platform.h"
#include "../model.h"
#include "ui_element.h"

// #define CF_MAXPLAYERNAMELENGTH_INCLUDINGTRAILINGZERO 9

//uint8_t playerEnableArray[CF_MAXPLAYERCOUNT];
//char playerNamesArray[CF_MAXPLAYERCOUNT][CF_MAXPLAYERNAMELENGTH_INCLUDINGTRAILINGZERO];

char toto;

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

ui_class_t labelClass = {labelDraw, 0};
ui_class_t radioButtonClass = {radioButtonDraw, 0};
ui_class_t checkBoxClass = {checkBoxDraw, 0};
ui_class_t textInputClass = {labelDraw, 0};

void gui_init( void )
{
        ui_element_t titleLabel = { 20, 5, &labelClass, "Color Flood", ( void * )1 };
        ui_element_t rbGrid12 = { 5, 05, &radioButtonClass, "Small (12)" };
        ui_element_t rbGrid16 = { 5, 15, &radioButtonClass, "Medium (16)" };
        ui_element_t rbGrid24 = { 5, 25, &radioButtonClass, "Big (24)" };
        ui_element_t pule = { 8, 05, &checkBoxClass, "Enable player up left" };
        ui_element_t pure = { 8, 25, &checkBoxClass, "Enable player up right" };
        ui_element_t pdle = { 16, 05, &checkBoxClass, "Enable player down left" };
        ui_element_t pdre = { 16, 25, &checkBoxClass, "Enable player down right" };
        ui_element_t puln = { 10, 05, &textInputClass, "Name" };
        ui_element_t purn = { 10, 25, &textInputClass, "Name" };
        ui_element_t pdln = { 18, 05, &textInputClass, "Name" };
        ui_element_t pdrn = { 18, 25, &textInputClass, "Name" };


}


