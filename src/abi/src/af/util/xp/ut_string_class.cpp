// ut_string_class.cpp

// A simple string class for use where templates are not
// allowed.
//
// Copyright (C) 2001 Mike Nordell <tamlin@algonet.se>
// Copyright (C) 2002 Tomas Frydrych <tomas@frydrych.uklinux.net>
// Copyright (C) 2002 Dom Lachowicz <cinamod@hotmail.com>
// 
// This class is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This class is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
// 02111-1307, USA.
//
#include <stdio.h>
#include <stdlib.h>				// size_t
#include <string.h>				// strcmp
#include <locale.h>
#include <ctype.h>
#include <stdarg.h>

#include "ut_string.h"
#include "ut_string_class.h"
#include "ut_stringbuf.h"
#include "ut_debugmsg.h"		// UT_DEBUGMSG
#include "ut_assert.h"			// UT_ASSERT

//
// This string class is intended to meet the following requirements.
//
// - It shall not use templates.
// - It shall not provide a sorting order [1].
// - It shall allow dated compilers to use it [2].
// - It shall work with non-conforming library implementations.
// - It shall not use reference counting since that is 1) not
//   platform independent (the need for some kind of locking mechanism)
//   and 2) in a multi threaded environment every single string would
//   still have to be copied, where the ref-counting would be useless
//   and finally 3) locking would slow us down.
//
// [1] It's impossible to get a sorting order other than plain strcmp
//     without adding locale information. This would make this class
//     unacceptably large, and it would still be close to impossible
//     to make it "right". Note that there is however a non-member
//     operator< to make it possible to put a UT_String in a STL
//     (std C++ library) container. It _only_ provides strcmp ordering.
//
// [2] This is somewhat arbitrary, but it basically means you should
//     be able to use it with an old compiler.
//

//////////////////////////////////////////////////////////////////

static const char pszEmpty[] = { 0 };

static const UT_UCS2Char ucs2Empty[] = { 0 };
static const UT_UCS4Char ucs4Empty[] = { 0 };

////////////////////////////////////////////////////////////////////////
//
//  8-bit string
//
//  String is built of 8-bit units (bytes)
//  Encoding could be any single-byte or multi-byte encoding
//
////////////////////////////////////////////////////////////////////////

UT_String::UT_String()
:	pimpl(new UT_Stringbuf)
{
}

UT_String::UT_String(const char* sz, size_t n)
:	pimpl(new UT_Stringbuf(sz, n ? n : (sz) ? strlen(sz) : 0))
{
}

UT_String::UT_String(const UT_String& rhs)
:	pimpl(new UT_Stringbuf(*rhs.pimpl))
{
}

UT_String::~UT_String()
{
	delete pimpl;
}


//////////////////////////////////////////////////////////////////
// accessors

size_t UT_String::size() const
{
	return pimpl->size();
}

bool UT_String::empty() const
{
	return pimpl->empty();
}

void UT_String::clear() const
{
	pimpl->clear();
}

UT_String UT_String::substr(size_t iStart, size_t nChars) const
{
	const size_t nSize = pimpl->size();

	if (iStart >= nSize || !nChars) {
		return UT_String();
	}

	const char* p = pimpl->data() + iStart;
	if (iStart + nChars > nSize) {
		nChars = nSize - iStart;
	}

	return UT_String(p, nChars);
}

const char* UT_String::c_str() const
{
	return pimpl->size() ? pimpl->data() : pszEmpty;
}

//////////////////////////////////////////////////////////////////
// mutators

UT_String& UT_String::operator=(const UT_String& rhs)
{
	if (this != &rhs) {
		*pimpl = *rhs.pimpl;
	}
	return *this;
}

UT_String& UT_String::operator=(const char* rhs)
{
  if (!rhs)
    pimpl->clear ();
  else
    pimpl->assign(rhs, strlen(rhs));
  return *this;
}

UT_String& UT_String::operator+=(const UT_String& rhs)
{
	if (this != &rhs) {
		pimpl->append(*rhs.pimpl);
	} else {
		UT_Stringbuf t(*rhs.pimpl);
		pimpl->append(t);
	}
	return *this;
}

// TODO What encoding do these functions think the
// TODO  right-hand character is in?  Same as the left-hand side?
// TODO  ASCII?  ISO-8859-1?  System encoding?
// TODO  any old 8-bit single-byte or multibyte encoding?

UT_String& UT_String::operator+=(const char* rhs)
{
	UT_return_val_if_fail(rhs, *this);
	pimpl->append(rhs, strlen(rhs));
	return *this;
}

UT_String& UT_String::operator+=(char rhs)
{
	char cs = rhs;
	pimpl->append(&cs, 1);
	return *this;
}

