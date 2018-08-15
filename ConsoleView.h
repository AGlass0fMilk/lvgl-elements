/*
 * ConsoleView.h
 *
 *  Created on: Aug 15, 2018
 *      Author: gdbeckstein
 */

#ifndef LVGL_ELEMENTS_CONSOLEVIEW_H_
#define LVGL_ELEMENTS_CONSOLEVIEW_H_

#include "config.h"

extern "C" {
#if MBED_CONF_LVGL_ELEMENTS_MBED_BUILD
#include "lvgl.h"
#else
#include "../lvgl.h"
#endif
}

#include <stdint.h>

#if MBED_CONF_LVGL_ELEMENTS_USE_CONSOLE_VIEW

// A simple console view for displaying debug information
class ConsoleView
{

public:

	/**
	 * Construct a console view
	 * @param[in] parent The parent object to attach this view to
	 * @param[in] number_of_lines Maximum number of text lines to show
	 */
	ConsoleView(lv_obj_t* parent, int16_t number_of_lines);
	virtual ~ConsoleView();

	void print(const char* str);
	void info(const char* str);
	void warning(const char* str);
	void error(const char* str);

	void show(void);
	void hide(void);

	void set_position(int16_t x, int16_t y);
	void set_width(int16_t w);

	void set_font(lv_font_t* font);

	lv_obj_t* get_obj(void);

protected:

	void add_text(const char* str, lv_style_t* style);

protected:

	lv_style_t console_style;
	lv_style_t info_style;
	lv_style_t warning_style;
	lv_style_t error_style;

	lv_obj_t* container;
	lv_obj_t** lines;
	uint16_t num_lines;

};

#endif

#endif /* LVGL_ELEMENTS_CONSOLEVIEW_H_ */
