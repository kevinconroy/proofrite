/* AbiSource Program Utilities
 * Copyright (C) 2002 Dom Lachowicz
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

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <string>
#include <vector>
#include <map>

#include "ut_types.h"
#include "ut_misc.h"

using namespace std;

// many of these typedefs and function declarations should also be placed
// in a corresponding .h file

// some code below graciously donated by Dom Lachowicz, Lenoard Rosenthal
// and Appligent, Inc.

/*!
 * Enum for the number of ways a line's ending can be drawn
 */
typedef enum 
{ 
  cap_Butt, 
  cap_Round, 
  cap_Square 
} SVG_CapStyle;

/*!
 * Enum for the number of ways 2 lines can be drawn when joined
 */
typedef enum 
{ 
  join_Miter,
  join_Round,
  join_Bevel
} SVG_JoinStyle;

/*!
 * Text alignment modes
 */
typedef enum 
{ 
  align_Left,
  align_Right, 
  align_Center,
  align_Justify
} SVG_AlignStyle;

/*!
 * OR (|) these together to make a compound font stlye
 * AND (&) using these to find out if any particular bit is set
 */
typedef enum
{
  font_Normal					= 0,
  font_Bold					= 1,
  font_Italic					= 2,
  font_Hnderline				= 4,
  font_Outline					= 8,
  font_Shadow					= 0x10,
  font_Condense					= 0x20,
  font_Extend					= 0x40
} SVG_FontStyle;

/*!
 * Our default font name is "Times Roman"
 */
static const std::string  defaultFontName = "Times Roman";
static const UT_RGBColor black;

/*!
 * Tracker struct/class for graphics state information, stored in a stack-like mechanism
 */
class SVG_GraphicsState {

public:
  SVG_GraphicsState ()
    : fill_opacity(1.), fill_valid(true), fill_evenOdd(true),
      stroke_opacity(1.), stroke_width(1.), stroke_valid(false),
      cap(cap_Butt), join(join_Miter), dashCount(0), font_name(defaultFontName), 
      font_size(12.), font_style(font_Normal), text_alignment(eAlignLeft), 
      text_decoration(""), letter_spacing(0), word_spacing(0), leading(0)
  {
    fill   = black;
    stroke = black;
    
    dashArray[0] = 0;	      
  }

  // TODO!!! TRANSFORM mtx needed!
  // matrix mtx;

  UT_RGBColor          fill;
  double 		fill_opacity;
  bool			fill_valid;
  bool			fill_evenOdd;
  
  UT_RGBColor		stroke;
  double		stroke_opacity;
  double		stroke_width;
  bool			stroke_valid;
  SVG_CapStyle		cap;
  SVG_JoinStyle         join;
  double		dashArray[100];
  UT_sint32		dashCount;
  
  string		font_name;
  double		font_size;
  UT_uint32             font_style;

  SVG_AlignStyle	text_alignment;
  string		text_decoration;
  double		letter_spacing;
  double		word_spacing;
  double		leading;
};

typedef map< string, string >	SVG_CSSAttrMap;
typedef map< string, string >	SVG_TransformMap;

typedef vector< SVG_GraphicsState > SVG_GraphicsStateStack;

/*!
 * Turns a string like "font-face: Times; font-weight: bold" into a 1:1
 * <string, string> map. These props would then be queriable like this:
 *
 * string face   = mymap [ "font-face" ] ;
 * string weight = mymap [ "font-weight" ] ;
 */
static void MakeCSSMap( const string& inString, SVG_CSSAttrMap& outMap )
{
  UT_uint32   idx = 0;  
  UT_sint32   colonLoc = inString.find( ':', idx );
  UT_sint32   valLoc   = 0;
  
  while ( colonLoc >= 0 ) 
    {
      string name = inString.substr( idx, colonLoc-idx );
      string value;
      
      // now find our value...
      valLoc = colonLoc + 1;
      while ( isspace ( inString[valLoc] ) )	
	valLoc++;
      idx = valLoc;
      while ( ( inString[idx] != ';' ) && ( idx < inString.length() ) )
	value += inString[idx++];
      outMap[name] = value;
      
      // and on to the next one...
      while ( isspace( inString[idx] ) || ( inString[idx] == ';' ) )
	idx++;
      colonLoc = inString.find( ':', idx );
    }
}

