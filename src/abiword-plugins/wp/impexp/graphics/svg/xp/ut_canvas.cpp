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


#include "ut_canvas.h"

#include "ut_canvas_hset.h"
#include "ut_canvas_image.h"
#include "ut_canvas_map.h"
#include "ut_canvas_png.h"
#include "ut_canvas_polygon.h"

UT_Canvas::UT_Canvas () :
  m_CanvasMode(cm_Canvas),
  m_left(0),
  m_right(0),
  m_top(0),
  m_bottom(0),
  m_BlendMode(bm_SrcCpy),
  m_HSet(128),
  m_empty(true)
{
  //
}

UT_Canvas::~UT_Canvas ()
{
  UT_VECTOR_PURGEALL (CanvasHSet *, m_HSet);
}

bool UT_Canvas::setAlpha (UT_sint32 x, UT_sint32 y, unsigned char a)
{
  xSet (x);
  ySet (y);

  bool create = (a ? true : false);
  CanvasHSet * hset = getHSet (y, create);
  if (hset)
    {
      hset->setBlend (m_BlendMode);
      return hset->setAlpha (x, a);
    }
  return (create ? false : true);
}

bool UT_Canvas::setColor (UT_sint32 x, UT_sint32 y, const UT_RGBAColor & rgba)
{
  xSet (x);
  ySet (y);

  bool create = ((rgba.m_r || rgba.m_g || rgba.m_b || rgba.m_a) ? true : false);
  CanvasHSet * hset = getHSet (y, create);
  if (hset)
    {
      hset->setBlend (m_BlendMode);
      return hset->setColor (x, rgba);
    }
  return (create ? false : true);
}

bool UT_Canvas::setAlpha (UT_sint32 offset_x, UT_sint32 offset_y, unsigned char a,
			  UT_uint32 width, UT_uint32 height, bool force_pixel)
{
  xSet (offset_x);
  xSet (offset_x + width - 1);
  ySet (offset_y);
  ySet (offset_y + height - 1);

  bool create = ((force_pixel || a) ? true : false);
  bool success = true;
  for (UT_sint32 y = offset_y; y < offset_y + height; y++)
    {
      CanvasHSet * hset = getHSet (y, create);
      if (hset)
	{
	  hset->setBlend (m_BlendMode);
	  if (!hset->setAlpha (offset_x, a, width, force_pixel)) success = false;
	}
      else if (create) success = false;
    }
  return success;
}

bool UT_Canvas::setColor (UT_sint32 offset_x, UT_sint32 offset_y, const UT_RGBAColor & rgba, 
			  UT_uint32 width, UT_uint32 height, bool force_pixel)
{
  xSet (offset_x);
  xSet (offset_x + width - 1);
  ySet (offset_y);
  ySet (offset_y + height - 1);

  bool create = ((force_pixel || (rgba.m_r || rgba.m_g || rgba.m_b || rgba.m_a)) ? true : false);
  bool success = true;
  for (UT_sint32 y = offset_y; y < offset_y + height; y++)
    {
      CanvasHSet * hset = getHSet (y, create);
      if (hset)
	{
	  hset->setBlend (m_BlendMode);
	  if (!hset->setColor (offset_x, rgba, width, force_pixel)) success = false;
	}
      else if (create) success = false;
    }
  return success;
}

bool UT_Canvas::setAlpha (UT_sint32 x, UT_sint32 y, const CanvasHSet * src, UT_sint32 src_x, UT_uint32 length)
{
  if (src == 0) return false;

  xSet (x);
  xSet (x + length - 1);
  ySet (y);

  CanvasHSet * hset = getHSet (y, true);
  if (hset)
    {
      hset->setBlend (m_BlendMode);
      return src->copyAlpha (hset, x, src_x, length);
    }
  return false;
}

bool UT_Canvas::setColor (UT_sint32 x, UT_sint32 y, const CanvasHSet * src, UT_sint32 src_x, UT_uint32 length)
{
  if (src == 0) return false;

  xSet (x);
  xSet (x + length - 1);
  ySet (y);

  CanvasHSet * hset = getHSet (y, true);
  if (hset)
    {
      hset->setBlend (m_BlendMode);
      return src->copyColor (hset, x, src_x, length);
    }
  return false;
}

