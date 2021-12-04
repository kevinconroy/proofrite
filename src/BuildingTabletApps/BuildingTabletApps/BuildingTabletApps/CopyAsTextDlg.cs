////////////////////////////////////////////////////////////////////
//
// CopyAsTextDlg.cs
//
// (c) 2002 Microsoft Press
// by Rob Jarrett
//
// This class implements a dialog which provides correction and
// clipboard copying of reco results via a RecognitionResults object.
//
////////////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Ink;

namespace MSPress.BuildingTabletApps
{
    public class CopyAsTextDlg : Form
    {
        private TextBox             txtResults;
        private ListBox             lbAlternates;
        private InkInputPanel       pnlInk;
        private Button              btnCopy;
        private Button              btnClose;
        private RecognitionResult   recoResult;
        private Strokes             strksDisplay;

        // Dialog setup
        public CopyAsTextDlg()
        {
            SuspendLayout();

            // Create and place all of our controls
            txtResults = new TextBox();
            txtResults.HideSelection = false;
            txtResults.Location = new Point(8, 8);
            txtResults.Multiline = true;
            txtResults.ReadOnly = true;
            txtResults.ScrollBars = ScrollBars.Vertical;
            txtResults.Size = new Size(384, 96);

            lbAlternates = new ListBox();
            lbAlternates.Location = new Point(8, 112);
            lbAlternates.Size = new Size(188, 96);

            pnlInk = new InkInputPanel();
            pnlInk.BackColor = Color.White;
            pnlInk.BorderStyle = BorderStyle.Fixed3D;
            pnlInk.Location = new Point(204, 112);
            pnlInk.Size = new Size(188, 96);

            btnCopy = new Button();
            btnCopy.DialogResult = DialogResult.OK;
            btnCopy.Location = new Point(264, 226);
            btnCopy.Size = new Size(60, 20);
            btnCopy.Text = "Copy";

            btnClose = new Button();
            btnClose.DialogResult = DialogResult.OK;
            btnClose.Location = new Point(332, 226);
            btnClose.Size = new Size(60, 20);
            btnClose.Text = "Close";

            // Configure the form itself
            AcceptButton = btnClose;
            CancelButton = btnClose;
            ClientSize = new Size(400, 256);
            Controls.AddRange(new Control[] { txtResults,
                                                lbAlternates,
                                                pnlInk,
                                                btnCopy,
                                                btnClose});
            FormBorderStyle = FormBorderStyle.FixedDialog;
            MinimizeBox = false;
            MaximizeBox = false;
            Text = "Copy As Text";

            ResumeLayout(false);

            // Get notification of user input occuring in the "Results"
            // TextBox so we can update the "Alternates" ListBox
            txtResults.KeyUp += new KeyEventHandler(txtResults_KeyUp);
            txtResults.MouseUp +=
                new MouseEventHandler(txtResults_MouseUp);

            // Get notification of an alternate getting chosen so we
            // can alter the result
            lbAlternates.SelectedIndexChanged +=
                new EventHandler(lbAlternates_SelectedIndexChanged);

            // Paint the preview of the strokes making up the selection
            pnlInk.Paint += new PaintEventHandler(pnlInk_Paint);

            // Perform copying of the text
            btnCopy.Click += new EventHandler(btnCopy_Click);
        }

        // Get or set the RecognitionResult object being used for the
        // correction
        public RecognitionResult RecognitionResult
        {
            get
            {
                return recoResult;
            }
            set
            {
                recoResult = value;
                if (recoResult != null)
                {
                    // Display the current result
                    txtResults.Text = recoResult.TopString;
                    txtResults.SelectionStart = 0;
                    txtResults.SelectionLength = 0;
                    SelectionChanged();
                }
            }
        }

        private void FillListbox(RecognitionAlternates recoAlternates)
        {
            // Clear out any current items in the listbox
            lbAlternates.BeginUpdate();
            lbAlternates.Items.Clear();

            // Fill up the listbox with each alternate
            foreach (RecognitionAlternate recoAlternate in recoAlternates)
            {
                lbAlternates.Items.Add(recoAlternate);
            }
            lbAlternates.EndUpdate();
        }

