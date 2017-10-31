#include "widget_configscreen.h"
#include "widget_classes.h"

const ui_configscreen_union_t ui_configscreen =
{
        .as_struct =
        {
                // Data parameter is grid size.
                .rbGrid12 = {win_radio_top + 1, 02, &radioButtonClass, "Small (12)", 12, { 0, &ui_configscreen.as_struct.pule, 0, &ui_configscreen.as_struct.rbGrid16} },
                .rbGrid16 = {win_radio_top + 1, 15, &radioButtonClass, "Medium (16)", 16, {0, &ui_configscreen.as_struct.pule, &ui_configscreen.as_struct.rbGrid12, &ui_configscreen.as_struct.rbGrid24}},
                .rbGrid24 = {win_radio_top + 1, 29, &radioButtonClass, "Big (24)", 24, {0, &ui_configscreen.as_struct.pure, &ui_configscreen.as_struct.rbGrid16, 0}},

                // Data parameter is to be correlated with playerHomes.
                .pule = {win_player_row1_top + 2, 3, &checkBoxClass, "Enable", 1, {&ui_configscreen.as_struct.rbGrid12, &ui_configscreen.as_struct.pdle, 0, &ui_configscreen.as_struct.pure}},
                .pure = {win_player_row1_top + 2, 23, &checkBoxClass, "Enable", 2, {&ui_configscreen.as_struct.rbGrid24, &ui_configscreen.as_struct.pdre, &ui_configscreen.as_struct.pule, 0}},
                .pdle = {win_player_row2_top + 2, 3, &checkBoxClass, "Enable", 8, {&ui_configscreen.as_struct.pule, &ui_configscreen.as_struct.buttonGo, 0, &ui_configscreen.as_struct.pdre}},
                .pdre = {win_player_row2_top + 2, 23, &checkBoxClass, "Enable", 4, {&ui_configscreen.as_struct.pure, &ui_configscreen.as_struct.buttonGo, &ui_configscreen.as_struct.pdle, 0}},

                .buttonGo = {go_button_top, 15, &buttonClass, "START GAME", 0, {&ui_configscreen.as_struct.pdle, 0, 0, 0}}
        }
};

//FIXME const ui_element_t **const radioButtonSetGridSize = ui_configscreen.as_array;
