/* AbiWord
 * Copyright (C) 2001 AbiSource, Inc.
 * Copyright (C) 2001-2002 William Lachance (wlach@interlog.com)
 * Copyright (C) 2002 Marc Maurer (j.m.maurer@student.utwente.nl)
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

/* See bug 1764
 * "This product is not manufactured, approved, or supported by 
 * Corel Corporation or Corel Corporation Limited."
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

#include "ut_types.h"
#include "ut_string.h"
#include "ut_string_class.h"
#include "ut_units.h"
#include "ut_growbuf.h"
#include "ut_assert.h"
#include "ut_debugmsg.h"
#include "ut_math.h" // for rint (font size)
#include "ut_rand.h"

#include "xap_Frame.h"
#include "xap_EncodingManager.h"

#include "pd_Document.h"
#include "pt_Types.h"

#include "fl_AutoLists.h"
#include "fl_AutoNum.h"

#include "ap_Strings.h"

#include "ie_imp_WordPerfect.h"
#include "ie_impexp_WordPerfect.h"

#define X_CheckFileError(v) if (v==EOF) { UT_DEBUGMSG(("X_CheckFileError: %d\n", __LINE__)); return UT_IE_IMPORTERROR; }
#define X_CheckFileReadElementError(v) if (v != 1) { UT_DEBUGMSG(("X_CheckFileReadElementError: %d\n", __LINE__)); return UT_IE_IMPORTERROR; } // makes sure that one element is read
#define X_CheckFileSeekError(v) if (v != 0) { UT_DEBUGMSG(("X_CheckFileSeekError: %d\n", __LINE__)); return UT_IE_IMPORTERROR; } // makes sure a seek was successful
#define X_CheckDocumentError(v) if (!v) { UT_DEBUGMSG(("X_CheckDocumentError: %d\n", __LINE__)); return UT_IE_IMPORTERROR; }
#define X_CheckWordPerfectError(v) if ((v != UT_OK)) { UT_DEBUGMSG(("X_CheckWordPerfectError: %d\n", __LINE__)); return UT_IE_IMPORTERROR; }

// This should probably be defined in pt_Types.h
static const UT_uint32 PT_MAX_ATTRIBUTES = 8;

WordPerfectTextAttributes::WordPerfectTextAttributes()
{
   m_extraLarge = false;
   m_veryLarge = false;
   m_large = false;
   m_smallPrint = false;
   m_finePrint = false;
   m_superScript = false;
   m_subScript = false;
   m_outline = false;
   m_italics = false;
   m_shadow = false;
   m_redLine = false;
   m_bold = false;
   m_strikeOut = false;
   m_underLine = false;
   m_smallCaps = false;
   m_Blink = false;
   m_reverseVideo = false;
   
   m_fontSize = 12; // silly default. TODO: read from file.
}

static int wp_internationalCharacterMapping[32] = 
{ 
  229, // lower case 'a' with a small circle
  197, // upper case 'a' with a small circle
  230, // lower case 'ae'
  198, // upper case 'ae'
  228, // lower case 'a' with diathesis
  196, // upper case 'a' with diathesis
  224, // lower case 'a' with acute
  192, // lower case 'a' with grave
  226, // lower case 'a' with circonflex
  227, // lower case 'a' with tilde
  195, // upper case 'a' with tilde
  231, // lower case 'c' with hook
  199, // upper case 'c' with hook
  235, // lower case 'e' with diathesis
  232, // lower case 'e' with acute
  200, // upper case 'e' with acute
  233, // lower case 'e' with grave
  234, // lower case 'e' with circonflex
  236, // lower case 'i' with acute
  241, // lower case 'n' with tilde
  209, // upper case 'n' with tilde
  248, // lower case 'o' with stroke
  216, // upper case 'o' with stroke
  241, // lower case 'o' with tilde
  213, // upper case 'o' with tilde
  246, // lower case 'o' with diathesis
  214, // upper case 'o' with diathesis
  252, // lower case 'u' with diathesis
  220, // upper case 'u' with diathesis
  250, // lower case 'u' with acute
  249, // lower case 'u' with grave
  223 // double s
};

// WP Extended Character -> Unicode Mappings by 
// Ariya Hidayat <ariyahidayat@yahoo.de> for the
// KWord project, licensed under the GPL (copyright 2001)

// WP multinational characters (charset 1)
static UT_UCS4Char multinationalMap[] = {
  0x0300, 0x00b7, 0x0303, 0x0302, 0x0335, 0x0338, 0x0301, 0x0308,
  0x0304, 0x0313, 0x0315, 0x02bc, 0x0326, 0x0315, 0x030a, 0x0307,
  0x030b, 0x0327, 0x0328, 0x030c, 0x0337, 0x0305, 0x0306, 0x00df,
  0x0138, 0xf801, 0x00c1, 0x00e1, 0x00c2, 0x00e2, 0x00c4, 0x00e4,
  0x00c0, 0x00e0, 0x00c5, 0x00e5, 0x00c6, 0x00e6, 0x00c7, 0x00e7,
  0x00c9, 0x00e9, 0x00ca, 0x00ea, 0x00cb, 0x00eb, 0x00c8, 0x00e8,
  0x00cd, 0x00ed, 0x00ce, 0x00ee, 0x00cf, 0x00ef, 0x00cc, 0x00ec,
  0x00d1, 0x00f1, 0x00d3, 0x00f3, 0x00d4, 0x00f4, 0x00d6, 0x00f6,
  0x00d2, 0x00f2, 0x00da, 0x00fa, 0x00db, 0x00fb, 0x00dc, 0x00fc,
  0x00d9, 0x00f9, 0x0178, 0x00ff, 0x00c3, 0x00e3, 0x0110, 0x0111,
  0x00d8, 0x00f8, 0x00d5, 0x00f5, 0x00dd, 0x00fd, 0x00d0, 0x00f0,
  0x00de, 0x00fe, 0x0102, 0x0103, 0x0100, 0x0101, 0x0104, 0x0105,
  0x0106, 0x0107, 0x010c, 0x010d, 0x0108, 0x0109, 0x010a, 0x010b,
  0x010e, 0x010f, 0x011a, 0x011b, 0x0116, 0x0117, 0x0112, 0x0113,
  0x0118, 0x0119, 0x0047, 0x0067, 0x011e, 0x011f, 0x0047, 0x0067,
  0x0122, 0x0123, 0x011c, 0x011d, 0x0120, 0x0121, 0x0124, 0x0125,
  0x0126, 0x0127, 0x0130, 0x0069, 0x012a, 0x012b, 0x012e, 0x012f,
  0x0128, 0x0129, 0x0132, 0x0133, 0x0134, 0x0135, 0x0136, 0x0137,
  0x0139, 0x013a, 0x013d, 0x013e, 0x013b, 0x013c, 0x013f, 0x0140,
  0x0141, 0x0142, 0x0143, 0x0144, 0xf802, 0x0149, 0x0147, 0x0148,
  0x0145, 0x0146, 0x0150, 0x0151, 0x014c, 0x014d, 0x0152, 0x0153,
  0x0154, 0x0155, 0x0158, 0x0159, 0x0156, 0x0157, 0x015a, 0x015b,
  0x0160, 0x0161, 0x015e, 0x015f, 0x015c, 0x015d, 0x0164, 0x0165,
  0x0162, 0x0163, 0x0166, 0x0167, 0x016c, 0x016d, 0x0170, 0x0171,
  0x016a, 0x016b, 0x0172, 0x0173, 0x016e, 0x016f, 0x0168, 0x0169,
  0x0174, 0x0175, 0x0176, 0x0177, 0x0179, 0x017a, 0x017d, 0x017e,
  0x017b, 0x017c, 0x014a, 0x014b, 0xf000, 0xf001, 0xf002, 0xf003,
  0xf004, 0xf005, 0xf006, 0xf007, 0xf008, 0xf009, 0xf00a, 0xf00b,
  0xf00c, 0xf00d, 0xf00e, 0xf00f, 0x010e, 0x010f, 0x01a0, 0x01a1,
  0x01af, 0x01b0, 0x0114, 0x0115, 0x012c, 0x012d, 0x0049, 0x0131,
  0x014e, 0x014f
};

// WP phonetic symbol (charset 2)
static UT_UCS4Char phoneticMap[] = {
  0x02b9, 0x02ba, 0x02bb, 0xf813, 0x02bd, 0x02bc, 0xf814, 0x02be,
  0x02bf, 0x0310, 0x02d0, 0x02d1, 0x0306, 0x032e, 0x0329, 0x02c8,
  0x02cc, 0x02c9, 0x02ca, 0x02cb, 0x02cd, 0x02ce, 0x02cf, 0x02c6,
  0x02c7, 0x02dc, 0x0325, 0x02da, 0x032d, 0x032c, 0x0323, 0x0308,
  0x0324, 0x031c, 0x031d, 0x031e, 0x031f, 0x0320, 0x0321, 0x0322,
  0x032a, 0x032b, 0x02d2, 0x02d3, 0xf815, 0xf816, 0x005f, 0x2017,
  0x033e, 0x02db, 0x0327, 0x0233, 0x030d, 0x02b0, 0x02b6, 0x0250,
  0x0251, 0x0252, 0x0253, 0x0299, 0x0254, 0x0255, 0x0297, 0x0256,
  0x0257, 0x0258, 0x0259, 0x025a, 0x025b, 0x025c, 0x025d, 0x029a,
  0x025e, 0x025f, 0x0278, 0x0261, 0x0260, 0x0262, 0x029b, 0x0263,
  0x0264, 0x0265, 0x0266, 0x0267, 0x029c, 0x0268, 0x026a, 0x0269,
  0x029d, 0x029e, 0x026b, 0x026c, 0x026d, 0x029f, 0x026e, 0x028e,
  0x026f, 0x0270, 0x0271, 0x0272, 0x0273, 0x0274, 0x0276, 0x0277,
  0x02a0, 0x0279, 0x027a, 0x027b, 0x027c, 0x027d, 0x027e, 0x027f,
  0x0280, 0x0281, 0x0282, 0x0283, 0x0284, 0x0285, 0x0286, 0x0287,
  0x0288, 0x0275, 0x0289, 0x028a, 0x028c, 0x028b, 0x028d, 0x03c7,
  0x028f, 0x0290, 0x0291, 0x0292, 0x0293, 0x0294, 0x0295, 0x0296,
  0x02a1, 0x02a2, 0x0298, 0x02a3, 0x02a4, 0x02a5, 0x02a6, 0x02a7,
  0x02a8
};

// WP typographic symbol (charset 4)
static UT_UCS4Char typographicMap[] = {
  0x25cf, 0x25cb, 0x25a0, 0x2022, 0xf817, 0x00b6, 0x00a7, 0x00a1,
  0x00bf, 0x00ab, 0x00bb, 0x00a3, 0x00a5, 0x20a7, 0x0192, 0x00aa,
  0x00ba, 0x00bd, 0x00bc, 0x00a2, 0x00b2, 0x207f, 0x00ae, 0x00a9,
  0x00a4, 0x00be, 0x00b3, 0x201b, 0x2019, 0x2018, 0x201f, 0x201d,
  0x201c, 0x2013, 0x2014, 0x2039, 0x203a, 0x25cb, 0x25a1, 0x2020,
  0x2021, 0x2122, 0x2120, 0x211e, 0x25cf, 0x25e6, 0x25a0, 0x25aa,
  0x25a1, 0x25ab, 0x2012, 0xfb00, 0xfb03, 0xfb04, 0xfb01, 0xfb02,
  0x2026, 0x0024, 0x20a3, 0x20a2, 0x20a0, 0x20a4, 0x201a, 0x201e,
  0x2153, 0x2154, 0x215b, 0x215c, 0x215d, 0x215e, 0x24c2, 0x24c5,
  0x20ac, 0x2105, 0x2106, 0x2030, 0x2116, 0xf818, 0x00b9, 0x2409,
  0x240c, 0x240d, 0x240a, 0x2424, 0x240b, 0xf819, 0x20a9, 0x20a6,
  0x20a8, 0xf81a, 0xf81b, 0xf81c, 0xf81d, 0xf81e, 0xf81f, 0xf820,
  0xf821, 0xf822, 0xf823, 0xf824, 0xf825, 0xf826
};

// WP iconic symbol (charset 5)
static UT_UCS4Char iconicMap[] = {
  0x2661, 0x2662, 0x2667, 0x2664, 0x2642, 0x2640, 0x263c, 0x263a,
  0x263b, 0x266a, 0x266c, 0x25ac, 0x2302, 0x203c, 0x221a, 0x21a8,
  0x2310, 0x2319, 0x25d8, 0x25d9, 0x21b5, 0x2104, 0x261c, 0x2007,
  0x2610, 0x2612, 0x2639, 0x266f, 0x266d, 0x266e, 0x260e, 0x231a,
  0x231b, 0x2701, 0x2702, 0x2703, 0x2704, 0x260e, 0x2706, 0x2707,
  0x2708, 0x2709, 0x261b, 0x261e, 0x270c, 0x270d, 0x270e, 0x270f,
  0x2710, 0x2711, 0x2712, 0x2713, 0x2714, 0x2715, 0x2716, 0x2717,
  0x2718, 0x2719, 0x271a, 0x271b, 0x271c, 0x271d, 0x271e, 0x271f,
  0x2720, 0x2721, 0x2722, 0x2723, 0x2724, 0x2725, 0x2726, 0x2727,
  0x2605, 0x2606, 0x272a, 0x272b, 0x272c, 0x272d, 0x272e, 0x272f,
  0x2730, 0x2731, 0x2732, 0x2733, 0x2734, 0x2735, 0x2736, 0x2737,
  0x2738, 0x2739, 0x273a, 0x273b, 0x273c, 0x273d, 0x273e, 0x273f,
  0x2740, 0x2741, 0x2742, 0x2743, 0x2744, 0x2745, 0x2746, 0x2747,
  0x2748, 0x2749, 0x274a, 0x274b, 0x25cf, 0x274d, 0x25a0, 0x274f,
  0x2750, 0x2751, 0x2752, 0x25b2, 0x25bc, 0x25c6, 0x2756, 0x25d7,
  0x2758, 0x2759, 0x275a, 0x275b, 0x275c, 0x275d, 0x275e, 0x2036,
  0x2033, 0xf827, 0xf828, 0xf829, 0xf82a, 0x2329, 0x232a, 0x005b,
  0x005d, 0xf82b, 0xf82c, 0xf82d, 0xf82e, 0xf82f, 0xf830, 0xf831,
  0x2190, 0xf832, 0xf833, 0xf834, 0xf835, 0xf836, 0x21e8, 0x21e6,
  0x2794, 0xf838, 0xf839, 0xf83a, 0xf83b, 0xf83c, 0x25d6, 0xf83d,
  0xf83e, 0x2761, 0x2762, 0x2763, 0x2764, 0x2765, 0x2766, 0x2767,
  0x2663, 0x2666, 0x2665, 0x2660, 0x2780, 0x2781, 0x2782, 0x2783,
  0x2784, 0x2785, 0x2786, 0x2787, 0x2788, 0x2789, 0x2776, 0x2777,
  0x2778, 0x2779, 0x277a, 0x277b, 0x277c, 0x277d, 0x277e, 0x277f,
  0x2780, 0x2781, 0x2782, 0x2783, 0x2784, 0x2785, 0x2786, 0x2787,
  0x2788, 0x2789, 0x278a, 0x278b, 0x278c, 0x278d, 0x278e, 0x278f,
  0x2790, 0x2791, 0x2792, 0x2793, 0x2794, 0x2192, 0x2194, 0x2195,
  0x2798, 0x2799, 0x279a, 0x279b, 0x279c, 0x279d, 0x279e, 0x279f,
  0x27a0, 0x27a1, 0x27a2, 0x27a3, 0x27a4, 0x27a5, 0x27a6, 0x27a7,
  0x27a8, 0x27a9, 0x27aa, 0x27ab, 0x27ac, 0x27ad, 0x27ae, 0x27af,
  0xf83f, 0x27b1, 0x27b2, 0x27b3, 0x27b4, 0x27b5, 0x27b6, 0x27b7,
  0x27b8, 0x27b9, 0x27ba, 0x27bb, 0x27bc, 0x27bd, 0x27be
};

// WP math/scientific (charset 6)
static UT_UCS4Char mathMap[] = {
  0x2212, 0x00b1, 0x2264, 0x2265, 0x221d, 0x01c0, 0x2215, 0x2216,
  0x00f7, 0x2223, 0x2329, 0x232a, 0x223c, 0x2248, 0x2261, 0x2208,
  0x2229, 0x2225, 0x2211, 0x221e, 0x00ac, 0x2192, 0x2190, 0x2191,
  0x2193, 0x2194, 0x2195, 0x25b8, 0x25c2, 0x25b4, 0x25be, 0x22c5,
  0xf850, 0x2218, 0x2219, 0x212b, 0x00b0, 0x00b5, 0x203e, 0x00d7,
  0x222b, 0x220f, 0x2213, 0x2207, 0x2202, 0x02b9, 0x02ba, 0x2192,
  0x212f, 0x2113, 0x210f, 0x2111, 0x211c, 0x2118, 0x21c4, 0x21c6,
  0x21d2, 0x21d0, 0x21d1, 0x21d3, 0x21d4, 0x21d5, 0x2197, 0x2198,
  0x2196, 0x2199, 0x222a, 0x2282, 0x2283, 0x2286, 0x2287, 0x220d,
  0x2205, 0x2308, 0x2309, 0x230a, 0x230b, 0x226a, 0x226b, 0x2220,
  0x2297, 0x2295, 0x2296, 0xf851, 0x2299, 0x2227, 0x2228, 0x22bb,
  0x22a4, 0x22a5, 0x2312, 0x22a2, 0x22a3, 0x25a1, 0x25a0, 0x25ca,
  0xf852, 0xf853, 0xf854, 0x2260, 0x2262, 0x2235, 0x2234, 0x2237,
  0x222e, 0x2112, 0x212d, 0x2128, 0x2118, 0x20dd, 0xf855, 0x25c7,
  0x22c6, 0x2034, 0x2210, 0x2243, 0x2245, 0x227a, 0x227c, 0x227b,
  0x227d, 0x2203, 0x2200, 0x22d8, 0x22d9, 0x228e, 0x228a, 0x228b,
  0x2293, 0x2294, 0x228f, 0x2291, 0x22e4, 0x2290, 0x2292, 0x22e5,
  0x25b3, 0x25bd, 0x25c3, 0x25b9, 0x22c8, 0x2323, 0x2322, 0xf856,
  0x219d, 0x21a9, 0x21aa, 0x21a3, 0x21bc, 0x21bd, 0x21c0, 0x21c1,
  0x21cc, 0x21cb, 0x21bf, 0x21be, 0x21c3, 0x21c2, 0x21c9, 0x21c7,
  0x22d3, 0x22d2, 0x22d0, 0x22d1, 0x229a, 0x229b, 0x229d, 0x2127,
  0x2221, 0x2222, 0x25c3, 0x25b9, 0x25b5, 0x25bf, 0x2214, 0x2250,
  0x2252, 0x2253, 0x224e, 0x224d, 0x22a8, 0xf857, 0x226c, 0x0285,
  0x2605, 0x226e, 0x2270, 0x226f, 0x2271, 0x2241, 0x2244, 0x2247,
  0x2249, 0x2280, 0x22e0, 0x2281, 0x22e1, 0x2284, 0x2285, 0x2288,
  0x2289, 0xf858, 0xf859, 0x22e2, 0x22e3, 0x2226, 0x2224, 0x226d,
  0x2204, 0x2209, 0xf85a, 0x2130, 0x2131, 0x2102, 0xf85b, 0x2115,
  0x211d, 0x225f, 0x221f, 0x220b, 0x22ef, 0xf85c, 0x22ee, 0x22f1,
  0xf85d, 0x20e1, 0x002b, 0x002d, 0x003d, 0x002a, 0xf85e, 0xf85f,
  0xf860, 0x210c, 0x2118, 0x2272, 0x2273, 0xf861
};

// WP math/scientific extended (charset 7)
static UT_UCS4Char mathextMap[] = {
  0x2320, 0x2321, 0xf702, 0xf703, 0x221a, 0xf705, 0xf706, 0xf707,
  0xf708, 0xf709, 0xf70a, 0xf70b, 0xf70c, 0xf70d, 0xf70e, 0xf70f,
  0xf710, 0xf711, 0xf712, 0xf713, 0xf714, 0xf715, 0xf716, 0xf717,
  0xf718, 0xf719, 0xf71a, 0xf71b, 0xf71c, 0xf71d, 0xf71e, 0xf71f,
  0xf720, 0xf721, 0xf722, 0xf723, 0xf724, 0xf725, 0xf726, 0xf727,
  0xf728, 0xf729, 0xf72a, 0xf72b, 0xf72c, 0xf72d, 0xf72e, 0xf72f,
  0xf730, 0xf731, 0xf732, 0xf733, 0xf734, 0xf735, 0xf736, 0xf737,
  0xf738, 0xf739, 0xf73a, 0xf73b, 0xf73c, 0xf73d, 0xf73e, 0xf73f,
  0xf740, 0xf741, 0xf742, 0xf743, 0xf744, 0xf745, 0xf746, 0xf747,
  0xf748, 0xf749, 0xf74a, 0xf74b, 0xf74c, 0xf74d, 0xf74e, 0xf74f,
  0xf750, 0xf751, 0xf752, 0xf753, 0xf754, 0xf755, 0xf756, 0xf757,
  0xf758, 0xf759, 0xf75a, 0xf75b, 0xf75c, 0xf75d, 0xf75e, 0xf75f,
  0xf760, 0xf761, 0xf762, 0xf763, 0xf764, 0xf765, 0xf766, 0xf767,
  0xf768, 0xf769, 0xf76a, 0xf76b, 0xf76c, 0xf76d, 0xf76e, 0xf76f,
  0xf770, 0xf771, 0xf772, 0xf773, 0xf774, 0xf775, 0xf776, 0xf777,
  0xf778, 0xf779, 0x20aa, 0xf77b, 0xf77c, 0xf77d, 0xf77e, 0xf77f,
  0xf780, 0xf781, 0xf782, 0xf783, 0xf784, 0xf785, 0xf786, 0xf787,
  0xf788, 0xf789, 0xf78a, 0xf78b, 0xf78c, 0xf78d, 0xf78e, 0xf78f,
  0xf790, 0xf791, 0xf792, 0xf793, 0xf794, 0xf795, 0xf796, 0xf797,
  0xf798, 0xf799, 0xf79a, 0xf79b, 0xf79c, 0xf79d, 0xf79e, 0xf79f,
  0xf7a0, 0xf7a1, 0xf7a2, 0xf7a3, 0xf7a4, 0xf7a5, 0xf7a6, 0xf7a7,
  0xf7a8, 0xf7a9, 0xf7aa, 0xf7ab, 0xf7ac, 0xf7ad, 0xf7ae, 0xf7af,
  0xf7b0, 0xf7b1, 0xf7b2, 0xf7b3, 0xf7b4, 0xf7b5, 0xf7b6, 0xf7b7,
  0xf7b8, 0xf7b9, 0xf7ba, 0xf7bb, 0xf7bc, 0xf7bd, 0xf7be, 0xf7bf,
  0xf7c0, 0xf7c1, 0xf7c2, 0xf7c3, 0xf7c4, 0xf7c5, 0xf7c6, 0xf7c7
};

// WP greek (charset 8)
static UT_UCS4Char greekMap[] = {
  0x0391, 0x03b1, 0x0392, 0x03b2, 0x0392, 0x03d0, 0x0393, 0x03b3,
  0x0394, 0x03b4, 0x0395, 0x03b5, 0x0396, 0x03b6, 0x0397, 0x03b7,
  0x0398, 0x03b8, 0x0399, 0x03b9, 0x039a, 0x03ba, 0x039b, 0x03bb,
  0x039c, 0x03bc, 0x039d, 0x03bd, 0x039e, 0x03be, 0x039f, 0x03bf,
  0x03a0, 0x03c0, 0x03a1, 0x03c1, 0x03a3, 0x03c3, 0x03a3, 0x03c2,
  0x03a4, 0x03c4, 0x03a5, 0x03c5, 0x03a6, 0x03c6, 0x03a7, 0x03c7,
  0x03a8, 0x03c8, 0x03a9, 0x03c9, 0x0386, 0x03ac, 0x0388, 0x03ad,
  0x0389, 0x03ae, 0x038a, 0x03af, 0x03aa, 0x03ca, 0x038c, 0x03cc,
  0x038e, 0x03cd, 0x03ab, 0x03cb, 0x038f, 0x03ce, 0x03b5, 0x03d1,
  0x03f0, 0x03d6, 0x03f1, 0x03db, 0x03d2, 0x03d5, 0x03d6, 0x03d7,
  0x00b7, 0x0374, 0x0375, 0x0301, 0x0308, 0xf216, 0xf217, 0x0300,
  0x0311, 0x0313, 0x0314, 0x0345, 0x1fce, 0x1fde, 0x1fcd, 0x1fdd,
  0xf200, 0xf201, 0xf022, 0xf021, 0xf202, 0xf203, 0xf204, 0xf300,
  0xf301, 0xf302, 0xf303, 0xf304, 0xf305, 0x1f70, 0xf100, 0x1fb3,
  0x1fb4, 0x1fb2, 0xf205, 0x1f00, 0x1f04, 0x1f02, 0xf206, 0x1f80,
  0x1f84, 0x1f82, 0xf306, 0x1f01, 0x1f05, 0x1f03, 0xf207, 0x1f81,
  0x1f85, 0x1f83, 0xf307, 0x1f72, 0x1f10, 0x1f14, 0x1f12, 0x1f11,
  0x1f15, 0x1f13, 0x1f74, 0xf101, 0x1fc3, 0x1fc4, 0x1fc2, 0xf208,
  0x1f20, 0x1f24, 0x1f22, 0xf209, 0x1f90, 0x1f94, 0x1f92, 0xf308,
  0x1f21, 0x1f25, 0x1f23, 0xf20a, 0x1f91, 0x1f95, 0x1f93, 0xf309,
  0x1f76, 0xf102, 0xf20b, 0xf20c, 0x1f30, 0x1f34, 0x1f32, 0xf20d,
  0x1f31, 0x1f35, 0x1f33, 0xf20e, 0x1f78, 0x1f40, 0x1f44, 0x1f42,
  0x1f41, 0x1f45, 0x1f43, 0x1fe5, 0x1fe4, 0x1f7a, 0xf103, 0xf20f,
  0xf210, 0x1f50, 0x1f54, 0x1f52, 0xf211, 0x1f51, 0x1f55, 0x1f53,
  0xf212, 0x1f7c, 0xf104, 0x1ff3, 0x1ff4, 0x1ff2, 0xf213, 0x1f60,
  0x1f64, 0x1f62, 0xf214, 0x1fa0, 0x1fa4, 0x1fa2, 0xf30a, 0x1f61,
  0x1f65, 0x1f63, 0xf215, 0x1fa1, 0x1fa5, 0x1fa3, 0xf30b, 0x03da,
  0x03dc, 0x03de, 0x03e0
};

// WP hebrew (charset 9)
static UT_UCS4Char hebrewMap[] = {
  0x05d0, 0x05d1, 0x05d2, 0x05d3, 0x05d4, 0x05d5, 0x05d6, 0x05d7,
  0x05d8, 0x05d9, 0x05da, 0x05db, 0x05dc, 0x05dd, 0x05de, 0x05df,
  0x05e0, 0x05e1, 0x05e2, 0x05e3, 0x05e4, 0x05e5, 0x05e6, 0x05e7,
  0x05e8, 0x05e9, 0x05ea, 0xf862, 0x05c0, 0x05c3, 0x05f3, 0x05f4,
  0x05b0, 0x05b1, 0x05b2, 0x05b3, 0x05b4, 0x05b5, 0x05b6, 0x05b7,
  0x05b8, 0x05b9, 0x05b9, 0x05bb, 0x05bc, 0x05bd, 0x05bf, 0x05b7,
  0xfb1e, 0x05f0, 0x05f1, 0x05f2, 0xf114, 0xf8b0, 0xf863, 0xf864,
  0xf865, 0xf866, 0xf867, 0xf868, 0xf869, 0xf86a, 0xf86b, 0xf86c,
  0xf86d, 0xf86e, 0xf86f, 0xf870, 0xf871, 0xf872, 0xf873, 0xf874,
  0x05f3, 0x05f3, 0x05f4, 0xf876, 0xf877, 0xf878, 0xf879, 0xf87a,
  0xf87b, 0xf87c, 0xf87d, 0xf87e, 0xf115, 0xf116, 0xf87f, 0xf117,
  0xf118, 0xf119, 0xf11a, 0xf11b, 0xf11c, 0xf11d, 0xf11e, 0xf11f,
  0xf120, 0xf121, 0xf122, 0xf123, 0xf124, 0xf125, 0xf126, 0xf127,
  0xf218, 0xf128, 0xf129, 0xf12a, 0xf12b, 0xf12c, 0xf12d, 0xf880,
  0xf12e, 0xf12f, 0xf130, 0xf219, 0x05e9, 0xf131, 0xf132, 0xf140,
  0xf141, 0xf142, 0x20aa
};

// WP cyrillic (charset 10)
static UT_UCS4Char cyrillicMap[] = {
  0x0410, 0x0430, 0x0411, 0x0431, 0x0412, 0x0432, 0x0413, 0x0433,
  0x0414, 0x0434, 0x0415, 0x0435, 0x0401, 0x0451, 0x0416, 0x0436,
  0x0417, 0x0437, 0x0418, 0x0438, 0x0419, 0x0439, 0x041a, 0x043a,
  0x041b, 0x043b, 0x041c, 0x043c, 0x041d, 0x043d, 0x041e, 0x043e,
  0x041f, 0x043f, 0x0420, 0x0440, 0x0421, 0x0441, 0x0422, 0x0442,
  0x0423, 0x0443, 0x0424, 0x0444, 0x0425, 0x0445, 0x0426, 0x0446,
  0x0427, 0x0447, 0x0428, 0x0448, 0x0429, 0x0449, 0x042a, 0x044a,
  0x042b, 0x044b, 0x042c, 0x044c, 0x042d, 0x044d, 0x042e, 0x044e,
  0x042f, 0x044f, 0x04d8, 0x04d9, 0x0403, 0x0453, 0x0490, 0x0491,
  0x0492, 0x0493, 0x0402, 0x0452, 0x0404, 0x0454, 0x0404, 0x0454,
  0x0496, 0x0497, 0x0405, 0x0455, 0xf159, 0xf889, 0xf15e, 0xf15f,
  0x0406, 0x0456, 0x0407, 0x0457, 0xf88c, 0xf88d, 0x0408, 0x0458,
  0x040c, 0x045c, 0x049a, 0x049b, 0xf160, 0xf161, 0x049c, 0x049d,
  0x0409, 0x0459, 0x04a2, 0x04a3, 0x040a, 0x045a, 0x047a, 0x047b,
  0x0460, 0x0461, 0x040b, 0x045b, 0x040e, 0x045e, 0x04ee, 0x04ef,
  0x04ae, 0x04af, 0x04b0, 0x04b1, 0x0194, 0x0263, 0x04b2, 0x04b3,
  0xf162, 0xf163, 0x04ba, 0x04bb, 0x047e, 0x047f, 0x040f, 0x045f,
  0x04b6, 0x04b7, 0x04b8, 0x04b9, 0xf164, 0xf165, 0x0462, 0x0463,
  0x0466, 0x0467, 0x046a, 0x046b, 0x046e, 0x046f, 0x0470, 0x0471,
  0x0472, 0x0473, 0x0474, 0x0475, 0xf400, 0xf401, 0xf402, 0xf403,
  0xf404, 0xf405, 0xf406, 0xf407, 0xf408, 0xf409, 0xf40a, 0xf40b,
  0xf40c, 0xf40d, 0xf40e, 0xf40f, 0xf410, 0xf411, 0xf412, 0xf413,
  0xf414, 0xf415, 0xf416, 0xf417, 0xf418, 0xf419, 0xf41a, 0xf41b,
  0xf41c, 0xf41d, 0xf41e, 0xf41f, 0xf420, 0xf421, 0xf422, 0xf423,
  0xf424, 0xf425, 0xf426, 0xf427, 0xf428, 0xf429, 0xf42a, 0xf42b,
  0x0301, 0x0300, 0x0308, 0x0306, 0x0326, 0x0328, 0x0304, 0xf893,
  0x201e, 0x201c, 0x10d0, 0x10d1, 0x10d2, 0x10d3, 0x10d4, 0x10d5,
  0x10d6, 0x10f1, 0x10d7, 0x10d8, 0x10d9, 0x10da, 0x10db, 0x10dc,
  0x10f2, 0x10dd, 0x10de, 0x10df, 0x10e0, 0x10e1, 0x10e2, 0x10e3,
  0x10f3, 0x10e4, 0x10e5, 0x10e6, 0x10e7, 0x10e8, 0x10e9, 0x10ea,
  0x10eb, 0x10ec, 0x10ed, 0x10ee, 0x10f4, 0x10ef, 0x10f0, 0x10f5,
  0x10f6, 0xf42c
};

// WP japanese (charset 11)
static UT_UCS4Char japaneseMap[] = {
  0xff61, 0xff62, 0xff63, 0xff64, 0xff65, 0xff66, 0xff67, 0xff68,
  0xff69, 0xff6a, 0xff6b, 0xff6c, 0xff6d, 0xff6e, 0xff6f, 0xff70,
  0xff71, 0xff72, 0xff73, 0xff74, 0xff75, 0xff76, 0xff77, 0xff78,
  0xff79, 0xff7a, 0xff7b, 0xff7c, 0xff7d, 0xff7e, 0xff7f, 0xff80,
  0xff81, 0xff82, 0xff83, 0xff84, 0xff85, 0xff86, 0xff87, 0xff88,
  0xff89, 0xff8a, 0xff8b, 0xff8c, 0xff8d, 0xff8e, 0xff8f, 0xff90,
  0xff91, 0xff92, 0xff93, 0xff94, 0xff95, 0xff96, 0xff97, 0xff98,
  0xff99, 0xff9a, 0xff9b, 0xff9c, 0xff9d, 0xff9e, 0xff9f
};

WordPerfectParagraphProperties::WordPerfectParagraphProperties()
{
   m_lineSpacing = 1;
   m_justificationMode = WordPerfectParagraphProperties::full;
}

WordPerfectByteTag::WordPerfectByteTag(UT_uint8 byte, UT_Error (IE_Imp_WordPerfect::*func)())
{
   m_byte = byte;
   m_func = func;
}

WordPerfectHeaderPacket::WordPerfectHeaderPacket(unsigned int PID, UT_uint8 type, long packetPosition, bool hasChildren)
{
   m_PID = PID;
   m_type = type;
   m_packetPosition = packetPosition;
   m_hasChildren = hasChildren;
}

WordPerfectFontDescriptor::WordPerfectFontDescriptor()
{
   m_fontName = 0;
}

WordPerfectFontDescriptor::~WordPerfectFontDescriptor()
{
   delete [] m_fontName;
}

WordPerfectListDefinition::WordPerfectListDefinition(UT_uint16 outlineHash, UT_uint8 *numberingMethods)
{
   m_outlineHash = outlineHash;
   for (unsigned int i=0; i<WP_NUM_LIST_LEVELS; i++)
     {
	m_listIDs[i] = 0;
	m_currentListNumbers[i]=0;
	UT_String_sprintf(m_listDelim[i], "%%L");
	if (numberingMethods) 
	  {	     
	     switch (numberingMethods[i])
	       {
		case WP_INDEX_HEADER_OUTLINE_STYLE_ARABIC_NUMBERING:
		  m_listTypes[i] = NUMBERED_LIST; 
		  m_bIsNumberedList[i] = true;
		  break;
		case WP_INDEX_HEADER_OUTLINE_STYLE_LOWERCASE_NUMBERING:
		  m_listTypes[i] = LOWERCASE_LIST; 
		  m_bIsNumberedList[i] = true;
		  break;
		case WP_INDEX_HEADER_OUTLINE_STYLE_UPPERCASE_NUMBERING:
		  m_listTypes[i] = UPPERCASE_LIST; 
		  m_bIsNumberedList[i] = true;
		  break;
		case WP_INDEX_HEADER_OUTLINE_STYLE_LOWERCASE_ROMAN_NUMBERING:
		  m_listTypes[i] = LOWERROMAN_LIST;
		  m_bIsNumberedList[i] = true;
		  break;
		case WP_INDEX_HEADER_OUTLINE_STYLE_UPPERCASE_ROMAN_NUMBERING:
		  m_listTypes[i] = UPPERROMAN_LIST;
		  m_bIsNumberedList[i] = true;
		  break;
		default: // something we're not handling yet (we may yet be able to get a more accurate spec from an outline paragraph group, later)
		  m_listTypes[i] = BULLETED_LIST;
		  m_bIsNumberedList[i] = false;
	       }   
	  }
	else 
	  {
	     m_listTypes[i] = BULLETED_LIST; //listTypes[i];
	     m_bIsNumberedList[i] = false;
	  }	
     }   
   
}

void WordPerfectListDefinition::updateListTypes(UT_uint16 *numberingMethods)
{
   for (unsigned int i=0; i<WP_NUM_LIST_LEVELS; i++)
     {	   
	switch (numberingMethods[i])
	  {
	   case WP_PARAGRAPH_GROUP_OUTLINE_DEFINE_BULLETED_NUMBERING:
	     m_listTypes[i] = BULLETED_LIST; 
	     m_bIsNumberedList[i] = false;
	     break;
	   case WP_PARAGRAPH_GROUP_OUTLINE_DEFINE_ARABIC_NUMBERING:
	     m_listTypes[i] = NUMBERED_LIST; 
	     m_bIsNumberedList[i] = true;
	     break;
	   case WP_PARAGRAPH_GROUP_OUTLINE_DEFINE_LOWERCASE_NUMBERING:
	     m_listTypes[i] = LOWERCASE_LIST; 
	     m_bIsNumberedList[i] = true;
	     break;
	   case WP_PARAGRAPH_GROUP_OUTLINE_DEFINE_LOWERCASE_ROMAN_NUMBERING:
	     m_listTypes[i] = LOWERROMAN_LIST; 
	     m_bIsNumberedList[i] = true;
	     break;
	   default: // something we're not handling yet (fall back on default)
	     break;
	  }   
     }
}


/****************************************************************************/
/****************************************************************************/

