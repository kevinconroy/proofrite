////////////////////////////////////////////////////////////////////
//
// InkEx.cs
//
// (c) 2002 Microsoft Press
// by Rob Jarrett
//
// This class implements some extra functionality for Ink objects.
//
////////////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Ink;

namespace MSPress.BuildingTabletApps
{
    public class InkEx
    {
        // Add strokes to an ink object, returning a Strokes collection
        public static Strokes AddStrokesAtRectangle(Ink ink,
            Strokes strokes, Rectangle destinationRectangle)
        {
            // Obtain a data object containing the strokes we want to
            // add to the ink object
            IDataObject dataObj = strokes.Ink.ClipboardCopy(
                strokes, InkClipboardFormats.InkSerializedFormat,
                InkClipboardModes.ExtractOnly);

            // Add the strokes to the ink object via a Paste operation
            Strokes strksNew = ink.ClipboardPaste(
                new Point(0,0), dataObj);

            // Scale and translate the strokes as needed
            strksNew.ScaleToRectangle(destinationRectangle);

            return strksNew;
        }
    }
}
