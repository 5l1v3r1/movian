/*
 *  Ptr vector
 *  Copyright (C) 2009 Andreas Öman
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

#ifndef PTRVEC_H__
#define PTRVEC_H__

typedef struct ptrvec {
  unsigned int capacity;
  unsigned int size;
  void **vec;
} ptrvec_t;

#define ptrvec_size(pv) ((pv)->size)

void ptrvec_insert_entry(ptrvec_t *pv, unsigned int position, void *ptr);

void *ptrvec_remove_entry(ptrvec_t *pv, unsigned int position);

void *ptrvec_get_entry(ptrvec_t *pv, unsigned int position);

#endif
