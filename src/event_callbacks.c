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

#include "event_callbacks.h"

void mouse_callback () {
	printf("Mouse event\n");
}

void key_callback (int key_sym) {
	printf("Key event\n");
}

void resize_callback (int width, int height) {
	printf("Configure Notify\n");

	glViewport(0, 0, width, height);
}
