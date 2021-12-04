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
 


#ifndef UTCANVAS_H
#define UTCANVAS_H

#include "ut_types.h"
#include "ut_vector.h"
#include "ut_bytebuf.h"

#include "ut_rgbacolor.h"

class ABI_EXPORT UT_Canvas
{
 public:

  enum BlendMode
  {
    bm_SrcCpy = 0, // Overwrite existing value
    bm_SrcAlpha    // Blend with existing value using source-pixel alpha channel transparency
  };

  class ABI_EXPORT CanvasHSet
    {
    public:
      CanvasHSet (UT_sint32 offset_y);
      ~CanvasHSet ();

      bool setAlpha (UT_sint32 x, unsigned char a,           UT_uint32 length = 1, bool force_pixel = false);
      bool setColor (UT_sint32 x, const UT_RGBAColor & rgba, UT_uint32 length = 1, bool force_pixel = false);

      unsigned char      getAlpha (UT_sint32 x) const;
      const UT_RGBAColor getColor (UT_sint32 x) const;

      bool copyAlpha (CanvasHSet * dest, UT_sint32 dest_x, UT_sint32 src_x, UT_uint32 length);
      bool copyAlpha (CanvasHSet * dest, UT_sint32 dest_x, UT_sint32 src_x, UT_uint32 length, const UT_RGBAColor & rgba);
      bool copyColor (CanvasHSet * dest, UT_sint32 dest_x, UT_sint32 src_x, UT_uint32 length);
      bool swapColor (CanvasHSet * dest, UT_sint32 dest_x, UT_sint32 src_x, UT_uint32 length);

      bool copyColor (unsigned char * dest, UT_sint32 x, UT_uint32 length); // PNG-write

      UT_sint32 xOffset () const { return (m_segment_count ? m_segment_offset[0] : 0); }
      UT_sint32 yOffset () const { return m_offset_y; }

      void setBlend (BlendMode bm) { m_BlendMode = bm; }

    private:
      const UT_sint32 m_offset_y;

      BlendMode m_BlendMode;

      void blendAlpha (UT_uint32 index, unsigned char a,           UT_uint32 length);
      void blendColor (UT_uint32 index, const UT_RGBAColor & rgba, UT_uint32 length);

      UT_uint32 m_segment_max;
      UT_uint32 m_segment_count;

      UT_sint32 * m_segment_offset;
      UT_uint32 * m_segment_length;

      UT_uint32 m_pixel_max;
      UT_uint32 m_pixel_count;

      /* map coordinate to pixel array index
       */
      bool getIndex (UT_sint32 x, UT_uint32 & index) const { return getIndex (x, 1, index); }
      bool getIndex (UT_sint32 x, UT_uint32 length, UT_uint32 & index) const;

      /* re-arrange segments to allow new mapping
       */
      bool makeIndex (UT_sint32 x, UT_uint32 length, UT_uint32 & index);

      bool segmentInsert (UT_uint32 seg_no, UT_sint32 offset, UT_uint32 length);
      bool segmentMergeWithNext (UT_uint32 seg_no);
      bool segmentGrow ();

      bool makePixelArray (unsigned char *& pixel_array);    // create specified pixel array of length m_pixel_max
      bool insertPixels (UT_uint32 index, UT_uint32 number); // insert <number> pixels at <index>

      unsigned char * m_r;
      unsigned char * m_g;
      unsigned char * m_b;
      unsigned char * m_a;
    };

  class ABI_EXPORT CanvasImage
    {
    public:
      CanvasImage ();
      ~CanvasImage ();

      bool loadPNG (UT_ByteBuf * pBB);

      bool resetCanvas (UT_RGBAColor & color, UT_uint32 width, UT_uint32 height);

      UT_uint32 width ()  const { return m_width;  }
      UT_uint32 height () const { return m_height; }

      bool copyColor (UT_Canvas * dest,
		      UT_sint32 dest_x, UT_sint32 dest_y, UT_uint32 dest_width, UT_uint32 dest_height,
		      UT_sint32 src_x,  UT_sint32 src_y,  UT_uint32 src_width,  UT_uint32 src_height);

