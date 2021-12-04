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

#include "xap_App.h"
#include "xap_Win32App.h"
#include "xap_Win32FrameImpl.h"

#include "xap_Strings.h"
#include "xap_Dialog_Id.h"
#include "xap_DialogFactory.h"

#include "xap_Win32Resources.rc2"
