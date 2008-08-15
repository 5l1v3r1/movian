/*
 *  Browser slideshow
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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include "showtime.h"
#include "browser.h"
#include "browser_view.h"
//#include "useraction.h"
#include "event.h"
#include "media.h"

void
browser_slideshow(browser_node_t *cur, glw_t *parent, glw_event_queue_t *geq)
{
  glw_t *top, *slideshow, *b;
  browser_node_t *dir = cur->bn_parent;
  browser_root_t *br  = cur->bn_root;
  browser_node_t *c, **a;
  int cnt, run = 1;
  int64_t type;
  glw_event_t *ge;
  mp_playstatus_t mps = MP_PLAY;
  glw_prop_t *prop_root, *prop_ps;

  prop_root = glw_prop_create(NULL, "slideshow", GLW_GP_DIRECTORY);
  prop_ps   = glw_prop_create(prop_root, "playstatus", GLW_GP_STRING);

  top = glw_model_create("theme://browser/slideshow/view.model", parent,
			 0, prop_global, prop_root, NULL);

  if((slideshow = glw_find_by_id(top, "slideshow", 0)) == NULL) {
      glw_destroy(top);
      glw_prop_destroy(prop_root);
      return;
  }

  a = browser_get_array_of_childs(br, dir);
  for(cnt = 0; (c = a[cnt]) != NULL; cnt++) {
    
    hts_mutex_lock(&c->bn_ftags_mutex);

    if(c->bn_type == FA_FILE &&
       !filetag_get_int(&c->bn_ftags, FTAG_FILETYPE, &type) &&
       type == FILETYPE_IMAGE) {

	b = glw_model_create("theme://browser/slideshow/node.model", slideshow,
			     GLW_MODEL_CACHE, 
			     c->bn_prop_root, prop_global, prop_root, NULL);
      if(c == cur)
	glw_select(b);
    }

    hts_mutex_unlock(&c->bn_ftags_mutex);

    browser_node_deref(c); /* 'c' may be free'd here */
  }

  free(a);

  while(run) {

    glw_set(slideshow, GLW_ATTRIB_TIME, 
	    mps == MP_PLAY ? 5.0 : 0.0, NULL);

    media_update_playstatus_prop(prop_ps, mps);

    ge = glw_event_get(-1, geq);

    switch(ge->ge_type) {
    default:
#if 0
      if (ie.u.key >= '0' && ie.u.key <= '9') {
	/* User-definable actions */
	if (useraction_slideshow(w, ie.u.key) != -1)
	  glw_send_signal(w, GLW_SIGNAL_NEXT, NULL);
      }
#endif
      break;

    case EVENT_KEY_PLAYPAUSE:
      mps = mps == MP_PLAY ? MP_PAUSE : MP_PLAY;
      break;

    case EVENT_KEY_PLAY:
      mps = MP_PLAY;
      break;
      
    case EVENT_KEY_PAUSE:
      mps = MP_PAUSE;
      break;
      
    case GEV_BACKSPACE:
      run = 0;
      break;

    case EVENT_KEY_NEXT:
      glw_event_signal_simple(slideshow, GEV_INCR);
      break;

    case EVENT_KEY_PREV:
    case EVENT_KEY_RESTART_TRACK:
      glw_event_signal_simple(slideshow, GEV_DECR);
      break;
    }
  }


  glw_detach(top);
  glw_prop_destroy(prop_root);
}
