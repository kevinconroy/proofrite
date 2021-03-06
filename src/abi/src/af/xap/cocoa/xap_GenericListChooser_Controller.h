/* AbiWord
 * Copyright (C) 2002 Hubert Figuiere
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


/* XAP_GenericListChooser_Controller */

#import <Cocoa/Cocoa.h>

@interface XAP_GenericListChooser_Controller : NSWindowController
{
    IBOutlet NSButton *m_cancelBtn;
    IBOutlet NSBox *m_enclosingBox;
    IBOutlet NSTableView *m_listTable;
    IBOutlet NSButton *m_okBtn;
}
+ (XAP_GenericListChooser_Controller *)loadFromNib;
- (IBAction)cancelClicked:(id)sender;
- (IBAction)listClicked:(id)sender;
- (IBAction)okClicked:(id)sender;
@end
