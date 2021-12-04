/* AbiWord: HTML_Parser class, uses libxml2
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

#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include "ut_types.h"

class ABI_EXPORT HTML_Parser
{
 public:
  HTML_Parser();
  ~HTML_Parser();

  bool sniff (const char * buffer, int length);
  bool parse (const char * filename);

  void stop () { m_bStopped = true; }

  void startElement (const char * name, const char ** atts);
  void endElement (const char * name);
  void charData (const char * buffer, int length);

  class ABI_EXPORT Listener
    {
    public:
      virtual ~Listener () { };

      virtual void startElement (const char * name, const char ** atts) = 0;
      virtual void endElement (const char * name) = 0;
      virtual void charData (const char * buffer, int length) = 0;
    };

  void setListener (Listener * pListener) { m_pListener = pListener; }

 private:
  bool m_bStopped;
  bool m_bValid;

  Listener * m_pListener;
};

#endif /* HTML_PARSER_H */
