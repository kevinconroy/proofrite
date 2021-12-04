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
#include <string.h>

UT_Canvas::UT_CanvasHSet::UT_CanvasHSet (UT_sint32 offset_y) :
  m_offset_y(offset_y),
  m_BlendMode(bm_SrcCpy),
  m_segment_max(0),
  m_segment_count(0),
  m_segment_offset(0),
  m_segment_length(0),
  m_pixel_max(8),
  m_pixel_count(0),
  m_r(0),
  m_g(0),
  m_b(0),
  m_a(0)
{
  //
}

UT_Canvas::UT_CanvasHSet::~UT_CanvasHSet ()
{
  FREEP (m_segment_offset);
  FREEP (m_segment_length);
  FREEP (m_r);
  FREEP (m_g);
  FREEP (m_b);
  FREEP (m_a);
}

bool UT_Canvas::UT_CanvasHSet::setAlpha (UT_sint32 x, unsigned char a, UT_uint32 length, bool force_pixel)
{
  if (length == 0) return true;

  UT_uint32 index;
  if (getIndex (x, length, index)) // trivial case: pixels exist
    {
      if (m_a == 0) // but alpha component not allocated, so do so
	{
	  if (!force_pixel)
	    if (a == 0) return true; // special case: no need to set the default value
	  if (!makePixelArray (m_a)) return false;
	}

      blendAlpha (index, length, a);
      return true;
    }

  if (makeIndex (x, length, index)) // pixels arranged into new formation
    {
      if (m_a == 0) // but alpha component not allocated, so do so
	{
	  if (!force_pixel)
	    if (a == 0) return true; // special case: no need to set the default value
	  if (!makePixelArray (m_a)) return false;
	}

      blendAlpha (index, length, a);
      return true;
    }

  return false; // yikes! unable to arrange pixels into new formation
}

bool UT_Canvas::UT_CanvasHSet::setColor (UT_sint32 x, const UT_RGBAColor & rgba, UT_uint32 length, bool force_pixel)
{
  if (length == 0) return true;

  UT_uint32 index;
  if (getIndex (x, length, index)) // trivial case: pixels exist
    {
      if (m_r == 0) // but red component not allocated, so do so
	if (rgba.m_r || force_pixel) // skip special case
	  if (!makePixelArray (m_r)) return false;

      if (m_g == 0) // but green component not allocated, so do so
	if (rgba.m_g || force_pixel) // skip special case
	  if (!makePixelArray (m_g)) return false;

      if (m_b == 0) // but blue component not allocated, so do so
	if (rgba.m_b || force_pixel) // skip special case
	  if (!makePixelArray (m_b)) return false;

      if (m_a == 0) // but alpha component not allocated, so do so
	if (rgba.m_a || force_pixel) // skip special case
	  if (!makePixelArray (m_a)) return false;

      blendColor (index, length, rgba);
      return true;
    }

  if (makeIndex (x, index)) // pixels arranged into new formation
    {
      if (m_r == 0) // but red component not allocated, so do so
	if (rgba.m_r || force_pixel) // skip special case
	  if (!makePixelArray (m_r)) return false;

      if (m_g == 0) // but green component not allocated, so do so
	if (rgba.m_g || force_pixel) // skip special case
	  if (!makePixelArray (m_g)) return false;

      if (m_b == 0) // but blue component not allocated, so do so
	if (rgba.m_b || force_pixel) // skip special case
	  if (!makePixelArray (m_b)) return false;

      if (m_a == 0) // but alpha component not allocated, so do so
	if (rgba.m_a || force_pixel) // skip special case
	  if (!makePixelArray (m_a)) return false;

      blendColor (index, length, rgba);
      return true;
    }

  return false; // yikes! unable to arrange pixels into new formation
}

