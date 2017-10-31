#ifndef __WIDGET_CLASSES_H__
#define __WIDGET_CLASSES_H__

#include "widget_base.h"

void draw_window( char *title, uint8_t top, uint8_t height, uint8_t left, uint8_t width );
void labelDraw( ui_element_t *element );
void radioButtonDraw( ui_element_t *element );
void checkBoxDraw( ui_element_t *element );

ui_class_t labelClass = {labelDraw, 0};
ui_class_t radioButtonClass = {radioButtonDraw, 0};
ui_class_t checkBoxClass = {checkBoxDraw, 0};
ui_class_t textInputClass = {labelDraw, 0};

#endif /* __WIDGET_CLASSES_H__ */
