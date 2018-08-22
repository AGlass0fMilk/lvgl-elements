/*
 * MbedConsole.h
 *
 * Wrapper so a console view can be used as a debug
 * output for mbed
 *
 *  Created on: Aug 15, 2018
 *      Author: gdbeckstein
 */

#ifndef LVGL_ELEMENTS_MBEDCONSOLE_H_
#define LVGL_ELEMENTS_MBEDCONSOLE_H_

#include "config.h"

#if MBED_CONF_LVGL_ELEMENTS_MBED_BUILD
#if MBED_CONF_LVGL_ELEMENTS_USE_CONSOLE_VIEW

#if 0
#warning this doesnt quite work yet!

#include "ConsoleView.h"
#include "platform/FileHandle.h"

class MbedConsole : public FileHandle
{

public:
	typedef enum
	{
		CONSOLE_PLAIN,
		CONSOLE_INFO,
		CONSOLE_WARNING,
		CONSOLE_ERROR
	} output_type_t;

public:
	MbedConsole(ConsoleView* console, output_type_t type) : _console(console),
	_type(type) { }

	virtual ~MbedConsole() {}

	/*** FileHandle methods */

	/** Read the contents of a file into a buffer
	 *
	 *  Devices acting as FileHandles should follow POSIX semantics:
	 *
	 *  * if no data is available, and non-blocking set return -EAGAIN
	 *  * if no data is available, and blocking set, wait until some data is available
	 *  * If any data is available, call returns immediately
	 *
	 *  @param buffer   The buffer to read in to
	 *  @param size     The number of bytes to read
	 *  @return         The number of bytes read, 0 at end of file, negative error on failure
	 */
	virtual ssize_t read(void *buffer, size_t size)
	{
		return -EAGAIN;
	}

	/** Write the contents of a buffer to a file
	 *
	 *  Devices acting as FileHandles should follow POSIX semantics:
	 *
	 * * if blocking, block until all data is written
	 * * if no data can be written, and non-blocking set, return -EAGAIN
	 * * if some data can be written, and non-blocking set, write partial
	 *
	 *  @param buffer   The buffer to write from
	 *  @param size     The number of bytes to write
	 *  @return         The number of bytes written, negative error on failure
	 */
	virtual ssize_t write(const void *buffer, size_t size)
	{
		char buf[size];
		memcpy(buf, buffer, size);
		buf[size-1] = '\0';

		switch(_type)
		{
		case CONSOLE_PLAIN:
			_console->print(buf);
			break;

		case CONSOLE_INFO:
			_console->info(buf);
			break;

		case CONSOLE_WARNING:
			_console->warning(buf);
			break;

		case CONSOLE_ERROR:
			_console->error(buf);
			break;
		}
		return size;
	}

	/** Move the file position to a given offset from from a given location
	 *
	 *  @param offset   The offset from whence to move to
	 *  @param whence   The start of where to seek
	 *      SEEK_SET to start from beginning of file,
	 *      SEEK_CUR to start from current position in file,
	 *      SEEK_END to start from end of file
	 *  @return         The new offset of the file, negative error code on failure
	 */
	virtual off_t seek(off_t offset, int whence = SEEK_SET)
	{
		return 0;
	}

	/** Close a file
	 *
	 *  @return         0 on success, negative error code on failure
	 */
	virtual int close()
	{
		return 0;
	}

protected:

	ConsoleView* _console;
	output_type_t _type;
};

#endif
#endif
#endif
#endif /* LVGL_ELEMENTS_MBEDCONSOLE_H_ */