IE_Imp_WordPerfect_Sniffer::IE_Imp_WordPerfect_Sniffer (const char * name) :
  IE_ImpSniffer(name)
{
  // 
}

UT_Confidence_t IE_Imp_WordPerfect_Sniffer::recognizeContents (const char * szBuf, 
						     UT_uint32 iNumbytes)
{
   
   char * magic    = 0;
   int magicoffset = 0;

   magic = "WPC";
   magicoffset = 1;
   
   if (iNumbytes > (magicoffset + strlen (magic)))
     {
	if (!strncmp (szBuf + magicoffset, magic, strlen (magic)))
	  {
	     int productType = (int) *(szBuf + WP_HEADER_PRODUCT_TYPE_OFFSET);
	     int fileType = (int) *(szBuf + WP_HEADER_FILE_TYPE_OFFSET);
	     int majorVersion = (int) *(szBuf + WP_HEADER_MAJOR_VERSION_OFFSET);
	     int minorVersion = (int) *(szBuf + WP_HEADER_MINOR_VERSION_OFFSET);
	     UT_DEBUGMSG(("product type: %i, file type: %i, major version: %i, minor version: %i\n", productType, fileType, majorVersion, minorVersion ));
	     // we only want to try parsing wordperfect 6/7/8/9 documents for now
	     if ((majorVersion != WP_WORDPERFECT6789_EXPECTED_MAJOR_VERSION) || (fileType != WP_WORDPERFECT_DOCUMENT_FILE_TYPE))
	       return UT_CONFIDENCE_POOR;
	     
	     return UT_CONFIDENCE_PERFECT;
	  }
     }

   // ok, that didn't work, we'll try to dig through the OLE stream
   // (TODO)
   return UT_CONFIDENCE_ZILCH;
}

