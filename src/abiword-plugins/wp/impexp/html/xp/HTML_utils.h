/* AbiWord: ie_imp_HTML - plugin for non-XHTML HTML
 * Copyright (C) 2002 Francis James Franklin <fjf@alinameridon.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 */


#include <string.h>

static const char * s_attrLookup (const char ** atts, const char * name)
{
  if ((atts == 0) || (name == 0)) return 0;

  const char ** attr = atts;
  const char * value = 0;

  while (*attr)
    {
      const char * attr_name = *attr;
      attr++;
      const char * attr_value = *attr;
      attr++;
      if (attr_name[0] != name[0]) continue;
      if (strcmp (attr_name, name) == 0)
	{
	  value = attr_value;
	  break;
	}
    }
  return value;
}
