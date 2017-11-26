#ifndef __PLATFORM_VIEW_H__
#define __PLATFORM_VIEW_H__

#include "../model.h"
#include "../model_podium.h"
#include "screen.h"

#define cf_model_dump(...)

void cf_view_init( cf_model_t *model );

void platform_show_who_plays_next( cf_model_t *const this_model );
cf_cellState_t platform_show_possible_next_moves( cf_model_t *const this_model );
void platform_show_player_wished_color( cf_cellState_t player_wished_action );
void platform_hide_who_plays_next( const cf_model_t *const this_model );

void cf_model_draw( cf_model_t *model );
void cf_grid_draw( const cf_grid_t *const grid );
void cf_player_area_bars( const cf_model_t *const model );
uint8_t state_to_color( cf_cellState_t state );

void cf_view_display_endgame_pause( cf_model_t *this_model, cf_podium_t *podium );

#endif /* __PLATFORM_VIEW_H__ */
