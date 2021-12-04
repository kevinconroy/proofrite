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

UT_Canvas::CanvasImage::CanvasImage () :
  m_width(0),
  m_height(0),
  m_image_max(0),
  m_Image(0)
{
  //
}

UT_Canvas::CanvasImage::~CanvasImage ()
{
  eraseCanvas ();
  FREEP (m_Image);
}

void UT_Canvas::CanvasImage::eraseCanvas ()
{
  for (UT_uint32 i = 0; i < m_height; i++) DELETEP (m_Image[i]);
  m_width = 0;
  m_height = 0;
}

bool UT_Canvas::CanvasImage::resetCanvas (UT_RGBAColor & color, UT_uint32 width, UT_uint32 height)
{
  if ((width == m_width) && (height == m_height))
    {
      if ((width == 0) || (height == 0)) return false;

      bool success = true;
      for (UT_uint32 i = 0; i < height; i++)
	if (!m_Image[i]->setColor (0, color, width, true)) success = false;
      return success;
    }

  eraseCanvas ();

  if ((width == 0) || (height == 0)) return false;

  if (m_Image == 0)
    {
      m_Image = (CanvasHSet **) malloc (height * sizeof (CanvasHSet *));
      if (m_Image == 0) return false;
      m_image_max = height;
    }
  if (height > m_image_max)
    {
      CanvasHSet ** more = (CanvasHSet **) realloc ((void *) m_Image, height * sizeof (CanvasHSet *));
      if (more == 0) return false;
      m_Image = more;
      m_image_max = height;
    }

  for (UT_uint32 i = 0; i < height; i++)
    {
      m_height++;
      m_Image[i] = new CanvasHSet;
      if (!m_Image[i]->setColor (0, color, width, true))
	{
	  eraseCanvas ();
	  return false;
	}
    }
  m_width = width;

  return true;
}

bool UT_Canvas::CanvasImage::copyColor (UT_Canvas * dest,
					UT_sint32 dest_x, UT_sint32 dest_y, UT_uint32 dest_width, UT_uint32 dest_height,
					UT_sint32 src_x,  UT_sint32 src_y,  UT_uint32 src_width,  UT_uint32 src_height)
{
  if (dest == 0) return false;
  if ((src_width == 0) || (dest_width == 0) || (src_height == 0) || (dest_height == 0)) return false;

  if ((src_x >= m_width)  || (src_x + src_width  <= 0)) return true;
  if ((src_y >= m_height) || (src_y + src_height <= 0)) return true;

  if ((src_width == dest_width) && (src_height == dest_height)) // no need to scale
    {
      bool success = true;
      for (UT_sint32 y = src_y; y < src_y + src_height; y++)
	if ((y >= 0) && (y < m_height))
	  if (!dest->setColor (dest_x, dest_y + y - src_y, m_Image[y], src_x, src_width)) success = false;
      return success;
    }

  CanvasHSet hset;
  UT_RGBAColor blank;
  if (!hset.setColor (0, blank, dest_width, true)) return false;

  if (src_height == dest_height) // lateral scaling only
    {
      bool success = true;
      for (UT_sint32 y = src_y; y < src_y + src_height; y++)
	if ((y >= 0) && (y < m_height))
	  {
	    CanvasHSet * src = m_Image[y];

	    UT_sint32 sx = src_x;
	    UT_RGBAColor scl = src->getColor (sx);
	    UT_RGBAColor scr = src->getColor (sx + 1);
	    UT_sint32 offset = 0;
	    for (UT_sint32 dx = 0; dx < dest_width; dx++)
	      {
		UT_RGBAColor color;
		color.m_r = (unsigned char) ((  ((UT_sint32) scl.m_r) * (dest_width - offset) +
						((UT_sint32) scr.m_r) *               offset    ) / dest_width);
		color.m_g = (unsigned char) ((  ((UT_sint32) scl.m_g) * (dest_width - offset) +
						((UT_sint32) scr.m_g) *               offset    ) / dest_width);
		color.m_b = (unsigned char) ((  ((UT_sint32) scl.m_b) * (dest_width - offset) +
						((UT_sint32) scr.m_b) *               offset    ) / dest_width);
		color.m_a = (unsigned char) ((  ((UT_sint32) scl.m_a) * (dest_width - offset) +
						((UT_sint32) scr.m_a) *               offset    ) / dest_width);

		if (!hset.setColor (dx, color)) success = false;

		offset += src_width;
		while (offset >= dest_width)
		  {
		    sx++;
		    scl = scr;
		    scr = src->getColor (sx + 1);
		    offset -= dest_width;
		  }
	      }

	    if (!dest->setColor (dest_x, dest_y + y - src_y, &hset, 0, dest_width)) success = false;
	  }
      return success;
    }
}
