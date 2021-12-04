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

IE_Imp_HTML::TokenStack::TokenStack () :
  m_stack(0),
  m_count(0),
  m_max(0)
{
  //
}

IE_Imp_HTML::TokenStack::~TokenStack ()
{
  if (m_stack)
    {
      free (m_stack);
      m_stack = 0;
    }
  m_count = 0;
  m_max = 0;
}

bool IE_Imp_HTML::TokenStack::reset ()
{
  m_count = 0;
  return grow ();
}

bool IE_Imp_HTML::TokenStack::push (int token)
{
  if (!grow ()) return false;
  m_stack[m_count] = token;
  m_count++;
  return true;
}

int IE_Imp_HTML::TokenStack::pop ()
{
  if (m_count == 0) return -1;
  m_count--;
  return m_stack[m_count];
}

bool IE_Imp_HTML::TokenStack::child_of_head ()
{
  if (m_count == 2)
    {
      if ((m_stack[0] == TT_HTML) && (m_stack[1] == TT_HEAD)) return true;
      else return false;
    }
  else return false;
}

/* Ignore <center>, <div>, <pre>, <a> and <noframes> when determining child-of-body
 */
bool IE_Imp_HTML::TokenStack::child_of_body ()
{
  bool is_child = false;
  if (m_count >= 2)
    if ((m_stack[0] == TT_HTML) && (m_stack[1] == TT_BODY))
      {
	is_child = true;
	for (UT_uint32 i = 2; i < m_count; i++)
	  if (   (m_stack[i] != TT_DIV) && (m_stack[i] != TT_PRE) && (m_stack[i] != TT_A) && (m_stack[i] != TT_NOFRAMES)
	      && (m_stack[i] != TT_CENTER))
	    {
	      is_child = false;
	      break;
	    }
      }
  return is_child;
}

bool IE_Imp_HTML::TokenStack::descendant_of (int token)
{
  bool is_descendant = false;
  for (UT_uint32 i = 0; i < m_count; i++)
    if (m_stack[i] == token)
      {
	is_descendant = true;
	break;
      }
  return is_descendant;
}

bool IE_Imp_HTML::TokenStack::grow ()
{
  if (m_stack == 0)
    {
      m_count = 0;
      m_stack = (int *) malloc (16 * sizeof (int));
      if (m_stack == 0) return false;
      m_max = 16;
      return true;
    }

  if (m_count < m_max) return true;

  int * more = (int *) realloc (m_stack, (m_max + 16) * sizeof (int));
  if (more == 0) return false;
  m_stack = more;
  m_max += 16;
  return true;
}
