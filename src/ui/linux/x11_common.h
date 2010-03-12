/**
 *  X11 common code
 *  Copyright (C) 2010 Andreas Öman
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef X11_COMMON_H__
#define X11_COMMON_H__

#include <X11/Xlib.h>
struct x11_screensaver_state;

struct x11_screensaver_state *x11_screensaver_suspend(Display *dpy);

void x11_screensaver_resume(struct x11_screensaver_state *s);

#endif
