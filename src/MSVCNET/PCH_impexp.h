#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>

#include "ut_types.h"
#include "ut_assert.h"
#include "ut_base64.h"
#include "ut_debugmsg.h"
#include "ut_bytebuf.h"
#include "ut_growbuf.h"
#include "ut_hash.h"
#include "ut_iconv.h"
#include "ut_stack.h"
#include "ut_string.h"
#include "ut_string_class.h"
#include "ut_units.h"
#include "ut_vector.h"
#include "ut_wctomb.h"
#include "ut_xml.h"

#include "expat.h"

#include "fl_AutoNum.h"
#include "fp_PageSize.h"

#include "pd_Document.h"
#include "pd_Style.h"
#include "pt_Types.h"
#include "pp_AttrProp.h"
#include "px_ChangeRecord.h"
#include "px_CR_Object.h"
#include "px_CR_Span.h"
#include "px_CR_Strux.h"

#include "ie_types.h"
#include "ie_imp.h"
#include "ie_exp.h"

#include "xap_App.h"
#include "xap_EncodingManager.h"

#ifdef ENABLE_PLUGINS
#include "xap_Module.h"
#endif

#include "ap_Prefs.h"