unsigned char UT_Canvas::getAlpha (UT_sint32 x, UT_sint32 y) const
{
  CanvasHSet * hset = getHSet (y);
  if (hset)
    return hset->getAlpha (x);
  return 0;
}

const UT_RGBAColor UT_Canvas::getColor (UT_sint32 x, UT_sint32 y) const
{
  CanvasHSet * hset = getHSet (y);
  if (hset)
    return hset->getColor (x);
  return UT_RGBAColor();
}

bool UT_Canvas::copyAlpha (UT_Canvas * dest, UT_sint32 dest_x, UT_sint32 dest_y,
			   UT_sint32 src_x, UT_sint32 src_y, UT_uint32 width, UT_uint32 height) const
{
  if (dest == 0) return false;

  bool success = true;
  for (UT_sint32 y = src_y; y < src_y + height; y++)
    {
      CanvasHSet * hset = getHSet (y);
      if (hset)
	if (!dest->setAlpha (dest_x, dest_y + y - src_y, hset, src_x, width)) success = false;
    }
  return success;
}

bool UT_Canvas::copyColor (UT_Canvas * dest, UT_sint32 dest_x, UT_sint32 dest_y,
			   UT_sint32 src_x, UT_sint32 src_y, UT_uint32 width, UT_uint32 height) const
{
  if (dest == 0) return false;

  bool success = true;
  for (UT_sint32 y = src_y; y < src_y + height; y++)
    {
      CanvasHSet * hset = getHSet (y);
      if (hset)
	if (!dest->setColor (dest_x, dest_y + y - src_y, hset, src_x, width)) success = false;
    }
  return success;
}

bool UT_Canvas::swapColor (UT_Canvas * dest, UT_sint32 dest_x, UT_sint32 dest_y,
			   UT_sint32 src_x, UT_sint32 src_y, UT_uint32 width, UT_uint32 height)
{
  if (dest == 0) return false;

  bool success = true;
  for (UT_sint32 y = src_y; y < src_y + height; y++)
    {
      CanvasHSet * hset = getHSet (y);
      if (hset)
	if (!dest->swapColor (dest_x, dest_y + y - src_y, hset, src_x, width)) success = false;
    }
  return success;
}

bool UT_Canvas::swapColor (UT_sint32 x, UT_sint32 y, CanvasHSet * src, UT_sint32 src_x, UT_uint32 length)
{
  if (src == 0) return false;

  xSet (x);
  xSet (x + length - 1);
  ySet (y);

  CanvasHSet * hset = getHSet (y, true);
  if (hset)
    {
      return src->swapColor (hset, x, src_x, length);
    }
  return false;
}

CanvasHSet * UT_Canvas::getHSet (UT_sint32 offset_y, bool create)
{
  UT_uint32 posNew = 0;
  UT_uint32 count = m_HSet.getItemCount ();

  if (count == 1)
    {
      CanvasHSet * only = (CanvasHSet *) m_HSet.getFirstItem ();
      if (only->yOffset () == offset_y) return only;

      if (only->yOffset () < offset_y) posNew = 1;
    }
  else if (count > 1)
    {
      CanvasHSet * setFound = 0;
      do
	{
	  count--;

	  CanvasHSet * hset = (CanvasHSet *) m_HSet.getNthItem (count);
	  if (hset->yOffset () == offset_y)
	    {
	      setFound = hset;
	      break;
	    }
	  if (hset->yOffset () < offset_y)
	    {
	      posNew = count + 1;
	      break;
	    }
	}
      while (count);
      if (setFound) return setFound;
    }

  if (!create) return 0;

  CanvasHSet * setNew = new CanvasHSet(offset_y);
  if (m_HSet.insertItemAt ((void *) setNew, posNew) < 0)
    {
      delete setNew;
      return 0;
    }
  m_empty = false;
  return setNew;
}
