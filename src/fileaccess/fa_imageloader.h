/*
 *  Imageloader
 *  Copyright (C) 2008 Andreas Öman
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

#ifndef FA_IMAGELOADER_H
#define FA_IMAGELOADER_H

#include "misc/pixmap.h"
struct backend;

pixmap_t *fa_imageloader(const char *url,int want_thumb, const char **vpaths,
			 char *errbuf, size_t errlen);

#endif /* FA_IMAGELOADER_H */
