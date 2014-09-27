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

#ifndef XUTIL_H_
#define XUTIL_H_

#include <GL/glx.h>

/*
 * Create an RGB, double-buffered window.
 * Return the window and context handles.
 */
extern void make_window (Display *dpy, const char *name, int x, int y, int width, int height, Window *winRet, GLXContext *ctxRet);

#endif /* XUTIL_H_ */