UT_Confidence_t IE_Imp_WordPerfect_Sniffer::recognizeSuffix (const char * szSuffix)
{
  // We recognize both word documents and their template versions
  if (!UT_stricmp(szSuffix,".wpd") || !UT_stricmp(szSuffix, ".wp"))
    return UT_CONFIDENCE_PERFECT;
  return UT_CONFIDENCE_ZILCH;
}

UT_Error IE_Imp_WordPerfect_Sniffer::constructImporter (PD_Document * pDocument,
													  IE_Imp ** ppie)
{
	IE_Imp_WordPerfect * p = new IE_Imp_WordPerfect(pDocument);
	*ppie = p;
	return UT_OK;
}

bool	IE_Imp_WordPerfect_Sniffer::getDlgLabels (const char ** pszDesc,
												const char ** pszSuffixList,
												IEFileType * ft)
{
	*pszDesc = "WordPerfect 6/7/8/9 (.wpd)";
	*pszSuffixList = "*.wpd";
	*ft = getFileType();
	return true;
}

/****************************************************************************/
/****************************************************************************/

// just buffer sizes, arbitrarily chosen
#define DOC_TEXTRUN_SIZE 2048
#define DOC_PROPBUFFER_SIZE 1024

IE_Imp_WordPerfect::IE_Imp_WordPerfect(PD_Document * pDocument)
  : IE_Imp (pDocument)
{
   m_undoOn = false;
   m_bParagraphChanged = false;
   m_bParagraphExists = false;
   m_bInSection = false;
   m_bSectionChanged = true;
   m_bFirstMargin = true;
   m_bParagraphInSection = false;
   m_bLeftMarginSet = false;
   m_bRightMarginSet = false;
   m_numberOfColumns = 1;
   m_bColumnsSet = false;
   m_bTextPropertiesChanged = false;
   m_paragraphStyleState = notInStyle;
   m_numDeferredParagraphBreaks = 0;
   
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_SOFT_EOL, &IE_Imp_WordPerfect::_insertSpace));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_SOFT_SPACE, &IE_Imp_WordPerfect::_insertSpace));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_HARD_HYPHEN, &IE_Imp_WordPerfect::_insertHyphen));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_EXTENDED_CHARACTER, &IE_Imp_WordPerfect::_handleExtendedCharacter));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_DORMANT_HARD_RETURN, &IE_Imp_WordPerfect::_handleHardEndOfLine));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_HARD_EOL, &IE_Imp_WordPerfect::_handleHardEndOfLine));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_EOL_GROUP, &IE_Imp_WordPerfect::_handleEndOfLineGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_PAGE_GROUP, &IE_Imp_WordPerfect::_handlePageGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_COLUMN_GROUP, &IE_Imp_WordPerfect::_handleColumnGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_PARAGRAPH_GROUP, &IE_Imp_WordPerfect::_handleParagraphGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_SET_NUMBER_GROUP, &IE_Imp_WordPerfect::_handleSetNumberGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_NUMBERING_METHOD_GROUP, &IE_Imp_WordPerfect::_handleNumberingMethodGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_DISPLAY_NUMBER_REFERENCE_GROUP, &IE_Imp_WordPerfect::_handleDisplayNumberReferenceGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_INCREMENT_NUMBER_GROUP, &IE_Imp_WordPerfect::_handleIncrementNumberGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_DECREMENT_NUMBER_GROUP, &IE_Imp_WordPerfect::_handleDecrementNumberGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_STYLE_GROUP, &IE_Imp_WordPerfect::_handleStyleGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_BOX_GROUP, &IE_Imp_WordPerfect::_handleBoxGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_PLATFORM_GROUP, &IE_Imp_WordPerfect::_handlePlatformGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_FORMATTER_GROUP, &IE_Imp_WordPerfect::_handleFormatterGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_TAB_GROUP, &IE_Imp_WordPerfect::_handleTabGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_CHARACTER_GROUP, &IE_Imp_WordPerfect::_handleCharacterGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_CROSSREFERENCE_GROUP, &IE_Imp_WordPerfect::_handleCrossReferenceGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_HEADER_FOOTER_GROUP, &IE_Imp_WordPerfect::_handleHeaderFooterGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_FOOTENDNOTE_GROUP, &IE_Imp_WordPerfect::_handleFootEndNoteGroup));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_UNDO_GROUP, &IE_Imp_WordPerfect::_handleUndo));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_ATTRIBUTE_ON, &IE_Imp_WordPerfect::_handleAttributeOn));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_ATTRIBUTE_OFF, &IE_Imp_WordPerfect::_handleAttributeOff));
   m_wordPerfectDispatchBytes.addItem(new WordPerfectByteTag(WP_TOP_UNDO_GROUP, &IE_Imp_WordPerfect::_handleUndo));
}

IE_Imp_WordPerfect::~IE_Imp_WordPerfect() 
{
   UT_VECTOR_PURGEALL(WordPerfectFontDescriptor *, m_fontDescriptorList);
   UT_VECTOR_PURGEALL(WordPerfectHeaderPacket *, m_headerPacketList);
   UT_VECTOR_PURGEALL(WordPerfectListDefinition *, m_listDefinitionList);
}

/****************************************************************************/
/****************************************************************************/

UT_Error IE_Imp_WordPerfect::importFile(const char * szFilename)
{
   m_importFile = fopen(szFilename, "rb");
   if (!m_importFile)
     {
	UT_DEBUGMSG(("Could not open file %s\n",szFilename));
	return UT_IE_FILENOTFOUND;
     }

   UT_Error error;  

   error = _parseHeader(); 
   if (error == UT_OK) 
     {
	error = _parseIndexHeader();
	if (error == UT_OK)
	  error = _parseDocument();   
     }
   
   UT_DEBUGMSG(("WordPerfect: done with document parse loop\n"));

   fclose(m_importFile);
   return error;
}

void IE_Imp_WordPerfect::pasteFromBuffer (PD_DocumentRange *, 
										unsigned char *, unsigned int, const char *)
{
	// nada
}

