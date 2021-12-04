#include "exedata.h"

#ifdef _DEBUG
#ifdef NSIS_CONFIG_COMPONENTPAGE
#include "exehead/bitmap1.h"
#include "exehead/bitmap2.h"
#endif
#include "exehead/icon.h"
#include "exehead/unicon.h"
#include "exehead/exehead.h"
static char pad[511]; // padding for if exehead&511
int exeheader_size = (sizeof(header_data)+511)&~511;
#else
#ifdef NSIS_CONFIG_COMPONENTPAGE
#include "exehead/bitmap1.h"
#include "exehead/bitmap2.h"
#endif
#include "exehead/icon.h"
#include "exehead/unicon.h"
#include "exehead/exehead.h"
int exeheader_size = sizeof(header_data);
#endif

int icondata_size=sizeof(icon_data);
int unicondata_size=sizeof(unicon_data);
