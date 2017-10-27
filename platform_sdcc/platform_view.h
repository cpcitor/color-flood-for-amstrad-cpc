#ifndef __PLATFORM_VIEW_H__
#define __PLATFORM_VIEW_H__

#include "../model.h"
#include "screen.h"

#define cf_model_dump(...)

void cf_view_init( cf_model_t *model );

char platform_prompt_next_move( cf_model_t *const model );

void cf_model_draw( cf_model_t *model );
void cf_grid_draw( const cf_grid_t *const grid );

void show_key_color_association();

#endif /* __PLATFORM_VIEW_H__ */