void UT_String::swap(UT_String& rhs)
{
	UT_Stringbuf* p = pimpl;
	pimpl = rhs.pimpl;
	rhs.pimpl = p;
}

//////////////////////////////////////////////////////////////////
// End of class members, start of free functions
//////////////////////////////////////////////////////////////////

size_t UT_String_findCh(const UT_String &st, char ch)
{
  for (size_t i = 0 ; i < st.size(); i++)
    if (st[i] == ch)
      return i;
  return (size_t)-1;
}

size_t UT_String_findRCh(const UT_String &st, char ch)
{
  for (size_t i = st.size() ; i > 0; i--)
    if (st[i] == ch)
      return i;
  return (size_t)-1;
}

static UT_uint32
UT_printf_string_upper_bound (const char* format,
			      va_list      args)
{
  UT_uint32 len = 1;

  while (*format)
    {
      bool long_int = false;
      bool extra_long = false;
      char c;

      c = *format++;

      if (c == '%')
	{
	  bool done = false;

	  while (*format && !done)
	    {
	      switch (*format++)
		{
		  char *string_arg;

		case '*':
		  len += va_arg (args, int);
		  break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		  /* add specified format length, since it might exceed the
		   * size we assume it to have.
		   */
		  format -= 1;
		  len += strtol (format, (char**) &format, 10);
		  break;
		case 'h':
		  /* ignore short int flag, since all args have at least the
		   * same size as an int
		   */
		  break;
		case 'l':
		  if (long_int)
		    extra_long = true; /* linux specific */
		  else
		    long_int = true;
		  break;
		case 'q':
		case 'L':
		  long_int = true;
		  extra_long = true;
		  break;
		case 's':
		  string_arg = va_arg (args, char *);
		  if (string_arg)
		    len += strlen (string_arg);
		  else
		    {
		      /* add enough padding to hold "(null)" identifier */
		      len += 16;
		    }
		  done = true;
		  break;
		case 'd':
		case 'i':
		case 'o':
		case 'u':
		case 'x':
		case 'X':
		    {
		      if (long_int)
			(void) va_arg (args, long);
		      else
			(void) va_arg (args, int);
		    }
		  len += extra_long ? 64 : 32;
		  done = true;
		  break;
		case 'D':
		case 'O':
		case 'U':
		  (void) va_arg (args, long);
		  len += 32;
		  done = true;
		  break;
		case 'e':
		case 'E':
		case 'f':
		case 'g':
		    (void) va_arg (args, double);
		  len += extra_long ? 64 : 32;
		  done = true;
		  break;
		case 'c':
		  (void) va_arg (args, int);
		  len += 1;
		  done = true;
		  break;
		case 'p':
		case 'n':
		  (void) va_arg (args, void*);
		  len += 32;
		  done = true;
		  break;
		case '%':
		  len += 1;
		  done = true;
		  break;
		default:
		  /* ignore unknow/invalid flags */
		  break;
		}
	    }
	}
      else
	len += 1;
    }

  return len;
}

#if !defined (VA_COPY)
#  if defined (__GNUC__) && defined (__PPC__) && (defined (_CALL_SYSV) || defined (_WIN32) || defined(WIN32)) || defined(__s390__)
#  define VA_COPY(ap1, ap2)	  (*(ap1) = *(ap2))
#  elif defined (VA_COPY_AS_ARRAY)
#  define VA_COPY(ap1, ap2)	  memmove ((ap1), (ap2), sizeof (va_list))
#  else /* va_list is a pointer */
#  define VA_COPY(ap1, ap2)	  ((ap1) = (ap2))
#  endif /* va_list is a pointer */
#endif /* !VA_COPY */

UT_String& UT_String_vprintf (UT_String & inStr, const char *format,
			      va_list      args1)
{
  char *buffer;
  va_list args2;

  VA_COPY (args2, args1);

  buffer = new char [ UT_printf_string_upper_bound (format, args1) ];
  vsprintf (buffer, format, args2);
  va_end (args2);

  inStr = buffer;

  delete [] buffer;

  return inStr;
}

UT_String& UT_String_vprintf (UT_String & inStr, const UT_String & format,
			va_list      args1)
{
  return UT_String_vprintf ( inStr, format.c_str(), args1 ) ;
}

UT_String& UT_String_sprintf(UT_String & inStr, const char * inFormat, ...)
{
  va_list args;
  va_start (args, inFormat);
  UT_String_vprintf (inStr, inFormat, args);
  va_end (args);

  return inStr;
}

UT_String UT_String_sprintf(const char * inFormat, ...)
{
  UT_String outStr ("");

  va_list args;
  va_start (args, inFormat);
  UT_String_vprintf (outStr, inFormat, args);
  va_end (args);

  return outStr;
}

