#ifndef __WIDGET_CONFIG_SCREEN_H__
#define __WIDGET_CONFIG_SCREEN_H__

#include "widget_base.h"

typedef struct ui_configscreen_t
{
        const ui_element_t rbGrid12;
        const ui_element_t rbGrid16;
        const ui_element_t rbGrid24;

        const ui_element_t pule;
        const ui_element_t pure;
        const ui_element_t pdle;
        const ui_element_t pdre;

        const ui_element_t buttonGo;
} ui_configscreen_t;

enum {ui_configscreen_element_count = 8};

typedef const union
{
        const ui_configscreen_t as_struct;
        const ui_element_t as_array[ui_configscreen_element_count];
} ui_configscreen_union_t;

extern const ui_configscreen_union_t ui_configscreen;

enum { radioButtonSetGridSizeCount = 3 };

//extern const ui_element_t *const radioButtonSetGridSize[radioButtonSetGridSizeCount];


#define gui_top (12)

#define win_radio_height (3)
#define win_player_height (5)

#define win_radio_top (gui_top)
#define win_player_row1_top (win_radio_top+win_radio_height)
#define win_player_row2_top (win_player_row1_top + win_player_height)
#define go_button_top (win_player_row2_top + win_player_height)


#endif /* __WIDGET_CONFIG_SCREEN_H__ */
