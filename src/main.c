/*  Copyright (C) 2014 Colin Pronovost

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "xutil.h"
#include "event_callbacks.h"

int main (int argn, char **argv) {
	Display *dpy;
	Window win;
	GLXContext ctx;
	char *dpyName = NULL;

	//Do some init stuff
	make_window(dpyName, "4D sudoku", 0, 0, 300, 300, &dpy, &win, &ctx);
	XMapWindow(dpy, win);
	glXMakeCurrent(dpy, win, ctx);
	//TODO: load shaders

	//Run main OpenGL loop, includes user input
	do {
		//draw();
	} while (process_events(dpy, resize_callback, key_callback, mouse_callback));

	//Exit
	glXDestroyContext(dpy, ctx);
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}
