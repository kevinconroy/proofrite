/* AbiSource Program Utilities
 * Copyright (C) 1998 AbiSource, Inc.
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

// TODO change this file to not reference GR_Graphics.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>

#include "ut_types.h"
#include "ut_misc.h"
#include "ut_assert.h"
#include "ut_string.h"
#include "ut_units.h"
#include "ut_debugmsg.h"
#include "gr_Graphics.h"

const char * UT_dimensionName(UT_Dimension dim)
{
	switch (dim)
	{
	case DIM_IN:
		return "in";

	case DIM_CM:
		return "cm";

	case DIM_MM:
	   	return "mm";

	case DIM_PI:
		return "pi";

	case DIM_PT:
		return "pt";

	case DIM_PX:
	   	return "px";

	case DIM_PERCENT:
		return "%";

	case DIM_none:
		return "";

	default:
		UT_ASSERT(UT_NOT_IMPLEMENTED);
		return "in";
	}
}

#define STR_COMPARE UT_stricmp

UT_Dimension UT_determineDimension(const char * sz, UT_Dimension fallback)
{
  char * p = NULL ;
  char * old_locale = setlocale(LC_NUMERIC, "C");
  strtod(sz, &p);
  setlocale(LC_NUMERIC, old_locale);

#if defined(__QNXNTO__)
  // workaround for QNX's strtod being overly ambitious
  // being totaly stupid and match 'in' for infinity, but still return 0.
  // it does work fine on qnx if there is a number before 'in..' though.
  if (STR_COMPARE(sz,"inch")==0 || STR_COMPARE(sz,"in")==0)
    return DIM_IN;
#endif

  // p should now point to the unit
  if (p && *p)
    {
      // trim off leading spaces
      while (*p && isspace(*p))
	p++;

      if (STR_COMPARE(p,"in") == 0 || STR_COMPARE(p, "inch") == 0)
	return DIM_IN;
      
      else if (STR_COMPARE(p,"cm") == 0)
	return DIM_CM;
      
      else if (STR_COMPARE(p,"mm") == 0)
	return DIM_MM;
      
      else if (STR_COMPARE(p,"pi") == 0)
	return DIM_PI;
      
      else if (STR_COMPARE(p,"pt") == 0)
	return DIM_PT;
      
      else if (STR_COMPARE(p,"px") == 0)
	return DIM_PX;
      
      else if (STR_COMPARE(p,"%") == 0)
	return DIM_PERCENT;

      UT_DEBUGMSG(("ut_units - unknown unit presented '%s' \n",p));
      UT_ASSERT_NOT_REACHED();
    }
  
  return fallback;
}

double UT_convertInchesToDimension(double inches, UT_Dimension dim)
{
	double valueScaled = inches;

	switch (dim)
	{
	case DIM_IN:	valueScaled = inches;			break;
	case DIM_CM:	valueScaled = (inches * 2.54);	break;
	case DIM_MM:    valueScaled = (inches * 25.4);  break;
	case DIM_PI:	valueScaled = (inches * 6.0);		break;
	case DIM_PT:	valueScaled = (inches * 72.0);	break;
	case DIM_PX:    valueScaled = (inches * GR_Graphics::s_getScreenResolution()); break;
	default:
		UT_ASSERT(UT_NOT_IMPLEMENTED);
		break;
	}

	return valueScaled;
}

double UT_convertDimensions(double f, UT_Dimension from, UT_Dimension to)
{
	double valueScaled = UT_convertDimToInches(f, from);
	return UT_convertInchesToDimension(valueScaled, to);
}

const char * UT_convertInchesToDimensionString(UT_Dimension dim, double valueInInches, const char * szPrecision)
{
	// return pointer to static buffer -- use it quickly.
	//
	// We temporarily force the locale back to english so that
	// we get a period as the decimal point.

	// TODO what should the decimal precision of each different
	// TODO unit of measurement be ??

	static char buf[100];
	char bufFormat[100];
	double valueScaled;

	switch (dim)
	{
	case DIM_IN:
		// (1/16th (0.0625) is smallest unit the ui will
		// let them enter (via the TopRuler), so let's
		// set the precision so that we get nice roundoff.
		// TODO we may need to improve this later.
		valueScaled = valueInInches;
		sprintf(bufFormat,"%%%sfin",((szPrecision && *szPrecision) ? szPrecision : ".4"));
		break;

	case DIM_CM:
		valueScaled = (valueInInches * 2.54);
		sprintf(bufFormat,"%%%sfcm",((szPrecision && *szPrecision) ? szPrecision : ".2"));
		break;

	case DIM_MM:
		valueScaled = (valueInInches * 25.4);
		sprintf(bufFormat,"%%%sfmm",((szPrecision && *szPrecision) ? szPrecision : ".1"));
		break;

	case DIM_PI:
		valueScaled = (valueInInches * 6);
		sprintf(bufFormat,"%%%sfpi",((szPrecision && *szPrecision) ? szPrecision : ".0"));
		break;

	case DIM_PT:
		valueScaled = (valueInInches * 72);
		sprintf(bufFormat,"%%%sfpt",((szPrecision && *szPrecision) ? szPrecision : ".0"));
		break;

	case DIM_PX:
		valueScaled = (valueInInches * GR_Graphics::s_getScreenResolution());
	  sprintf(bufFormat,"%%%sfpx",((szPrecision && *szPrecision) ? szPrecision : ".0"));
	  break;

 	case DIM_none:
		valueScaled = valueInInches;
		sprintf(bufFormat,"%%%sf",((szPrecision && *szPrecision) ? szPrecision : ""));
		break;

	case DIM_PERCENT:
		valueScaled = valueInInches;
		sprintf(bufFormat,"%%%sf%%",((szPrecision && *szPrecision) ? szPrecision : ""));
		break;

	default:
		UT_ASSERT(UT_NOT_IMPLEMENTED);
		valueScaled = valueInInches;
		sprintf(bufFormat,"%%%sf",((szPrecision && *szPrecision) ? szPrecision : ""));
		break;
	}

	char * old_locale = setlocale(LC_NUMERIC,"C");
	sprintf(buf,bufFormat,valueScaled);
	setlocale(LC_NUMERIC,old_locale); // restore original locale

	return buf;
}

const char * UT_formatDimensionString(UT_Dimension dim, double value, const char * szPrecision)
{
	// return pointer to static buffer -- use it quickly.
	//
	// We temporarily force the locale back to english so that
	// we get a period as the decimal point.

	// TODO what should the decimal precision of each different
	// TODO unit of measurement be ??

	static char buf[100];
	char bufFormat[100];

	switch (dim)
	{
	case DIM_IN:
		// (1/16th (0.0625) is smallest unit the ui will
		// let them enter (via the TopRuler), so let's
		// set the precision so that we get nice roundoff.
		// TODO we may need to improve this later.
		sprintf(bufFormat,"%%%sfin",((szPrecision && *szPrecision) ? szPrecision : ".4"));
		break;

	case DIM_CM:
		sprintf(bufFormat,"%%%sfcm",((szPrecision && *szPrecision) ? szPrecision : ".2"));
		break;

	case DIM_MM:
		sprintf(bufFormat,"%%%sfmm",((szPrecision && *szPrecision) ? szPrecision : ".1"));
		break;

	case DIM_PI:
		sprintf(bufFormat,"%%%sfpi",((szPrecision && *szPrecision) ? szPrecision : ".0"));
		break;

	case DIM_PT:
		sprintf(bufFormat,"%%%sfpt",((szPrecision && *szPrecision) ? szPrecision : ".0"));
		break;

	case DIM_PX:
	  sprintf(bufFormat,"%%%sfpx",((szPrecision && *szPrecision) ? szPrecision : ".0"));
		break;

 	case DIM_none:
		sprintf(bufFormat,"%%%sf",((szPrecision && *szPrecision) ? szPrecision : ""));
		break;

	case DIM_PERCENT:
		sprintf(bufFormat,"%%%sf%%",((szPrecision && *szPrecision) ? szPrecision : ""));
		break;

	default:
		UT_ASSERT(UT_NOT_IMPLEMENTED);
		sprintf(bufFormat,"%%%sf",((szPrecision && *szPrecision) ? szPrecision : ""));
		break;
	}
	char * old_locale = setlocale(LC_NUMERIC,"C");
	sprintf(buf,bufFormat,value);
	setlocale(LC_NUMERIC,old_locale); // restore original locale

	return buf;
}

const char * UT_reformatDimensionString(UT_Dimension dim, const char *sz, const char * szPrecision)
{
	UT_ASSERT(sz);  // this function segfaults if it gets a null
	if (!sz)	// if we really need to give it a null, we make it = 0in
	{
		sz = "0.0in";
		UT_DEBUGMSG(("UT_reformatDimensionString just made the assumption null = 0.0in\n"));
	}
	double d = UT_convertDimensionless(sz);

	// if needed, switch unit systems and round off
	UT_Dimension dimOld = UT_determineDimension(sz, dim);

	if (dimOld != dim)
	{
		double dInches = UT_convertToInches(sz);
		d = UT_convertInchesToDimension(dInches, dim);
	}

	return UT_formatDimensionString(dim, d, szPrecision);
}

/*!
 * This method increments a dimenstioned string by the amount given.
\param const char * dimString - string to be incremented.
\param amount of increment.
*/
const char * UT_incrementDimString(const char * dimString, double inc)
{
  UT_Dimension dim = UT_determineDimension(dimString);
  double val = UT_convertDimensionless(dimString);
  val += inc;
  const char * retv = UT_formatDimensionString(dim, val);
  return retv;
}


