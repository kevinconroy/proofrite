////////////////////////////////////////////////////////////////////
//
// InkControl.cs
//
// (c) 2002 Microsoft Press
// by Rob Jarrett
//
// This control encapsulates common functionality augmenting the
// InkOverlay class.
//
////////////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Drawing;
using System.Reflection;
using System.Windows.Forms;
using Microsoft.Ink;

namespace MSPress.BuildingTabletApps
{
    public class InkControl : UserControl
    {
        enum InkControlEraserSize
        {
            Small,
            Medium,
            Large
        }
        private InkInputPanel   pnlInput;
        private Button          btnColor;
        private ComboBox        cbxEditMode;
        private ComboBox        cbxEraserMode;
        private ComboBox        cbxEraserSize;
        private InkOverlay      inkOverlay;

        public InkControl()
        {
            SuspendLayout();

            // Create and place all of our controls
            pnlInput = new InkInputPanel();
            pnlInput.BorderStyle = BorderStyle.Fixed3D;
            pnlInput.BackColor = Color.White;
            pnlInput.Location = new Point(0, 0);
            pnlInput.Size = new Size(352, 192);

            btnColor = new Button();
            btnColor.Location = new Point(0, 196);
            btnColor.Size = new Size(60, 20);
            btnColor.Text = "Color";
            btnColor.Click += new System.EventHandler(btnColor_Click);

            cbxEditMode = new ComboBox();
            cbxEditMode.DropDownStyle = ComboBoxStyle.DropDownList;
            cbxEditMode.Location = new Point(68, 196);
            cbxEditMode.Size = new Size(60, 20);
            cbxEditMode.SelectedIndexChanged +=
                new System.EventHandler(cbxEditMode_SelIndexChg);

            cbxEraserMode = new ComboBox();
            cbxEraserMode.DropDownStyle = ComboBoxStyle.DropDownList;
            cbxEraserMode.Location = new Point(136, 196);
            cbxEraserMode.Size = new Size(90, 20);
            cbxEraserMode.SelectedIndexChanged +=
                new System.EventHandler(cbxEraserMode_SelIndexChg);

            cbxEraserSize = new ComboBox();
            cbxEraserSize.DropDownStyle = ComboBoxStyle.DropDownList;
            cbxEraserSize.Location = new Point(234, 196);
            cbxEraserSize.Size = new Size(64, 20);
            cbxEraserSize.SelectedIndexChanged +=
                new System.EventHandler(cbxEraserSize_SelIndexChg);

            // Configure the parent control itself
            //ClientSize = new Size(352, 220);
            Controls.AddRange(new Control[] { pnlInput,
                                                btnColor,
                                                cbxEditMode,
                                                cbxEraserMode,
                                                cbxEraserSize});
            ResumeLayout(false);

            // Fill up the editing mode combobox
            foreach (InkOverlayEditingMode m in 
                InkOverlayEditingMode.GetValues(
                typeof(InkOverlayEditingMode)))
            {
                cbxEditMode.Items.Add(m);
            }

            // Fill up the eraser mode combobox
            foreach (InkOverlayEraserMode m in
                InkOverlayEraserMode.GetValues(
                typeof(InkOverlayEraserMode)))
            {
                cbxEraserMode.Items.Add(m);
            }

            // Fill up the eraser size combobox
            cbxEraserSize.Items.Add(InkControlEraserSize.Small);
            cbxEraserSize.Items.Add(InkControlEraserSize.Medium);
            cbxEraserSize.Items.Add(InkControlEraserSize.Large);

            // Create a new InkOverlay, using pnlInput for the input
            // area
            inkOverlay = new InkOverlay(pnlInput.Handle);

            // Select the initial settings of the UI
            cbxEditMode.SelectedItem = inkOverlay.EditingMode;
            cbxEraserMode.SelectedItem = inkOverlay.EraserMode;
            cbxEraserSize.SelectedIndex = 0;
        }

        // Handle the click of the color button
        private void btnColor_Click(object sender, System.EventArgs e)
        {
            // Display the common color dialog
            ColorDialog dlgColor = new ColorDialog();
            dlgColor.AllowFullOpen = false;
            dlgColor.Color = inkOverlay.DefaultDrawingAttributes.Color;
            if (dlgColor.ShowDialog(this) == DialogResult.OK)
            {
                // Set the current ink color to the selection chosen in
                // the dialog
                inkOverlay.DefaultDrawingAttributes.Color =
                    dlgColor.Color;
            }
        }

        // Handle the selection change of the editing mode combobox
        private void cbxEditMode_SelIndexChg(object sender,
            System.EventArgs e)
        {
            // Set the current editing mode to the selection chosen in
            // the combobox
            inkOverlay.EditingMode =
                (InkOverlayEditingMode)cbxEditMode.SelectedItem;

            // Show or hide the eraser settings comboboxes
            cbxEraserMode.Visible =
               (inkOverlay.EditingMode == InkOverlayEditingMode.Delete);
            cbxEraserSize.Visible =
                cbxEraserMode.Visible && (inkOverlay.EraserMode ==
                InkOverlayEraserMode.PointErase);
        }

        // Handle the selection change of the eraser mode combobox
        private void cbxEraserMode_SelIndexChg(object sender,
            System.EventArgs e)
        {
            // Set the current eraser mode to the selection chosen in the
            // combobox
            inkOverlay.EraserMode =
                (InkOverlayEraserMode)cbxEraserMode.SelectedItem;

            // Show or hide the eraser size combobox
            cbxEraserSize.Visible =
                (inkOverlay.EraserMode == InkOverlayEraserMode.PointErase);
        }

        // Handle the selection change of the eraser size combobox
        private void cbxEraserSize_SelIndexChg(object sender,
            System.EventArgs e)
        {
            switch ((InkControlEraserSize)cbxEraserSize.SelectedItem)
            {
                case InkControlEraserSize.Small:
                    inkOverlay.EraserWidth = 100;
                    break;
                case InkControlEraserSize.Medium:
                    inkOverlay.EraserWidth = 200;
                    break;
                case InkControlEraserSize.Large:
                    inkOverlay.EraserWidth = 400;
                    break;
            }
        }

        // Allow users readonly access to the InkOverlay object
        public InkOverlay InkOverlay
        {
            get
            {
                return inkOverlay;
            }
        }

        // Allow users readonly access to the input panel
        public InkInputPanel InkInputPanel
        {
            get
            {
                return pnlInput;
            }
        }
    }
}