        // The selection in the results textbox has changed, so figure
        // out what word(s) were selected, "snap" the selection to them
        // if needed, fill the listbox, and update the preview with the
        // ink being used
        private void SelectionChanged()
        {
            // Figure out the best text range in the "Results" TextBox
            // to use in obtaining the alternates
            int nStart = txtResults.SelectionStart;
            int nLength = txtResults.SelectionLength;
            if (nLength == 0)
            {
                if (nStart < txtResults.Text.Length &&
                    txtResults.Text.Length > 0)
                {
                    nLength = 1;
                }
                else if (nStart > 0)
                {
                    nStart--;
                    nLength = 1;
                }
            }

            // If we still have no selection, no need to do anything
            if (nLength == 0)
            {
                return;
            }

            // Select the strokes that represent the selection in the
            // "Results" Textbox
            strksDisplay =
                recoResult.TopAlternate.GetStrokesFromTextRange(
                ref nStart, ref nLength);
            txtResults.Select(nStart, nLength);
            pnlInk.Invalidate();

            // Show the list of alternates for the selection
            FillListbox(
                recoResult.GetAlternatesFromSelection(nStart, nLength));
        }

        // Handle a key being released
        private void txtResults_KeyUp(object sender, KeyEventArgs e)
        {
            // Selection probably changed, so update the alternates listbox
            SelectionChanged();
        }

        // Handle a mouse button being released
        private void txtResults_MouseUp(object sender, MouseEventArgs e)
        {
            // Selection probably changed, so update the alternates listbox
            SelectionChanged();
        }

        // Handle an alternate getting selected
        private void lbAlternates_SelectedIndexChanged(
            object sender, EventArgs e)
        {
            // Get the alternate that was selected
            RecognitionAlternate recoAlternate =
                (RecognitionAlternate)lbAlternates.SelectedItem;

            // Adjust the current reco results with it
            recoResult.ModifyTopAlternate(recoAlternate);

            // Update selected text
            int nStart = txtResults.SelectionStart;
            int nLength = txtResults.SelectionLength;
            recoResult.TopAlternate.GetTextRangeFromStrokes(
                strksDisplay, ref nStart, ref nLength);

            // Update the results edit box
            txtResults.Text = recoResult.TopString;
            txtResults.Select(nStart, nLength);

            // Show the list of alternates for the selection
            FillListbox(
                recoResult.GetAlternatesFromSelection(nStart, nLength));
        }

        // Handle painting the preview of ink
        private void pnlInk_Paint(object sender, PaintEventArgs e)
        {
            if (strksDisplay != null)
            {
                Renderer r = new Renderer();

                // Offset the ink to be drawn so it will display in
                // the top-left of the preview window
                Rectangle rcBounds = strksDisplay.GetBoundingBox();
                r.Move(-rcBounds.Left, -rcBounds.Top);

                // Figure out how much the ink needs to be scaled in
                // order for it all to fit within the preview window
                float fScaleWidth = 1, fScaleHeight = 1;

                RendererEx.InkSpaceToPixel(r, e.Graphics, ref rcBounds);
                if (pnlInk.ClientSize.Width < rcBounds.Width)
                {
                    fScaleWidth =
                        (float)pnlInk.ClientSize.Width / rcBounds.Width;
                }
                if (pnlInk.ClientSize.Height < rcBounds.Height)
                {
                    fScaleHeight =
                        (float)pnlInk.ClientSize.Height / rcBounds.Height;
                }
                float fScaleBy = Math.Min(fScaleWidth, fScaleHeight);
                r.Scale(fScaleBy, fScaleBy);

                // Now we can draw the ink
                r.Draw(e.Graphics, strksDisplay);
            }
        }

        // Handle copying the current result to the clipboard
        private void btnCopy_Click(object sender, EventArgs e)
        {
            Clipboard.SetDataObject(txtResults.Text);
        }
    }
}
