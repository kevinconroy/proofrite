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


#include <stdlib.h>
#include <string.h>

#include "HTML_StyleString.h"

HTML_StyleString::HTML_StyleString () :
  m_string(0),
  m_length(0),
  m_max(0)
{
  //
}

HTML_StyleString::~HTML_StyleString ()
{
  if (m_string)
    {
      free (m_string);
      m_string = 0;
    }
  m_length = 0;
  m_max = 0;
}

bool HTML_StyleString::reset ()
{
  m_length = 0;
  if (!grow ()) return false;
  m_string[0] = 0;
  return true;
}

bool HTML_StyleString::append (const char * name, const char * value)
{
  if ((name == 0) || (value == 0)) return false;

  UT_uint32 len_name  = strlen (name);
  UT_uint32 len_value = strlen (value);

  if (!grow (len_name + len_value + (UT_uint32) 4)) return false;

  if (m_length)
    {
      strcat (m_string + m_length, "; ");
      m_length += 2;
    }

  strcat (m_string + m_length, name);
  m_length += len_name;

  strcat (m_string + m_length, ":");
  m_length++;

  strcat (m_string + m_length, value);
  m_length += len_value;
  return true;
}

bool HTML_StyleString::grow (UT_uint32 require /* = 32 */)
{
  if (m_string == 0)
    {
      m_length = 0;
      m_string = (char *) malloc (require * sizeof (char));
      if (m_string == 0) return false;
      m_max = require;
      return true;
    }

  if ((m_length + require) < m_max) return true;

  char * more = (char *) realloc (m_string, (m_max + require) * sizeof (char));
  if (more == 0) return false;
  m_string = more;
  m_max += require;
  return true;
}
