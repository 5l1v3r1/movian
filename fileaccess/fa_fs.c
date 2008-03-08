/*
 *  File browser
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

#define _GNU_SOURCE

#include <pthread.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include "showtime.h"
#include "fa_fs.h"

static int 
scan_filter(const struct dirent *d)
{
  if(d->d_name[0] == '.')
    return 0;
  return 1;
}

static void
fs_urlsnprintf(char *buf, size_t bufsize, const char *prefix, const char *base,
	       const char *fname)
{
  if(!strcmp(base, "/"))
    base = "";
  snprintf(buf, bufsize, "%s%s/%s", prefix, base, fname);
}
	       


static int
fs_scandir(const char *url, fa_scandir_callback_t *cb, void *arg)
{
  char buf[1000];
  struct stat st;
  struct dirent **namelist, *d;
  int n, type, i;

  n = scandir(url, &namelist, scan_filter, versionsort);

  if(n < 0) {
    return -1;
  } else {
    for(i = 0; i < n; i++) {
      d = namelist[i];

      fs_urlsnprintf(buf, sizeof(buf), "", url, d->d_name);

      if(stat(buf, &st))
	continue;

      switch(st.st_mode & S_IFMT) {
      case S_IFDIR:
	type = FA_DIR;
	break;
      case S_IFREG:
	type = FA_FILE;
	break;
      default:
	continue;
      }


      fs_urlsnprintf(buf, sizeof(buf), "file://", url, d->d_name);

      cb(arg, buf, d->d_name, type);
    }
    free(namelist);
  }
  return 0;
}


fa_protocol_t fa_protocol_fs = {
  .fap_name = "file",
  .fap_scan = fs_scandir,
};
