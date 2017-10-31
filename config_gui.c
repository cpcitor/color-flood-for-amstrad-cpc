#include "platform.h"
#include "model.h"
#include "widget_classes.h"

// #define CF_MAXPLAYERNAMELENGTH_INCLUDINGTRAILINGZERO 9

//uint8_t playerEnableArray[CF_MAXPLAYERCOUNT];
//char playerNamesArray[CF_MAXPLAYERCOUNT][CF_MAXPLAYERNAMELENGTH_INCLUDINGTRAILINGZERO];

void setup( ui_element_t *element, ui_element_t *up, ui_element_t *down, ui_element_t *left, ui_element_t *right )
{
        element->neighbour_up = up;
        element->neighbour_down = down;
        element->neighbour_left = left;
        element->neighbour_right = right;
        ( element->class->draw_func )( element );
}

#define gui_top (12)

#define win_radio_height (3)
#define win_player_height (4)

#define win_radio_top (gui_top)
#define win_player_row1_top (win_radio_top+win_radio_height)
#define win_player_row2_top (win_player_row1_top + win_player_height)

void config_gui_init( void )
{
//        ui_element_t titleLabel = { 20, 5, &labelClass, "Color Flood", ( void * )1 };
        ui_element_t rbGrid12 = { win_radio_top + 1, 02, &radioButtonClass, "Small (12)" };
        ui_element_t rbGrid16 = { win_radio_top + 1, 15, &radioButtonClass, "Medium (16)" };
        ui_element_t rbGrid24 = { win_radio_top + 1, 29, &radioButtonClass, "Big (24)" };
        ui_element_t pule = { win_player_row1_top + 1, 3, &checkBoxClass, "Enable" };
        ui_element_t pure = { win_player_row1_top + 1, 23, &checkBoxClass, "Enable" };
        ui_element_t pdle = { win_player_row2_top + 1, 3, &checkBoxClass, "Enable" };
        ui_element_t pdre = { win_player_row2_top + 1, 23, &checkBoxClass, "Enable" };
        ui_element_t puln = { win_player_row1_top + 2, 3, &textInputClass, "Name" };
        ui_element_t purn = { win_player_row1_top + 2, 23, &textInputClass, "Name" };
        ui_element_t pdln = { win_player_row2_top + 2, 3, &textInputClass, "Name" };
        ui_element_t pdrn = { win_player_row2_top + 2, 23, &textInputClass, "Name" };

        draw_window( "Grid size", gui_top, gui_top + 2, 1, 40 );
        draw_window( "Player up left", gui_top + 3, gui_top + 6, 1, 20 );
        draw_window( "Player up right", gui_top + 3, gui_top + 6, 21, 40 );
        draw_window( "Player down left", gui_top + 7, gui_top + 11, 1, 20 );
        draw_window( "Player down right", gui_top + 7, gui_top + 11, 21, 40 );

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
