#ifndef __GUI_LOOP_H__
#define __GUI_LOOP_H__

#include "widget_base.h"

void radioButtonAction( ui_element_t *source );
void checkBoxAction( ui_element_t *source );
void buttonAction( ui_element_t *source );

void gui_loop( ui_element_t *first_selected_element );

#endif /* __GUI_LOOP_H__ */


