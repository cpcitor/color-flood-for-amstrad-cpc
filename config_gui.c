#include "platform.h"
#include "model.h"
#include "widget_classes.h"
#include "gui_loop.h"

// #define CF_MAXPLAYERNAMELENGTH_INCLUDINGTRAILINGZERO 9

//char playerNamesArray[CF_MAXPLAYERCOUNT][CF_MAXPLAYERNAMELENGTH_INCLUDINGTRAILINGZERO];

ui_class_t radioButtonClass = {radioButtonDraw, radioButtonAction};
ui_class_t checkBoxClass = {checkBoxDraw, checkBoxAction};
//ui_class_t textInputClass={textInputDraw, 0};
ui_class_t buttonClass = {buttonDraw, buttonAction};

void setup( ui_element_t *element, ui_element_t *up, ui_element_t *down, ui_element_t *left, ui_element_t *right )
{
        element->neighbours[neighbour_up] = up;
        element->neighbours[neighbour_down] = down;
        element->neighbours[neighbour_left] = left;
        element->neighbours[neighbour_right] = right;
        ( element->class->draw_func )( element );
}

#define gui_top (12)

#define win_radio_height (3)
#define win_player_height (5)

#define win_radio_top (gui_top)
#define win_player_row1_top (win_radio_top+win_radio_height)
#define win_player_row2_top (win_player_row1_top + win_player_height)
#define go_button_top (win_player_row2_top + win_player_height)

void config_gui_init( void )
{
        // Data parameter is grid size.
        ui_element_t rbGrid12 = {win_radio_top + 1, 02, &radioButtonClass, "Small (12)", {.value_uint8 = 12}};
        ui_element_t rbGrid16 = {win_radio_top + 1, 15, &radioButtonClass, "Medium (16)", {.value_uint8 = 16}};
        ui_element_t rbGrid24 = {win_radio_top + 1, 29, &radioButtonClass, "Big (24)", {.value_uint8 = 24}};

        // Data parameter is to be correlated with playerHomes.
        ui_element_t pule = {win_player_row1_top + 2, 3, &checkBoxClass, "Enable", {.value_uint8 = 1}};
        ui_element_t pure = {win_player_row1_top + 2, 23, &checkBoxClass, "Enable", {.value_uint8 = 2}};
        ui_element_t pdle = {win_player_row2_top + 2, 3, &checkBoxClass, "Enable", {.value_uint8 = 4}};
        ui_element_t pdre = {win_player_row2_top + 2, 23, &checkBoxClass, "Enable", {.value_uint8 = 8}};
        /*        ui_element_t puln={win_player_row1_top + 3, 3, &textInputClass, "Name"};
                ui_element_t purn={win_player_row1_top + 3, 23, &textInputClass, "Name"};
                ui_element_t pdln={win_player_row2_top + 3, 3, &textInputClass, "Name"};
                ui_element_t pdrn={win_player_row2_top + 3, 23, &textInputClass, "Name"}; */
        ui_element_t buttonGo = {go_button_top, 15, &buttonClass, "START GAME"};

        draw_window( ( char * )0, 1, 4, 1, 40 );
        draw_window( "Rules", 5, 10, 1, 40 );
        draw_window( "Grid size", win_radio_top, win_radio_top + win_radio_height - 1, 1, 40 );
        draw_window( "Player up left", win_player_row1_top, win_player_row1_top + win_player_height - 1, 1, 20 );
        draw_window( "Player up right", win_player_row1_top, win_player_row1_top + win_player_height - 1, 21, 40 );
        draw_window( "Player down left", win_player_row2_top, win_player_row2_top + win_player_height - 1, 1, 20 );
        draw_window( "Player down right", win_player_row2_top, win_player_row2_top + win_player_height - 1, 21, 40 );

        setup( &rbGrid12, 0, &pule, 0, &rbGrid16 );
        setup( &rbGrid16, 0, &pule, &rbGrid12, &rbGrid24 );
        setup( &rbGrid24, 0, &pure, &rbGrid16, 0 );

        /*
        setup( &pule, &rbGrid12, &puln, 0, &pure );
        setup( &pure, &rbGrid24, &purn, &pule, 0 );
        setup( &puln, &pule, &pdle, 0, &purn );
        setup( &purn, &pure, &pdre, &puln, 0 );

        setup( &pdle, &puln, &pdln, 0, &pdre );
        setup( &pdre, &purn, &pdrn, &pdle, 0 );
        setup( &pdln, &pdle, &buttonGo, 0, &pdrn );
        setup( &pdrn, &pdre, &buttonGo, &pdln, 0 );
        */

        setup( &pule, &rbGrid12, &pdle, 0, &pure );
        setup( &pure, &rbGrid24, &pdre, &pule, 0 );

        setup( &pdle, &pule, &buttonGo, 0, &pdre );
        setup( &pdre, &pure, &buttonGo, &pdle, 0 );


        //setup( &buttonGo, &pdln, 0, 0, 0 );
        setup( &buttonGo, &pdle, 0, 0, 0 );

        gui_loop( &rbGrid12 );
}