void UT_Canvas::UT_CanvasHSet::blendAlpha (UT_uint32 index, unsigned char alpha, UT_uint32 length)
{
  switch (m_BlendMode)
    {
    case bm_SrcAlpha:
      /* I'm just guessing here...
       */
      if (m_a)
	{
	  for (UT_uint32 i = 0; i < length; i++)
	    {
	      UT_uint32 a = 1 + (UT_uint32) alpha;
	      a = ((a * (0x100 - m_a[index+i])) - 1) >> 8;
	      m_a[index+i] = (unsigned char) ((m_a[index+i] + a) & 0xff);
	    }
	}
      break;

    default:
    case bm_SrcCpy:
      if (m_a) for (UT_uint32 i = 0; i < length; i++) m_a[index+i] = alpha;
      break;
    }
}

void UT_Canvas::UT_CanvasHSet::blendColor (UT_uint32 index, const UT_RGBAColor & rgba, UT_uint32 length)
{
  switch (m_BlendMode)
    {
    case bm_SrcAlpha:
      /* I'm just guessing here...
       */
      for (UT_uint32 i = 0; i < length; i++)
	{
	  UT_uint32 a = 1 + (UT_uint32) rgba.m_a;
	  if (m_r)
	    {
	      UT_uint32 r = ((a * (1 + (UT_uint32) rgba.m_r) + (0x100 - a) * (1 + (UT_uint32) m_r[index+i])) - 1) >> 8;
	      m_r[index+i] = (unsigned char) (r & 0xff);
	    }
	  if (m_g)
	    {
	      UT_uint32 g = ((a * (1 + (UT_uint32) rgba.m_g) + (0x100 - a) * (1 + (UT_uint32) m_g[index+i])) - 1) >> 8;
	      m_g[index+i] = (unsigned char) (g & 0xff);
	    }
	  if (m_b)
	    {
	      UT_uint32 b = ((a * (1 + (UT_uint32) rgba.m_b) + (0x100 - a) * (1 + (UT_uint32) m_b[index+i])) - 1) >> 8;
	      m_b[index+i] = (unsigned char) (b & 0xff);
	    }
	  if (m_a)
	    {
	      a = ((a * (0x100 - m_a[index+i])) - 1) >> 8;
	      m_a[index+i] = (unsigned char) ((m_a[index+i] + a) & 0xff);
	    }
	}
      break;

    default:
    case bm_SrcCpy:
      if (m_r) for (UT_uint32 i = 0; i < length; i++) m_r[index+i] = rgba.m_r;
      if (m_g) for (UT_uint32 i = 0; i < length; i++) m_g[index+i] = rgba.m_g;
      if (m_b) for (UT_uint32 i = 0; i < length; i++) m_b[index+i] = rgba.m_b;
      if (m_a) for (UT_uint32 i = 0; i < length; i++) m_a[index+i] = rgba.m_a;
      break;
    }
}

unsigned char UT_Canvas::UT_CanvasHSet::getAlpha (UT_sint32 x) const
{
  if (m_a == 0) return 0;

  UT_uint32 index;
  if (!getIndex (x, index)) return 0;

  return m_a[index];
}

const UT_RGBAColor UT_Canvas::UT_CanvasHSet::getColor (UT_sint32 x) const
{
  UT_uint32 index;
  if (!getIndex (x, index)) return UT_RGBAColor();

  return UT_RGBAColor((m_r ? m_r[index] : 0), (m_g ? m_g[index] : 0), (m_b ? m_b[index] : 0), (m_a ? m_a[index] : 0));
}

bool UT_Canvas::UT_CanvasHSet::copyColor (unsigned char * dest, UT_sint32 src_x, UT_uint32 length)
{
  if (dest == 0) return false;

  bool done = false;
  UT_uint32 index = 0;
  for (UT_uint32 seg_no = 0; seg_no < m_segment_count; seg_no++)
    {
      for (UT_sint x = m_segment_offset[seg_no]; x - m_segment_offset[seg_no] < m_segment_length[seg_no]; x++)
	{
	  if (x >= src_x)
	    {
	      if (x - src_x >= length)
		{
		  done = true;
		  break;
		}
	      unsigned char * pixel = dest + 4 * (x - src_x);
	      *pixel = (m_r ? m_r[index] : 0); pixel++;
	      *pixel = (m_g ? m_g[index] : 0); pixel++;
	      *pixel = (m_b ? m_b[index] : 0); pixel++;
	      *pixel = (m_a ? m_a[index] : 0);
	    }
	  index++;
	}
      if (done) break;
    }
  return true;
}