UT_Error IE_Imp_WordPerfect::_parseHeader()
{
   UT_DEBUGMSG(("WordPerfect: Parsing the Header \n"));
   UT_uint16 documentEncrypted;
   
   X_CheckFileSeekError(fseek(m_importFile, WP_HEADER_DOCUMENT_POINTER_POSITION, SEEK_SET));
   if (fread(&m_documentPointer, sizeof(UT_uint32), 1, m_importFile) != 1)
     return UT_IE_IMPORTERROR;

   X_CheckFileSeekError(fseek(m_importFile, WP_HEADER_DOCUMENT_SIZE_POSITION, SEEK_SET));
   if (fread(&m_documentEnd, sizeof(UT_uint32), 1, m_importFile) != 1)
     return UT_IE_IMPORTERROR;
   
   X_CheckFileSeekError(fseek(m_importFile, WP_HEADER_INDEX_HEADER_POSITION, SEEK_SET));
   if (fread(&m_indexPointer, sizeof(UT_uint16), 1, m_importFile) != 1)
     return UT_IE_IMPORTERROR;
   
   X_CheckFileSeekError(fseek(m_importFile, WP_HEADER_ENCRYPTION_POSITION, SEEK_SET));
   if (fread(&documentEncrypted, sizeof(UT_uint16), 1, m_importFile) != 1)
     return UT_IE_IMPORTERROR;
   
   UT_DEBUGMSG(("WordPerfect: Index Header Position = %i \n",(int)m_indexPointer));
   UT_DEBUGMSG(("WordPerfect: Document Pointer = %i \n",(int)m_documentPointer));
   UT_DEBUGMSG(("WordPerfect: Document End Position = %i \n",(int)m_documentEnd));
   
   if (documentEncrypted != 0)
     return UT_IE_PROTECTED;
   
   // sanity check
   if (m_documentPointer > m_documentEnd)
     return UT_IE_IMPORTERROR;
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_parseIndexHeader()
{
   UT_DEBUGMSG(("WordPerfect: Parsing the Index Header \n"));
   UT_uint16 numIndices;
   
   X_CheckFileSeekError(fseek(m_importFile, (long) (m_indexPointer+WP_INDEX_HEADER_NUM_INDICES_POSITION), SEEK_SET));
   if (fread(&numIndices, sizeof(UT_uint16), 1, m_importFile) != 1)
     return UT_IE_IMPORTERROR;
   UT_DEBUGMSG(("WordPerfect: Index header has %i packet indices \n", (int) numIndices));
   
   X_CheckFileSeekError(fseek(m_importFile, (long) (m_indexPointer+WP_INDEX_HEADER_INDICES_POSITION), SEEK_SET));
   
   for (unsigned int i=1; i<numIndices; i++)
     {
	UT_uint8 flags, packetType;
	UT_uint16 packetUseCount, hiddenCount;
	UT_uint32 dataPacketSize, dataPointer;
	bool hasChildren = false;
	X_CheckFileReadElementError(fread(&flags, sizeof(UT_uint8), 1, m_importFile));
	if (flags & WP_INDEX_HEADER_ELEMENT_CHILD_PACKET_BIT)
	  hasChildren = true;
	X_CheckFileReadElementError(fread(&packetType, sizeof(UT_uint8), 1, m_importFile));
	X_CheckFileReadElementError(fread(&packetUseCount, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&hiddenCount, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&dataPacketSize, sizeof(UT_uint32), 1, m_importFile));
	X_CheckFileReadElementError(fread(&dataPointer, sizeof(UT_uint32), 1, m_importFile));
	UT_DEBUGMSG(("WordPerfect: (Packet Element %i: flags: %i, type: %i, use count: %i, hidden count: %i, size: %i, pointer: %i hasChildren: %i) \n", (int)i, (int)flags, (int)packetType, (int)packetUseCount, (int)hiddenCount, (int)dataPacketSize, (int)dataPointer, (int) hasChildren));

	switch (packetType)
	  {
	   case WP_INDEX_HEADER_DESIRED_FONT_DESCRIPTOR_POOL:
	     X_CheckWordPerfectError(_parseFontDescriptorPacket(i, dataPacketSize, dataPointer));
	     break;
	   case WP_INDEX_HEADER_EXTENDED_DOCUMENT_SUMMARY_DESCRIPTOR_POOL:
	     X_CheckWordPerfectError(_parseDocumentInformationDescriptorPacket(i, dataPacketSize, dataPointer));
	     break;
	   case WP_INDEX_HEADER_OUTLINE_STYLE:
	     X_CheckWordPerfectError(_parseOutlineStylePacket(i, dataPacketSize, dataPointer));
	     break;
	   default:
	     break;
	  }
	
	// insert into a generic list of header packets, for later use
	// (we include the font descriptors in this list because it makes it
	// trivial to look up the right PID..)
	WordPerfectHeaderPacket *headerPacket = new WordPerfectHeaderPacket(i, packetType, dataPointer, hasChildren);
	m_headerPacketList.addItem(headerPacket); // todo: check for error? how?
     }
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_parseFontDescriptorPacket(int packetID, UT_uint32 dataPacketSize, UT_uint32 dataPointer)
{
   UT_DEBUGMSG(("WordPerfect: Parsing a Font Descriptor\n"));
   UT_uint32 lastPosition = ftell(m_importFile);

   WordPerfectFontDescriptor *fontDescriptor = new WordPerfectFontDescriptor;
   UT_uint16 fontNameLength;
   
   X_CheckFileSeekError(fseek(m_importFile, (long) (dataPointer), SEEK_SET));

   // the packet number that this font is representative of
   // (this is what we use in the document to look up the correct font for a face/size change)
   fontDescriptor->m_packetID = packetID;

   // short sized characteristics
   X_CheckFileReadElementError(fread(&fontDescriptor->m_characterWidth, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_ascenderHeight, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_xHeight, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_descenderHeight, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_italicsAdjust, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_primaryFamilyId, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_primaryFamilyMemberId, sizeof(UT_uint8), 1, m_importFile));
   // byte sized characteristics
   X_CheckFileReadElementError(fread(&fontDescriptor->m_scriptingSystem, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_primaryCharacterSet, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_width, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_weight, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_attributes, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_generalCharacteristics, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_classification, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_fill, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_fontType, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptor->m_fontSourceFileType, sizeof(UT_uint8), 1, m_importFile));

   X_CheckFileReadElementError(fread(&fontNameLength, sizeof(UT_uint16), 1, m_importFile));
   if(fontNameLength > 0 && fontNameLength < WP_FONT_NAME_MAX_LENGTH)
     {	
	fontDescriptor->m_fontName = new char[fontNameLength];
	if(fread(fontDescriptor->m_fontName, sizeof(char), fontNameLength, m_importFile) != fontNameLength)
	  return UT_IE_IMPORTERROR;
     }
   else
     return UT_IE_IMPORTERROR;
   
   UT_DEBUGMSG(("WordPerfect: Read Font (primary family id: %i, font type: %i, font source file type: %i font name length: %i, font name: %s)\n", (int) fontDescriptor->m_primaryFamilyId, (int) fontDescriptor->m_fontType, (int) fontDescriptor->m_fontSourceFileType, (int) fontNameLength, fontDescriptor->m_fontName));
   
   m_fontDescriptorList.addItem(fontDescriptor); 
   
   X_CheckFileSeekError(fseek(m_importFile, (long) (lastPosition), SEEK_SET));
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_parseOutlineStylePacket(int packetID, UT_uint32 dataPacketSize, UT_uint32 dataPointer)
{
   UT_DEBUGMSG(("WordPerfect: Parsing an Outline Style Packet\n"));
   UT_uint32 lastPosition = ftell(m_importFile);
   
   X_CheckFileSeekError(fseek(m_importFile, (long) (dataPointer), SEEK_SET));

   UT_uint16 numPIDs;
   UT_uint16 paragraphStylePIDs[WP_NUM_LIST_LEVELS]; // seemingly useless
   UT_uint16 nonDeletableInfoSize;
   UT_uint16 definitionHash;
   UT_uint8 numberingMethods[WP_NUM_LIST_LEVELS];
   UT_uint8 outlineFlags;
   UT_uint8 tabBehaviourFlag;
      
   X_CheckFileReadElementError(fread(&numPIDs, sizeof(UT_uint16), 1, m_importFile));
   for (unsigned int i=0; i<WP_NUM_LIST_LEVELS; i++) 
     X_CheckFileReadElementError(fread(&paragraphStylePIDs[i], sizeof(UT_uint16), 1, m_importFile)); // seemingly useless
   X_CheckFileReadElementError(fread(&outlineFlags, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&definitionHash, sizeof(UT_uint16), 1, m_importFile)); // this is how we identify the list an element may belong to
   for (unsigned int i=0; i<WP_NUM_LIST_LEVELS; i++)  
     X_CheckFileReadElementError(fread(&numberingMethods[i], sizeof(UT_uint8), 1, m_importFile));
   //X_CheckFileReadElementError(fread(&tabBehaviourFlag, sizeof(UT_uint8), 1, m_importFile));
   
   UT_DEBUGMSG(("WordPerfect: Read Outline Style Packet (numPrefixIDs: %i, outlineStylePID: %i, definitionHash: %i, outlineFlags: %s)\n", (int) numPIDs, (int) definitionHash, (int) outlineFlags));
   UT_DEBUGMSG(("WordPerfect: Read Outline Style Packet (paragraphStylePIDs: %i %i %i %i %i %i %i %i)\n", paragraphStylePIDs[0], paragraphStylePIDs[1], paragraphStylePIDs[2], paragraphStylePIDs[3],
		paragraphStylePIDs[4], paragraphStylePIDs[5], paragraphStylePIDs[6], paragraphStylePIDs[7]));
   UT_DEBUGMSG(("WordPerfect: Read Outline Style Packet (numberingMethods: %i %i %i %i %i %i %i %i)\n", numberingMethods[0], numberingMethods[1], numberingMethods[2], numberingMethods[3],
		numberingMethods[4], numberingMethods[5], numberingMethods[6], numberingMethods[7]));
   
   WordPerfectListDefinition *listDefinition = new WordPerfectListDefinition(definitionHash, numberingMethods);
   m_listDefinitionList.addItem((void *)listDefinition);
   
   X_CheckFileSeekError(fseek(m_importFile, (long) (lastPosition), SEEK_SET));
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_parseDocumentInformationDescriptorPacket(int packetID, UT_uint32 dataPacketSize, UT_uint32 dataPointer)
{
   UT_DEBUGMSG(("WordPerfect: Parsing Extended Document Summary information\n"));
   UT_uint32 lastPosition = ftell(m_importFile);

   X_CheckFileSeekError(fseek(m_importFile, (long) (dataPointer), SEEK_SET));

   UT_uint16 groupLength;
   UT_uint16 tagID;
   UT_uint16 flags;
   UT_uint16 userDefinedFieldName;
   UT_uint16 emptyBytes; // ? there always seem to be 2 empty bytes after each Document Summary Data Group
   
   for (int i=0; i < dataPacketSize; i+=groupLength)
   {
       UT_String sBuf = 0;
       UT_uint16 readVal = 0; 
       
       UT_DEBUGMSG(("WordPerfect: Parsing Document Summary Data group\n"));
       X_CheckFileReadElementError(fread(&groupLength, sizeof(UT_uint16), 1, m_importFile));
       X_CheckFileReadElementError(fread(&tagID, sizeof(UT_uint16), 1, m_importFile));
       X_CheckFileReadElementError(fread(&flags, sizeof(UT_uint16), 1, m_importFile));
       X_CheckFileReadElementError(fread(&userDefinedFieldName, sizeof(UT_uint16), 1, m_importFile));
       
       for (int j = 0; j < groupLength - 10; j+=2)
       {
        	  X_CheckFileReadElementError(fread(&readVal, sizeof(UT_uint16), 1, m_importFile));
           //UT_DEBUGMSG((" current char = %c \n",(char)readVal));
           // FIXME: Handle this charachter data more properly!
           sBuf += (char) readVal;
       }
       
       switch (tagID)
       {
           case 0x0005: // Author
              getDoc()->setMetaDataProp(PD_META_KEY_CREATOR, sBuf);
              break;
           case 0x002E: // Subject
              getDoc()->setMetaDataProp(PD_META_KEY_SUBJECT, sBuf);
              break;
           case 0x0006: // Authorization
              // getDoc()->setMetaDataProp(???, sBuf);
              break;           
           case 0x0021: // Publisher
              getDoc()->setMetaDataProp(PD_META_KEY_PUBLISHER, sBuf);
              break;  
           case 0x000A: // Category
              getDoc()->setMetaDataProp(PD_META_KEY_TYPE, sBuf);
              break;  
           case 0x001A: // Keywords
              getDoc()->setMetaDataProp(PD_META_KEY_KEYWORDS, sBuf);
              break;  
           case 0x001B: // Language
              getDoc()->setMetaDataProp(PD_META_KEY_LANGUAGE, sBuf);
              break;  
           case 0x0001: /* Abstract (use the WP Abstract value instead of the WP Description value to fill the AbiWord Description 
                                     field, because the WP Abstract value is a multiline value and Description is not)*/
              getDoc()->setMetaDataProp(PD_META_KEY_DESCRIPTION, sBuf);
              break;  
           default:
              break;
       }
       
       X_CheckFileReadElementError(fread(&emptyBytes, sizeof(UT_uint16), 1, m_importFile));
   }
   
   
   X_CheckFileSeekError(fseek(m_importFile, (long) (lastPosition), SEEK_SET));

   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_handleBoxGroupContent(int boxContentPID)
{
   // find the appropriate packet - wp packets start at 1, we start at 0
   WordPerfectHeaderPacket *boxContentPacket = (WordPerfectHeaderPacket *)m_headerPacketList.getNthItem((boxContentPID - 1));
   
   // FIXME: we should really handle externally declared files. but we don't.
   if( !boxContentPacket->m_hasChildren )
	  return UT_IE_IMPORTERROR;
   
   long documentParsePosition = ftell(m_importFile); // keep track of where we were
	   
   X_CheckFileSeekError(fseek(m_importFile, boxContentPacket->m_packetPosition, SEEK_SET));
   
   UT_uint16 numChildPackets;
   X_CheckFileReadElementError(fread(&numChildPackets, sizeof(UT_uint16), 1, m_importFile));
   UT_uint16 *graphicContentPIDs = new UT_uint16[numChildPackets];
   for( unsigned int i=0; i<numChildPackets; i++ )
     X_CheckFileReadElementError(fread(&graphicContentPIDs[i], sizeof(UT_uint16), 1, m_importFile));
   
   UT_DEBUGMSG(("WordPerfect: Parsed box group content with %i childpackets\n", numChildPackets));
   
   // FIXME: for now, we only handle one packet of graphic content
   if( numChildPackets > 0 )
     X_CheckWordPerfectError(_handleGraphicsData(graphicContentPIDs[0]))
   
   // return to where we were before
   X_CheckFileSeekError(fseek(m_importFile, documentParsePosition, SEEK_SET));
   
   delete(graphicContentPIDs);
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_handleGraphicsData(int graphicPID)
{
   UT_DEBUGMSG(("WordPerfect: Handling graphics data\n"));
   // find the appropriate packet - wp packets start at 1, we start at 0
   // WordPerfectHeaderPacket *graphicPacket = (WordPerfectHeaderPacket *)m_headerPacketList.getNthItem((graphicPID - 1)); 
   // ...
															    
   return UT_OK;
}


UT_Error IE_Imp_WordPerfect::_handleBoxGroupTemplate(int boxGroupTemplatePID)
{
   UT_DEBUGMSG(("WordPerfect: Handling a box group template (currently disabled)\n"));
   /*
   // find the appropriate packet
   WordPerfectHeaderPacket *boxTemplatePacket = (WordPerfectHeaderPacket *)m_headerPacketList.getNthItem((boxGroupTemplatePID - 1)); // wp packets start at 1, we start at 0
   
   // we're only going to bother with graphics for now
   if (boxTemplatePacket->m_type == WP_INDEX_HEADER_GRAPHICS_BOX_STYLE)
     {
	long documentParsePosition = ftell(m_importFile); // keep track of where we were
	   
	X_CheckFileSeekError((fseek(m_importFile, boxTemplatePacket->m_packetPosition, SEEK_SET));
	
	// now we read out a list of (possible) child packets to parse
	UT_uint16 numPrefixPacketIDs;
	UT_uint16 dataPrefixIDs;
	UT_uint16 counterPrefixIDs;
	UT_uint16 positioningDataPrefixIDs;
	UT_uint16 contentPrefixIDs;
	UT_uint16 captionPrefixIDs;
	UT_uint16 borderPrefixIDs;
	UT_uint16 fillPrefixIDs;
	UT_uint16 wrapPrefixIDs;
	UT_uint16 hyperTextPrefixIDs;
	
  	X_CheckFileReadElementError(fread(&numPrefixPacketIDs, sizeof(UT_uint16), 1, m_importFile));   
	X_CheckFileReadElementError(fread(&dataPrefixIDs, sizeof(UT_uint16), 1, m_importFile));   
	X_CheckFileReadElementError(fread(&counterPrefixIDs, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&positioningDataPrefixIDs, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&contentPrefixIDs, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&captionPrefixIDs, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&borderPrefixIDs, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&fillPrefixIDs, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&wrapPrefixIDs, sizeof(UT_uint16), 1, m_importFile));
	X_CheckFileReadElementError(fread(&hyperTextPrefixIDs, sizeof(UT_uint16), 1, m_importFile));
	UT_DEBUGMSG(("WordPerfect: Read Box Template Packet Header (numPrefixPacketIDs: %i, dataPrefixIDs: %i, counterPrefixIDs: %i, positioningDataPrefixIDs: %i, contentPrefixIDs: %i, captionPrefixIDs: %i, borderPrefixIDs: %i, fillPrefixIDs: %i, wrapPrefixIDs: %i, hypertextPrefixIDs: %i\n",
		     (int)numPrefixPacketIDs, (int)dataPrefixIDs, (int)counterPrefixIDs, (int)positioningDataPrefixIDs, (int)contentPrefixIDs, (int)captionPrefixIDs, (int)borderPrefixIDs, (int)fillPrefixIDs, (int)wrapPrefixIDs, (int) hyperTextPrefixIDs));
	
	// return to where we were before
	X_CheckFileSeekError(fseek(m_importFile, documentParsePosition, SEEK_SET));
     }
   */
   return UT_OK;
  
}

UT_Error IE_Imp_WordPerfect::_parseDocument()
{
   UT_DEBUGMSG(("WordPerfect: Parsing the Document \n"));
   
   X_CheckFileSeekError(fseek(m_importFile, m_documentPointer, SEEK_SET));
   
   UT_uint8 readVal;
   
   while (ftell(m_importFile) < (int)m_documentEnd)
     {
	X_CheckFileReadElementError(fread(&readVal, sizeof(UT_uint8), 1, m_importFile));
	
	if(readVal > 0 && readVal < 127)
	  {	     
	     if (readVal < 32) // International Characters
	       {		  
		  X_CheckWordPerfectError(_insertCharacter(wp_internationalCharacterMapping[(readVal-1)]));
	       }	     
	     else // normal ASCII characters
	       {		  
		  X_CheckWordPerfectError(_insertCharacter((UT_UCS4Char)readVal));
	       }
	  }	     
	else 
	  {	     
	     for (unsigned int i=0; i<m_wordPerfectDispatchBytes.size(); i++)
	       {
		  WordPerfectByteTag *dispatchByte = (WordPerfectByteTag *) m_wordPerfectDispatchBytes.getNthItem( i );
		  if( dispatchByte->m_byte == readVal )
		    {
		       (*this.*(dispatchByte->m_func)) ();
		       break;
		    }
	       }
	  }
     }
  
   UT_DEBUGMSG(("WordPerfect: File Pointer at %i equals or exceeds document length of %i\n", (int)ftell(m_importFile), (int)m_documentEnd));      

   X_CheckWordPerfectError(_flushText());

   return UT_OK;
}

// inserts a character into the document, or not, depending on wordperfect's current state
UT_Error IE_Imp_WordPerfect::_insertCharacter(UT_UCS4Char ucs)
{
   if (!m_undoOn) 
     {		  
	if (m_paragraphStyleState == styleBody || m_paragraphStyleState == notInStyle)
	  {	     
	     UT_GrowBufElement wc = (UT_GrowBufElement) ucs; // doing a cast from unsigned (UT_UCS4Char) -> signed (UT_GrowbufElement). kinda nerve wracking, but should be o.k.
	     m_textBuf.append(&wc, 1);
	  }
	else if (m_paragraphStyleState == beginNumbering)
	  {
	     UT_DEBUGMSG(("WordPerfect: Character during numbering.. assuming right delim\n"));
	     m_rightListDelim += ucs;
	     // (AFAIK WP doesn't do left delimiters on bullets?)
	     //if (m_paragraphStyleState == beginPart2BeforeNumbering)
	     //  m_leftListDelim+=wc;
	     //else
	  }
     }   
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_insertSpace()
{
   X_CheckWordPerfectError(_insertCharacter(UCS_SPACE));
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_insertHyphen()
{
   X_CheckWordPerfectError(_insertCharacter(UCS_MINUS)); // UCS_HYPHEN doesn't seem to work properly.. font issue?
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_handleHardEndOfLine()
{
   // (TODO: eliminate a prev space if it's just before this)
   UT_DEBUGMSG(("WordPerfect: Handling a hard EOL \n"));
   if(!m_undoOn) //  && m_paragraphStyleState != end fixme: can there be multiple breaks in an end state? (prolly just add deferred paragraph breaks when we find end)
   {      
      if (!m_bParagraphChanged) 
        {
	   X_CheckWordPerfectError(_flushText());
	   m_numDeferredParagraphBreaks++;
        }
      else
        {
	   X_CheckWordPerfectError(_flushText());
        }
   }
   
   return UT_OK;
}

// handles an end-of-line function that has formatting information embedded
// into it. Fortunately, only the first code is relevant for our purposes..
// the rest can be safely skipped (at least according to the developer documentation)
UT_Error IE_Imp_WordPerfect::_handleEndOfLineGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a EOL group\n"));

   UT_uint8 subGroup;   
   UT_uint16 size;
   long startPosition = ftell(m_importFile);

   X_CheckFileReadElementError(fread(&subGroup, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&size, sizeof(UT_uint16), 1, m_importFile));

   UT_GrowBufElement wc = 0;
   
   // WL FIXME: am I handling all the special cases properly here? quite possibly not
   if(!m_undoOn)/* && m_paragraphStyleState != beginPart2BeforeNumbering && 
      m_paragraphStyleState != beginPart2Numbering && 
      m_paragraphStyleState != end) */
     {
	switch(subGroup)
	  {
	   case 0: // 0x00 (beginning of file)
	     break; // ignore
	   case 1: // 0x01 (soft EOL)
	   case 2: // 0x02 (soft EOC) 
	   case 3: // 0x03 (soft EOC at EOP) 
	   case 20: // 0x014 (deletable soft EOL)
	   case 21: // 0x15 (deletable soft EOC) 
	   case 22: // 0x16 (deleteable soft EOC at EOP) 
	     wc = ' ';
	     m_textBuf.append(&wc, 1);
	     break;
	   case 4: // 0x04 (hard end-of-line)
	   case 5: // 0x05 (hard EOL at EOC) 
	   case 6: // 0x06 (hard EOL at EOP)
	   case 23: // 0x17 (deletable hard EOL)
	   case 24: // 0x18 (deletable hard EOL at EOC)
	   case 25: // 0x19 (deletable hard EOL at EOP)	
	     X_CheckWordPerfectError(_handleHardEndOfLine());
	     break;
	   case 7: // 0x07 (hard end of column)
	     {
	       X_CheckWordPerfectError(_flushText());
	       UT_UCS4Char ucs = UCS_VTAB;
	       X_CheckDocumentError(getDoc()->appendSpan(&ucs,1));
	     }
	     break;
	   case 9: // hard EOP
	   case 28: // deletable hard EOP
	     { 
	       X_CheckWordPerfectError(_flushText());
	       UT_UCS4Char ucs = UCS_FF;
	       X_CheckDocumentError(getDoc()->appendSpan(&ucs,1));
	     }
	     break;
	   case 0x0A: // Table Cell
	   {
		 UT_DEBUGMSG(("WordPerfect: Table Cell\n"));
		 
	     // check if a previous cell exists which should be closed first
	     if (m_iCurrentTableColumn != -1)
	     {
	       X_CheckWordPerfectError(_handleHardEndOfLine());
	       X_CheckDocumentError(getDoc()->appendStrux(PTX_EndCell, NULL));
	     }

	     m_iCurrentTableColumn++;

	     UT_String propBuffer;
	     UT_String_sprintf(propBuffer, "left-attach:%d; right-attach:%d; top-attach:%d; bot-attach:%d", m_iCurrentTableColumn, m_iCurrentTableColumn+1, m_iCurrentTableRow, m_iCurrentTableRow+1);

	     XML_Char* pProps = "props";
	     const XML_Char* propsArray[3];
	     propsArray[0] = pProps;
	     propsArray[1] = propBuffer.c_str();
	     propsArray[2] = NULL;

	     X_CheckDocumentError(getDoc()->appendStrux(PTX_SectionCell, propsArray));
	     break;
	   }
	   case 0x0B: // Table Row and Cell
	   {
		 UT_DEBUGMSG(("WordPerfect: Table Row and Cell\n"));
		   
	     // check if a previous cell exists which should be closed first
	     if (m_iCurrentTableColumn != -1)
	     {
	       X_CheckWordPerfectError(_handleHardEndOfLine());
	       X_CheckDocumentError(getDoc()->appendStrux(PTX_EndCell, NULL));
	     }
	     m_iCurrentTableRow++;
	     m_iCurrentTableColumn = 0;

	     UT_String propBuffer;
	     UT_String_sprintf(propBuffer, "left-attach:%d; right-attach:%d; top-attach:%d; bot-attach:%d", m_iCurrentTableColumn, m_iCurrentTableColumn+1, m_iCurrentTableRow, m_iCurrentTableRow+1);

	     XML_Char* pProps = "props";
	     const XML_Char* propsArray[3];
	     propsArray[0] = pProps;
	     propsArray[1] = propBuffer.c_str();
	     propsArray[2] = NULL;

	     X_CheckDocumentError(getDoc()->appendStrux(PTX_SectionCell, propsArray));
	     break;
	   }
	   case 0x11: // Table Off
		 UT_DEBUGMSG(("WordPerfect: TABLE OFF\n"));
	     if (m_iCurrentTableColumn != -1)
	     {
	       X_CheckWordPerfectError(_handleHardEndOfLine());
	       X_CheckDocumentError(getDoc()->appendStrux(PTX_EndCell, NULL));
	     }
	     X_CheckDocumentError(getDoc()->appendStrux(PTX_EndTable, NULL));
	     break;
	   
	   default: // something else we don't support yet
	     break;
	  }
     }
   
   X_CheckWordPerfectError(_skipGroup(startPosition, size));

   return UT_OK;
}

// handles a page group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handlePageGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a page group\n"));
   long startPosition;
   UT_uint8 subGroup;   
   UT_uint16 size;
   UT_uint8 flags;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));   
   X_CheckWordPerfectError(_skipGroup(startPosition, size));

   return UT_OK;
}

// handles a column group
// (TODO: partially implemented)
UT_Error IE_Imp_WordPerfect::_handleColumnGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a column group\n"));
   long startPosition;
   UT_uint8 subGroup;
   UT_uint16 size;
   UT_uint8 flags;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
    
   if(!m_undoOn)
   {
       UT_DEBUGMSG(("WordPerfect: Column subgroup: %d\n", subGroup));

	   switch (subGroup)
       {
          case 0: // Left Margin Set
	      case 1: // Right Margin Set
				  {
					  UT_uint16 margin; // WPU (WordPerfect Unit), which is one 1200th of an inch)
					  float marginInch; 
					  UT_uint16 nonDeletableInfoSize;
					  
					  // if there is a section in the document which current properties are not changed,
					  // but the contents of it _are_ changed then flush the changes first, before changing the section style
					  if (!m_bSectionChanged && (m_bParagraphChanged || m_textBuf.getLength() > 0))
					  {
						  X_CheckWordPerfectError(_flushText());
					  }
					  
					  X_CheckFileReadElementError(fread(&nonDeletableInfoSize, sizeof(UT_uint16), 1, m_importFile));
					  X_CheckFileReadElementError(fread(&margin, sizeof(UT_uint16), 1, m_importFile));
					  if (subGroup == 0)
						  UT_DEBUGMSG(("WordPerfect: Left margin: %d WPUs\n", margin));
					  else
						  UT_DEBUGMSG(("WordPerfect: Right margin: %d WPUs\n", margin));

					  marginInch = ((float)margin / 1200);

					  // set the new margin properties
					  if (subGroup == 0)
					  {
						  m_leftMargin = marginInch;
						  m_bLeftMarginSet = true;
					  }
					  else
					  {
						  m_rightMargin = marginInch;
						  m_bRightMarginSet = true;
					  }
                      
					  m_bSectionChanged = true;
					  
                      // set m_bParagraphChanged to true so the paragraph properties will 
                      // unconditionally be added in this new section
                      m_bParagraphChanged = true;
					  
					  break;
				  }
          case 2: // TODO: Define Text Columns, Partially implemented
                  UT_uint8 colType;
                  UT_uint8 rowSpacing[4]; // a WP SPacing type variable, which is 4 bytes
                  UT_uint8 unknown; 
                  UT_uint8 nonDeletableInfoSize; // 1 byte only this case

				  X_CheckFileReadElementError(fread(&nonDeletableInfoSize, sizeof(UT_uint8), 1, m_importFile));
                  X_CheckFileReadElementError(fread(&colType, sizeof(UT_uint8), 1, m_importFile));
                  if (fread(&rowSpacing[0], sizeof(UT_uint8), 4, m_importFile) != 4*sizeof(UT_uint8))
                     return UT_IE_IMPORTERROR;
                  // I don't have a clue what this lonely byte does...
                  X_CheckFileReadElementError(fread(&unknown, sizeof(UT_uint8), 1, m_importFile));
                  X_CheckFileReadElementError(fread(&m_numberOfColumns, sizeof(UT_uint8), 1, m_importFile));
          
                  UT_DEBUGMSG(("WordPerfect: Column type: %d\n", colType & 0x03));
                                    
                  // number of columns = {0,1} means columns off
                  if ((m_numberOfColumns == 0) || (m_numberOfColumns == 1))
                  {
					 m_bColumnsSet = false;
                     X_CheckWordPerfectError(_flushText());
                     X_CheckWordPerfectError(_appendSection());
                     // set m_bParagraphChanged to true so the paragraph properties will 
                     // unconditionally be added in this new section
                     m_bParagraphChanged = true;
                  } 
                  else
                  {
                     switch (colType & 0x03)
                     {
                        // TODO: implement the seperate cases
                        case 0: // newspaper
                        case 1: // newspaper with vertical balance
                        case 2: // parallel
                        case 3: // parallel with protect [what does this mean? for now, handle the same as parallel]
                                {
                                   m_bColumnsSet = true;

                                   if ((m_bParagraphChanged) || (m_textBuf.getLength() > 0))
                                   {
                                      X_CheckWordPerfectError(_flushText());
                                   }
				   
                                   m_bSectionChanged = true;
				   
                                   // set m_bParagraphChanged to true so the paragraph properties will 
                                   // unconditionally be added in this new section
                                   m_bParagraphChanged = true;
                                }
                                break;
                        default: // something else we don't support, since it isn't in the docs
                                 break;
                     }
                  }
                  break;
          case 3: // TODO: Column Border
                  break;
          default: // something else we don't support, since it isn't in the docs
                   break;
       }
   }
     
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles a paragraph group
// (TODO: not completely implemented)
UT_Error IE_Imp_WordPerfect::_handleParagraphGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a paragraph group\n"));

   long startPosition;
   UT_uint8 subGroup, flags;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));   

   if (!m_undoOn)
     {			
	switch (subGroup)
	  {
	   case WP_PARAGRAPH_GROUP_JUSTIFICATION:
	       {   
		  X_CheckWordPerfectError(_handleParagraphGroupJustification());
		  m_bParagraphChanged = true;
		  break;
	       }
	   case WP_PARAGRAPH_GROUP_OUTLINE_DEFINE:
	       {
		  UT_DEBUGMSG(("WordPerfect: LISTS: Outline Define\n"));
		  X_CheckWordPerfectError(_handleOutlineDefine());		  
		  break;
	       }
	  }
     }   

   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}


// handles a style group
// (partially implemented, handles stuff which is relevant to list properties being set)
UT_Error IE_Imp_WordPerfect::_handleStyleGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a style group\n"));
   long startPosition;
   UT_uint8 subGroup;   
   UT_uint16 size;
   UT_uint8 flags;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));   
   
   if (!m_undoOn) 
     {	
	switch (subGroup) 
	  {
	   case WP_STYLE_GROUP_PARASTYLE_BEGIN_ON_PART1:
	     UT_DEBUGMSG(("WordPerfect: Handling para style begin 1 (ON)\n"));	     
	     m_paragraphStyleState = beginBeforeNumbering;
	     m_paragraphStyleMarginLeft = WP_PARAGRAPH_STYLE_MARGIN_LEFT_INCREMENT; 
	     m_paragraphStyleTextIndent = WP_PARAGRAPH_STYLE_TEXT_INDENT_DECREMENT; // WL: this is abi's default (not wordperfect's) -- I think it is better to use abi's
	     m_bPutativeListHasParagraphNumber = false;
	     break;
	   case WP_STYLE_GROUP_PARASTYLE_BEGIN_OFF_PART1:
	     UT_DEBUGMSG(("WordPerfect: Handling a para style begin 1 (OFF)\n"));
	     break;
	   case WP_STYLE_GROUP_PARASTYLE_BEGIN_ON_PART2:
	     UT_DEBUGMSG(("WordPerfect: Handling a para style begin 2 (ON)\n"));
	     m_numDeferredParagraphBreaks--; // wordperfect does not consider that appending list properties causes a paragraph break. we do.
	     X_CheckWordPerfectError(_flushText()); // flush the item (list or otherwise) text, minus a paragraph break
	     break;
	   case WP_STYLE_GROUP_PARASTYLE_BEGIN_OFF_PART2:
	     UT_DEBUGMSG(("WordPerfect: Handling a para style begin 2 (OFF)\n"));
	     m_paragraphStyleState = styleBody;	     
	     break;
	   case WP_STYLE_GROUP_PARASTYLE_END_ON:
	     UT_DEBUGMSG(("WordPerfect: Handling a para style end (ON)\n"));
	     if (!m_bPutativeListHasParagraphNumber)
	       {		
		  m_numDeferredParagraphBreaks++; // give back what we took away, since we didn't append any list properties, and hence the eol is still wanted
	       }
	     X_CheckWordPerfectError(_flushText()); // flush the item (list or otherwise) text
	     m_paragraphStyleState = end;
	     break;
	   case WP_STYLE_GROUP_PARASTYLE_END_OFF:
	     UT_DEBUGMSG(("WordPerfect: Handling a parastyle end (OFF)\n"));
	     m_paragraphStyleState = notInStyle;
	     break;
	  }
     }   
   
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles a tab group
// (TODO: partially implemented, only basic tab import is done)
UT_Error IE_Imp_WordPerfect::_handleTabGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a tab group\n"));
 
   long startPosition = ftell(m_importFile);
   UT_uint8 tabDefinition;   
   UT_uint16 size;
   
   X_CheckFileReadElementError(fread(&tabDefinition, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&size, sizeof(UT_uint16), 1, m_importFile));

   if(!m_undoOn)
     {
        // TODO: soft type (tab, align, centerm and so forth), (uses tab set definition type)
        if (tabDefinition & 0x01) { }
        // TODO: dot leader 
        if (tabDefinition & 0x02) { }
        // TODO: generic search (only used in search code, ignore bits 0 and 1 when comparing)
        if (tabDefinition & 0x04) { }    
	
        switch ((tabDefinition & 0xF8) >> 3)
	  {
	   case  0: // 00000b = back tab
	   case  1: // 00001b = table tab
	   case  2: // 00010b = left tab
	   case  4: // 00100b = bar tab
	   case  6: // 00110b = left indent
	   case  7: // 00111b = left/right indent
	   case  8: // 01000b = center on margins
	   case  9: // 01001b = center on current position
	   case 10: // 01010b = center tab
	   case 16: // 10000b = flush right
	   case 18: // 10010b = right tab
	   case 26: // 11010b = decimal tab
	     // TODO: fix stupid default implementation of adding just a TAB char without looking what it actually should be
	     {
		// we handle things a bit differently in certain parts of wordperfect list parsing
		if (m_paragraphStyleState == beginBeforeNumbering)
		  {
		     UT_DEBUGMSG(("WordPerfect: Incrementing paragraph style margin left\n"));		     
		     m_paragraphStyleMarginLeft += WP_PARAGRAPH_STYLE_MARGIN_LEFT_INCREMENT;
		  }	     
		else 
		  {
		     X_CheckWordPerfectError(_insertCharacter(UCS_TAB));
		  }
		
	     }
	     break;
	   default: // something else shouldn't be possible according to the documentation
	     break;
	  }
     }

   X_CheckWordPerfectError(_skipGroup(startPosition, size));

   return UT_OK;
}