UT_String UT_String_vprintf(const char * inFormat, va_list args1)
{
  UT_String outStr ("");  
  return UT_String_vprintf( outStr, inFormat, args1 );
}

UT_String UT_String_vprintf(const UT_String & inFormat, va_list args1)
{
  UT_String outStr ("");
  return UT_String_vprintf( outStr, inFormat, args1 );
}

/*!
 * Assuming a string of standard abiword properties eg. "fred:nerk; table-width:1.0in; table-height:10.in"
 * Return the value of the property sProp or NULL if it is not present.
 * This UT_String * should be deleted by the calling programming after it is finished with it.
 */
UT_String UT_String_getPropVal(const UT_String & sPropertyString, const UT_String & sProp)
{
	UT_String sWork(sProp);
	sWork += ":";

	const char * szWork = sWork.c_str();
	const char * szProps = sPropertyString.c_str();
	const char * szLoc = strstr(szProps,szWork);
	if(szLoc == NULL)
	{
		return UT_String();
	}
//
// Look if this is the last property in the string.
//
	const char * szDelim = strchr(szLoc,';');
	if(szDelim == NULL)
	{
//
// Remove trailing spaces
//
		UT_sint32 iSLen = strlen(szProps);
		while(iSLen > 0 && szProps[iSLen-1] == ' ')
		{
			iSLen--;
		}
//
// Calculate the location of the substring
//
		UT_sint32 offset = (UT_sint32) ((size_t) szLoc - (size_t)szProps);
		offset += strlen(szWork);
		return UT_String(sPropertyString.substr(offset,(iSLen - offset)));
	}
	else
	{
		szDelim = strchr(szLoc,';');
		if(szDelim == NULL)
		{
//
// bad property string
//
			UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
			return UT_String();
		}
//
// Remove trailing spaces.
//
		while(*szDelim == ';' || *szDelim == ' ')
		{
			szDelim--;
		}
//
// Calculate the location of the substring
//
		UT_sint32 offset = (UT_sint32) ((size_t) szLoc - (size_t)szProps);
		offset += strlen(szWork);
		UT_sint32 iLen = (UT_sint32) ((size_t) szDelim - (size_t) szProps) + 1; 
		return UT_String(sPropertyString.substr(offset,(iLen - offset)));
	}
}

/*!
 * Assuming a string of standard abiword properties eg. "fred:nerk; table-width:1.0in; table-height:10.in"
 * Add the property sProp with value sVal to the string of properties. If the property is already present, replace the 
 * old value with the new value.
 */
void UT_String_setProperty(UT_String & sPropertyString, const UT_String & sProp, const UT_String & sVal)
{
//
// Remove the old value if it exists and tack the new property on the end.
//
	UT_String_removeProperty(sPropertyString, sProp);
	if(sPropertyString.size() > 0)
	{
		sPropertyString += "; ";
	}
	sPropertyString += sProp;
	sPropertyString += ":";
	sPropertyString += sVal;
}

/*!
 * Assuming a string of standard abiword properties eg. "fred:nerk; table-width:1.0in; table-height:10.in"
 * Remove the property sProp and it's value from the string of properties. 
 */
void UT_String_removeProperty(UT_String & sPropertyString, const UT_String & sProp)
{
	UT_String sWork ( sProp );
	sWork += ":";
	const char * szWork = sWork.c_str();
	const char * szProps = sPropertyString.c_str();
	const char * szLoc = strstr(szProps,szWork);
	if(szLoc == NULL)
	{
//
// Not here, do nothing
		return ;
	}
//
// Found it, Get left part.
//
	UT_sint32 locLeft = (UT_sint32) ((size_t) szLoc - (size_t) szProps);
	UT_String sLeft;
	if(locLeft == 0)
	{
		sLeft.clear();
	}
	else
	{
		sLeft = sPropertyString.substr(0,locLeft);
	}
	locLeft = (UT_sint32) sLeft.size();
	if(locLeft > 0)
	{
//
// If this element is the last item in the properties there is no "; ".
//
// Remove trailing ';' and ' '
//
		locLeft--;
		while(locLeft >= 0 && (sLeft[locLeft] == ';' || sLeft[locLeft] == ' '))
		{
			locLeft--;
		}
	}
	UT_String sNew;
	if(locLeft > 0)
	{
		sNew = sLeft.substr(0,locLeft+1);
	}
	else
	{
		sNew.clear();
	}
//
// Look for ";" to get right part
//
	const char * szDelim = strchr(szLoc,';');
	if(szDelim == NULL)
	{
//
// No properties after this, just assign and return
//
		sPropertyString = sNew;
	}
	else
	{
//
// Just slice off the properties and tack them onto the pre-existing sNew
//
		while(*szDelim == ';' || *szDelim == ' ')
		{
			szDelim++;
		}
		UT_sint32 offset = (UT_sint32) ((size_t) szDelim - (size_t) szProps);
		UT_sint32 iLen = sPropertyString.size() - offset;
		if(sNew.size() > 0)
		{
			sNew += "; ";
		}
		sNew += sPropertyString.substr(offset,iLen);
		sPropertyString = sNew;
	}
}

