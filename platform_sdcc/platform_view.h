#ifndef __PLATFORM_VIEW_H__
#define __PLATFORM_VIEW_H__

#include "../model.h"
#include "../model_podium.h"
#include "screen.h"

#define cf_model_dump(...)

void cf_view_init( cf_model_t *model );

char platform_prompt_next_move( cf_model_t *const model );

void cf_model_draw( cf_model_t *model );
void cf_grid_draw( const cf_grid_t *const grid );
void cf_player_area_bars( const cf_model_t *const model );
uint8_t state_to_color( cf_cellState_t state );

void show_key_color_association();

bool cf_view_display_endgame_should_we_play_again( cf_model_t *model, cf_podium_t *podium );

#endif /* __PLATFORM_VIEW_H__ */