bool UT_Canvas::UT_CanvasHSet::copyAlpha (CanvasHSet * dest, UT_sint32 dest_x, UT_sint32 src_x, UT_uint32 length)
{
  if (dest == 0) return false;

  bool done = false;
  bool success = true;
  UT_uint32 index = 0;
  for (UT_uint32 seg_no = 0; seg_no < m_segment_count; seg_no++)
    {
      for (UT_sint x = m_segment_offset[seg_no]; x - m_segment_offset[seg_no] < m_segment_length[seg_no]; x++)
	{
	  if (x >= src_x)
	    {
	      if (x - src_x >= length)
		{
		  done = true;
		  break;
		}
	      if (!dest->setAlpha (dest_x + x - src_x, (m_a ? m_a[index] : 0)))
		{
		  success = false;
		  done = true;
		  break;
		}
	    }
	  index++;
	}
      if (done) break;
    }
  return success;
}

bool UT_Canvas::UT_CanvasHSet::copyAlpha (CanvasHSet * dest, UT_sint32 dest_x, UT_sint32 src_x, UT_uint32 length, const UT_RGBAColor & rgba)
{
  if (dest == 0) return false;

  bool done = false;
  bool success = true;
  UT_uint32 index = 0;
  UT_RGBAColor color(rgba);
  for (UT_uint32 seg_no = 0; seg_no < m_segment_count; seg_no++)
    {
      for (UT_sint x = m_segment_offset[seg_no]; x - m_segment_offset[seg_no] < m_segment_length[seg_no]; x++)
	{
	  if (x >= src_x)
	    {
	      if (x - src_x >= length)
		{
		  done = true;
		  break;
		}
	      /* so, is there an official way to combine alpha?
	       */
	      UT_uint32 alpha = (((((UT_uint32) (m_a ? m_a[index] : 0)) + 1) * (((UT_uint32) rgba.m_a) + 1)) - 1) >> 8;
	      color.m_a = (unsigned char) (alpha & 0xff);
	      if (!dest->setColor (dest_x + x - src_x, color))
		{
		  success = false;
		  done = true;
		  break;
		}
	    }
	  index++;
	}
      if (done) break;
    }
  return success;
}

bool UT_Canvas::UT_CanvasHSet::copyColor (CanvasHSet * dest, UT_sint32 dest_x, UT_sint32 src_x, UT_uint32 length)
{
  if (dest == 0) return false;

  bool done = false;
  bool success = true;
  UT_uint32 index = 0;
  UT_RGBAColor color;
  for (UT_uint32 seg_no = 0; seg_no < m_segment_count; seg_no++)
    {
      for (UT_sint x = m_segment_offset[seg_no]; x - m_segment_offset[seg_no] < m_segment_length[seg_no]; x++)
	{
	  if (x >= src_x)
	    {
	      if (x - src_x >= length)
		{
		  done = true;
		  break;
		}
	      color.m_r = (m_r ? m_r[index] : 0);
	      color.m_g = (m_g ? m_g[index] : 0);
	      color.m_b = (m_b ? m_b[index] : 0);
	      color.m_a = (m_a ? m_a[index] : 0);
	      if (!dest->setColor (dest_x + x - src_x, color))
		{
		  success = false;
		  done = true;
		  break;
		}
	    }
	  index++;
	}
      if (done) break;
    }
  return success;
}