// handles a platform group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handlePlatformGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a platform group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles a formatter group
// (undocumented in corel's documentation, we have to skip)
UT_Error IE_Imp_WordPerfect::_handleFormatterGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a formatter group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));

   return UT_OK;
}

// handles a foot or end note group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handleFootEndNoteGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a foot/endnote group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles a set number group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handleSetNumberGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a set number group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles a number  method group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handleNumberingMethodGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a numbering method group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}


// handles a display number reference group: which, as of now, we just use to determine
// where a list bullet starts and ends (but only for numbered lists..)
UT_Error IE_Imp_WordPerfect::_handleDisplayNumberReferenceGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a display number reference group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   
   if (!m_undoOn) 
     {	
	switch (subGroup) 
	  {
	   case WP_DISPLAY_NUMBER_REFERENCE_GROUP_PARAGRAPH_NUMBER_DISPLAY_ON:
	     UT_DEBUGMSG(("WordPerfect: Display number reference group (about to display number)\n"));
	     if (m_paragraphStyleState == beginNumbering)
	       m_paragraphStyleState = beginDisplayReferencing;
	     break;
	   case WP_DISPLAY_NUMBER_REFERENCE_GROUP_PARAGRAPH_NUMBER_DISPLAY_OFF:
	     UT_DEBUGMSG(("WordPerfect: Display number reference group (no longer displaying number)\n"));
	     if (m_paragraphStyleState == beginDisplayReferencing)
	       m_paragraphStyleState = beginNumbering;
	     break;
	  }
     }
   
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles a increment number group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handleIncrementNumberGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling an increment number group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}


