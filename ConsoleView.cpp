/*
 * ConsoleView.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: gdbeckstein
 */

#if MBED_CONF_LVGL_ELEMENTS_USE_CONSOLE_VIEW

#include "ConsoleView.h"

ConsoleView::ConsoleView(lv_obj_t* parent, int16_t number_of_lines) : num_lines(number_of_lines)
{
	// Create the styles
	lv_style_copy(&console_style, &lv_style_plain);
	console_style.body.main_color = LV_COLOR_BLACK;
	console_style.body.grad_color = LV_COLOR_BLACK;
	console_style.body.border.color = LV_COLOR_BLACK;
	console_style.body.border.width = 0;
	console_style.text.font = MBED_CONF_LVGL_ELEMENTS_CONSOLE_VIEW_DEFULAT_FONT;
	console_style.text.color = LV_COLOR_WHITE;

	lv_style_copy(&info_style, &console_style);
	info_style.text.color = LV_COLOR_BLUE;

	lv_style_copy(&warning_style, &console_style);
	warning_style.text.color = LV_COLOR_ORANGE;

	lv_style_copy(&error_style, &console_style);
	error_style.text.color = LV_COLOR_RED;

	// Create the main container
	container = lv_cont_create(parent, NULL);
	lv_obj_set_style(container, &console_style);
	lv_cont_set_layout(container, LV_LAYOUT_COL_L);

	// Create all the children objects
	lines = new lv_obj_t*[number_of_lines]();
	for(int i = 0; i < number_of_lines; i++)
	{
		lines[i] = lv_label_create(container, NULL);
		lv_obj_set_style(lines[i], &console_style);
		lv_label_set_long_mode(lines[i], LV_LABEL_LONG_DOT);
		lv_label_set_text(lines[i], "test");
	}

}

ConsoleView::~ConsoleView() {

	// Delete the main container (will delete all of its children)
	lv_obj_del(container);
	container = NULL;

	// Delete the lines list
	delete[] lines;
	lines = NULL;

}

void ConsoleView::print(std::string str) {
	add_text(str, &console_style);
}

void ConsoleView::info(std::string str) {
	add_text(str, &info_style);
}

void ConsoleView::warning(std::string str) {
	add_text(str, &warning_style);
}

void ConsoleView::error(std::string str) {
	add_text(str, &error_style);
}

void ConsoleView::show(void) {
	lv_obj_set_hidden(container, false);
}

void ConsoleView::hide(void) {
	lv_obj_set_hidden(container, true);
}

void ConsoleView::set_position(int16_t x, int16_t y) {
	lv_obj_set_pos(container, x, y);
}

void ConsoleView::set_font(lv_font_t* font) {
	console_style.text.font = font;
	info_style.text.font = font;
	warning_style.text.font = font;
	error_style.text.font = font;
}

void ConsoleView::add_text(std::string str, lv_style_t* style) {
}

#endif
