/*
 * config.h
 *
 *  Created on: Aug 15, 2018
 *      Author: gdbeckstein
 */

#ifndef LVGL_ELEMENTS_CONFIG_H_
#define LVGL_ELEMENTS_CONFIG_H_

// This will change some includes to be less annoying when using the mbed build system
#ifndef MBED_CONF_LVGL_ELEMENTS_MBED_BUILD
#define MBED_CONF_LVGL_ELEMENTS_MBED_BUILD 0

#ifndef MBED_CONF_LVGL_ELEMENTS_USE_CONSOLE_VIEW
#define MBED_CONF_LVGL_ELEMENTS_USE_CONSOLE_VIEW 1
#endif

#ifndef MBED_CONF_LVGL_ELEMENTS_CONSOLE_VIEW_DEFAULT_FONT
#define MBED_CONF_LVGL_ELEMENTS_CONSOLE_VIEW_DEFAULT_FONT lv_font_dejavu_10
#endif

#endif /* MBED_CONF_LVGL_ELEMENTS_MBED_BUILD */

#endif /* LVGL_ELEMENTS_CONFIG_H_ */