    private:
      void eraseCanvas ();

      UT_uint32 m_width;
      UT_uint32 m_height;

      UT_uint32 m_image_max;

      CanvasHSet ** m_Image;
    };

  class ABI_EXPORT CanvasPolygon
    {
    public:
      CanvasPolygon ();
      ~CanvasPolygon ();

      bool reset ();

      bool addPoint (UT_uint32 xvi_x, UT_uint32 xvi_y); // See note on 16ths (xvi) in CanvasMap below

    private:
      bool grow ();

      UT_uint32 m_max;
      UT_uint32 m_count;

      UT_uint32 * m_x;
      UT_uint32 * m_y;

    public:
      enum PolygonRule
      {
	pr_EvenOdd        = 0,
	pr_NonExterior    = 1,
	pr_NonzeroWinding = 2
      };

      void setRule (PolygonRule pr) { m_PolygonRule = pr; }

    private:
      PolygonRule m_PolygonRule;

    public:
      /* Determine an alpha value for a given rectangle
       */
      unsigned char getAlpha (UT_uint32 xvi_x_min, UT_uint32 xvi_y_min, UT_uint32 xvi_x_max, UT_uint32 xvi_y_max);

    private:
      /* Determine an alpha value for a given line
       */
      unsigned char getLineAlpha (UT_uint32 xvi_y, UT_uint32 xvi_x_min, UT_uint32 xvi_x_max);

      bool calcIntercepts (UT_uint32 y);
      void sortIntercepts ();
      void sortLineCache ();

      void clearLineCache ();
      bool resetLineCache (UT_uint32 xvi_y_min, UT_uint32 xvi_y_max);

      bool growLineCache ();

      UT_uint32 m_lc_y_min; // cache intersectors to reduce overhead scanwise
      UT_uint32 m_lc_y_max;

      UT_uint32 m_lc_max;
      UT_uint32 m_lc_count;

      UT_uint32 * m_lc_x1;
      UT_uint32 * m_lc_y1;
      UT_uint32 * m_lc_x2;
      UT_uint32 * m_lc_y2;

      UT_sint32 * m_lc_xi; // intercepts
    };

  class ABI_EXPORT CanvasMap
    {
    public:
      CanvasMap ();
      ~CanvasMap ();

      /* There are 3 discrete length scales employed here:
       * 
       * (1) layout units (lo)
       * 
       *     AbiWord's internal page-based resolution (probably 1200 'lo' per inch)
       *     As far as AbiWord is concerned, an image has an absolute size of, e.g., 3 inches by 2 inches, so:
       * 
       *        lo_abs_width  = 3 * 1200;
       *        lo_abs_height = 2 * 1200;
       * 
       *     of which, perhaps, only the top right square inch is visible currently:
       * 
       *        lo_sub_x      = 2 * 1200;
       *        lo_sub_y      = 1 * 1200;
       *        lo_sub_width  = 1 * 1200;
       *        lo_sub_height = 1 * 1200;
       * 
       * (2) pixels (px)
       * 
       *     In SVG and various other standards, pixels ("px") are a unit of length referring to screen pixels.
       *     Current displays have resolutions of about 100-133 pixels per inch (ppi)
       * 
       *     AbiWord is page-layout based whereas pixels are normally display-dependent, so in order for
       *     documents to render in a display-invariant fashion, the pixel length scale needs to be re-defined
       *     relative to the absolute page. For example, 1'px' = 12'lo'
       * 
       *     IMPORTANT
       *     However, the renderer (CanvasMap) needs to know the size of the visible region in *screen* pixels:
       * 
       *        px_sub_width  = 100;
       *        px_sub_height = 100;
       * 
       *     The size of the image in pixels will vary with AbiWord's current zoom setting.
       * 
       *     IMPORTANT
       *     Screen resolution must not exceed layout resolution!
       * 
       * (3) 16ths (xvi)
       * 
       *     For polygon vertex specification, coordinates are specified in 16ths of a layout unit. Note that
       *     high-level shapes take coordinates in layout units (lo), but these need to make fine adjustments
       *     such as line joins, dashes, bezier decomposition, etc. that require finer resolution.
       */
      bool setRegion (UT_uint32 lo_abs_width,  // width, height in layout units of whole figure
		      UT_uint32 lo_abs_height,
		      UT_uint32 lo_sub_x,      // x, y, width, height in layout units of visible sub-region
		      UT_uint32 lo_sub_y,      // (x,y) is minimum coordinate
		      UT_uint32 lo_sub_width,  // REQUIRE: lo_sub_width  >= px_sub_width
		      UT_uint32 lo_sub_height, // REQUIRE: lo_sub_height >= px_sub_height
		      UT_uint32 px_sub_width,  // width & height in screen pixels (at current zoom/magnification/etc.)
		      UT_uint32 px_sub_height  // of visible sub-region
		      );

