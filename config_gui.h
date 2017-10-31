#ifndef __CONFIG_GUI_H__
#define __CONFIG_GUI_H__

#include "widget_base.h"

void config_gui_init( void );

enum { radioButtonSetGridSizeCount = 3 };

extern ui_element_t *radioButtonSetGridSize[radioButtonSetGridSizeCount];

#endif /* __CONFIG_GUI_H__ */