//////////////////////////////////////////////////////////////////
// Helpers

bool operator==(const UT_String& s1, const UT_String& s2)
{
	return strcmp(s1.c_str(), s2.c_str()) == 0;
}

bool operator==(const UT_String& s1, const char* s2)
{
	return strcmp(s1.c_str(), s2) == 0;
}

bool operator==(const char* s1, const UT_String& s2)
{
	return s2 == s1;
}

bool operator!=(const UT_String& s1, const UT_String& s2)
{
	return !(s1 == s2);
}

bool operator!=(const UT_String& s1, const char*  s2)
{
	return !(s1 == s2);
}

bool operator!=(const char* s1, const UT_String& s2)
{
	return !(s2 == s1);
}

bool operator<(const UT_String& s1, const UT_String& s2)
{
	return strcmp(s1.c_str(), s2.c_str()) < 0;
}

UT_String operator+(const UT_String& s1, const UT_String& s2)
{
	UT_String s(s1);
	s += s2;
	return s;
}

char UT_String::operator[](size_t iPos) const
{
	UT_ASSERT(iPos <= size());
	if (iPos == size())
		return '\0';
	return pimpl->data()[iPos];
}

char& UT_String::operator[](size_t iPos)
{
	UT_ASSERT(iPos <= size());
	return pimpl->data()[iPos];
}


UT_uint32 hashcode(const UT_String& string)
{
	// from glib
	const char* p = string.c_str();
	UT_uint32 h = (UT_uint32)*p;
	
	if (h)
	{
		for (p += 1; *p != '\0'; p++)
		{
			h = (h << 5) - h + *p;
		}
	}
	
	return h;
}

////////////////////////////////////////////////////////////////////////
//
//  UTF-8 string: encoding is *always* UTF-8
//
////////////////////////////////////////////////////////////////////////

UT_UTF8String::UT_UTF8String () :
	pimpl(new UT_UTF8Stringbuf)
{
	// 
}

UT_UTF8String::UT_UTF8String (const char * sz) :
	pimpl(new UT_UTF8Stringbuf(sz))
{
	// 
}

UT_UTF8String::UT_UTF8String (const UT_UTF8String & rhs) :
	pimpl(new UT_UTF8Stringbuf(*rhs.pimpl))
{
	// 
}

#ifdef ENABLE_UCS2_STRINGS
UT_UTF8String::UT_UTF8String (const UT_UCS2String & rhs) :
	pimpl(new UT_UTF8Stringbuf)
{
	if (rhs.size ()) appendUCS2 (rhs.ucs2_str (), rhs.size ());
}
#endif

UT_UTF8String::UT_UTF8String (const UT_UCS4String & rhs) :
	pimpl(new UT_UTF8Stringbuf)
{
	if (rhs.size ()) appendUCS4 (rhs.ucs4_str (), rhs.size ());
}

UT_UTF8String::UT_UTF8String (const UT_UCS4Char * sz, size_t n) :
	pimpl(new UT_UTF8Stringbuf)
{
	appendUCS4 (sz, n);
}

UT_UTF8String::~UT_UTF8String ()
{
	delete pimpl;
}

size_t UT_UTF8String::size () const
{
	return pimpl->utf8Length ();
}

size_t UT_UTF8String::byteLength () const
{
	return pimpl->byteLength ();
}

bool UT_UTF8String::empty () const
{
	return pimpl->empty ();
}

void UT_UTF8String::clear () const
{
	pimpl->clear ();
}

UT_UTF8String &	UT_UTF8String::operator=(const char * rhs)
{
  // treat null string assignment as a clear
  if (!rhs)
    pimpl->clear();
  else
    pimpl->assign (rhs);

  return *this;
}

UT_UTF8String &	UT_UTF8String::operator=(const UT_UTF8String & rhs)
{
	if (this != &rhs) {
		*pimpl = *rhs.pimpl;
	}
	return *this;
}

#ifdef ENABLE_UCS2_STRINGS
UT_UTF8String &	UT_UTF8String::operator=(const UT_UCS2String & rhs)
{
	pimpl->clear ();
	if (rhs.size ()) appendUCS2 (rhs.ucs2_str (), rhs.size ());
	return *this;
}
#endif

UT_UTF8String &	UT_UTF8String::operator+=(const char * rhs)
{
	UT_return_val_if_fail(rhs, *this);
	pimpl->append (rhs);
	return *this;
}

UT_UTF8String &	UT_UTF8String::operator+=(const UT_UTF8String & rhs)
{
	pimpl->append (*rhs.pimpl);
	return *this;
}

