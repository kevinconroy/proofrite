/* AbiWord
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

#include <string.h>
#include "ut_string.h"

#include "ie_impGraphic_PNG.h"
#include "fg_GraphicRaster.h"

UT_Confidence_t IE_ImpGraphicPNG_Sniffer::recognizeSuffix(const char * szSuffix)
{
	if (UT_stricmp(szSuffix,".png") == 0)
	  return UT_CONFIDENCE_PERFECT;
	return UT_CONFIDENCE_ZILCH;
}

UT_Confidence_t IE_ImpGraphicPNG_Sniffer::recognizeContents(const char * szBuf, UT_uint32 iNumbytes)
{
   	char str1[10] = "\211PNG";
   	char str2[10] = "<89>PNG";
   
   	if ( !(strncmp(szBuf, str1, 4)) || !(strncmp(szBuf, str2, 6)) )
	  return UT_CONFIDENCE_PERFECT;
	return UT_CONFIDENCE_ZILCH;
}

bool IE_ImpGraphicPNG_Sniffer::getDlgLabels(const char ** pszDesc,
									   const char ** pszSuffixList,
									   IEGraphicFileType * ft)
{
	*pszDesc = "Portable Network Graphics (.png)";
	*pszSuffixList = "*.png";
	*ft = getType ();
	return true;
}

UT_Error IE_ImpGraphicPNG_Sniffer::constructImporter(IE_ImpGraphic **ppieg)
{
	*ppieg = new IE_ImpGraphic_PNG();
	if (*ppieg == NULL)
	  return UT_IE_NOMEMORY;

	return UT_OK;
}

//  This actually creates our FG_Graphic object for a PNG
UT_Error IE_ImpGraphic_PNG::importGraphic(UT_ByteBuf* pBB, 
										  FG_Graphic ** ppfg)
{
	FG_GraphicRaster *pFGR;

	pFGR = new FG_GraphicRaster();
	if(pFGR == NULL)
		return UT_IE_NOMEMORY;

	if(!pFGR->setRaster_PNG(pBB)) {
		DELETEP(pFGR);
		
		return UT_IE_FAKETYPE;
	}

	*ppfg = (FG_Graphic *) pFGR;
	return UT_OK;
}

UT_Error IE_ImpGraphic_PNG::convertGraphic(UT_ByteBuf* pBB,
					   UT_ByteBuf** ppBB)
{
   	if (!ppBB) return UT_ERROR;
   	*ppBB = pBB;
   	return UT_OK;
}
