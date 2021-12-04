#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <conio.h>
#include "exedata.h"
#include "exehead/fileform.h"
#include "util.h"
#include "strlist.h"

int g_dopause=0;
extern int g_display_errors;
extern FILE *g_output;


void dopause(void)
{
  if (g_dopause)
  {
    if (g_display_errors) fprintf(g_output,"MakeNSIS done - hit enter to close...");
    fflush(stdout);
    int a;
    while ((a=_getch()) != '\r' && a != 27/*esc*/);
  }
}

BOOL get_addr_of_res(unsigned char*header_data_new, 
#ifdef NSIS_CONFIG_COMPONENTPAGE
                     int*enabled_bitmap_offset,int*disabled_bitmap_offset,
#endif
                     int*icon_offset)
{

IMAGE_DOS_HEADER *dos_head = (IMAGE_DOS_HEADER*)header_data_new;
  
  typedef struct
      {
          DWORD signature; // "PE"
          IMAGE_FILE_HEADER _head; // file head
          IMAGE_OPTIONAL_HEADER opt_head;
		      IMAGE_SECTION_HEADER section_header[1];
      } PE_HEAD;

  typedef struct _img_dir_new {
	  IMAGE_RESOURCE_DIRECTORY img_dir;
	  IMAGE_RESOURCE_DIRECTORY_ENTRY DirectoryEntries[1];
  } IMAGE_RESOURCE_DIRECTORY_NEW;
  
  PE_HEAD *header = (PE_HEAD *)((char *)dos_head + dos_head->e_lfanew);

  int i=0;
  DWORD ResourceVirtualAddress = header->opt_head.DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress;
  DWORD ResourceRawAddress;
  
  while ( header->section_header[i].VirtualAddress != ResourceVirtualAddress && i<header->_head.NumberOfSections)i++;
  
  if (header->section_header[i].VirtualAddress != ResourceVirtualAddress)
  {
	  if (g_display_errors) fprintf(g_output,"Internal compiler error #12345: resource section missing\n");
	  return FALSE;
  }  

  ResourceRawAddress=header->section_header[i].PointerToRawData;
//  fprintf(g_output,"Resource Directory\n\tVirtualAddress: %xh..\n", ResourceVirtualAddress);
//  fprintf(g_output,"\tPointerToRawData: %xh..\n", ResourceRawAddress);
  
  // for convenience get ptr to initial resource dir..
  // (PointerToRawData is file based offset)
  
  IMAGE_RESOURCE_DIRECTORY_NEW *res_dir = (IMAGE_RESOURCE_DIRECTORY_NEW *)(header_data_new+header->section_header[i].PointerToRawData);
  
  // really a recursive function should be used to process these directories,
  // but as it is only simple, no need (I wanted to keep this all inline).
  IMAGE_RESOURCE_DIRECTORY_NEW *sub_dir;

  // note to save time, we [I] dont bother about named entries. Thus 
  // a sure way to make sure your new resources wont break the 
  // compile, use named entries :)

  i = (int)res_dir->img_dir.NumberOfNamedEntries;
 // fprintf(g_output,"\tNumber of entries: %u\n", res_dir->img_dir.NumberOfNamedEntries+res_dir->img_dir.NumberOfIdEntries);

  while (i<res_dir->img_dir.NumberOfNamedEntries+res_dir->img_dir.NumberOfIdEntries)
  {
	  if (res_dir->DirectoryEntries[i].DataIsDirectory && res_dir->DirectoryEntries[i].Id==3)
	  {
		  // found icon directory
		  sub_dir = (IMAGE_RESOURCE_DIRECTORY_NEW *)((char*)res_dir + res_dir->DirectoryEntries[i].OffsetToDirectory);
		  // look for icon
	  
		  if (!sub_dir->DirectoryEntries[0].DataIsDirectory) // ???
		  {
			  if (g_display_errors) fprintf(g_output,"Could not find icon!\n");
			  return FALSE;
		  }

		  sub_dir = (IMAGE_RESOURCE_DIRECTORY_NEW *)((char*)res_dir + sub_dir->DirectoryEntries[0].OffsetToDirectory);

		  // get first

		  if (sub_dir->DirectoryEntries[0].DataIsDirectory) // ???
		  {
			  if (g_display_errors) fprintf(g_output,"Could not find icon!\n");
			  return FALSE;
		  }

		  // found first icon
		  
		  IMAGE_RESOURCE_DATA_ENTRY *id;
		  id = (IMAGE_RESOURCE_DATA_ENTRY *)((char*)res_dir+sub_dir->DirectoryEntries[0].OffsetToData);
		  
//		   fprintf(g_output,"\tfound icon:\n");
		   *icon_offset = id->OffsetToData-ResourceVirtualAddress+ResourceRawAddress;		  
	//	   fprintf(g_output,"\t\tOffset: %xh\n", *icon_offset);
		//   fprintf(g_output,"\t\tSize: %xh\n", id->Size);
	  }
	  else if (res_dir->DirectoryEntries[i].DataIsDirectory && res_dir->DirectoryEntries[i].Id==2)
	  {
		  // bitmap
		  sub_dir = (IMAGE_RESOURCE_DIRECTORY_NEW *)((char*)res_dir + res_dir->DirectoryEntries[i].OffsetToDirectory);
		  // look for bmp
	  
		  if (!sub_dir->DirectoryEntries[0].DataIsDirectory) // ???
		  {
			  if (g_display_errors) fprintf(g_output,"Could not find bitmap!\n");
			  return FALSE;
		  }

		  sub_dir = (IMAGE_RESOURCE_DIRECTORY_NEW *)((char*)res_dir + sub_dir->DirectoryEntries[0].OffsetToDirectory);

		  // get first

		  if (sub_dir->DirectoryEntries[0].DataIsDirectory) // ???
		  {
			  if (g_display_errors) fprintf(g_output,"Could not find bitmap!\n");
			  return FALSE;
		  }

		  // found first bmp
		  
		  IMAGE_RESOURCE_DATA_ENTRY *id;
		  id = (IMAGE_RESOURCE_DATA_ENTRY *)((char*)res_dir+sub_dir->DirectoryEntries[0].OffsetToData);
		  
		 // fprintf(g_output,"\tfound bitmap1:\n");
#ifdef NSIS_CONFIG_COMPONENTPAGE
		  *enabled_bitmap_offset = id->OffsetToData-ResourceVirtualAddress+ResourceRawAddress;		  
#endif
		//  fprintf(g_output,"\t\tOffset: %xh\n", *enabled_bitmap_offset);
		 // fprintf(g_output,"\t\tSize: %xh\n", id->Size);
		  
		  // look for bmp again
		  sub_dir = (IMAGE_RESOURCE_DIRECTORY_NEW *)((char*)res_dir + res_dir->DirectoryEntries[i].OffsetToDirectory);
		  if (!sub_dir->DirectoryEntries[1].DataIsDirectory) // ???
		  {
			  if (g_display_errors) fprintf(g_output,"Could not find bitmap!\n");
			  return FALSE;
		  }
		  sub_dir = (IMAGE_RESOURCE_DIRECTORY_NEW *)((char*)res_dir + sub_dir->DirectoryEntries[1].OffsetToDirectory);

		  id = (IMAGE_RESOURCE_DATA_ENTRY *)((char*)res_dir+sub_dir->DirectoryEntries[0].OffsetToData);
		 // fprintf(g_output,"\tfound bitmap2:\n");
#ifdef NSIS_CONFIG_COMPONENTPAGE
		  *disabled_bitmap_offset = id->OffsetToData-ResourceVirtualAddress+ResourceRawAddress;
#endif
		//  fprintf(g_output,"\t\tOffset: %xh\n", *disabled_bitmap_offset);
		 // fprintf(g_output,"\t\tSize: %xh\n", id->Size);

	  }

	  i++;
  }

#ifdef NSIS_CONFIG_COMPONENTPAGE
  *enabled_bitmap_offset -= BMP_HDRSKIP;
  *disabled_bitmap_offset -= BMP_HDRSKIP;
  
  *enabled_bitmap_offset += 6;
  *disabled_bitmap_offset += 6;
#endif

  *icon_offset -= ICO_HDRSKIP;
  
  return TRUE;

}


