/*
    Copyright (C) 2002  Christian Biesinger <cbiesinger@web.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 */
#include "ms-ole.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	MsOle* ole;
	MsOleStream* s;
	MsOleStat stat;
	MsOleErr err;
	char* data;
	if (argc < 2) {
		printf("Usage: %s filename [streamname]\n", argv[0]);
		return 1;
	}
	err = ms_ole_open(&ole, argv[1]);
	if (err != MS_OLE_ERR_OK) {
		printf("error %i opening file %s\n", err, argv[1]);
		return 1;
	}
	if (argc == 2) {
		char **dirNames;
		char **p;
		err = ms_ole_directory(&dirNames, ole, "/");
		if (err != MS_OLE_ERR_OK) {
			printf("error %i opening directory\n", err);
			ms_ole_destroy(&ole);
			return 1;
		}
		for (p = dirNames; *p; p++) {
			MsOleStat s;
			err = ms_ole_stat(&s, ole, "/", *p);
			if (err == MS_OLE_ERR_OK)
				printf("%s:\tType = %i\tSize = %i\n", *p, s.type, s.size);
			else
				printf("%s:\tstat failed\n", *p);
		}
		return 0;

	}
	ms_ole_stat(&stat, ole, "/", argv[2]);
	data = (char*)malloc(stat.size);
	if (!data) {
		printf("Out of memory\n");
		ms_ole_destroy(&ole);
		return 1;
	}
	err = ms_ole_stream_open(&s, ole, "/", argv[2], 'r');
	if (err != MS_OLE_ERR_OK) {
		printf("err %i opening stream %s\n", err, argv[2]);
		ms_ole_destroy(&ole);
		return 1;
	}
	ms_ole_stream_read_copy(s, (guint8*)data, stat.size);
	fwrite(data, stat.size, 1, stdout);
	ms_ole_stream_close(&s);
	ms_ole_destroy(&ole);
	return 0;
}