// handles a decrement number reference group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handleDecrementNumberGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a decrement number group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles a merge group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handleMergeGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a merge group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles a box group (which has something to do with wordperfect graphics)
// (TODO: not really implemented, parses a bunch of info, but doesn't do anything with it)
UT_Error IE_Imp_WordPerfect::_handleBoxGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a box group\n"));
   UT_uint8 subGroup, prefixIndex;
   long startPosition;
   UT_uint16 size;

   UT_uint8 numPIDs;
   UT_uint16 numNonDeletableBytes;
   // (14 reserved bytes)
   UT_uint16 sizeOverrideAndWrapRectangleData;
   UT_uint16 sizeOverrideData;
   UT_uint16 boxOverrideFlags;
   UT_uint16 numWrapRectangles;
   UT_uint16 leftOffset;
   UT_uint16 rightOffset;
   UT_uint16 topOffset;
   UT_uint16 bottomOffset;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, prefixIndex));
   
   X_CheckFileReadElementError(fread(&numPIDs, sizeof(UT_uint8), 1, m_importFile));
   if( numPIDs < 1 )
     return UT_IE_IMPORTERROR;
   UT_uint16 *boxPIDs = new UT_uint16[numPIDs];
   for( unsigned int i=0; i<numPIDs; i++ )
        X_CheckFileReadElementError(fread(&boxPIDs[i], sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&numNonDeletableBytes, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileSeekError(fseek(m_importFile, WP_BOX_GROUP_NUM_RESERVED_BYTES, SEEK_CUR));
   
   X_CheckFileReadElementError(fread(&sizeOverrideAndWrapRectangleData, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&sizeOverrideData, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&boxOverrideFlags, sizeof(UT_uint16), 1, m_importFile));   
   
   X_CheckFileReadElementError(fread(&numWrapRectangles, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&leftOffset, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&rightOffset, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&topOffset, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&bottomOffset, sizeof(UT_uint16), 1, m_importFile));
   
   UT_DEBUGMSG(("WordPerfect: Box Group: subGroup: %i, prefixIndex: %i, numPIDs: %i\n", (int) subGroup, (int)prefixIndex, (int) numPIDs));
   UT_DEBUGMSG(("WordPerfect: Box Group: sizeOverrideAndWrapRectangleData: %i, sizeOverrideData: %i, boxOverrideFlags: %i, numWrapRectangles: %i\n", (int) sizeOverrideAndWrapRectangleData, (int) sizeOverrideData, (int)boxOverrideFlags, (int) numWrapRectangles));
   UT_DEBUGMSG(("WordPerfect: Box Group: leftOffset: %i, rightOffset: %i, topOffset: %i, bottomOffset: %i\n", (int) leftOffset, (int) rightOffset, (int) topOffset, (int) bottomOffset));
   
   int j=1;
   if( boxOverrideFlags & WP_BOX_GROUP_OVERRIDE_FLAGS_BOX_CONTENT )
     {
	UT_DEBUGMSG(("WordPerfect: Override flags set for content. Content PID: %i\n", boxPIDs[j]));
	j++;
     }
   
   X_CheckWordPerfectError(_handleBoxGroupTemplate(boxPIDs[0]));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   
   return UT_OK;
}

// handles an attribute "on" group in wordperfect. turns a formatting/style
// property on.
UT_Error IE_Imp_WordPerfect::_handleAttributeOn()
{   
   UT_DEBUGMSG(("WordPerfect: Handling an attribute ON\n"));
   long startPosition = ftell(m_importFile);
   
   int readVal = fgetc(m_importFile); // TODO: handle case that we get eof?
   X_CheckFileError(readVal);
   
   if(!m_undoOn)
     {
	// flush what's come before this change (even if it's nothing, which
	// IS a case we have to be worried about in case we are writing the first
	// paragraph)
	X_CheckWordPerfectError(_flushText());

	switch (readVal)
	  { 
	   case 5: // superscript
		  m_textAttributes.m_superScript = true;
		  break;
	   case 6: // subscript
		  m_textAttributes.m_subScript = true;
		  break;
	   case 8: // italics
		  m_textAttributes.m_italics = true;
	      break;
	   case 12: // bold
	     m_textAttributes.m_bold = true;
	     break;
	   case 13: // strike-out
		  m_textAttributes.m_strikeOut = true;
	      break;
	   case 14: // underline
	     m_textAttributes.m_underLine = true;
	     break;
	   default: // something we don't support yet
	     break;
	  }
	
	X_CheckWordPerfectError(_flushText());
	m_bTextPropertiesChanged = true;
     }
      
   X_CheckWordPerfectError(_skipGroup(startPosition, WP_ATTRIBUTE_ON_GROUP_SIZE));
   return UT_OK;
}

// handles an attribute "off" byte in wordperfect. turns a formatting/style
// property off.
UT_Error IE_Imp_WordPerfect::_handleAttributeOff()
{   
   UT_DEBUGMSG(("WordPerfect: Handling an attribute OFF\n"));
   long startPosition = ftell(m_importFile);

   int readVal = fgetc(m_importFile); // TODO: handle case that we get eof?
   X_CheckFileError(readVal);
   
   if(!m_undoOn)
     {
	// flush what's come before this change (even if it's nothing, which
	// IS a case we have to be worried about in case we are writing the first
	// paragraph)
	X_CheckWordPerfectError(_flushText());

	switch (readVal)
	  { 
	   case 5: // superscript
		  m_textAttributes.m_superScript = false;
		  break;
	   case 6: // subscript
		  m_textAttributes.m_subScript = false;
		  break;
	   case 8: // italics
		  m_textAttributes.m_italics = false;
	      break;
	   case 12: // bold
	     m_textAttributes.m_bold = false;
	     break;
	   case 13: // strike-out
		  m_textAttributes.m_strikeOut = false;
	      break;
	   case 14: // underline
	     m_textAttributes.m_underLine = false;
	     break;
	   default: // something we don't support yet
	     break;
	  }
        
	X_CheckWordPerfectError(_flushText());
	m_bTextPropertiesChanged = true;
     }
      
   X_CheckWordPerfectError(_skipGroup(startPosition, WP_ATTRIBUTE_OFF_GROUP_SIZE));
   return UT_OK;
}

// handles a character group (related to stuff like font size changing and list recognition)
UT_Error IE_Imp_WordPerfect::_handleCharacterGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a character group\n"));

   long startPosition;
   UT_uint8 subGroup;
   UT_uint16 size;
   UT_uint8 flags;
   
   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   
   if (!m_undoOn)
     {	
	switch(subGroup)
	  {
	   case WP_CHARACTER_GROUP_FONT_FACE_CHANGE:
	     X_CheckWordPerfectError(_handleFontFaceChange());
	     break;	
	   case WP_CHARACTER_GROUP_FONT_SIZE_CHANGE:
	     X_CheckWordPerfectError(_handleFontSizeChange());
	     break;
	   case WP_CHARACTER_GROUP_PARAGRAPH_NUMBER_ON:
	     if (m_paragraphStyleState == beginBeforeNumbering || m_paragraphStyleState == styleBody)
	       {
		  m_bPutativeListHasParagraphNumber = true; // indicates that a paragraph style really does encapsulate a list
		  UT_uint16 nonDeletableInfoSize;
		  UT_uint16 outlineStyleHash;
		  UT_uint8 flag;
		  X_CheckFileReadElementError(fread(&nonDeletableInfoSize, sizeof(UT_uint16), 1, m_importFile));
		  X_CheckFileReadElementError(fread(&m_currentOutlineHash, sizeof(UT_uint16), 1, m_importFile));
		  X_CheckFileReadElementError(fread(&m_currentListLevel, sizeof(UT_uint8), 1, m_importFile));
		  X_CheckFileReadElementError(fread(&flag, sizeof(UT_uint8), 1, m_importFile));
		  UT_DEBUGMSG(("WordPerfect: LISTS Paragraph Number ON (outlineStyleHash: %i, level: %i, flag: %i)\n", (int)m_currentOutlineHash, (int)m_currentListLevel, (int) flag));
		  // first, find the correct list definition
		  WordPerfectListDefinition *listDefinition = _getListDefinition(m_currentOutlineHash);
		  if( listDefinition == NULL )
		    return UT_ERROR;
		  xxx_UT_DEBUGMSG(("WordPerfect: %i %i\n", listDefinition->getListID(0), listDefinition->getListID(1)));
		  X_CheckWordPerfectError(_updateDocumentListDefinition(listDefinition, m_currentListLevel));
		  if (listDefinition->isLevelNumbered(m_currentListLevel))
		    listDefinition->incrementLevelNumber(m_currentListLevel);
		  m_currentListTag = UT_rand();
		  m_paragraphStyleState = beginNumbering;
	       }	
	     break;
	   case WP_CHARACTER_GROUP_PARAGRAPH_NUMBER_OFF:
	     UT_DEBUGMSG(("WordPerfect: LISTS Paragraph Number OFF\n"));
	     if (m_paragraphStyleState == beginNumbering || m_paragraphStyleState == beginDisplayReferencing)
	       { 
		  m_paragraphStyleState = styleBody;	     
		  X_CheckWordPerfectError(_appendCurrentListProperties());
		  m_numDeferredParagraphBreaks = 0; // just to make sure that the no. of deferred paragraph breaks doesn't continually go down - we only need to compensate once
	       }
	     break;
	   case WP_CHARACTER_GROUP_TABLE_DEFINITION_ON:
	     UT_DEBUGMSG(("WordPerfect: TABLE Definition ON\n"));
	     UT_uint8 numPfxID;

	     // FIXME: The following prefix IDs only exist if the PFX bit is set
	     // in the flags. For now, we just assume it _is_ set.
	     X_CheckFileReadElementError(fread(&numPfxID, sizeof(numPfxID), 1, m_importFile));
	     UT_DEBUGMSG(("WordPerfect: Number of Table PFX IDs: %d\n", numPfxID));
	     for (int i=0; i<numPfxID; i++)
	     {
	        UT_uint16 pfxID;
	        X_CheckFileReadElementError(fread(&pfxID, sizeof(pfxID), 1, m_importFile));
	        // FIXME: handle the differt prefixes
	        // For now, we just skip over them
	     }

	     UT_uint16 sizeOfNonDelData;
	     X_CheckFileReadElementError(fread(&sizeOfNonDelData, sizeof(sizeOfNonDelData), 1, m_importFile));
	     // FIXME: handle all the non-deletable (style) data.
	     // For now, we just skip over it.

	     m_iCurrentTableRow = -1;
	     m_iCurrentTableColumn = -1;
	     X_CheckDocumentError(getDoc()->appendStrux(PTX_SectionTable, NULL));
	     break;
	   case WP_CHARACTER_GROUP_TABLE_DEFINITION_OFF:
	     UT_DEBUGMSG(("WordPerfect: TABLE Definition OFF\n"));
	     break;
	   case WP_CHARACTER_GROUP_TABLE_COLUMN:
	     UT_DEBUGMSG(("WordPerfect: Table Column\n"));
	     // FIXME: handle all the table column data.
	     // For now, we just skip over it.
	     break;
	   default: // something else we don't support yet
	     break;
	  }
     }
   
   X_CheckWordPerfectError(_skipGroup(startPosition, size));
   return UT_OK;
}