static void MakeTransformMap( const string& inString, 
			      SVG_TransformMap& outMap )
{
  UT_uint32 idx = 0;
  
  UT_sint32 parenLoc = inString.find( '(', idx );
  UT_sint32 valLoc = 0;

  while ( parenLoc >= 0 ) 
    {
      string name = inString.substr( idx, parenLoc-idx );
      string value;
			
      // now find our value...
      valLoc = parenLoc + 1;
      while ( isspace( inString[valLoc] ) )
	valLoc++;
      idx = valLoc;
      while ( ( inString[idx] != ')' ) )
 	value += inString[idx++];
      outMap[name] = value;
      
      // and on to the next one...
      while ( isspace( inString[++idx] ) ) 
	idx++;
      parenLoc = inString.find( '(', idx );
      if ( parenLoc > 0 )
	idx--;	// adjust for actually finding the character!
    }
}

// this needs to be put into some parsing class to keep track of the state list
void ProcessStyleString( const string& styleStr )
{
  // get copy of the current state, since states are inherited
  SVG_GraphicsState curState = mStateList.back(); 

  // now figure out what things we need to change!
  SVG_CSSAttrMap cssMap;
  MakeCSSMap( styleStr, cssMap );

  // font styles
  if ( cssMap [ "font-family" ].length () )
    {
      curState.font_name = cssMap [ "font-family" ];
    }

  if ( cssMap[ "font-size" ].length() ) 
    {
      curState.font_size = atof( cssMap[ "font-size" ].c_str() );
    }
		
  if ( cssMap[ "font-style" ].length() ) 
    {
      string	fontStyleStr = cssMap[ "font-style" ];
      if ( ( fontStyleStr == "italic" ) || ( fontStyleStr == "oblique" ) )
	curState.fontStyle |= italic;
    }

  if ( cssMap[ "font-weight" ].length() ) 
    {
      string	fontStyleStr = cssMap[ "font-weight" ];
      if ( ( fontStyleStr == "bold" ) || ( fontStyleStr == "bolder" ) )
	curState.fontStyle |= bold;
    }
  
  if ( cssMap[ "font-stretch" ].length() ) 
    {
      string	fontStyleStr = cssMap[ "font-stretch" ];
      
      if( fontStyleStr.find("condensed") >= 0 )
	curState.fontStyle |= condense;
    }

  if ( cssMap[ "text-align" ].length() ) 
    {
      string	align = cssMap[ "text-align" ];
      if ( ( align == "right" ) || ( align == "ai-right" ) )			
	curState.text_alignment = align_Right;
      else if ( ( align == "center" )	|| ( align == "ai-center" ) )	
	curState.text_alignment = align_Center;
      else if ( ( align == "left" ) || ( align == "ai-left" ) )
	curState.text_alignment = align_Left;
      else if ( ( align == "justify" ) )
	curState.text_alignment = align_Justify;
  }

  if ( cssMap[ "text-anchor" ].length() ) 
    {
      string	align = cssMap[ "text-anchor" ];
      if ( align == "end" )			
	curState.text_alignment = align_Right;
      else if ( align == "middle" )
	curState.text_alignment = align_Center;
    }

  if ( cssMap[ "text-decoration" ].length() ) 
    {
      string decoration = cssMap[ "text-decoration" ];
      curState.text_decoration = decoration;
    }
  
  if ( cssMap[ "letter-spacing" ].length() ) 
    {
      double letterSpace = atof( cssMap[ "letter-spacing" ].c_str() );
      curState.letter_spacing = letterSpace;
    }
  
  if ( cssMap[ "word-spacing" ].length() ) 
    {
      double wordSpace = atof( cssMap[ "word-spacing" ].c_str() );
      curState.word_spacing = wordSpace;
    }
  
  if ( cssMap[ "line-height" ].length() ) 
    {
      double leading = atof( cssMap[ "line-height" ].c_str() );
      curState.leading = leading;
    }
	
  // NOTE: moved fill & stroke AFTER text, due to needs of text to play with fill_valid!

  if ( cssMap[ "fill" ].length() ) 
    {
      if ( UT_parseColor( cssMap[ "fill" ].c_str(), curState.fill ) ) 
	curState.fill_valid = true;
      else
	curState.fill_valid = false;
    }

  // handle both fillrule and fill-rule, given changes in SVG spec
  string  ruleStr;
  if ( cssMap[ "fillrule" ].length() ) 		
    ruleStr = cssMap[ "fillrule" ];
  else if ( cssMap[ "fill-rule" ].length() ) 	
    ruleStr = cssMap[ "fill-rule" ];

  if ( ruleStr.length() ) 
    {
      if ( ruleStr == "nonzero" )
	curState.fill_evenOdd = false;
      else
	curState.fill_evenOdd = true;
    } 
  else if ( this->groupLevel == 0 )	// don't switch to default if inside a group, because it may already be setup!
    curState.fill_evenOdd = true;
  
  // handle fill opacity
  if ( cssMap[ "fill-opacity" ].length() ) 
    {
      double	opac = atof( cssMap[ "fill-opacity" ].c_str() );
      curState.fill_opacity = opac;
    }
  
  // stroke styles
  if ( cssMap[ "stroke" ].length() ) 
    {      
      if ( HexStr2Color( cssMap[ "stroke" ].c_str(), curState.stroke ) ) 
	curState.stroke_valid = true;
      else
	curState.stroke_valid = false;	// none
    }
  
  if ( cssMap[ "stroke-width" ].length() ) 
    {
      double lineWidth = atof( cssMap[ "stroke-width" ].c_str() );
      if ( lineWidth == 0 )	
	curState.stroke_valid = false;	// it's pretty safe to assume that 0 width == NONE
      else 
	{
	  curState.stroke_valid = true;
	  curState.stroke_width = lineWidth;
	}
    }

  if ( cssMap[ "stroke-linejoin" ].length() ) 
    {
      string tStr = cssMap[ "stroke-linejoin" ];
      if ( tStr == "miter" )		
	curState.join = join_Miter;
      else if ( tStr == "round" )	
	curState.join = join_Round;
      else if ( tStr == "bevel" )	
	curState.join = join_Bevel;
      curState.stroke_valid = true;
    }
  
  if ( cssMap[ "stroke-linecap" ].length() ) 
    {
      string	tStr = cssMap[ "stroke-linecap" ];
      if ( tStr == "butt" )	
	curState.cap = cap_Butt;
      else if ( tStr == "round" )		
	curState.cap = cap_Butt;
      else if ( tStr == "square" )	
	curState.cap = cap_Square;
      curState.stroke_valid = true;
    }
  
  if ( cssMap[ "stroke-dasharray" ].length() ) 
    {
      UT_sint32	fCount = 0;
      double	floatArray[100];	// shouldn't ever have that many
      string	tStr = cssMap[ "stroke-dasharray" ];
    
      if ( tStr == "none" ) 
	{
	  curState.dashCount = 0;
	  curState.stroke_valid = true;
	} 
      else 
	{
	  UT_uint32	idx = 0;
	  while ( idx < tStr.length() ) 
	    {
	      string	aPoint;
	      
	      // scan for first point
	      while ( !isdigit( tStr[idx] ) && ( idx < tStr.length() ) )	
		idx++;
	      
	      // now build up the point list (everything until next letter!)
	      while ( isdigit( tStr[idx] ) && ( idx < tStr.length() ) ) {
		aPoint += tStr[idx++];
	      }
	      
	      // add to the list
	      if ( aPoint.length() > 0 )
		floatArray[ fCount++ ] = atof( aPoint.c_str() );
	    }
	  memcpy( curState.dashArray, floatArray, sizeof( floatArray ) );
	  curState.dashCount = fCount;
	  curState.stroke_valid = true;
	}
    }
  
  // handle stroke opacity
  if ( cssMap[ "stroke-opacity" ].length() ) 
    {
      curState.stroke_opacity = atof( cssMap[ "stroke-opacity" ].c_str() );
      curState.stroke_valid = true;
    }
  
  // set the back of the state list to the current state
  mStateList.back () = curState;
}
