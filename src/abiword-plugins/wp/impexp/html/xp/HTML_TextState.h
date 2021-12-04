/* AbiWord: ie_imp_HTML - plugin for non-XHTML HTML
 * Copyright (C) 2002 Francis James Franklin <fjf@alinameridon.com>
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

IE_Imp_HTML::TextState::TextState () :
  m_stack(0),
  m_count(0),
  m_max(0),
  m_style(0)
{
  m_Text.font_family = 0;
  m_Text.font_size = 0;
}

IE_Imp_HTML::TextState::~TextState ()
{
  if (m_stack)
    {
      while (pop ());

      free (m_stack);
      m_stack = 0;
    }
  m_count = 0;
  m_max = 0;

  if (m_Text.font_family) free (m_Text.font_family);
  if (m_Text.font_size) free (m_Text.font_size);
}

void IE_Imp_HTML::TextState::defineStyles (IE_Imp_HTML * imp)
{
  const char * attribute[12];

  attribute[ 0] = "type";
  attribute[ 1] = "P";
  attribute[ 2] = "basedon";
  attribute[ 4] = "followedby";
  attribute[ 6] = "name";
  attribute[ 8] = "props";
  attribute[10] = 0;
  attribute[11] = 0;

  attribute[3] = "";
  attribute[5] = "Current Settings";
  attribute[7] = "Normal";
  attribute[9] = "margin-top:0pt; field-font:NULL; font-size:12pt; font-family:Times New Roman; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Normal";
  attribute[7] = "Heading 1";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Arial; font-size:17pt; font-weight:bold; margin-top:22pt; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Normal";
  attribute[7] = "Heading 2";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Arial; font-size:14pt; font-weight:bold; margin-top:18pt; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Normal";
  attribute[7] = "Heading 3";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Arial; font-size:12pt; font-weight:bold; margin-top:15pt; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Normal";
  attribute[7] = "Heading 4";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Arial; font-size:12pt; font-weight:normal; margin-top:15pt; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Normal";
  attribute[7] = "Heading 5";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Arial; font-size:10pt; font-weight:normal; margin-top:13pt; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Normal";
  attribute[7] = "Heading 6";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Arial; font-size:8pt; font-weight:normal; margin-top:10pt; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Current Settings";
  attribute[7] = "Fixed Normal";
  attribute[9] = "margin-top:0pt; field-font:NULL; font-size:12pt; font-family:Courier; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Fixed Normal";
  attribute[7] = "Fixed Heading 1";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Courier; font-size:17pt; font-weight:bold; margin-top:22pt; font-style:normal; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Fixed Normal";
  attribute[7] = "Fixed Heading 2";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Courier; font-size:14pt; font-weight:bold; margin-top:18pt; font-style:normal; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Fixed Normal";
  attribute[7] = "Fixed Heading 3";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Courier; font-size:12pt; font-weight:bold; margin-top:15pt; font-style:normal; text-decoration:none; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Fixed Normal";
  attribute[7] = "Fixed Heading 4";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Courier; font-size:12pt; font-weight:normal; margin-top:15pt; text-decoration:underline; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Fixed Normal";
  attribute[7] = "Fixed Heading 5";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Courier; font-size:10pt; font-weight:normal; margin-top:13pt; text-decoration:underline; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);

  attribute[3] = "Normal";
  attribute[5] = "Fixed Normal";
  attribute[7] = "Fixed Heading 6";
  attribute[9] = "keep-with-next:1; field-font:NULL; margin-bottom:3pt; font-family:Courier; font-size:8pt; font-weight:normal; margin-top:10pt; text-decoration:underline; text-position:normal; color:000000; bgcolor:transparent";

  imp->addStyle ((const char **) attribute);
}

bool IE_Imp_HTML::TextState::reset (BlockStyle bs /* = bs_Normal */, bool truncate /* = true */)
{
  if (truncate)
    {
      while (pop ());
    }
  if (!grow ()) return false;

  m_Text.bold = false;
  m_Text.italic = false;
  m_Text.underline = false;
  m_Text.linethrough = false;
  m_Text.overline = false;

  if (m_Text.font_family) free (m_Text.font_family);
  if (m_Text.font_size) free (m_Text.font_size);

  m_Text.font_family = 0;
  m_Text.font_size = 0;

  m_Text.script_style = ss_Normal;

  m_Text.fg[0] = 0;
  m_Text.bg[0] = 0;

  switch (bs)
    {
    case bs_Normal:
      m_style = "Normal";
      m_Text.font_family = UT_strdup ("Times New Roman");
      m_Text.font_size = UT_strdup ("12pt");
      break;
    case bs_Heading1:
      m_Text.bold = true;
      m_style = "Heading 1";
      m_Text.font_family = UT_strdup ("Arial");
      m_Text.font_size = UT_strdup ("17pt");
      break;
    case bs_Heading2:
      m_Text.bold = true;
      m_style = "Heading 2";
      m_Text.font_family = UT_strdup ("Arial");
      m_Text.font_size = UT_strdup ("14pt");
      break;
    case bs_Heading3:
      m_Text.bold = true;
      m_style = "Heading 3";
      m_Text.font_family = UT_strdup ("Arial");
      m_Text.font_size = UT_strdup ("12pt");
      break;
    case bs_Heading4:
      m_style = "Heading 4";
      m_Text.font_family = UT_strdup ("Arial");
      m_Text.font_size = UT_strdup ("12pt");
      break;
    case bs_Heading5:
      m_style = "Heading 5";
      m_Text.font_family = UT_strdup ("Arial");
      m_Text.font_size = UT_strdup ("10pt");
      break;
    case bs_Heading6:
      m_style = "Heading 6";
      m_Text.font_family = UT_strdup ("Arial");
      m_Text.font_size = UT_strdup ("8pt");
      break;
    case bs_FixedNormal:
      m_style = "Fixed Normal";
      m_Text.font_family = UT_strdup ("Courier");
      m_Text.font_size = UT_strdup ("12pt");
      break;
    case bs_FixedHeading1:
      m_Text.bold = true;
      m_style = "Fixed Heading 1";
      m_Text.font_family = UT_strdup ("Courier");
      m_Text.font_size = UT_strdup ("17pt");
      break;
    case bs_FixedHeading2:
      m_Text.bold = true;
      m_style = "Fixed Heading 2";
      m_Text.font_family = UT_strdup ("Courier");
      m_Text.font_size = UT_strdup ("14pt");
      break;
    case bs_FixedHeading3:
      m_Text.bold = true;
      m_style = "Fixed Heading 3";
      m_Text.font_family = UT_strdup ("Courier");
      m_Text.font_size = UT_strdup ("12pt");
      break;
    case bs_FixedHeading4:
      m_Text.underline = true;
      m_style = "Fixed Heading 4";
      m_Text.font_family = UT_strdup ("Courier");
      m_Text.font_size = UT_strdup ("12pt");
      break;
    case bs_FixedHeading5:
      m_Text.underline = true;
      m_style = "Fixed Heading 5";
      m_Text.font_family = UT_strdup ("Courier");
      m_Text.font_size = UT_strdup ("10pt");
      break;
    case bs_FixedHeading6:
      m_Text.underline = true;
      m_style = "Fixed Heading 6";
      m_Text.font_family = UT_strdup ("Courier");
      m_Text.font_size = UT_strdup ("8pt");
      break;
    }

  return m_props.reset ();
}