int find_data_offset(char *hdr, int hdr_len, char *srch, int startoffs, int srchlen)
{
  int offs=0;
  hdr_len-=srchlen;
  while (hdr_len>=0 && memcmp(hdr+offs+startoffs,srch+startoffs,srchlen-startoffs))
  {
    offs++;
    hdr_len--;
  }
  if (hdr_len<0)
  {
    if (g_display_errors) fprintf(g_output,"find_data_offset: error searching data -- failing!\n");
    return -1;
  }
  return offs;
}

// will update out+ICO_HDRSKIP with a 766-ICO_HDRSKIP bytes of 32x32x16 icon
int replace_icon(char *out, char *filename)
{
  FILE *fp=fopen(filename,"rb");
  if (!fp)
  {
    if (g_display_errors) fprintf(g_output,"replace_icon: error: error opening file \"%s\" -- failing!\n",filename);
    return -1;
  }
  if (icondata_size == 766) // 32x32x16 icon
  {
    char obuf[766];
    int success=0;

    if (!fgetc(fp) && !fgetc(fp) && fgetc(fp)==1 && !fgetc(fp))
    {
      int num_images=fgetc(fp);
      num_images|=fgetc(fp)<<8;
      int x;
      for (x = 0; x < num_images; x++)
      {
        fseek(fp,6+x*16,SEEK_SET);
        int w=fgetc(fp);
        int h=fgetc(fp);
        int colors=fgetc(fp);
        int res=fgetc(fp);
        int planes=fgetc(fp); planes|=fgetc(fp)<<8;
        int bitcnt=fgetc(fp); bitcnt|=fgetc(fp)<<8;
        int size=fgetc(fp); size|=fgetc(fp)<<8; size|=fgetc(fp)<<16; size|=fgetc(fp)<<24;
        int offs=fgetc(fp); offs|=fgetc(fp)<<8; offs|=fgetc(fp)<<16; offs|=fgetc(fp)<<24;
        if (w == 32 && h == 32 && ((planes == 1 && bitcnt == 4) || colors == 16) && size <= 766-6-16) 
        {
          fseek(fp,offs,SEEK_SET);
          if (fgetc(fp) == 40 && !fgetc(fp) && !fgetc(fp) && !fgetc(fp))
          {
            memset(obuf,0,sizeof(obuf));
            obuf[2]=1;
            obuf[4]=1;
            fseek(fp,6+x*16,SEEK_SET);
            fread(obuf+6,1,12,fp);
            obuf[6+12]=6+16;
            fseek(fp,offs,SEEK_SET);
            fread(obuf+6+16,1,size,fp);
            success=1;
            break;
          }
        }
      }
    }
  
    fclose(fp);
    if (!success)
    {
      if (g_display_errors) fprintf(g_output,"replace_icon: error: icon file \"%s\" has no 32x32x16 icon -- failing!\n",filename);
      return 1;
    }
    else
      memcpy(out+ICO_HDRSKIP,obuf+ICO_HDRSKIP,766-ICO_HDRSKIP);
  }
  else // if using another icon, blindly read in new icon.
  {
    if (g_display_errors) fprintf(g_output,"replace_icon: using non-32x32x16 hackish mode, hopefully it will work!\n");
    fseek(fp,0,SEEK_END);
    int len=ftell(fp);
    if (len != icondata_size)
    {
      if (g_display_errors) fprintf(g_output,"replace_icon: error: icon file is %d bytes, needs to be %d bytes\n",len,icondata_size);
      return 1;
    }
    fseek(fp,ICO_HDRSKIP,SEEK_SET);
    fread(out+ICO_HDRSKIP,1,icondata_size-ICO_HDRSKIP,fp);
    fclose(fp);
  }
  return 0;
}


