/* AbiSource Program Utilities
 * Copyright (C) 2002 Dom Lachowicz
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
#include <stdio.h>
#include "ut_locale.h"

// don't like XAP in UT, but oh well...
#include "xap_EncodingManager.h"

/********************************************/

static const char *
explicit_setlocale (int category, const char * locale)
{
  return setlocale (category, locale);
}

/**
 * Class serves to make rolling back exceptions simple, automatic,
 * and transparent
 *
 * USAGE:
 * UT_LocaleTransactor (LC_NUMERIC, "C");
 * sprintf();
 * sprintf();
 * return; // <-- old locale gets reset transparently for you at the end of
 * // the block
 *
 * SEE ALSO: man setlocale
 */
UT_LocaleTransactor::UT_LocaleTransactor (int category, const char * locale)
  : mCategory (category), mOldLocale ("")
{
  mOldLocale = explicit_setlocale (category, locale);
}

UT_LocaleTransactor::UT_LocaleTransactor (int category, const UT_String & locale)
  : mCategory (category), mOldLocale ("")
{
  mOldLocale = explicit_setlocale (category, locale.c_str ());
}

UT_LocaleTransactor::~UT_LocaleTransactor ()
{
  (void)explicit_setlocale (mCategory, mOldLocale.c_str ());
}

/********************************************/

/**
 * Essentially identical to UT_LocaleInfo(getenv("LANG")), except
 * works on non-unix platforms too (i.e. win32)
 */
UT_LocaleInfo::UT_LocaleInfo ()
{
  // should work on any platform, as opposed to init(getenv("LANG"))
  XAP_EncodingManager * instance = XAP_EncodingManager::get_instance ();

  if (instance->getLanguageISOName () != NULL)
    mLanguage = instance->getLanguageISOName ();

  if (instance->getLanguageISOTerritory () != NULL)
    mTerritory = instance->getLanguageISOTerritory ();

  if (instance->getNative8BitEncodingName () != NULL)
    mEncoding = instance->getNative8BitEncodingName ();
}

/**
 * Takes in a string of the form "language_TERRITORY.ENCODING" or
 * "language-TERRITORY.ENCODING" and decomposes it. TERRITORY and ENCODING
 * parts are optional
 */
UT_LocaleInfo::UT_LocaleInfo (const char * locale)
{
  init (locale);
}

UT_LocaleInfo::UT_LocaleInfo (const UT_String & locale)
{
  init (locale);
}

/* static */const UT_LocaleInfo UT_LocaleInfo::system()
{
  return UT_LocaleInfo();
}

/**
 * True if language field is non-null/non-empty, false if not
 */
bool UT_LocaleInfo::hasLanguage () const
{
  return mLanguage.size () != 0;
}

/**
 * True if territory field is non-null/non-empty, false if not
 */
bool UT_LocaleInfo::hasTerritory () const
{
  return mTerritory.size () != 0;
}

/**
 * True if encoding field is non-null/non-empty, false if not
 */
bool UT_LocaleInfo::hasEncoding () const
{
  return mEncoding.size () != 0;
}

/**
 * Returns empty string or language. Example languages are
 * "en", "wen", "fr", "es"
 */
UT_String UT_LocaleInfo::getLanguage () const
{
  return mLanguage;
}

/**
 * Returns empty string or territory. Example territories are:
 * "US", "GB", "FR", ...
 */
UT_String UT_LocaleInfo::getTerritory () const
{
  return mTerritory;
}

/**
 * Returns empty string or encoding. Encoding is like "UTF-8" or
 * "ISO-8859-1"
 */
UT_String UT_LocaleInfo::getEncoding () const
{
  return mEncoding;
}

void UT_LocaleInfo::init (const UT_String & locale)
{
  if (locale.size () == 0)
    return;

  size_t dot    = 0;
  size_t hyphen = 0;

  // take both hyphen types into account
  hyphen = UT_String_findCh (locale, '_');
  if (hyphen == (size_t)-1)
    hyphen = UT_String_findCh (locale, '-');

  dot = UT_String_findCh (locale, '.');

  if (hyphen == (size_t)-1 && dot == (size_t)-1)
    {
      mLanguage = locale;
      return;
    }

  if (hyphen != (size_t)-1 && dot != (size_t)-1)
    {
      if (hyphen < dot)
	{
	  mLanguage  = locale.substr (0, hyphen);
	  mTerritory = locale.substr (hyphen+1, dot-(hyphen+1));
	  mEncoding  = locale.substr (dot+1, locale.size ()-(dot+1));
	}
      else
	{
	  mLanguage = locale.substr (0, dot);
	  mEncoding = locale.substr (dot+1, locale.size ()-(dot+1));
	}
    }
  else if (dot != (size_t)-1)
    {
      mLanguage = locale.substr (0, dot);
      mEncoding = locale.substr (dot+1, locale.size ()-(dot+1));
    }
  else if (hyphen != (size_t)-1)
    {
      mLanguage = locale.substr (0, hyphen);
      mEncoding = locale.substr (hyphen+1, locale.size ()-(hyphen+1));
    }
}

/**
 * Turns object back into a string of the form language_TERRITORY.ENCODING
 * (eg): en_US.UTF-8
 */
UT_String UT_LocaleInfo::toString () const
{
  UT_String ret (mLanguage);

  if (hasTerritory ())
    {
      ret += '_';
      ret += mTerritory;
    }

  if (hasEncoding ())
    {
      ret += '.';
      ret += mEncoding;
    }

  return ret;
}

bool UT_LocaleInfo::operator==(const UT_LocaleInfo & rhs) const
{
  if ((this->mLanguage  == rhs.mLanguage) && 
      (this->mTerritory == rhs.mTerritory) &&
      (this->mEncoding  == rhs.mEncoding))
    return true;
  return false;
}

bool UT_LocaleInfo::operator!=(const UT_LocaleInfo & rhs) const
{
  return (!(*this == rhs));
}