#ifdef ENABLE_UCS2_STRINGS
UT_UTF8String &	UT_UTF8String::operator+=(const UT_UCS2String & rhs)
{
	if (rhs.size ()) appendUCS2 (rhs.ucs2_str (), rhs.size ());
	return *this;
}
#endif

const char * UT_UTF8String::utf8_str () const
{
	return pimpl->utf8Length () ? pimpl->data() : pszEmpty;
}

#ifdef ENABLE_UCS2_STRINGS
void UT_UTF8String::appendUCS2 (const UT_UCS2Char * sz, size_t n /* 0 = null-terminated */)
{
	pimpl->appendUCS2 (sz, n);
}
#endif

void UT_UTF8String::appendUCS4 (const UT_UCS4Char * sz, size_t n /* 0 = null-terminated */)
{
	pimpl->appendUCS4 (sz, n);
}

/* escapes '<', '>' & '&' in the current string
 */
const UT_UTF8String & UT_UTF8String::escapeXML ()
{
	pimpl->escapeXML ();
	return *this;
}

/* translates the current string to MIME "quoted-printable" format
 */
const UT_UTF8String & UT_UTF8String::escapeMIME ()
{
	pimpl->escapeMIME ();
	return *this;
}

#ifdef ENABLE_UCS2_STRINGS
UT_UCS2String UT_UTF8String::ucs2_str ()
{
	UT_UCS2String ucs2string;

	const char * utf8string = pimpl->data ();
	size_t bytelength = pimpl->byteLength ();

	while (true)
	{
		UT_UCS2Char ucs2 = UT_UCS2Stringbuf::UTF8_to_UCS2 (utf8string, bytelength);
		if (ucs2 == 0) break;
		ucs2string += ucs2;
	}
	return ucs2string;
}
#endif

UT_UCS4String UT_UTF8String::ucs4_str ()
{
	UT_UCS4String ucs4string;

	const char * utf8string = pimpl->data ();
	size_t bytelength = pimpl->byteLength ();

	while (true)
	{
		UT_UCS4Char ucs4 = UT_UCS4Stringbuf::UTF8_to_UCS4 (utf8string, bytelength);
		if (ucs4 == 0) break;
		ucs4string += ucs4;
	}
	return ucs4string;
}

bool operator==(const UT_UTF8String& s1, const UT_UTF8String& s2)
{
	return strcmp(s1.utf8_str(), s2.utf8_str()) == 0;
}

UT_UTF8String operator+(const UT_UTF8String & s1, const UT_UTF8String & s2)
{
	UT_UTF8String s(s1);
	s += s2;
	return s;
}

UT_UTF8String UT_UTF8String_sprintf(const char * inFormat, ...)
{
  UT_String str ("");

  va_list args;
  va_start (args, inFormat);
  UT_String_vprintf (str, inFormat, args);
  va_end (args);

  // create&return a validated utf8 string based on the input
  return UT_UTF8String(str.c_str());
}

UT_UTF8String & UT_UTF8String_sprintf(UT_UTF8String & inStr, const char * inFormat, ...)
{
  UT_String str ("");

  va_list args;
  va_start (args, inFormat);
  UT_String_vprintf (str, inFormat, args);
  va_end (args);

  // create a validated utf8 string based on the input
  inStr = str.c_str();
  return inStr;
}

#ifdef ENABLE_UCS2_STRINGS

////////////////////////////////////////////////////////////////////////
//
//  UCS-2 string
//
//  String is built of 16-bit units (words)
//
//  TODO: Is this really UCS-2 or UTF-16?
//  TODO:  meaning, does it support surrogates or is it intended to
//  TODO:  support them at any time in the future?
//  TODO: Correctly, UCS-2 does not support surrogates and UTF-16 does.
//  TODO: BUT Microsoft calls their native Unicode encoding UCS-2
//  TODO:  while it supports surrogates and is thus really UTF-16.
//  TODO: Surrogates are Unicode characters with codepoints above
//  TODO:  65535 which cannot therefore fit into a 2-byte word.
//  TODO: This means that TRUE UCS-2 is a single-word encoding and
//  TODO:  UTF-16 is a multi-word encoding.
//
//  NOTE: We shouldn't actually need 16-bit strings anymore since
//  NOTE:  AbiWord is now fully converted to using 32-bit Unicode
//  NOTE:  internally. The only possible needs for this is for
//  NOTE:  Windows GUI, filesystem and API functions where applicable;
//  NOTE:  and perhaps some file formats or external libraries
//
////////////////////////////////////////////////////////////////////////

UT_UCS2String::UT_UCS2String()
:	pimpl(new UT_UCS2Stringbuf)
{
}