/*!
 * This method multiplys a dimenstioned string by the amount given.
\param const char * dimString - string to be incremented.
\param amount to be multiplied.
*/
const char * UT_multiplyDimString(const char * dimString, double mult)
{
  UT_Dimension dim = UT_determineDimension(dimString);
  double val = UT_convertDimensionless(dimString);
  val *= mult;
  const char * retv = UT_formatDimensionString(dim, val);
  return retv;
}


double UT_convertToInches(const char* s)
{
	// NOTE: we explicitly use a period '.' as a decimal place
	// NOTE: and assume that the locale is set to english.
	// NOTE: all other places where we deal with these values
	// NOTE: are wrapped with locale code.

	double result = 0;

	if (!s || !*s)
		return 0;

	double f = UT_convertDimensionless(s);

	if (f == 0.)
	    return 0.;

	UT_Dimension dim = UT_determineDimension(s, (UT_Dimension)-1);
	result = UT_convertDimToInches (f, dim);

	return result;
}

double UT_convertDimToInches (double f, UT_Dimension dim)
{
  double result = 0.0;
  switch(dim)
    {
    case DIM_IN: result = f;        break;
    case DIM_PI: result = f / 6;    break;
    case DIM_PT: result = f / 72;   break;
    case DIM_CM: result = f / 2.54; break;
    case DIM_MM: result = f / 25.4; break;
    case DIM_PX: result = f / GR_Graphics::s_getScreenResolution(); break;
    default:
      UT_DEBUGMSG(("Unknown dimension type: %d", dim));
      UT_ASSERT_NOT_REACHED();
      result = f;
    }
  return result;
}

