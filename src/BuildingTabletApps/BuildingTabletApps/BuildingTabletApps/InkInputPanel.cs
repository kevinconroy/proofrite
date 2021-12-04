////////////////////////////////////////////////////////////////////
//
// InkInputPanel.cs
//
// (c) 2002 Microsoft Press
// by Rob Jarrett
//
// This control helps reduce flicker when ink changes (e.g. added
// or deleted) by buffering painting.
//
////////////////////////////////////////////////////////////////////

using System;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Ink;

namespace MSPress.BuildingTabletApps
{
    public class InkInputPanel : Panel
    {
        public InkInputPanel()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.DoubleBuffer, true);
        }
    }
}