UT_UCS2String::UT_UCS2String(const UT_UCS2Char* sz, size_t n)
:	pimpl(new UT_UCS2Stringbuf(sz, n ? n : (sz) ? UT_UCS2_strlen(sz) : 0))
{
}

UT_UCS2String::UT_UCS2String(const UT_UCS2String& rhs)
	:	pimpl(new UT_UCS2Stringbuf(*rhs.pimpl))
{
}

UT_UCS2String::~UT_UCS2String()
{
	delete pimpl;
}


//////////////////////////////////////////////////////////////////
// accessors

size_t UT_UCS2String::size() const
{
	return pimpl->size();
}

bool UT_UCS2String::empty() const
{
	return pimpl->empty();
}

void UT_UCS2String::clear() const
{
	pimpl->clear();
}

UT_UCS2String UT_UCS2String::substr(size_t iStart, size_t nChars) const
{
	const size_t nSize = pimpl->size();

	if (iStart >= nSize || !nChars) {
		return UT_UCS2String();
	}

	const UT_UCS2Char* p = pimpl->data() + iStart;
	if (iStart + nChars > nSize) {
		nChars = nSize - iStart;
	}

	return UT_UCS2String(p, nChars);
}

const UT_UCS2Char* UT_UCS2String::ucs2_str() const
{
	return pimpl->size() ? pimpl->data() : ucs2Empty;
}

const UT_UCS4Char* UT_UCS2String::ucs4_str()
{
	if(!pimpl->size()) return ucs4Empty;

	return pimpl->ucs4_data ();
}

const char* UT_UCS2String::utf8_str()
{
	if(!pimpl->size()) return pszEmpty;

	return pimpl->utf8_data ();
}

//////////////////////////////////////////////////////////////////
// mutators

UT_UCS2String& UT_UCS2String::operator=(const UT_UCS2String& rhs)
{
	if (this != &rhs) {
		*pimpl = *rhs.pimpl;
	}
	return *this;
}

UT_UCS2String& UT_UCS2String::operator=(const UT_UCS2Char* rhs)
{
	UT_return_val_if_fail(rhs, *this);
	pimpl->assign(rhs, UT_UCS2_strlen(rhs));
	return *this;
}

UT_UCS2String& UT_UCS2String::operator+=(const UT_UCS2String& rhs)
{
	if (this != &rhs) {
		pimpl->append(*rhs.pimpl);
	} else {
		UT_UCS2Stringbuf t(*rhs.pimpl);
		pimpl->append(t);
	}
	return *this;
}

UT_UCS2String& UT_UCS2String::operator+=(const UT_UCS2Char* rhs)
{
	UT_return_val_if_fail(rhs, *this);
	pimpl->append(rhs, UT_UCS2_strlen(rhs));
	return *this;
}

UT_UCS2String& UT_UCS2String::operator+=(UT_UCS2Char rhs)
{
	UT_UCS2Char cs = rhs;
	pimpl->append(&cs, 1);
	return *this;
}

// TODO What encoding do these functions think the 8-bit
// TODO  character is in?  ASCII?  ISO-8859-1?  System encoding?
// TODO  any old 8-bit single-byte or multibyte encoding?

UT_UCS2String& UT_UCS2String::operator+=(char rhs)
{
	return this->operator+=((unsigned char)rhs);
}

UT_UCS2String& UT_UCS2String::operator+=(unsigned char rhs)
{
	UT_UCS2Char cs[2];
	char rs[2];

	rs[0] = (char)rhs; rs[1] = 0;
	UT_UCS2_strcpy_char (cs, rs);

	pimpl->append(cs, 1);
	return *this;
}

void UT_UCS2String::swap(UT_UCS2String& rhs)
{
	UT_UCS2Stringbuf* p = pimpl;
	pimpl = rhs.pimpl;
	rhs.pimpl = p;
}

//////////////////////////////////////////////////////////////////
// End of class members, start of free functions
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// Helpers

bool operator==(const UT_UCS2String& s1, const UT_UCS2String& s2)
{
	return UT_UCS2_strcmp(s1.ucs2_str(), s2.ucs2_str()) == 0;
}

bool operator==(const UT_UCS2String& s1, const UT_UCS2Char* s2)
{
	return UT_UCS2_strcmp(s1.ucs2_str(), s2) == 0;
}

bool operator==(const UT_UCS2Char* s1, const UT_UCS2String& s2)
{
	return s2 == s1;
}

bool operator!=(const UT_UCS2String& s1, const UT_UCS2String& s2)
{
	return !(s1 == s2);
}

bool operator!=(const UT_UCS2String& s1, const UT_UCS2Char*  s2)
{
	return !(s1 == s2);
}

bool operator!=(const UT_UCS2Char* s1, const UT_UCS2String& s2)
{
	return !(s2 == s1);
}