double UT_convertToPoints(const char* s)
{
	if (!s || !*s)
		return 0.;

	double result = 0.;
	double f = UT_convertDimensionless(s);
	UT_Dimension dim = UT_determineDimension(s, (UT_Dimension)-1);

	switch(dim)
	  {
	  case DIM_PT: result = f;             break;
	  case DIM_PI: result = f * 12;        break; // ie, 72 / 6
	  case DIM_IN: result = f * 72;        break;
	  case DIM_CM: result = f * 72 / 2.54; break;
	  case DIM_MM: result = f * 72 / 25.4; break;
	  case DIM_PX: result = f * 72 / GR_Graphics::s_getScreenResolution(); break;
	  default:
	    UT_DEBUGMSG(("Unknown dimension type for: %s", s));
	    UT_ASSERT_NOT_REACHED();
	    result = f;
	  }

	return result;
}

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_sint32 UT_convertToLayoutUnits(const char* s)
{
	return (UT_sint32)(UT_convertToInches(s) * UT_LAYOUT_UNITS);
}

UT_sint32 UT_convertSizeToLayoutUnits(double Value, UT_Dimension dim)
{
	return (UT_sint32)(UT_convertDimToInches(Value, dim) * UT_LAYOUT_UNITS);
}
#endif

double UT_convertDimensionless(const char * sz)
{
	// convert given string into a number -- without using any dimension
	// info that may be in the string.
	//
	// normally we would just use atof(), but that is locale-aware and
	// we want our file format to be locale-independent and thus portable.
	// this means that anything we do internally (eg top ruler gadgets),
	// needs to be in this convention.
	//
	// we can let the GUI do locale-specific conversions for presentation
	// in dialogs and etc.

	char * old_locale = setlocale(LC_NUMERIC,"C");
	double f = atof(sz);
	setlocale(LC_NUMERIC,old_locale);

	return f;
}

