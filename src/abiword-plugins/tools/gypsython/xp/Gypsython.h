/* GypsyPlugin
 * Copyright (C) 2002 Mauro Colorio
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

#include "xap_Module.h"
#include "xap_App.h"
#include "xap_Frame.h"
#include "fv_View.h"
#include "ap_Menu_Id.h"
#include "ev_Menu_Actions.h"
#include "ev_Menu.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Labels.h"
#include "ev_EditMethod.h"
#include "xap_Menu_Layouts.h"
#include "ut_string_class.h"
#include "ut_path.h"

#include "xap_Dialog_Id.h"
#include "xap_DialogFactory.h"
#include "xap_Dlg_FileOpenSaveAs.h"
#include "xap_Dlg_Language.h"
#include "xap_Frame.h"

#include <python2.2/Python.h>
 
 
 
#ifndef PLUGIN_GYPSYTHON_H
#define PLUGIN_GYPSYTHON_H
 
 class Gypsython
{
 public:
  Gypsython(void);
  virtual                  ~Gypsython(void);


  bool insertText(char * text);
  bool setPaperColor(char * color);
  bool editHeader();
  bool editFooter();
  bool editBody();
  XAP_Frame * openFile(char * filename);

  bool RunModule(char * modulename);
  bool AskScriptFilename();
  //	bool RunPythonfunction(PyObject * pFunction);
  //	bool Python_invoke(AV_View * v, EV_EditMethodCallData * d);
  bool DoCommand();
  
 private:
  PD_Document * m_pCurDoc;
  AV_View *                m_pCurView;
  FL_DocLayout *           m_pLayout;
  XAP_App *                m_pApp;
  XAP_Frame * 		   m_pFrame;	
  char *                   m_sModulePath;
};

#endif /* PLUGIN_GYPSYTHON_H */
