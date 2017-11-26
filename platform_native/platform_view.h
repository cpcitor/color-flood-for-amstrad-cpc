#ifndef __PLATFORM_VIEW_H__
#define __PLATFORM_VIEW_H__

#include "../model.h"
#include "../model_podium.h"
#include <stdbool.h>

void cf_view_init( cf_model_t *model );

void platform_show_who_plays_next( cf_model_t *const this_model );
cf_cellState_t platform_show_possible_next_moves( cf_model_t *const this_model );
void platform_show_player_wished_color( cf_cellState_t player_wished_action );
void platform_hide_who_plays_next( const cf_model_t *const this_model );

#define platform_wait_for_key getchar

void cf_model_draw( const cf_model_t *const this_model );
void cf_model_dump( const cf_model_t *const this_model );
void cf_grid_draw( const cf_grid_t *const this_grid );
void cf_grid_dump( const cf_grid_t *const this_grid );

void cf_view_display_endgame_pause( cf_model_t *model, cf_podium_t *podium );

#endif /* __PLATFORM_VIEW_H__ */