    private:
      void clearRegion ();

      UT_sint32 * m_x; // pixel offsets in sixteenths of a layout unit
      UT_sint32 * m_y;
    };

  UT_Canvas ();
  ~UT_Canvas ();

  virtual bool setAlpha (UT_sint32 x, UT_sint32 y, unsigned char a);
  virtual bool setColor (UT_sint32 x, UT_sint32 y, const UT_RGBAColor & rgba);

  virtual bool setAlpha (UT_sint32 x, UT_sint32 y, unsigned char a,
			 UT_uint32 width, UT_uint32 height, bool force_pixel = false);
  virtual bool setColor (UT_sint32 x, UT_sint32 y, const UT_RGBAColor & rgba,
			 UT_uint32 width, UT_uint32 height, bool force_pixel = false);

  virtual bool setAlpha (UT_sint32 x, UT_sint32 y, const CanvasHSet * src, UT_sint32 src_x, UT_uint32 length);
  virtual bool setColor (UT_sint32 x, UT_sint32 y, const CanvasHSet * src, UT_sint32 src_x, UT_uint32 length);

  virtual unsigned char      getAlpha (UT_sint32 x, UT_sint32 y) const;
  virtual const UT_RGBAColor getColor (UT_sint32 x, UT_sint32 y) const;

  virtual bool copyAlpha (UT_Canvas * dest, UT_sint32 dest_x, UT_sint32 dest_y,
			  UT_sint32 src_x, UT_sint32 src_y, UT_uint32 width, UT_uint32 height) const;
  virtual bool copyColor (UT_Canvas * dest, UT_sint32 dest_x, UT_sint32 dest_y,
			  UT_sint32 src_x, UT_sint32 src_y, UT_uint32 width, UT_uint32 height) const;
  virtual bool swapColor (UT_Canvas * dest, UT_sint32 dest_x, UT_sint32 dest_y,
			  UT_sint32 src_x, UT_sint32 src_y, UT_uint32 width, UT_uint32 height);
  virtual bool swapColor (UT_sint32 x, UT_sint32 y, CanvasHSet * src, UT_sint32 src_x, UT_uint32 length);

  UT_sint32 left ()   const { return m_left;   }
  UT_sint32 right ()  const { return m_right;  }
  UT_sint32 top ()    const { return m_top;    }
  UT_sint32 bottom () const { return m_bottom; }

  virtual void setBlend (BlendMode bm) { m_BlendMode = bm; }

  bool savePNG (UT_ByteBuf ** pBB, UT_sint32 offset_x, UT_sint32 offset_y, UT_uint32 length_x, UT_uint32 length_y);

 protected:
  UT_sint32 m_left;
  UT_sint32 m_right;
  UT_sint32 m_top;
  UT_sint32 m_bottom;

  BlendMode m_BlendMode;

 private:
  CanvasHSet * getHSet (UT_sint32 offset_y, bool create = false);

  UT_Vector m_HSet;

  bool m_empty;

  inline void xSet (UT_sint32 x)
    {
      if (m_empty || (m_left   > x)) m_left   = x;
      if (m_empty || (m_right  < x)) m_right  = x;
    }
  inline void ySet (UT_sint32 y)
    {
      if (m_empty || (m_bottom > y)) m_bottom = y;
      if (m_empty || (m_top    < y)) m_top    = y;
    }
};

#endif /* UTCANVAS_H */
