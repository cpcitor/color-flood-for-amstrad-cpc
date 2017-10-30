#include "platform.h"
#include "../model.h"
#include "ui_element.h"

// #define CF_MAXPLAYERNAMELENGTH_INCLUDINGTRAILINGZERO 9

//uint8_t playerEnableArray[CF_MAXPLAYERCOUNT];
//char playerNamesArray[CF_MAXPLAYERCOUNT][CF_MAXPLAYERNAMELENGTH_INCLUDINGTRAILINGZERO];

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

void setup( ui_element_t *element, ui_element_t *up, ui_element_t *down, ui_element_t *left, ui_element_t *right )
{
        ( element->class->draw_func )( element );
        element->neighbour_up = up;
        element->neighbour_down = down;
        element->neighbour_left = left;
        element->neighbour_right = right;
}

void gui_init( void )
{
//        ui_element_t titleLabel = { 20, 5, &labelClass, "Color Flood", ( void * )1 };
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

        setup( &rbGrid12, 0, &pule, 0, &rbGrid16 );
        setup( &rbGrid16, 0, &pule, &rbGrid12, &rbGrid24 );
        setup( &rbGrid24, 0, &pure, &rbGrid16, 0 );
        setup( &rbGrid24, 0, &pure, &rbGrid16, 0 );

        setup( &pule, 0, &puln, 0, &pure );
        setup( &pure, 0, &purn, &pule, 0 );
        setup( &puln, &pule, &pdle, 0, &purn );
        setup( &purn, &pure, &pdre, &puln, 0 );

        setup( &pdle, &puln, &pdln, 0, &pdre );
        setup( &pdre, &purn, 0, &pdle, 0 );
        setup( &pdln, &pdle, 0, 0, &pdrn );
        setup( &pdrn, &pdre, 0, &pdln, 0 );

}