void IE_Imp_HTML::TextState::scaleFontSize (float ratio) // TODO: Write this properly ??
{
  if (m_Text.font_size == 0) return;

  // Going to assume that font-size is <int>"pt"
  m_Text.font_size[strlen (m_Text.font_size) - 2] = 0;

  int size;
  sscanf (m_Text.font_size, "%d", &size);

  size = (int) (0.5 + ((float) size) * ratio);
  if (size < 7) size = 7;
  if (size > 255) size = 255;

  char buf[6];
  sprintf (buf, "%dpt", size);

  free (m_Text.font_size);
  m_Text.font_size = UT_strdup (buf);
}

bool IE_Imp_HTML::TextState::push ()
{
  if (!grow ()) return false;
  m_stack[m_count] = m_Text;
  m_count++;

  m_Text.font_family = (m_Text.font_family ? UT_strdup (m_Text.font_family) : 0);
  m_Text.font_size = (m_Text.font_size ? UT_strdup (m_Text.font_size) : 0);

  return true;
}

bool IE_Imp_HTML::TextState::pop ()
{
  if (m_count == 0) return false;

  if (m_Text.font_family) free (m_Text.font_family);
  if (m_Text.font_size) free (m_Text.font_size);

  m_count--;
  m_Text = m_stack[m_count];
  return true;
}

bool IE_Imp_HTML::TextState::grow ()
{
  if (m_stack == 0)
    {
      m_count = 0;
      m_stack = (Text *) malloc (16 * sizeof (Text));
      if (m_stack == 0) return false;
      m_max = 16;
      return true;
    }

  if (m_count < m_max) return true;

  Text * more = (Text *) realloc (m_stack, (m_max + 16) * sizeof (Text));
  if (more == 0) return false;
  m_stack = more;
  m_max += 16;
  return true;
}

char * IE_Imp_HTML::TextState::getProps ()
{
  m_props.reset ();

  if (m_Text.bold)
    m_props.append ("font-weight", "bold");
  else
    m_props.append ("font-weight", "normal");
  if (m_Text.italic)
    m_props.append ("font-style", "italic");
  else
    m_props.append ("font-style", "normal");

  if (m_Text.underline || m_Text.linethrough || m_Text.overline)
    {
      char decoration[33];
      decoration[0] = 0;
      if (m_Text.underline)   strcat (decoration, "underline ");
      if (m_Text.linethrough) strcat (decoration, "line-through ");
      if (m_Text.overline)    strcat (decoration, "overline ");
      m_props.append ("text-decoration", decoration);
    }
  else
    m_props.append ("text-decoration", "none");

  if (m_Text.font_family)
    m_props.append ("font-family", m_Text.font_family);
  if (m_Text.font_size)
    m_props.append ("font-size", m_Text.font_size);

  switch (m_Text.script_style)
    {
    case ss_Normal:
      m_props.append ("text-position", "normal");
      break;
    case ss_Super:
      m_props.append ("text-position", "superscript");
      break;
    case ss_Sub:
      m_props.append ("text-position", "subscript");
      break;
    }

  if (m_Text.fg[0])
    m_props.append ("color", m_Text.fg);
  if (m_Text.bg[0])
    m_props.append ("bgcolor", m_Text.bg);

  return m_props.getString ();
}
