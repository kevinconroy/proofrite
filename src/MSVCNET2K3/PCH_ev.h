#define WIN32_LEAN_AND_MEAN
#define NOSERVICE
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "ut_types.h"
#include "ut_assert.h"
#include "ut_string.h"
#include "ut_stack.h"
#include "ut_debugmsg.h"
#include "ut_growbuf.h"
#include "ut_misc.h"
#include "ut_vector.h"
#include "ut_xml.h"

#include "ev_Win32Menu.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Actions.h"
#include "ev_Menu_Labels.h"
#include "ev_EditEventMapper.h"

#include "xap_Types.h"
#include "xap_Win32App.h"
#include "xap_Win32FrameImpl.h"
