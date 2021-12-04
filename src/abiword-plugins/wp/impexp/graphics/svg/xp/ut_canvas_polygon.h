/* AbiSource Program Utilities
 * Copyright (C) 2002 Francis James Franklin
 * Copyright (C) 2002 AbiSource, Inc.
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

UT_Canvas::CanvasPolygon::CanvasPolygon () :
  m_max(0),
  m_count(0),
  m_x(0),
  m_y(0),
  m_PolygonRule(pr_EvenOdd),
  m_lc_y_min(0),
  m_lc_y_max(0),
  m_lc_max(0),
  m_lc_count(0),
  m_lc_x1(0),
  m_lc_y1(0),
  m_lc_x2(0),
  m_lc_y2(0),
  m_lc_xi(0)
{
  //
}

UT_Canvas::CanvasPolygon::~CanvasPolygon ()
{
  FREEP (m_x);
  FREEP (m_y);
  FREEP (m_lc_x1);
  FREEP (m_lc_y1);
  FREEP (m_lc_x2);
  FREEP (m_lc_y2);
  FREEP (m_lc_xi);
}

bool UT_Canvas::CanvasPolygon::reset ()
{
  clearLineCache ();

  m_count = 0;
  return grow ();
}

bool UT_Canvas::CanvasPolygon::addPoint (UT_uint32 xvi_x, UT_uint32 xvi_y)
{
  if (!grow ()) return false;

  clearLineCache ();

  m_x[m_count] = xvi_x;
  m_y[m_count] = xvi_y;
  m_count++;

  return true;
}

bool UT_Canvas::CanvasPolygon::grow ()
{
  if (m_count < m_max) return true;

  if (m_max == 0)
    {
      m_x = (UT_uint32 *) malloc (16 * sizeof (UT_uint32));
      if (m_x == 0)
	{
	  return false;
	}
      m_y = (UT_uint32 *) malloc (16 * sizeof (UT_uint32));
      if (m_y == 0)
	{
	  FREEP (m_x);
	  return false;
	}
      m_max = 16;
      return true;
    }

  UT_uint32 * more = 0;

  more = (UT_uint32 *) realloc ((void *) m_x, (m_max + 16) * sizeof (UT_uint32));
  if (more == 0) return false;
  m_x = more;

  more = (UT_uint32 *) realloc ((void *) m_y, (m_max + 16) * sizeof (UT_uint32));
  if (more == 0) return false;
  m_y = more;

  m_max += 16;
  return true;
}

unsigned char UT_Canvas::CanvasPolygon::getAlpha (UT_uint32 xvi_x_min, UT_uint32 xvi_y_min,
						  UT_uint32 xvi_x_max, UT_uint32 xvi_y_max)
{
  if (!resetLineCache (xvi_y_min, xvi_y_max)) return 0x00;

  unsigned char alpha = 0x00;

  for (UT_uint32 xvi_y = xvi_y_min; xvi_y <= xvi_y_max; xvi_y++)
    {
      if (!calcIntercepts (xvi_y)) break;
      sortIntercepts ();

      unsigned char line_alpha = getLineAlpha (xvi_y, xvi_x_min, xvi_x_max);
      // 
    }

  return alpha;
}

unsigned char UT_Canvas::CanvasPolygon::getLineAlpha (UT_uint32 xvi_y, UT_uint32 xvi_x_min, UT_uint32 xvi_x_max)
{
  if (m_lc_count == 0) return 0x00;

  UT_uint32 x;
  for (UT_uint32 i = 0; i < m_lc_count; i++)
    {
      bool up = false;
      UT_sint32 xi = m_lc_xi[i];
      if (xi < 0)
	{
	  xi = - xi;
	  up = true;
	}

      // 
    }

  switch (m_PolygonRule)
    {
    case pr_EvenOdd:
    case pr_NonExterior:
    case pr_NonzeroWinding:
      break;
    }
  return 0;
}

bool UT_Canvas::CanvasPolygon::calcIntercepts (UT_uint32 y)
{
  if ((y < m_lc_y_min) || (y > m_lc_y_max)) return false;

  for (UT_uint32 i = 0; i < m_lc_count; i++)
    {
      if (m_lc_x1[i] == m_lc_x2[i])
	m_lc_xi[i] = m_lc_x1[i];
      else
	m_lc_xi[i] = m_lc_x1[i] + ((y - m_lc_y1[i]) * (m_lc_x2[i] - m_lc_x1[i])) / (m_lc_y2[i] - m_lc_y1[i]);

      if ((m_lc_y1[i] <= y) && (m_lc_y2[i] >= y)) // line crossing up
	{
	  m_lc_xi[i] = - m_lc_xi[i]; // i.e., invert 'sense'
	}
    }
  return true;
}

void UT_Canvas::CanvasPolygon::sortIntercepts ()
{
  // I'm not very good at sorting, so this next bit probably sucks
  // Need to sort on absolute value; also, [+n] cancels a [-n], if you like

  for (UT_uint32 i1 = 0; i1 < m_lc_count - 1; i1++)
    {
      UT_sint32 v1 = m_lc_xi[i1];
      if (v1 < 0) v1 = - v1;

      for (UT_uint32 i2 = i1 + 1; i2 < m_lc_count; i2++)
	{
	  UT_sint32 v2 = m_lc_xi[i2];
	  if (v2 < 0) v2 = - v2;

	  if (v2 < v1) // swap
	    {
	      v1 = v2;
	      UT_sint32 t = m_lc_xi[i2];
	      m_lc_xi[i2] = m_lc_xi[i1];
	      m_lc_xi[i1] = t;
	    }
	}
    }
}

void UT_Canvas::CanvasPolygon::sortLineCache ()
{
  // I'm not very good at sorting, so this next bit probably sucks
  // Sort on absolute value of intercept

  for (UT_uint32 i1 = 0; i1 < m_lc_count - 1; i1++)
    {
      UT_sint32 v1 = m_lc_xi[i1];
      if (v1 < 0) v1 = - v1;

      for (UT_uint32 i2 = i1 + 1; i2 < m_lc_count; i2++)
	{
	  UT_sint32 v2 = m_lc_xi[i2];
	  if (v2 < 0) v2 = - v2;

	  if (v2 < v1) // swap
	    {
	      v1 = v2;
	      UT_sint32 t = m_lc_xi[i2];
	      m_lc_xi[i2] = m_lc_xi[i1];
	      m_lc_xi[i1] = t;

	      t = m_lc_x1[i2]; m_lc_x1[i2] = m_lc_x1[i1]; m_lc_x1[i1] = t;
	      t = m_lc_y1[i2]; m_lc_y1[i2] = m_lc_y1[i1]; m_lc_y1[i1] = t;
	      t = m_lc_x2[i2]; m_lc_x2[i2] = m_lc_x2[i1]; m_lc_x2[i1] = t;
	      t = m_lc_y2[i2]; m_lc_y2[i2] = m_lc_y2[i1]; m_lc_y2[i1] = t;
	    }
	}
    }
}

void UT_Canvas::CanvasPolygon::clearLineCache ()
{
  m_lc_y_min = 0;
  m_lc_y_max = 0;

  m_lc_count = 0;
}

bool UT_Canvas::CanvasPolygon::resetLineCache (UT_uint32 xvi_y_min, UT_uint32 xvi_y_max)
{
  if (m_count < 3) return false; // not a polygon
  if (xvi_y_min >= xvi_y_max) return false;
  if ((xvi_y_min == m_lc_y_min) && (xvi_y_max == m_lc_y_max)) return true; // LineCache is valid

  m_lc_y_min = xvi_y_min;
  m_lc_y_max = xvi_y_max;

  /* Build line cache
   */
  bool success = true;
  UT_uint32 x_prev = m_x[m_count-1];
  UT_uint32 y_prev = m_y[m_count-1];
  for (UT_uint32 i = 0; i < m_count; i++)
    {
      UT_uint32 x = m_x[i];
      UT_uint32 y = m_y[i];

      if (y != y_prev) // ignore horizontal lines
	if ( ((y_prev >= m_lc_y_min) && (y <= m_lc_y_max)) || ((y >= m_lc_y_min) && (y_prev <= m_lc_y_max)) )
	  {
	    /* This polygon edge is in scope of the scanline; add it to the cache
	     */
	    success = growLineCache ();
	    if (!success) break;

	    m_lc_x1[m_lc_count] = x_prev;
	    m_lc_y1[m_lc_count] = y_prev;
	    m_lc_x2[m_lc_count] = x;
	    m_lc_y2[m_lc_count] = y;
	    m_lc_count++;
	  }

      x_prev = x;
      y_prev = y;
    }
  if (success)
    success = calcIntercepts (m_lc_y_min);

  if (success)
    {
      sortLineCache ();
    }
  else
    {
      clearLineCache ();
    }

  return success;
}

