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

#include <stdlib.h>
#include <stdio.h>
#include <GL/glx.h>

#include "xutil.h"
#include "event_callbacks.h"

/*
 * Create an RGB, double-buffered window.
 * Return the window and context handles.
 */
void make_window (char *dpyName, const char *name, int x, int y, int width, int height, Display **dpyRet, Window *winRet, GLXContext *ctxRet) {
	int attrib[] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 1, None };
	int scrnum;
	XSetWindowAttributes attr;
	unsigned long mask;
	Window root;
	Window win;
	GLXContext ctx;
	XVisualInfo *visinfo;

	*dpyRet = XOpenDisplay(dpyName);
	if (!(*dpyRet)) {
		printf("Error: couldn't open display %s\n", dpyName);
		exit(1);
	}

	scrnum = DefaultScreen(*dpyRet);
	root = RootWindow(*dpyRet, scrnum);

	visinfo = glXChooseVisual(*dpyRet, scrnum, attrib);
	if (!visinfo) {
		printf("Error: couldn't get an RGB, double-buffered visual\n");
		exit(1);
	}

	/* window attributes */
	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.colormap = XCreateColormap(*dpyRet, root, visinfo->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask;
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

	win = XCreateWindow(*dpyRet, root, 0, 0, width, height, 0, visinfo->depth, InputOutput, visinfo->visual, mask, &attr);

	/* set hints and properties */
	XSizeHints sizehints;
	sizehints.x = x;
	sizehints.y = y;
	sizehints.width = width;
	sizehints.height = height;
	sizehints.flags = USSize | USPosition;
	XSetNormalHints(*dpyRet, win, &sizehints);
	XSetStandardProperties(*dpyRet, win, name, name, None, (char **) NULL, 0, &sizehints);

	ctx = glXCreateContext(*dpyRet, visinfo, NULL, True);
	if (!ctx) {
		printf("Error: glXCreateContext failed\n");
		exit(1);
	}

	XFree(visinfo);

	*winRet = win;
	*ctxRet = ctx;
}

/*
 * Process events.
 * Return 0 when the user indicates that the program should close.
 */
int process_events(Display *dpy, resizeCallback resizeCB, keyCallback keyCB, mouseCallback mouseCB) {
	XEvent event;

	if (XPending(dpy) > 0) {
		XNextEvent(dpy, &event);
		switch (event.type) {
		case KeyPress:
			keyCB(XLookupKeysym(&event.xkey, 0));
			if (XLookupKeysym(&event.xkey, 0) == XK_Escape) return 0;
			break;
		case ConfigureNotify:
			resizeCB();
			break;
		case ButtonPress:
			mouseCB();
			break;
		default:
			break;
		}
	}

	return 1;
}
