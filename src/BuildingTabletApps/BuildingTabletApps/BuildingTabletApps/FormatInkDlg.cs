////////////////////////////////////////////////////////////////////
//
// FormatInkDlg.cs
//
// (c) 2002 Microsoft Press
// by Rob Jarrett
//
// This class implements a dialog which provides editing of a
// DrawingAttributes object.
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
    public class FormatInkDlg : Form
    {
        private DrawingAttributes   attrsData;
        private Button              btnColor;
        private ComboBox            cbxThickness;
        private CheckBox            cbAntialiased;
        private CheckBox            cbFitToCurve;
        private CheckBox            cbIgnorePressure;
        private ComboBox            cbxTipStyle;
        private ComboBox            cbxROP;
        private ComboBox            cbxTransparency;
        private Button              btnOK;
        private Button              btnCancel;

        // Dialog setup
        public FormatInkDlg()
        {
            SuspendLayout();

            // Create and place all of our controls
            Label lblColor = new Label();
            lblColor.Location = new Point(8, 8);
            lblColor.Size = new Size(96, 20);
            lblColor.Text = "Color:";
            lblColor.TextAlign = ContentAlignment.MiddleRight;

            btnColor = new Button();
            btnColor.Location = new Point(104, 8);
            btnColor.Size = new Size(45, 20);
            btnColor.Text = "";
            btnColor.Click += new System.EventHandler(btnColor_Click);

            Label lblThickness = new Label();
            lblThickness.Location = new Point(8, 36);
            lblThickness.Size = new Size(96, 20);
            lblThickness.Text = "Thickness:";
            lblThickness.TextAlign = ContentAlignment.MiddleRight;

            cbxThickness = new ComboBox();
            cbxThickness.Location = new Point(104, 36);
            cbxThickness.Size = new Size(45, 20);
            cbxThickness.DropDownStyle = ComboBoxStyle.DropDownList;
            cbxThickness.SelectedIndexChanged +=
                new System.EventHandler(cbxThickness_SelIndexChg);

            Label lblTipStyle = new Label();
            lblTipStyle.Location = new Point(8, 64);
            lblTipStyle.Size = new Size(96, 20);
            lblTipStyle.Text = "Tip style:";
            lblTipStyle.TextAlign = ContentAlignment.MiddleRight;

            cbxTipStyle = new ComboBox();
            cbxTipStyle.DropDownStyle = ComboBoxStyle.DropDownList;
            cbxTipStyle.Location = new Point(104, 64);
            cbxTipStyle.Size = new Size(90, 20);
            cbxTipStyle.SelectedIndexChanged +=
                new System.EventHandler(cbxTipStyle_SelIndexChg);

            cbAntialiased = new CheckBox();
            cbAntialiased.CheckAlign = ContentAlignment.MiddleRight;
            cbAntialiased.Location = new Point(8, 92);
            cbAntialiased.Size = new Size(108, 16);
            cbAntialiased.Text = "Antialiased:";
            cbAntialiased.TextAlign = ContentAlignment.MiddleRight;
            cbAntialiased.CheckStateChanged += new System.EventHandler(
                cbAntialiased_CheckStateChanged);

            cbFitToCurve = new CheckBox();
            cbFitToCurve.CheckAlign = ContentAlignment.MiddleRight;
            cbFitToCurve.Location = new Point(8, 116);
            cbFitToCurve.Size = new Size(108, 16);
            cbFitToCurve.Text = "Fit to curve:";
            cbFitToCurve.TextAlign = ContentAlignment.MiddleRight;
            cbFitToCurve.CheckStateChanged +=
                new System.EventHandler(cbFitToCurve_CheckStateChanged);

            cbIgnorePressure = new CheckBox();
            cbIgnorePressure.CheckAlign = ContentAlignment.MiddleRight;
            cbIgnorePressure.Location = new Point(8, 140);
            cbIgnorePressure.Size = new Size(108, 16);
            cbIgnorePressure.Text = "Ignore pressure:";
            cbIgnorePressure.TextAlign = ContentAlignment.MiddleRight;
            cbIgnorePressure.CheckStateChanged +=
                new System.EventHandler(
                cbIgnorePressure_CheckStateChanged);

            Label lblROP = new Label();
            lblROP.Location = new Point(8, 164);
            lblROP.Size = new Size(96, 20);
            lblROP.Text = "ROP code:";
            lblROP.TextAlign = ContentAlignment.MiddleRight;

            cbxROP = new ComboBox();
            cbxROP.DropDownStyle = ComboBoxStyle.DropDownList;
            cbxROP.Location = new Point(104, 164);
            cbxROP.Size = new Size(90, 20);
            cbxROP.SelectedIndexChanged +=
                new System.EventHandler(cbxROP_SelIndexChg);

            Label lblTransparency = new Label();
            lblTransparency.Location = new Point(8, 192);
            lblTransparency.Size = new Size(96, 20);
            lblTransparency.Text = "Transparency:";
            lblTransparency.TextAlign = ContentAlignment.MiddleRight;

            cbxTransparency = new ComboBox();
            cbxTransparency.DropDownStyle = ComboBoxStyle.DropDownList;
            cbxTransparency.Location = new Point(104, 192);
            cbxTransparency.Size = new Size(90, 20);
            cbxTransparency.SelectedIndexChanged +=
                new System.EventHandler(cbxTransparency_SelIndexChg);

            btnOK = new Button();
            btnOK.Location = new Point(64, 226);
            btnOK.Size = new Size(60, 20);
            btnOK.Text = "OK";
            btnOK.Click += new System.EventHandler(btnOK_Click);

            btnCancel = new Button();
            btnCancel.Location = new Point(132, 226);
            btnCancel.Size = new Size(60, 20);
            btnCancel.Text = "Cancel";
            btnCancel.Click += new System.EventHandler(btnCancel_Click);

            // Configure the form itself
            AcceptButton = btnOK;
            CancelButton = btnCancel;
            ClientSize = new Size(200, 256);
            Controls.AddRange(new Control[] { lblColor,
                                                btnColor,
                                                lblThickness,
                                                cbxThickness,
                                                lblTipStyle,
                                                cbxTipStyle,
                                                cbAntialiased,
                                                cbFitToCurve,
                                                cbIgnorePressure,
                                                lblROP,
                                                cbxROP,
                                                lblTransparency,
                                                cbxTransparency,
                                                btnOK,
                                                btnCancel});
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MinimizeBox = false;
            MaximizeBox = false;
            Text = "Format Ink";

            ResumeLayout(false);

            // Fill up the thickness combobox with some values
            cbxThickness.Items.Add(1f);
            cbxThickness.Items.Add(50f);
            cbxThickness.Items.Add(100f);
            cbxThickness.Items.Add(150f);
            cbxThickness.Items.Add(300f);
            cbxThickness.Items.Add(500f);

            // Fill up the pen tip combobox with all pen tip values
            foreach (PenTip t in PenTip.GetValues(typeof(PenTip)))
            {
                cbxTipStyle.Items.Add(t);
            }

            // Fill up the ROP code combobox with all raster operation
            // values
            foreach (RasterOperation o in
                RasterOperation.GetValues(typeof(RasterOperation)))
            {
                cbxROP.Items.Add(o);
            }

            // Fill up the transparency combobox with some values
            cbxTransparency.Items.Add((byte)0);
            cbxTransparency.Items.Add((byte)64);
            cbxTransparency.Items.Add((byte)128);
            cbxTransparency.Items.Add((byte)192);
            cbxTransparency.Items.Add((byte)255);
        }

        // Allow the dialog data to be externally viewable and settable
        public DrawingAttributes DrawingAttributes
        {
            get
            {
                return attrsData;
            }
            set
            {
                attrsData = value.Clone();

                // Reflect the values of the DrawingAttributes in the
                // controls

                btnColor.BackColor = attrsData.Color;

                // Add thickness value to the combobox if not there
                if (!cbxThickness.Items.Contains(attrsData.Width))
                {
                    int nLoc = 0;
                    while (nLoc < cbxThickness.Items.Count &&
                        (float)cbxThickness.Items[nLoc] < attrsData.Width)
                    {
                        nLoc++;
                    }

                    if (nLoc < cbxThickness.Items.Count)
                    {
                        cbxThickness.Items.Insert(nLoc, attrsData.Width);
                    }
                    else
                    {
                        cbxThickness.Items.Add(attrsData.Width);
                    }
                }
                cbxThickness.SelectedItem = attrsData.Width;

                cbxTipStyle.SelectedItem = attrsData.PenTip;

                cbAntialiased.CheckState = attrsData.AntiAliased ?
                    CheckState.Checked : CheckState.Unchecked;

                cbFitToCurve.CheckState = attrsData.FitToCurve ?
                    CheckState.Checked : CheckState.Unchecked;

                cbIgnorePressure.CheckState = attrsData.IgnorePressure ?
                    CheckState.Checked : CheckState.Unchecked;

                cbxROP.SelectedItem = attrsData.RasterOperation;

                // Add transparenccy value to the combobox if not there
                if (!cbxTransparency.Items.Contains(
                    attrsData.Transparency))
                {
                    int nLoc = 0;
                    while (nLoc < cbxTransparency.Items.Count &&
                        (byte)cbxTransparency.Items[nLoc] <
                        attrsData.Transparency)
                    {
                        nLoc++;
                    }
                    if (nLoc < cbxTransparency.Items.Count)
                    {
                        cbxTransparency.Items.Insert(nLoc,
                            attrsData.Transparency);
                    }
                    else
                    {
                        cbxTransparency.Items.Add(
                            attrsData.Transparency);
                    }
                }
                cbxTransparency.SelectedItem = attrsData.Transparency;
            }
        }

        // Handle the click of the color button
        private void btnColor_Click(object sender, System.EventArgs e)
        {
            // Display the common color dialog
            ColorDialog dlgColor = new ColorDialog();
            dlgColor.AllowFullOpen = false;
            dlgColor.Color = attrsData.Color;
            if (dlgColor.ShowDialog(this) == DialogResult.OK)
            {
                // Set the current ink color to the selection chosen in
                // the dialog
                attrsData.Color = dlgColor.Color;
                btnColor.BackColor = attrsData.Color;
            }
        }

        // Handle the selection change of the width combobox
        private void cbxThickness_SelIndexChg(object sender,
            System.EventArgs e)
        {
            attrsData.Width = (float)cbxThickness.SelectedItem;
            attrsData.Height = attrsData.Width;
        }

        // Handle the selection change of the pen tip combobox
        private void cbxTipStyle_SelIndexChg(object sender,
            System.EventArgs e)
        {
            attrsData.PenTip = (PenTip)cbxTipStyle.SelectedItem;
        }

        // Handle the checked state change of the antialiased checkbox
        private void cbAntialiased_CheckStateChanged(object sender,
            System.EventArgs e)
        {
            attrsData.AntiAliased =
                (cbAntialiased.CheckState == CheckState.Checked);
        }

        // Handle the checked state change of the fit to curve checkbox
        private void cbFitToCurve_CheckStateChanged(object sender,
            System.EventArgs e)
        {
            attrsData.FitToCurve =
                (cbFitToCurve.CheckState == CheckState.Checked);
        }

        // Handle the checked state change of the ignore pressure checkbox
        private void cbIgnorePressure_CheckStateChanged(object sender,
            System.EventArgs e)
        {
            attrsData.IgnorePressure =
                (cbIgnorePressure.CheckState == CheckState.Checked);
        }

        // Handle the selection change of the raster operation combobox
        private void cbxROP_SelIndexChg(object sender, 
            System.EventArgs e)
        {
            attrsData.RasterOperation =
                (RasterOperation)cbxROP.SelectedItem;
        }

        // Handle the selection change of the transparency combobox
        private void cbxTransparency_SelIndexChg(object sender,
            System.EventArgs e)
        {
            attrsData.Transparency = (byte)cbxTransparency.SelectedItem;
        }

        // Handle the button click of the OK button
        private void btnOK_Click(object sender, System.EventArgs e)
        {
            DialogResult = DialogResult.OK;
        }

        // Handle the button click of the cancel button
        private void btnCancel_Click(object sender, System.EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
        }
    }
}