// handles a cross reference group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handleCrossReferenceGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a crossreference group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;

   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
   X_CheckWordPerfectError(_skipGroup(startPosition, size));

   return UT_OK;
}

// handles a header/footer group
// (TODO: not implemented, just skips over it)
UT_Error IE_Imp_WordPerfect::_handleHeaderFooterGroup()
{
   UT_DEBUGMSG(("WordPerfect: Handling a header/footer group\n"));
   UT_uint8 subGroup, flags;
   long startPosition;
   UT_uint16 size;
   UT_uint8 numPfxIdRefs;
   UT_uint16 nonDeletableInfoSize;
   UT_uint8 occurence;

   if(!m_undoOn)
   {
	   X_CheckWordPerfectError(_handleVariableGroupHeader(startPosition, subGroup, size, flags));
	   X_CheckFileReadElementError(fread(&numPfxIdRefs, sizeof(UT_uint8), 1, m_importFile));
	   UT_DEBUGMSG(("WordPerfect: Number of Prefix ID References: %d\n", numPfxIdRefs));
	
	   for (int i=0; i<numPfxIdRefs; i++)
	   {
		   UT_uint16 PfxRef;
		   UT_DEBUGMSG(("WordPerfect: Reading Prefix %d...\n", i));
		   X_CheckFileReadElementError(fread(&PfxRef, sizeof(UT_uint16), 1, m_importFile));
		   // TODO: handle the prefix reference here
		   // ...
	   }
	   X_CheckFileReadElementError(fread(&nonDeletableInfoSize, sizeof(UT_uint16), 1, m_importFile));
	   X_CheckFileReadElementError(fread(&occurence, sizeof(UT_uint8), 1, m_importFile));
	   UT_DEBUGMSG(("WordPerfect: Occurence: %d\n", occurence));
   
	   // TODO: handle to different occurences below
	   if (occurence & 0x01)
	   {
		   // does occur on odd pages
	   } else
	   {
		   // does not occur on odd pages
	   }
   
	   if (occurence & 0x02)
	   {
		   // does occur on even pages
	   } else
	   {
		   // does not occur on even pages
	   }
	   
	   if (occurence & 0x04)
	   {
		   // vertical direction (top to bottom - East Asia)
	   } else	
	   {	
		   // horizontal direction (left to right)
	   }
   
	   if (occurence & 0x08)
	   {
		   // use space between headers and footers to display watermark
	   } else
	   {
		   // use full page to display watermark
	   }
   }
   
   X_CheckWordPerfectError(_skipGroup(startPosition, size));

   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_handleExtendedCharacter()
{
   UT_DEBUGMSG(("WordPerfect: Handling an extended character\n"));

   UT_uint8 character, characterSet, closingByte;
   X_CheckFileReadElementError(fread(&character, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&characterSet, sizeof(UT_uint8), 1, m_importFile));

   UT_UCS4Char extendedCharacter;
   
   switch (characterSet) 
     {
      case WP_MULTINATIONAL_CHARACTER_SET:
	extendedCharacter = multinationalMap[character];
	break;
      case WP_PHONETIC_SYMBOL_CHARACTER_SET:
        extendedCharacter = phoneticMap[character];
	break;
      case WP_TYPOGRAPHIC_SYMBOL_CHARACTER_SET:
        extendedCharacter = typographicMap[character];
	break;
      case WP_ICONIC_SYMBOL_CHARACTER_SET:
	extendedCharacter = iconicMap[character];
	break;
      case WP_MATH_SCIENTIFIC_CHARACTER_SET:
	extendedCharacter = mathMap[character];       
	break;
      case WP_MATH_SCIENTIFIC_EXTENDED_CHARACTER_SET:
	extendedCharacter = mathextMap[character];       
	break;
      case WP_GREEK_CHARACTER_SET:
	extendedCharacter = greekMap[character];       
	break;
      case WP_HEBREW_CHARACTER_SET:
	extendedCharacter = hebrewMap[character];       
	break;
      case WP_CYRILLIC_CHARACTER_SET:
	extendedCharacter = cyrillicMap[character];       
	break;
      case WP_JAPANESE_CHARACTER_SET:
	extendedCharacter = japaneseMap[character];       
	break;
      default:
	extendedCharacter = 0; // whitespace
	break;
     }
   
   X_CheckWordPerfectError(_insertCharacter((UT_UCS4Char)extendedCharacter));
   
   // check that the end byte is the extended character flag
   X_CheckFileReadElementError(fread(&closingByte, sizeof(UT_uint8), 1, m_importFile));
   if(closingByte != WP_TOP_EXTENDED_CHARACTER)
     return UT_IE_IMPORTERROR;
       
   return UT_OK;
}


// handles a font face change
// (supposedly, not really actually, we parse a bunch of information but don't do anything with it yet-- abi's font system
// is too fucked at the moment to make it worth bothering with -WL)
UT_Error IE_Imp_WordPerfect::_handleFontFaceChange()
{
   UT_DEBUGMSG(("WordPerfect: Handling a Font Face Change\n"));
   
   UT_uint8 numPIDs;
   UT_uint16 fontDescriptorPID; 
   UT_uint16 nonDeletableInfoSize;
   UT_uint16 oldMatchedPointSize;
   UT_uint16 hash;
   UT_uint16 matchedFontIndex;
   UT_uint16 matchedFontPointSize;
   
   X_CheckFileReadElementError(fread(&numPIDs, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&fontDescriptorPID, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&nonDeletableInfoSize, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&oldMatchedPointSize, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&hash, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&matchedFontIndex, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&matchedFontPointSize, sizeof(UT_uint16), 1, m_importFile));
   
   UT_DEBUGMSG(("WordPerfect: Got this font face change info: (num PIDS: %i, font descriptor PID: %i, old matched point size: %i, hash: %i, matched font index: %i, matched font point size: %i)\n",
		(int) numPIDs, (int) fontDescriptorPID, (int) oldMatchedPointSize, (int) hash, (int) matchedFontIndex, (int) matchedFontPointSize));

   m_textAttributes.m_fontSize = (UT_uint16) rint((double)((((float)matchedFontPointSize)/100.0f)*2.0f)); // fixme: ghastly magic numbers;   
   X_CheckWordPerfectError(_flushText());
   m_bTextPropertiesChanged = true;

   return UT_OK;
}

// handles a font size change
// FIXME: we could be more precise about this..
UT_Error IE_Imp_WordPerfect::_handleFontSizeChange()
{
   UT_DEBUGMSG(("WordPerfect: Handling a Font Size Change\n"));
   
   UT_uint8 numPIDs;
   UT_uint16 oldDesiredDescriptorPID; 
   UT_uint16 nonDeletableInfoSize;
   UT_uint16 desiredPointSize;
   UT_uint16 hash;
   UT_uint16 matchedFontIndex;
   UT_uint16 matchedFontPointSize;
   
   X_CheckFileReadElementError(fread(&numPIDs, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&oldDesiredDescriptorPID, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&nonDeletableInfoSize, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&desiredPointSize, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&hash, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&matchedFontIndex, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&matchedFontPointSize, sizeof(UT_uint16), 1, m_importFile));
   
   UT_DEBUGMSG(("WordPerfect: Got this font size change info: (num PIDS: %i, old typeface PID: %i, desired point size: %i, hash: %i, matched font index: %i, matched font point size: %i)\n",
		(int) numPIDs, (int) oldDesiredDescriptorPID, (int) desiredPointSize, (int) hash, (int) matchedFontIndex, (int) matchedFontPointSize));
   
   m_textAttributes.m_fontSize = (UT_uint16) rint((double)((((float)desiredPointSize)/100.0f)*2.0f)); // fixme: ghastly magic numbers;
   X_CheckWordPerfectError(_flushText());
   m_bTextPropertiesChanged = true;
   
   return UT_OK;
}

// _handleUndo: handles a wordperfect undo group, which defines area of text which are "invalid"
// we basically handle this by skipping over any text which wordperfect deems invalid
UT_Error IE_Imp_WordPerfect::_handleUndo()
{
   // this function isn't very well documented 
   // but this seems to work fine after repeated testing
   UT_DEBUGMSG(("WordPerfect: Handling an undo group\n"));
   long startPosition = ftell(m_importFile);

   int undoType = fgetc(m_importFile);
   X_CheckFileError(undoType);
      
   if(undoType==0 && !m_undoOn)
     {	
	m_undoOn=true;
	UT_DEBUGMSG(("WordPerfect: undo is now ON\n"));
     }
   
   else if(undoType==1 && m_undoOn)
     {	
	m_undoOn=false;
	UT_DEBUGMSG(("WordPerfect: undo is now OFF\n"));
     }

   X_CheckWordPerfectError(_skipGroup(startPosition, WP_UNDO_GROUP_SIZE));
   return UT_OK;
}

// handles a paragraph justification (e.g.: manipulating how a paragraph is positioned)
UT_Error IE_Imp_WordPerfect::_handleParagraphGroupJustification()
{
   UT_DEBUGMSG(("WordPerfect: Handling a paragraph group's justification\n"));
 
   UT_uint16 nonDeletableInfoSize; // we don't really care about this..
   X_CheckFileReadElementError(fread(&nonDeletableInfoSize, sizeof(UT_uint16), 1, m_importFile));
   
   UT_uint8 paragraphJustification;
   X_CheckFileReadElementError(fread(&paragraphJustification, sizeof(UT_uint8), 1, m_importFile));

   switch(paragraphJustification)
     {
      case WP_PARAGRAPH_GROUP_JUSTIFICATION_LEFT:
	m_paragraphProperties.m_justificationMode = WordPerfectParagraphProperties::left;
	break;
      case WP_PARAGRAPH_GROUP_JUSTIFICATION_FULL:
	m_paragraphProperties.m_justificationMode = WordPerfectParagraphProperties::full;
	break;
      case WP_PARAGRAPH_GROUP_JUSTIFICATION_CENTER:
	m_paragraphProperties.m_justificationMode = WordPerfectParagraphProperties::center;
	break;
      case WP_PARAGRAPH_GROUP_JUSTIFICATION_RIGHT:
	m_paragraphProperties.m_justificationMode = WordPerfectParagraphProperties::right;
	break;
      case WP_PARAGRAPH_GROUP_JUSTIFICATION_FULL_ALL_LINES:
	m_paragraphProperties.m_justificationMode = WordPerfectParagraphProperties::fullAllLines;
	break;
      case WP_PARAGRAPH_GROUP_JUSTIFICATION_RESERVED:
	m_paragraphProperties.m_justificationMode = WordPerfectParagraphProperties::reserved;
	break;
     }
   UT_DEBUGMSG(("WordPerfect: Paragraph Justification is now: %i\n", paragraphJustification));
   
   return UT_OK;
}

// _handleOutlineDefine: parses a WordPerfect outline definition, creates an importer-temporary list definition and stores it for later use
// Outline Definitions are used to define "lists" in WordPerfect
UT_Error IE_Imp_WordPerfect::_handleOutlineDefine()
{
   UT_uint8 numPrefixIDs;
   UT_uint16 outlineStylePID;
   UT_uint16 paragraphStylePIDs[WP_NUM_LIST_LEVELS]; // seemingly useless
   UT_uint16 nonDeletableInfoSize;
   UT_uint16 definitionHash;
   UT_uint16 numberingMethods[WP_NUM_LIST_LEVELS];
   UT_uint8 outlineFlags;
   UT_uint8 tabBehaviourFlag;
      
   X_CheckFileReadElementError(fread(&numPrefixIDs, sizeof(UT_uint8), 1, m_importFile));
   UT_DEBUGMSG(("WordPerfect: LISTS: Outline Define 1 (numPrefixIDs: %i)\n", numPrefixIDs));
   X_CheckFileReadElementError(fread(&outlineStylePID, sizeof(UT_uint16), 1, m_importFile));
   for (unsigned int i=0; i<WP_NUM_LIST_LEVELS; i++) // -1 because we've already read one prefix id defn
     X_CheckFileReadElementError(fread(&paragraphStylePIDs[i], sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileSeekError(fseek( m_importFile, (numPrefixIDs-(WP_NUM_LIST_LEVELS+1))*sizeof(UT_uint16), SEEK_CUR)); // skip any wayward prefix packets

   X_CheckFileReadElementError(fread(&nonDeletableInfoSize, sizeof(UT_uint16), 1, m_importFile));
   X_CheckFileReadElementError(fread(&definitionHash, sizeof(UT_uint16), 1, m_importFile)); // this is how we identify the list an element may belong to
   UT_DEBUGMSG(("WordPerfect: LISTS: Outline Define 2\n"));
   for (unsigned int i=0; i<WP_NUM_LIST_LEVELS; i++) 
	X_CheckFileReadElementError(fread(&numberingMethods[i], sizeof(UT_uint16), 1, m_importFile));
   UT_DEBUGMSG(("WordPerfect: LISTS: Outline Define 3\n"));
   X_CheckFileReadElementError(fread(&outlineFlags, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&tabBehaviourFlag, sizeof(UT_uint8), 1, m_importFile));
   UT_DEBUGMSG(("WordPerfect: LISTS: Outline Define 4\n"));
   
   UT_DEBUGMSG(("WordPerfect: Read Outline Define Group (numPrefixIDs: %i, outlineStylePID: %i, nonDeletableInfoSize: %i, definitionHash: %i, outlineFlags: %i, tabBehaviourFlag: %i)\n", (int) numPrefixIDs, (int) outlineStylePID, (int) nonDeletableInfoSize, (int) definitionHash, (int) outlineFlags, (int) tabBehaviourFlag));
   UT_DEBUGMSG(("WordPerfect: Read Outline Define Group (paragraphStylePIDs: %i %i %i %i %i %i %i %i)\n", paragraphStylePIDs[0], paragraphStylePIDs[1], paragraphStylePIDs[2], paragraphStylePIDs[3],
		paragraphStylePIDs[4], paragraphStylePIDs[5], paragraphStylePIDs[6], paragraphStylePIDs[7]));
   UT_DEBUGMSG(("WordPerfect: Read Outline Define Group (numberingMethods: %i %i %i %i %i %i %i %i)\n", numberingMethods[0], numberingMethods[1], numberingMethods[2], numberingMethods[3],
		numberingMethods[4], numberingMethods[5], numberingMethods[6], numberingMethods[7]));
   
   // we're starting a new outline, so reset it, and put the more explicit properties offered by this group into the list definition
   for (UT_uint32 i=0; i<m_listDefinitionList.size(); i++)
     {
	WordPerfectListDefinition *tempListDefinition = (WordPerfectListDefinition *) m_listDefinitionList.getNthItem(i);
	if (tempListDefinition->getOutlineHash() == definitionHash)
	  {
	     UT_DEBUGMSG(("WordPerfect: LISTS: Reusing an old list hash (resetting it though)\n"));
	     tempListDefinition->resetListIDsAndNumbers();
	     tempListDefinition->updateListTypes(numberingMethods);
	     return UT_OK;
	  }
     }
   
   // couldn't find the list definition matching the outline hash. need to define one.
   UT_DEBUGMSG(("WordPerfect: LISTS: Creating a new list definition (on the fly)"));
   WordPerfectListDefinition *listDefinition = new WordPerfectListDefinition(definitionHash);
   listDefinition->updateListTypes(numberingMethods);
   m_listDefinitionList.addItem((void *)listDefinition);

   return UT_OK;
}


// _handleVariableGroupHeader: gets the info common to all groups
UT_Error IE_Imp_WordPerfect::_handleVariableGroupHeader(long &startPosition, UT_uint8 &subGroup, UT_uint16 &size, UT_uint8 &flags)
{
   startPosition = ftell(m_importFile);
   
   X_CheckFileReadElementError(fread(&subGroup, sizeof(UT_uint8), 1, m_importFile));
   X_CheckFileReadElementError(fread(&size, sizeof(UT_uint16), 1, m_importFile)); 
   X_CheckFileReadElementError(fread(&flags, sizeof(UT_uint8), 1, m_importFile));
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_skipGroup(long startPosition, UT_uint16 groupSize)
{
   UT_DEBUGMSG(("WordPerfect: Skipping a group (startPosition: %i, groupSize: %i)\n", startPosition, groupSize));
   X_CheckFileSeekError(fseek(m_importFile, (startPosition + groupSize - 1), SEEK_SET));
   
   return UT_OK;
}


// insert the text in the current textbuf to the document, taking its
// style into account
UT_Error IE_Imp_WordPerfect::_flushText()
{
   UT_DEBUGMSG(("WordPerfect: Flushing Text\n"));

   // place any deferred paragraph breaks in now
   while (m_numDeferredParagraphBreaks > 0)
     {
	UT_DEBUGMSG(("WordPerfect: Placing in a deferred paragraph break\n"));
	X_CheckWordPerfectError(_appendCurrentParagraphProperties());
	m_numDeferredParagraphBreaks--;
     }
   
   if(m_textBuf.getLength() > 0) // until we have actual text to flush, we can postpone this operation indefinitely (and we should, because lists can change breaks)
     {	        	
	// append the current paragraph properties, but only when the paragraph properties 
	// have changed or there is no paragraph at all (and there is text to flush)
	if(m_bParagraphChanged || !m_bParagraphExists)
	  {	
	     UT_DEBUGMSG(("WordPerfect: Appending Paragraph Properties\n"));
	     X_CheckWordPerfectError(_appendCurrentParagraphProperties());
	  }
      
	if (m_bTextPropertiesChanged)     
	  X_CheckWordPerfectError(_appendCurrentTextProperties());
	
	X_CheckDocumentError(getDoc()->appendSpan((UT_UCS4Char *)m_textBuf.getPointer(0), m_textBuf.getLength()));
	m_textBuf.truncate(0);
	
	UT_DEBUGMSG(("WordPerfect: Text flushed\n"));
     }
   

   return UT_OK;
}

// insert the text in the current textbuf to the document, taking its
// style into account
UT_Error IE_Imp_WordPerfect::_appendCurrentListProperties()
{
   UT_DEBUGMSG(("WordPerfect: LISTS: Appending Current List Properties (outline hash: %i)\n", m_currentOutlineHash));

   WordPerfectListDefinition *listDefinition = _getListDefinition(m_currentOutlineHash);
   if (listDefinition == NULL)
     return UT_ERROR;
   
   UT_String szListID;
   UT_String szParentID;
   UT_String szLevel;
   UT_String_sprintf(szListID,"%d",listDefinition->getListID(m_currentListLevel));
   if (m_currentListLevel > 0) 
     UT_String_sprintf(szParentID,"%d", listDefinition->getListID((m_currentListLevel-1)));
   else
     UT_String_sprintf(szParentID,"0"); 
   UT_String_sprintf(szLevel,"%d", (m_currentListLevel+1));

   const XML_Char* listAttribs[PT_MAX_ATTRIBUTES*2 + 1];
   UT_uint32 attribsCount=0;
   
   listAttribs[attribsCount++] = PT_LISTID_ATTRIBUTE_NAME;
   listAttribs[attribsCount++] = szListID.c_str();
   listAttribs[attribsCount++] = PT_PARENTID_ATTRIBUTE_NAME;
   listAttribs[attribsCount++] = szParentID.c_str();
   listAttribs[attribsCount++] = PT_LEVEL_ATTRIBUTE_NAME;
   listAttribs[attribsCount++] = szLevel.c_str();

   // Now handle the Abi List properties
   UT_String propBuffer;
   UT_String tempBuffer;
   UT_String_sprintf(tempBuffer,"list-style:%d;", listDefinition->getListType(m_currentListLevel));
   propBuffer += tempBuffer;
   // FIXME: writing the list delimiter is kind of tricky and silly (because wordperfect wants to define
   // it within the document, while abi wants to (sensibly probably) define it in the list definition)
   // (we reset it each time but only for numbered lists)
   if (listDefinition->isLevelNumbered(m_currentListLevel)) 
     {	
	UT_DEBUGMSG(("WordPerfect: Appending this list delim: %s\n", m_rightListDelim.c_str()));
	listDefinition->setListRightDelimText(m_currentListLevel, m_rightListDelim.c_str());
	X_CheckWordPerfectError(_updateDocumentListDefinition(listDefinition, m_currentListLevel));
     }   
   if (listDefinition->getListType(m_currentListLevel) == BULLETED_LIST)
     UT_String_sprintf(tempBuffer, "field-font:Symbol; ");
   else
     UT_String_sprintf(tempBuffer, "field-font:NULL; ");
   propBuffer += tempBuffer;
   UT_String_sprintf(tempBuffer, "start-value:%i; ", listDefinition->getListNumber(m_currentListLevel));
   propBuffer += tempBuffer;
   UT_String_sprintf(tempBuffer, "text-indent:%fin; ", m_paragraphStyleTextIndent); 
   propBuffer += tempBuffer;
   UT_String_sprintf(tempBuffer, "margin-left:%fin", m_paragraphStyleMarginLeft);
   propBuffer += tempBuffer;
   listAttribs[attribsCount++] = PT_PROPS_ATTRIBUTE_NAME;
   listAttribs[attribsCount++] = propBuffer.c_str();
   listAttribs[attribsCount++] = NULL;

   if ( (!m_bInSection) || m_bSectionChanged)
     X_CheckWordPerfectError(_appendSection ());

   X_CheckDocumentError(getDoc()->appendStrux(PTX_Block, listAttribs));   

   UT_DEBUGMSG(("WordPerfect: LISTS - Appended a list attributes section (text-indent: %f, margin-left:%f)\n", m_paragraphStyleTextIndent, m_paragraphStyleMarginLeft));

   // hang text off of a list label
   X_CheckWordPerfectError(_appendCurrentTextProperties());
   getDoc()->appendFmtMark();
   m_currentListTag = 0;
   UT_DEBUGMSG(("WordPerfect: LISTS - Appended a list tag def'n (character props)\n"));
   
   // append a list field label
   const XML_Char* fielddef[3];
   fielddef[0] ="type";
   fielddef[1] = "list_label";
   fielddef[2] = NULL;
   X_CheckDocumentError(getDoc()->appendObject(PTO_Field,fielddef));
   UT_DEBUGMSG(("WordPerfect: LISTS - Appended a field def'n\n"));
      
   X_CheckWordPerfectError(_appendCurrentTextProperties());
   
   m_bParagraphExists = true; // in case we start the document with a list
   m_bParagraphChanged = false; // we already changed the paragraph here, so don't go around saying it hasn't been changed when we flush the text
   
   //m_leftListDelim.clear();
   m_rightListDelim.clear();
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_appendCurrentTextProperties()
{
   UT_DEBUGMSG(("WordPerfect: Appending current text properties\n"));
      
   XML_Char* pProps = "props";
   UT_String propBuffer;
   UT_String tempBuffer;
   
   // bold 418
   propBuffer += "font-weight:";
   if ( m_textAttributes.m_bold )
     propBuffer += "bold" ;
   else
     propBuffer += "normal";

   // italic
   propBuffer += "; font-style:";
   if ( m_textAttributes.m_italics )
     propBuffer += "italic" ;
   else
     propBuffer += "normal";

   // superscript or subscript
   if ( m_textAttributes.m_superScript || m_textAttributes.m_subScript )
   {
	   propBuffer += "; text-position:";
	   if ( m_textAttributes.m_superScript )
		 propBuffer += "superscript" ;
	   else
		 propBuffer += "subscript" ;
   }
   
   // underline & strike-out
   if (m_textAttributes.m_underLine || m_textAttributes.m_strikeOut)
   {
	   propBuffer += "; text-decoration:";
	   if (m_textAttributes.m_underLine)
		 propBuffer += "underline ";
	   if (m_textAttributes.m_strikeOut)
		 propBuffer += "line-through ";
   }
	 
   UT_String_sprintf(tempBuffer, "; font-size:%spt", std_size_string((float)m_textAttributes.m_fontSize));
   propBuffer += tempBuffer;
   
   if(m_currentListTag != 0)
     {
	// List Tag to hang lists off
	UT_String_sprintf(tempBuffer, "; list-tag:%d", m_currentListTag);
	propBuffer += tempBuffer;
     }
   
   UT_DEBUGMSG(("Appending Format: %s\n", propBuffer.c_str()));
   const XML_Char* propsArray[5];

   propsArray[0] = pProps;
   propsArray[1] = propBuffer.c_str();
   propsArray[2] = NULL;
   if (m_bPutativeListHasParagraphNumber) 
     {
	propsArray[2] ="type";
	propsArray[3] = "list_label";
	propsArray[4] = NULL;
     }	

   X_CheckDocumentError(getDoc()->appendFmt(propsArray));

   m_bTextPropertiesChanged = false;
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_appendCurrentParagraphProperties()
{
   UT_String propBuffer;

   propBuffer += "text-align:";
   switch( m_paragraphProperties.m_justificationMode )
     {
      case WordPerfectParagraphProperties::left:
	propBuffer += "left";
	break;
      case WordPerfectParagraphProperties::right:
	propBuffer += "right";
	break;
      case WordPerfectParagraphProperties::center:
	propBuffer += "center";
	break;
      case WordPerfectParagraphProperties::full:  	// either normal justification or something I don't understand yet. same deal.
      case WordPerfectParagraphProperties::fullAllLines:
      case WordPerfectParagraphProperties::reserved:
	propBuffer += "justify";
	break;
     }
   
   if ( (!m_bInSection) || m_bSectionChanged)
   {
      X_CheckWordPerfectError(_appendSection ());
   }
   
   UT_DEBUGMSG(("WordPerfect: Appending Paragraph Properties: %s\n", propBuffer.c_str()));
   const XML_Char* propsArray[3];
   propsArray[0] = "props";
   propsArray[1] = propBuffer.c_str();
   propsArray[2] = NULL;
   X_CheckDocumentError(getDoc()->appendStrux(PTX_Block, propsArray));   

   m_bParagraphChanged = false;
   m_bParagraphExists = true; // _never_ set m_bParagraphExists to false again!
   m_bParagraphInSection = true;
   
   return UT_OK;
}

UT_Error IE_Imp_WordPerfect::_appendSection()
{
   UT_DEBUGMSG(("WordPerfect: Appending section\n"));

   XML_Char * propsArray[3];
   UT_String myProps ( "" ) ;
   propsArray[0] = "props";
   propsArray[2] = NULL ;

   setlocale(LC_NUMERIC, "C");
	
   if (m_bLeftMarginSet)
   {
      UT_DEBUGMSG(("WordPerfect: Appending left margin\n"));
      myProps += UT_String_sprintf("page-margin-left:%4.4fin", m_leftMargin);
   }
  
   if (m_bRightMarginSet)
   {
      UT_DEBUGMSG(("WordPerfect: Appending right margin\n"));

      if ( myProps.size () )
         myProps += "; " ;
	
      myProps += UT_String_sprintf("page-margin-right:%4.4fin", m_rightMargin);
   }
  
   if (m_bColumnsSet)
   {
      UT_DEBUGMSG(("Appending column definition\n"));

      if ( myProps.size () )
	     myProps += "; " ;

      myProps += UT_String_sprintf("columns:%d", m_numberOfColumns);
   }
  
   setlocale(LC_NUMERIC, NULL);
   propsArray[1] = (XML_Char*)myProps.c_str() ;

   if (myProps.size() == 0)
   {
 	  X_CheckDocumentError(getDoc()->appendStrux(PTX_Section, NULL));
   }
   else
   {
 	  X_CheckDocumentError(getDoc()->appendStrux(PTX_Section, (const XML_Char**)propsArray));
   }

   m_bInSection = true;
   m_bSectionChanged = false;
   m_bParagraphInSection = false;
   return UT_OK;
}

WordPerfectListDefinition * IE_Imp_WordPerfect::_getListDefinition(UT_uint16 outlineHash)
{
  for (UT_uint32 i=0; i<m_listDefinitionList.size(); i++)
     {
	WordPerfectListDefinition *tempListDefinition = (WordPerfectListDefinition *) m_listDefinitionList.getNthItem( i );
	if( tempListDefinition->getOutlineHash() == outlineHash )
	  {
	     return tempListDefinition;
	  }
     }
   
   return NULL;	
}

UT_Error IE_Imp_WordPerfect::_updateDocumentListDefinition(WordPerfectListDefinition *listDefinition, int level)
{
   // add a list definition to the current document, if necessary
   if (listDefinition->getListID(level) == 0)
     listDefinition->setListID(level, UT_rand());
	     
   // finally, set the document's list identification info..
   // FIXME: AbiWord doesn't support different types of lists being appended to their parents.. so we just have to stick with what level 0 provides
   int startingNumber;
   if (listDefinition->getListType(0) == BULLETED_LIST) // REPLACE WITH (WHEN FIXED IN ABI): if (listDefinition->getListType(level) == BULLETED_LIST)
     startingNumber = 0;
   else
     startingNumber = 1;
   fl_AutoNum * pAuto = getDoc()->getListByID(listDefinition->getListID(level));
   // not in document yet, we should create a list for it
   if (pAuto == NULL) 
     {	
	if (level > 0) 
	  {	
	     // REPLACE WITH (WHEN FIXED IN ABI): pAuto = new fl_AutoNum(listDefinition->getListID(level), listDefinition->getListID((level-1)), listDefinition->getListType(level), startingNumber, (XML_Char *)"%L", ".", getDoc());
	     pAuto = new fl_AutoNum(listDefinition->getListID(level), listDefinition->getListID((level-1)), listDefinition->getListType(0), startingNumber, (XML_Char *)listDefinition->getListDelim(level).c_str(), ".", getDoc());
	  }   
	else
	  pAuto = new fl_AutoNum(listDefinition->getListID(level), 0, listDefinition->getListType(level), startingNumber, (XML_Char *)listDefinition->getListDelim(level).c_str(), ".", getDoc());
	
	getDoc()->addList(pAuto);
     }
   // we should update what we have
   else 
     {
	
	// ADD (WHEN FIXED IN ABI): pAuto->setListType(listDefinition->getListType(level));
	pAuto->setStartValue(startingNumber);
	pAuto->setDelim((XML_Char *)listDefinition->getListDelim(level).c_str());
     }
   
   pAuto->fixHierarchy();
   
   return UT_OK;
}