const char * UT_convertToDimensionlessString(double value, const char * szPrecision)
{
	// return pointer to static buffer -- use it quickly.
	//
	// We temporarily force the locale back to english so that
	// we get a period as the decimal point.

	static char buf[100];

	char bufFormat[100];
	sprintf(bufFormat,"%%%sf",((szPrecision && *szPrecision) ? szPrecision : ""));

	char * old_locale = setlocale(LC_NUMERIC,"C");
	sprintf(buf,bufFormat,value);
	setlocale(LC_NUMERIC,old_locale); // restore original locale

	return buf;
}

bool UT_hasDimensionComponent(const char * sz)
{
	// TODO : check against known units instead of taking any
	// TODO : ASCII chars after a number as a sign of units.

	if (!sz)
		return false;

	char *p = NULL;
	char * old_locale = setlocale(LC_NUMERIC, "C");
	strtod(sz, &p);
	setlocale(LC_NUMERIC, old_locale);

	// if we landed on non-NULL, unit component
	if(p && *p)
		return true;
	else
		return false;
}

UT_sint32 UT_paperUnits(const char * sz)
{
	// convert string in form "8.5in" into "paper" units.
	// paper units are a relatively low-resolution (say
	// 1/100 inch) but are suitable for specifying margins,
	// etc. -- stuff relative to the actual paper.

	if (!sz || !*sz)
		return 0;

	double dInches = UT_convertToInches(sz);
	double dResolution = UT_PAPER_UNITS_PER_INCH;

	return (UT_sint32)(dInches * dResolution);
}

/*!
  Converts paper units into inches.
  \param1 quantity of paper units
  \return corresponding quantity of inches

  This function uses the UT_PAPER_UNITS_PER_INCH constant
  to convert paper units into inches.

  Paper units are a relatively low-resolution measurement (say
  1/100 inch) but are suitable for specifying margins,
  etc. -- stuff relative to the actual paper.

  \see    UT_paperUnits
  \see    UT_paperUnitsFromInches
*/

double    UT_inchesFromPaperUnits(UT_sint32 iPaperUnits)
{
	double dResolution = UT_PAPER_UNITS_PER_INCH;

	return ((double)iPaperUnits / dResolution);
}

/*!
  Converts inches into paper units.
  \param1 quantity of inches
  \return corresponding quantity of paper units

  This function uses the UT_PAPER_UNITS_PER_INCH constant
  to convert paper units into inches.  Unlike UT_paperUnits,
  this function does not require a string as input.

  Paper units are a relatively low-resolution measurement (say
  1/100 inch) but are suitable for specifying margins,
  etc. -- stuff relative to the actual paper.

  \see    UT_paperUnits
  \see    UT_paperUnitsFromInches
*/
UT_sint32 UT_paperUnitsFromInches(double dInches)
{
	double dResolution = UT_PAPER_UNITS_PER_INCH;

	return (UT_sint32)(dInches * dResolution);
}

UT_sint32 UT_docUnitsFromPaperUnits(GR_Graphics * pG, UT_sint32 iPaperUnits)
{
	// convert number in paper units (see above) into
	// "document" units in the given graphics context.

	UT_ASSERT(pG);

	return (pG->getResolution() * iPaperUnits / UT_PAPER_UNITS_PER_INCH);
}

UT_sint32 UT_layoutUnitsFromPaperUnits(UT_sint32 iPaperUnits)
{
	// convert number in paper units (see above) into
	// "layout" units.

	return (UT_LAYOUT_UNITS * iPaperUnits / UT_PAPER_UNITS_PER_INCH);
}

#if !defined(WITH_PANGO) && defined(USE_LAYOUT_UNITS)
UT_sint32 UT_paperUnitsFromLayoutUnits(UT_sint32 iLayoutUnits)
{
	// convert number in layout units into paper units (loss of precision)

   	return (UT_PAPER_UNITS_PER_INCH * iLayoutUnits / UT_LAYOUT_UNITS);
}
#endif

const char * UT_formatDimensionedValue(double value,
									   const char * szUnits,
									   const char * szPrecision)
{
	// format the given value into a static buffer with
	// the optional format precision and using the given
	// physical units.

	static char buf[100];

	const char * szValue = UT_convertToDimensionlessString(value,szPrecision);

	sprintf(buf,"%s%s",szValue,szUnits);

	return buf;
}

double UT_convertToDimension(const char* s, UT_Dimension dim)
{
	double d;

	// if needed, switch unit systems and round off

	if (UT_determineDimension(s, dim) != dim)
	{
		double dInches = UT_convertToInches(s);
		d = UT_convertInchesToDimension(dInches, dim);
	}
	else
	{
		d = UT_convertDimensionless(s);
	}

	return d;
}
