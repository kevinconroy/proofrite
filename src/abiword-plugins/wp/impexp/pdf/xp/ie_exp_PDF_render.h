/* Some code Copyright (C) 2002 John Wyrwas
 *
 * Based on the KWord Exporter 
 *
 * AbiWord
 * Copyright (C) 2001 AbiSource, Inc.
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
 *
 *
 */

/* PDF code based loosely on HTMLDOC
 *
 *   Copyright 1997-2002 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Easy Software Products and are protected by Federal
 *   copyright law.  Distribution and use rights are outlined in the file
 *   "COPYING.txt" which should have been included with this file.  If this
 *   file is missing or damaged please contact Easy Software Products
 *   at:
 *
 *       Attn: ESP Licensing Information
 *       Easy Software Products
 *       44141 Airport View Drive, Suite 204
 *       Hollywood, Maryland 20636-3111 USA
 *
 *       Voice: (301) 373-9600
 *       EMail: info@easysw.com
 *         WWW: http://www.easysw.com
 *
 */


#ifndef PDF_RENDER_H
#define PDF_RENDER_H

#define RENDER_TEXT	0
#define RENDER_IMAGE	1
#define RENDER_BOX	2  //used for hr's, underlines, overlines, strikethrues, etc.


const char	*_genericFonts[4][4] =
  {
    {
      "Courier",
      "Courier-Bold",
      "Courier-Oblique",
      "Courier-BoldOblique"
    },
    {
      "Times-Roman",
      "Times-Bold",
      "Times-Italic",
      "Times-BoldItalic"
    },
    {
      "Helvetica",
      "Helvetica-Bold",
      "Helvetica-Oblique",
      "Helvetica-BoldOblique"
    },
    {
      "Symbol",
      "Symbol",
      "Symbol",
      "Symbol"
    }
  };



struct image_t			// Image structure 
  {
    int		width,		// Width of image in pixels 
    height,		// Height of image in pixels 
    depth,		// 1 for grayscale, 3 for RGB 
    use,		// Number of times this image was used 
    obj;		// Object number 
    UT_Byte		*pixels;	// 8-bit pixel data
    UT_Byte		*mask;		// 1-bit mask data, if any 
    int		maskwidth;	// Byte width of mask data 
    UT_ByteBuf data;
  };

struct r_text
  {
    int	typeface;	// Typeface for text (use m_pie->addfont) 
    float	size;		// Size of text in points 
    float	spacing;	// Inter-character spacing 
    float	rgb[3];		// Color of text 
    UT_String buffer;
  };

struct render_t	// Render entity structure 
  {
    int	type;			//Type of entity 
    float	x,			// Position in points 
    y,
    width,			//Size in points 
    height;
    r_text text;
    image_t	*image;		// Image pointer 
    float	box[3];		//Box color 
  };


struct page_t		//// Page information
  {
    int		width,			// Width of page in points
    length,			// Length of page in points
    left,			// Left margin in points
    right,			// Right margin in points
    top,			// Top margin in points
    bottom;			// Bottom margin in points

    UT_Vector renders; //(of links to render_t's)
    float		background_color[3];	// Background color
  }
;


#endif /* PDF_RENDER_H */