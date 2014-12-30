#ifndef __PLATFORM_VIEW_H__
#define __PLATFORM_VIEW_H__

#include "screen.h"

#define cf_model_dump(...)

void cf_model_draw( cf_model_t *model );
void cf_grid_draw( const cf_grid_t *const grid );

#endif /* __PLATFORM_VIEW_H__ */