int replace_bitmap(char *out, char *filename)
{

  static unsigned char header_4bpp[54] = {	
	0x42, 0x4d, 0x66, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00,
	0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x14, 0x00,
	0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xc4, 0x0e,
	0x00, 0x00, 0xc4, 0x0e, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	// note: input file must be 16 colors;
	//		 can be any width and height, though

	HANDLE			hbmp;
	unsigned char	header[54];
	unsigned char	colors[64];

	FILE *fIn = fopen(filename, "rb");
	if (!fIn) 
  {
    if (g_display_errors) fprintf(g_output,"replace_bitmap: error: bitmap file not found \"%s\" -- failing!\n",filename);
		return 1;
  }

	fread(header, 54, 1, fIn);	// read the header (ignore)
	//int w = header[18] + header[19]*256;
	//int h = header[22] + header[23]*256;
	//int bpp = header[28];
	fread(colors, 64, 1, fIn);	// read the colors
	fclose(fIn);
	
	hbmp = LoadImage(NULL, filename, IMAGE_BITMAP, 20, 20, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if (!hbmp) 
	{
    if (g_display_errors) fprintf(g_output,"replace_bitmap: error: invalid bitmap file \"%s\" -- failing!\n",filename);
		return 1;
	}

	BITMAP bm;
	GetObject(hbmp, sizeof(bm), (LPSTR)&bm);
	int w = bm.bmWidth;
	int h = bm.bmHeight;
	int bpp = bm.bmBitsPixel;

	if (w == 20 && h == 20 && bpp == 4 && bm.bmWidthBytes*bm.bmHeight + 64 + 54 <= 358) 
	{
	  // update & write header
	  header_4bpp[18] = w % 256;
	  header_4bpp[19] = w / 256;
	  header_4bpp[22] = h % 256;
	  header_4bpp[23] = h / 256;

    char obuf[358];

    memcpy(obuf,header_4bpp,54);
    memcpy(obuf+54,colors,64);
	  
    bm.bmWidthBytes+=3;
    bm.bmWidthBytes&=~3;

    memcpy(obuf+54+64,bm.bmBits,bm.bmWidthBytes*bm.bmHeight);
    memcpy(out+BMP_HDRSKIP,obuf+BMP_HDRSKIP,358-BMP_HDRSKIP);
  }
  else
  {
    DeleteObject(hbmp);
    if (g_display_errors) fprintf(g_output,"replace_bitmap: error: bitmap error in \"%s\" -- failing!\n",filename);
    return 1;
  }
  DeleteObject(hbmp);
	
  return 0;
}
