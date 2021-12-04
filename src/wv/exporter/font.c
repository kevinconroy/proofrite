#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "wvexporter-priv.h"

void
wvPutFONTSIGNATURE (wvFONTSIGNATURE * fs, wvStream * fd)
{
    int i;
    for (i = 0; i < 4; i++)
	write_32ubit (fd, fs->fsUsb[i]);
    for (i = 0; i < 2; i++)
	write_32ubit (fd, fs->fsCsb[i]);
}

void
wvPutPANOSE (wvPANOSE * item, wvStream * fd)
{
    write_8ubit (fd, item->bFamilyType);
    write_8ubit (fd, item->bSerifStyle);
    write_8ubit (fd, item->bWeight);
    write_8ubit (fd, item->bProportion);
    write_8ubit (fd, item->bContrast);
    write_8ubit (fd, item->bStrokeVariation);
    write_8ubit (fd, item->bArmStyle);
    write_8ubit (fd, item->bLetterform);
    write_8ubit (fd, item->bMidline);
    write_8ubit (fd, item->bXHeight);
}
