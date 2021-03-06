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

#import <Cocoa/Cocoa.h>

#import "XAP_GenericListChooser_Controller.h"

@implementation XAP_GenericListChooser_Controller

+ (XAP_GenericListChooser_Controller *)loadFromNib
{
	XAP_GenericListChooser_Controller * dlg = [[XAP_GenericListChooser_Controller alloc] initWithWindowNibName:@"xap_GenericListChooser_Controller"];
	return [dlg autorelease];
}


- (IBAction)cancelClicked:(id)sender
{
}

- (IBAction)listClicked:(id)sender
{
}

- (IBAction)okClicked:(id)sender
{
}

@end
