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

UT_Canvas::CanvasMap::CanvasMap () :
  m_x(0),
  m_y(0)
{
  //
}

UT_Canvas::CanvasMap::~CanvasMap ()
{
  clearRegion ();
}

void UT_Canvas::CanvasMap::clearRegion ()
{
  FREEP (m_x);
  FREEP (m_y);
}

bool UT_Canvas::CanvasMap::setRegion (UT_uint32 lo_abs_width,  // width, height in layout units of whole figure
				      UT_uint32 lo_abs_height,
				      UT_uint32 lo_sub_x,      // x, y, width, height in layout units of visible sub-region
				      UT_uint32 lo_sub_y,      // (x,y) is minimum coordinate
				      UT_uint32 lo_sub_width,  // REQUIRE: lo_sub_width  >= px_sub_width
				      UT_uint32 lo_sub_height, // REQUIRE: lo_sub_height >= px_sub_height
				      UT_uint32 px_sub_width,  // width & height in screen pixels (at current zoom)
				      UT_uint32 px_sub_height  // of visible sub-region
				      )
{
  clearRegion ();

  if ((lo_abs_width == 0) || (lo_abs_height == 0)) return false;
  if ((lo_sub_width == 0) || (lo_sub_height == 0)) return false;
  if ((px_sub_width == 0) || (px_sub_height == 0)) return false;

  if ((lo_sub_x + lo_sub_width > lo_abs_width) || (lo_sub_y + lo_sub_height > lo_abs_height)) return false;

  m_x = (UT_uint32 *) malloc ((px_sub_width + 1) * sizeof (UT_uint32));
  if (m_x == 0) return false;

  m_y = (UT_uint32 *) malloc ((px_sub_height + 1) * sizeof (UT_uint32));
  if (m_y == 0)
    {
      FREEP (m_x);
      return false;
    }

  UT_uint32 sum = 0;
  UT_uint32 div = lo_sub_x;
  m_x[0] = lo_sub_x << 4;
  for (UT_uint32 i = 1; i < px_sub_width; i++)
    {
      sum += lo_sub_width;
      while (sum >= px_sub_width)
	{
	  sum -= px_sub_width;
	  div++;
	}
      m_x[i] = div << 4 + (sum << 4) / px_sub_width;
    }
  m_x[px_sub_width ] = (lo_sub_x + lo_sub_width ) << 4;

  sum = 0;
  div = lo_sub_y;
  m_y[0] = lo_sub_y << 4;
  for (UT_uint32 i = 1; i < px_sub_height; i++)
    {
      sum += lo_sub_height;
      while (sum >= px_sub_height)
	{
	  sum -= px_sub_height;
	  div++;
	}
      m_y[i] = div << 4 + (sum << 4) / px_sub_height;
    }
  m_y[px_sub_height] = (lo_sub_y + lo_sub_height) << 4;

  return true;
}