bool UT_Canvas::UT_CanvasHSet::swapColor (CanvasHSet * dest, UT_sint32 dest_x, UT_sint32 src_x, UT_uint32 length)
{
  if (dest == 0) return false;

  if (m_r == 0) if (!makePixelArray (m_r)) return false;
  if (m_g == 0) if (!makePixelArray (m_g)) return false;
  if (m_b == 0) if (!makePixelArray (m_b)) return false;
  if (m_a == 0) if (!makePixelArray (m_a)) return false;

  bool done = false;
  bool success = true;
  UT_uint32 index = 0;
  UT_RGBAColor current;
  UT_RGBAColor replace;
  for (UT_uint32 seg_no = 0; seg_no < m_segment_count; seg_no++)
    {
      for (UT_sint x = m_segment_offset[seg_no]; x - m_segment_offset[seg_no] < m_segment_length[seg_no]; x++)
	{
	  if (x >= src_x)
	    {
	      if (x - src_x >= length)
		{
		  done = true;
		  break;
		}
	      current = dest->getColor (dest_x + x);
	      replace = UT_RGBAColor(m_r[index], m_g[index], m_b[index], m_a[index]);
	      if (!dest->setColor (dest_x + x - src_x, replace))
		{
		  success = false;
		  done = true;
		  break;
		}
	      m_r[index] = current.m_r;
	      m_g[index] = current.m_g;
	      m_b[index] = current.m_b;
	      m_a[index] = current.m_a;
	    }
	  index++;
	}
      if (done) break;
    }
  return success;
}

bool UT_Canvas::UT_CanvasHSet::getIndex (UT_sint32 x, UT_uint32 length, UT_uint32 & index) const
{
  if (m_segment_count == 0) return false;
  if (x < m_segment_offset[0]) return false;

  bool inRange = false;
  index = 0;
  for (UT_uint32 seg_no = 0; seg_no < m_segment_count; seg_no++)
    {
      if ((x >= m_segment_offset[seg_no]) && (x < m_segment_offset[seg_no] + m_segment_length[seg_no]))
	{
	  if (x + length <= m_segment_offset[seg_no] + m_segment_length[seg_no])
	    {
	      index += x - m_segment_offset[seg_no];
	      inRange = true;
	    }
	  break;
	}
      index += m_segment_length[seg_no];
    }
  if (!inRange) index = 0;

  return inRange;
}

/* can't help wondering if this method is too time-consuming... is it worth looking up sparse matrix techniques
 * for a superior solution?
 */
