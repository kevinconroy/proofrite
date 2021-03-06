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
/* $Id: xap_Cocoa_NSTableUtils.h,v 1.1.1.1 2003/05/18 17:53:35 kmconroy Exp $ */

#import <Cocoa/Cocoa.h>


@interface XAP_StringListDataSource : NSObject {
	NSMutableArray*		_array;
}

- (id)init;

- (oneway void)dealloc;

- (void)insertString:(NSString*)string atIndex:(int)index;
- (void)addString:(NSString*)string;

/* NSTableDataSource */
- (int)numberOfRowsInTableView:(NSTableView *)tableView;
- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(int)row;
@end