bool operator<(const UT_UCS2String& s1, const UT_UCS2String& s2)
{
	return UT_UCS2_strcmp(s1.ucs2_str(), s2.ucs2_str()) < 0;
}

UT_UCS2String operator+(const UT_UCS2String& s1, const UT_UCS2String& s2)
{
	UT_UCS2String s(s1);
	s += s2;
	return s;
}

UT_UCS2Char UT_UCS2String::operator[](size_t iPos) const
{
	UT_ASSERT(iPos <= size());
	if (iPos == size())
		return '\0';
	return pimpl->data()[iPos];
}

UT_UCS2Char& UT_UCS2String::operator[](size_t iPos)
{
	UT_ASSERT(iPos <= size());
	return pimpl->data()[iPos];
}

#endif

////////////////////////////////////////////////////////////////////////
//
//  UCS-4 string
//
//  String is built of 32-bit units (longs)
//
//  NOTE: Ambiguity between UCS-2 and UTF-16 above makes no difference
//  NOTE:  in the case of UCS-4 and UTF-32 since they really are
//  NOTE:  identical
//
////////////////////////////////////////////////////////////////////////

UT_UCS4String::UT_UCS4String()
:	pimpl(new UT_UCS4Stringbuf)
{
}

UT_UCS4String::UT_UCS4String(const UT_UCS4Char* sz, size_t n)
:	pimpl(new UT_UCS4Stringbuf(sz, n ? n : (sz) ? UT_UCS4_strlen(sz) : 0))
{
}

UT_UCS4String::UT_UCS4String(const UT_UCS4String& rhs)
:	pimpl(new UT_UCS4Stringbuf(*rhs.pimpl))
{
}

#ifdef ENABLE_UCS2_STRINGS
UT_UCS4String::UT_UCS4String(const UT_UCS2String& rhs)
	:	pimpl(new UT_UCS4Stringbuf(NULL, rhs.size()))
{
	const UT_UCS2Char * pUcs2 = rhs.ucs2_str();
	
	for(UT_uint32 i = 0; i < pimpl->size(); i++)
		*(pimpl->data()+i) = (UT_UCS4Char)(*(pUcs2 + i));
}
#endif

/* construct from a string in UTF-8 format
 */
UT_UCS4String::UT_UCS4String(const char * utf8_str, size_t bytelength /* 0 == zero-terminate */)
:	pimpl(new UT_UCS4Stringbuf)
{
	if (bytelength == 0) {
		if (utf8_str == 0) return;
		bytelength = strlen (utf8_str);
	}
	while (true) {
		UT_UCS4Char ucs4 = UT_UCS4Stringbuf::UTF8_to_UCS4 (utf8_str, bytelength);
		if (ucs4 == 0) break; // end-of-string
		pimpl->append (&ucs4, 1);
	}
}

/* construct from a string in UTF-8 format
 * if (strip_whitespace == true) replace all white space sequences with a single UCS_SPACE
 * if (strip_whitespace != true) replace CR-LF & CR by LF
 * non-breaking spaces (&nbsp; UCS_NBSP 0x0a) are not white space; see UT_UCS4_isspace()
 */
UT_UCS4String::UT_UCS4String(const char * utf8_str, size_t bytelength /* 0 == zero-terminate */, bool strip_whitespace)
:	pimpl(new UT_UCS4Stringbuf)
{
	if (bytelength == 0) {
		if (utf8_str == 0) return;
		bytelength = strlen (utf8_str);
	}
	UT_UCS4Char ucs4a = UT_UCS4Stringbuf::UTF8_to_UCS4 (utf8_str, bytelength);
	while (true) {
		if (ucs4a == 0) break; // end-of-string
		UT_UCS4Char ucs4b = UT_UCS4Stringbuf::UTF8_to_UCS4 (utf8_str, bytelength);
		if (UT_UCS4_isspace (ucs4a)) {
			if (strip_whitespace) {
				if (!UT_UCS4_isspace (ucs4b)) {
					ucs4a = UCS_SPACE;
					pimpl->append (&ucs4a, 1);
					ucs4a = ucs4b;
				}
			} else if (ucs4a == UCS_CR) {
				if (ucs4b == UCS_LF) {
					ucs4a = ucs4b;
				} else {
					ucs4a = UCS_LF;
					pimpl->append (&ucs4a, 1);
					ucs4a = ucs4b;
				}
			} else {
				pimpl->append (&ucs4a, 1);
				ucs4a = ucs4b;
			}
		} else {
			pimpl->append (&ucs4a, 1);
			ucs4a = ucs4b;
		}
	}
}

UT_UCS4String::~UT_UCS4String()
{
	delete pimpl;
}


//////////////////////////////////////////////////////////////////
// accessors

size_t UT_UCS4String::size() const
{
	return pimpl->size();
}