bool UT_Canvas::CanvasPolygon::growLineCache ()
{
  if (m_lc_count < m_lc_max) return true;

  if (m_lc_max == 0)
    {
      m_lc_x1 = (UT_uint32 *) malloc (16 * sizeof (UT_uint32));
      if (m_lc_x1 == 0)
	{
	  return false;
	}
      m_lc_y1 = (UT_uint32 *) malloc (16 * sizeof (UT_uint32));
      if (m_lc_y1 == 0)
	{
	  FREEP (m_lc_x1);
	  return false;
	}
      m_lc_x2 = (UT_uint32 *) malloc (16 * sizeof (UT_uint32));
      if (m_lc_x2 == 0)
	{
	  FREEP (m_lc_x1);
	  FREEP (m_lc_y1);
	  return false;
	}
      m_lc_y2 = (UT_uint32 *) malloc (16 * sizeof (UT_uint32));
      if (m_lc_y2 == 0)
	{
	  FREEP (m_lc_x1);
	  FREEP (m_lc_y1);
	  FREEP (m_lc_x2);
	  return false;
	}
      m_lc_xi = (UT_sint32 *) malloc (16 * sizeof (UT_sint32));
      if (m_lc_xi == 0)
	{
	  FREEP (m_lc_x1);
	  FREEP (m_lc_y1);
	  FREEP (m_lc_x2);
	  FREEP (m_lc_y2);
	  return false;
	}
      m_lc_max = 16;
      return true;
    }

  UT_uint32 * more = 0;

  more = (UT_uint32 *) realloc ((void *) m_lc_x1, (m_lc_max + 16) * sizeof (UT_uint32));
  if (more == 0) return false;
  m_lc_x1 = more;

  more = (UT_uint32 *) realloc ((void *) m_lc_y1, (m_lc_max + 16) * sizeof (UT_uint32));
  if (more == 0) return false;
  m_lc_y1 = more;

  more = (UT_uint32 *) realloc ((void *) m_lc_x2, (m_lc_max + 16) * sizeof (UT_uint32));
  if (more == 0) return false;
  m_lc_x2 = more;

  more = (UT_uint32 *) realloc ((void *) m_lc_y2, (m_lc_max + 16) * sizeof (UT_uint32));
  if (more == 0) return false;
  m_lc_y2 = more;

  more = (UT_uint32 *) realloc ((void *) m_lc_xi, (m_lc_max + 16) * sizeof (UT_uint32));
  if (more == 0) return false;
  m_lc_xi = more;

  m_lc_max += 16;
  return true;
}
