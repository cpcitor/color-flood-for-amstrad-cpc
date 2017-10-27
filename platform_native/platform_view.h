#ifndef __PLATFORM_VIEW_H__
#define __PLATFORM_VIEW_H__

#include "../model.h"

void cf_view_init( cf_model_t *model );

char platform_prompt_next_move( cf_model_t *const model );

void cf_model_draw( const cf_model_t *const this_model );
void cf_model_dump( const cf_model_t *const this_model );
void cf_grid_draw( const cf_grid_t *const this_grid );
void cf_grid_dump( const cf_grid_t *const this_grid );

#endif /* __PLATFORM_VIEW_H__ */
