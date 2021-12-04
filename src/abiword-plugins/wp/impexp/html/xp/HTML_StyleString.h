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


#ifndef HTML_STYLESTRING_H
#define HTML_STYLESTRING_H

#include "ut_types.h"

class ABI_EXPORT HTML_StyleString
{
 public:
  HTML_StyleString ();
  ~HTML_StyleString ();

  bool reset ();
  bool append (const char * name, const char * value);

  char * getString () const { return m_string; }

 private:
  bool grow (UT_uint32 require = 32);

  char * m_string;

  UT_uint32 m_length;
  UT_uint32 m_max;
};

#endif /* HTML_STYLESTRING_H */