bool UT_UCS4String::empty() const
{
	return pimpl->empty();
}

void UT_UCS4String::clear() const
{
	pimpl->clear();
}

UT_UCS4String UT_UCS4String::substr(size_t iStart, size_t nChars) const
{
	const size_t nSize = pimpl->size();

	if (iStart >= nSize || !nChars) {
		return UT_UCS4String();
	}

	const UT_UCS4Char* p = pimpl->data() + iStart;
	if (iStart + nChars > nSize) {
		nChars = nSize - iStart;
	}

	return UT_UCS4String(p, nChars);
}

const UT_UCS4Char* UT_UCS4String::ucs4_str() const
{
	return pimpl->size() ? pimpl->data() : ucs4Empty;
}

const char* UT_UCS4String::utf8_str()
{
	return pimpl->size() ? pimpl->utf8_data() : pszEmpty;
}

//////////////////////////////////////////////////////////////////
// mutators

UT_UCS4String& UT_UCS4String::operator=(const UT_UCS4String& rhs)
{
	if (this != &rhs) {
		*pimpl = *rhs.pimpl;
	}
	return *this;
}

UT_UCS4String& UT_UCS4String::operator=(const UT_UCS4Char* rhs)
{
	UT_return_val_if_fail(rhs, *this);
	pimpl->assign(rhs, UT_UCS4_strlen(rhs));
	return *this;
}

UT_UCS4String& UT_UCS4String::operator+=(const UT_UCS4String& rhs)
{
	if (this != &rhs) {
		pimpl->append(*rhs.pimpl);
	} else {
		UT_UCS4Stringbuf t(*rhs.pimpl);
		pimpl->append(t);
	}
	return *this;
}

UT_UCS4String& UT_UCS4String::operator+=(const UT_UCS4Char* rhs)
{
	UT_return_val_if_fail(rhs, *this);
	pimpl->append(rhs, UT_UCS4_strlen(rhs));
	return *this;
}

UT_UCS4String& UT_UCS4String::operator+=(UT_UCS4Char rhs)
{
	UT_UCS4Char cs = rhs;
	pimpl->append(&cs, 1);
	return *this;
}

// TODO What encoding do these functions think the 8-bit
// TODO  character is in?  ASCII?  ISO-8859-1?  System encoding?
// TODO  any old 8-bit single-byte or multibyte encoding?

UT_UCS4String& UT_UCS4String::operator+=(char rhs)
{
  return this->operator+=((unsigned char)rhs);
}

UT_UCS4String& UT_UCS4String::operator+=(unsigned char rhs)
{
	UT_UCS4Char cs[2];
	char rs[2];

	rs[0] = (char)rhs; rs[1] = 0;
	UT_UCS4_strcpy_char (cs, rs);

	pimpl->append(cs, 1);
	return *this;
}

void UT_UCS4String::swap(UT_UCS4String& rhs)
{
	UT_UCS4Stringbuf* p = pimpl;
	pimpl = rhs.pimpl;
	rhs.pimpl = p;
}


//////////////////////////////////////////////////////////////////
// End of class members, start of free functions
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// Helpers

bool operator==(const UT_UCS4String& s1, const UT_UCS4String& s2)
{
	return UT_UCS4_strcmp(s1.ucs4_str(), s2.ucs4_str()) == 0;
}

bool operator==(const UT_UCS4String& s1, const UT_UCS4Char* s2)
{
	return UT_UCS4_strcmp(s1.ucs4_str(), s2) == 0;
}

bool operator==(const UT_UCS4Char* s1, const UT_UCS4String& s2)
{
	return s2 == s1;
}

bool operator!=(const UT_UCS4String& s1, const UT_UCS4String& s2)
{
	return !(s1 == s2);
}

bool operator!=(const UT_UCS4String& s1, const UT_UCS4Char*  s2)
{
	return !(s1 == s2);
}

bool operator!=(const UT_UCS4Char* s1, const UT_UCS4String& s2)
{
	return !(s2 == s1);
}

bool operator<(const UT_UCS4String& s1, const UT_UCS4String& s2)
{
	return UT_UCS4_strcmp(s1.ucs4_str(), s2.ucs4_str()) < 0;
}

UT_UCS4String operator+(const UT_UCS4String& s1, const UT_UCS4String& s2)
{
	UT_UCS4String s(s1);
	s += s2;
	return s;
}

UT_UCS4Char UT_UCS4String::operator[](size_t iPos) const
{
	UT_ASSERT(iPos <= size());
	if (iPos == size())
		return '\0';
	return pimpl->data()[iPos];
}

UT_UCS4Char& UT_UCS4String::operator[](size_t iPos)
{
	UT_ASSERT(iPos <= size());
	return pimpl->data()[iPos];
}
