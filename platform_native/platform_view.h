#ifndef __PLATFORM_VIEW_H__
#define __PLATFORM_VIEW_H__

#include "../model.h"
#include "../model_podium.h"
#include <stdbool.h>

void cf_view_init( cf_model_t *model );

char platform_prompt_next_move( cf_model_t *const model );

void cf_model_draw( const cf_model_t *const this_model );
void cf_model_dump( const cf_model_t *const this_model );
void cf_grid_draw( const cf_grid_t *const this_grid );
void cf_grid_dump( const cf_grid_t *const this_grid );

bool cf_view_display_endgame_should_we_play_again( cf_model_t *model, cf_podium_t *podium );

#endif /* __PLATFORM_VIEW_H__ */