bool makeIndex (UT_sint32 x, UT_uint32 requested_length, UT_uint32 & index) // this is the core of it...
{
  if (!segmentGrow ()) return false; // the plan is to create a segment, and merge segments (up to twice) after

  UT_uint32 length = (requested_length < 8) ? 8 : requested_length;

  if (m_segment_count == 0) // no existing pixels, just add a segment of required length
    {
      if (!segmentInsert (0, x, length)) return false;
      return getIndex (x, requested_length, index);
    }

  if (x + length < m_segment_offset[0]) // new segment is entirely before others
    {
      if (!segmentInsert (0, x, length)) return false;
      return getIndex (x, requested_length, index);
    }

  UT_uint32 end_offset = m_segment_offset[m_segment_count-1] + m_segment_length[m_segment_count-1];
  if (x >= end_offset)      // new segment is entirely after others
    if (x < end_offset + 8) // if close, then append to last
      {
	if (!segmentInsert (m_segment_count, end_offset, length + (end_offset + 8 - x))) return false;
	segmentMergeWithNext (m_segment_count-2); // since m_segment_count has been incremented by segmentInsert ()
	return getIndex (x, requested_length, index);
      }
    else // append segment of required length
      {
	if (!segmentInsert (m_segment_count, x, length)) return false;
	return getIndex (x, requested_length, index);
      }

  /* Try for easy insertion, and do any double-merges
   */
  bool foundInsertion = false;
  bool failedInsertion = false;
  bool inserted = false;
  UT_uint32 seg_no = m_segment_count - 1;
  while ((m_segment_count > 1) && seg_no)
    {
      UT_sint32 gap_offset = m_segment_offset[seg_no-1] + m_segment_length[seg_no-1];
      UT_uint32 gap_length = m_segment_offset[seg_no] - gap_offset;

      if ((x >= m_segment_offset[seg_no-1]) && (x + length <= m_segment_offset[seg_no] + m_segment_length[seg_no]))
	{
	  foundInsertion = true;
	  if ((x > gap_offset) && (x + length < m_segment_offset[seg_no]))
	    {
	      inserted = segmentInsert (seg_no, x, length);
	    }
	  else if (x > gap_offset)
	    {
	      inserted = segmentInsert (seg_no, x, m_segment_offset[seg_no] - x);
	      if (inserted) segmentMergeWithNext (seg_no);
	    }
	  else if (x + length < m_segment_offset[seg_no])
	    {
	      inserted = segmentInsert (seg_no, gap_offset, x + length - gap_offset);
	      if (inserted) segmentMergeWithNext (seg_no-1);
	    }
	  else
	    {
	      inserted = segmentInsert (seg_no, gap_offset, m_segment_offset[seg_no] - gap_offset);
	      if (inserted)
		{
		  segmentMergeWithNext (seg_no);
		  segmentMergeWithNext (seg_no-1);
		}
	    }
	  break;
	}
      if ((x < gap_offset) && (x + length >= m_segment_offset[seg_no]))
	{
	  inserted = segmentInsert (seg_no, gap_offset, m_segment_offset[seg_no] - gap_offset);
	  if (!inserted)
	    {
	      failedInsertion = true;
	      break;
	    }
	  segmentMergeWithNext (seg_no);
	  segmentMergeWithNext (seg_no-1);
	  seg_no--;
	}
      if (seg_no) seg_no--;
    }
  if (foundInsertion)
    {
      if (!inserted) return false;
      return getIndex (x, requested_length, index);
    }
  if (failedInsertion) return false;

  /* By this point, there should be a single segment that requires extending, possibly in both directions
   */
  for (seg_no = 0; seg_no < m_segment_count; seg_no++)
    if ((x < m_segment_offset[seg_no] + m_segment_length[seg_no]) && (x + length >= m_segment_offset[seg_no]))
      break;
  if (seg_no == m_segment_count) return false; // shouldn't happen, but check anyway

  if (x < m_segment_offset[seg_no])
    if (!segmentInsert (seg_no, x, m_segment_offset[seg_no] - x)) return false;

  if (!segmentGrow ()) return false;

  UT_uint32 gap_offset = m_segment_offset[seg_no] + x_segment_length[seg_no];
  if (x + length > gap_offset)
    if (!segmentInsert (seg_no, gap_offset, x + length - gap_offset)) return false;

  return getIndex (x, requested_length, index);
}

bool UT_Canvas::UT_CanvasHSet::segmentInsert (UT_uint32 seg_first, UT_sint32 offset, UT_uint32 length)
{
  if (seg_first > m_segment_count) return false; // erk!

  if (!segmentGrow ()) return false; // redundant, but just in case...

  UT_uint32 seg_no = m_segment_count;
  while (seg_no - seg_first)
    {
      m_segment_offset[seg_no] = m_segment_offset[seg_no-1];
      m_segment_length[seg_no] = m_segment_length[seg_no-1];
      seg_no--;
    }
  m_segment_offset[seg_first] = offset;
  m_segment_length[seg_first] = length;

  UT_uint32 pixel_index = 0;
  for (seg_no = 0; seg_no < seg_first; seg_no++) pixel_index += m_segment_length[seg_no];

  return insertPixels (pixel_index, length);
}

bool UT_Canvas::UT_CanvasHSet::segmentMergeWithNext (UT_uint32 seg_first)
{
  m_segment_length[seg_first] += m_segment_length[seg_first+1];
  for (UT_uint32 seg_no = seg_first + 1; seg_no + 1 < m_segment_count)
    {
      m_segment_offset[seg_no] = m_segment_offset[seg_no+1];
      m_segment_length[seg_no] = m_segment_length[seg_no+1];
    }
  m_segment_count--;
}

