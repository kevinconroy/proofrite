#ifndef _UTIL_H_
#define _UTIL_H_

// these are the standard pause-before-quit shit.
extern int g_dopause;
extern void dopause(void);

// finds address of resources
BOOL get_addr_of_res(unsigned char*header_data_new, 
#ifdef NSIS_CONFIG_COMPONENTPAGE
                     int*enabled_bitmap_offset,int*disabled_bitmap_offset,
#endif
                     int*icon_offset);

// searches hdr for srch, allowing the first startoffs bytes to differ.
int find_data_offset(char *hdr, int hdr_len, char *srch, int startoffs, int srchlen);

#ifdef NSIS_CONFIG_COMPONENTPAGE
int replace_bitmap(char *out, char *filename); // repalces out with a 358 byte image of a 20x20x16 bitmap from filename.
#endif
int replace_icon(char *out, char *filename); // replaces out with a icondata_size byte image of an icon. if icon size is 766, it is loaded from the 32x32x16 color portion of filename.

#endif //_UTIL_H_