bool UT_Canvas::UT_CanvasHSet::segmentGrow ()
{
  if (m_segment_count < m_segment_max) return true;
  if (m_segment_max == 0)
    {
      m_segment_offset = (UT_sint32 *) malloc (4 * sizeof (UT_sint32));
      if (m_segment_offset == 0)
	{
	  return false;
	}
      m_segment_length = (UT_uint32 *) malloc (4 * sizeof (UT_uint32));
      if (m_segment_length == 0)
	{
	  FREEP (m_segment_offset);
	  return false;
	}
      m_segment_max = 4;
      return true;
    }

  UT_sint32 * more_offset = (UT_sint32 *) realloc ((void *) m_segment_offset, (4 + m_segment_max) * sizeof (UT_sint32));
  if (more_offset) m_segment_offset = more_offset;
  else return false;

  UT_uint32 * more_length = (UT_uint32 *) realloc ((void *) m_segment_length, (4 + m_segment_max) * sizeof (UT_uint32));
  if (more_length) m_segment_length = more_length;
  else return false;

  m_segment_max += 4;

  return true;
}

bool UT_Canvas::UT_CanvasHSet::makePixelArray (unsigned char *& pixel_array)
{
  pixel_array = (unsigned char *) malloc (m_pixel_max * sizeof (unsigned char));
  if (pixel_array == 0) return false;

  for (UT_uint32 pix_no = 0; pix_no < m_pixel_max; pix_no++) pixel_array[pix_no] = 0;

  return true;
}

bool UT_Canvas::UT_CanvasHSet::insertPixels (UT_uint32 index, UT_uint32 number)
{
  if (m_pixel_count + number > m_pixel_max)
    {
      UT_uint32 pixel_max = m_pixel_max + number;

      if (m_r)
	{
	  unsigned char * more_pixels = (unsigned char *) realloc ((void *) m_r, pixel_max * sizeof (unsigned char));
	  if (more_pixels == 0) return false;
	  m_r = more_pixels;
	}
      if (m_g)
	{
	  unsigned char * more_pixels = (unsigned char *) realloc ((void *) m_g, pixel_max * sizeof (unsigned char));
	  if (more_pixels == 0) return false;
	  m_g = more_pixels;
	}
      if (m_b)
	{
	  unsigned char * more_pixels = (unsigned char *) realloc ((void *) m_b, pixel_max * sizeof (unsigned char));
	  if (more_pixels == 0) return false;
	  m_b = more_pixels;
	}
      if (m_a)
	{
	  unsigned char * more_pixels = (unsigned char *) realloc ((void *) m_a, pixel_max * sizeof (unsigned char));
	  if (more_pixels == 0) return false;
	  m_a = more_pixels;
	}

      m_pixel_max = pixel_max;
    }

  if (m_r)
    {
      if (index < m_pixel_count)
	memmove (m_r + index + number, m_r + index, m_pixel_count - index);
      for (UT_uint32 pix_no = index; pix_no < number; pix_no++)
	m_r[pix_no] = 0;
    }
  if (m_g)
    {
      if (index < m_pixel_count)
	memmove (m_g + index + number, m_g + index, m_pixel_count - index);
      for (UT_uint32 pix_no = index; pix_no < number; pix_no++)
	m_g[pix_no] = 0;
    }
  if (m_b)
    {
      if (index < m_pixel_count)
	memmove (m_b + index + number, m_b + index, m_pixel_count - index);
      for (UT_uint32 pix_no = index; pix_no < number; pix_no++)
	m_b[pix_no] = 0;
    }
  if (m_a)
    {
      if (index < m_pixel_count)
	memmove (m_a + index + number, m_a + index, m_pixel_count - index);
      for (UT_uint32 pix_no = index; pix_no < number; pix_no++)
	m_a[pix_no] = 0;
    }

  return true;
}
