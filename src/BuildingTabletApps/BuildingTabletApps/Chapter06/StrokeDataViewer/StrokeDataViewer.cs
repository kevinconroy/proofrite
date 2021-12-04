////////////////////////////////////////////////////////////////////
//
// StrokeDataViewer.cs
//
// (c) 2002 Microsoft Press
// by Rob Jarrett
//
// This program displays lots of different information for
// Stroke objects. An InkOverlaySharp control is created and the
// user can choose various data attributes from the app's menu
// to be drawn, such as points, bounding box, cusps, and
// intersections. The data is kept up to date as strokes are added,
// removed, and modified.
//
////////////////////////////////////////////////////////////////////

using System;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Ink;
using MSPress.BuildingTabletApps;

public class frmMain : Form
{
	private NumericUpDown		windowSizeCombo;
    private InkControl2     inkCtl;
	private	int				windowSize = 3;

    private MenuItem        miStrokeId;
    private MenuItem        miNoPoints;
    private MenuItem        miPolylinePoints;
    private MenuItem        miBezierPoints;
    private MenuItem        miFlattenedBezierPoints;
    private MenuItem        miNoCusps;
    private MenuItem        miBezierCusps;
    private MenuItem        miPolylineCusps;
    private MenuItem        miNoBoundingBox;
    private MenuItem        miDefaultBoundingBox;
    private MenuItem        miCurveFitBoundingBox;
    private MenuItem        miNoCurveFitBoundingBox;
    private MenuItem        miPointsOnlyBoundingBox;
    private MenuItem        miUnionBoundingBox;
    private MenuItem        miNoIntersections;
    private MenuItem        miSelfIntersections;
    private MenuItem        miStrokeIntersections;
    private MenuItem        miBoundingBoxIntersections;
	private MenuItem		miNoInsertionPoint;
	private	MenuItem		miFirstVerticalSlope;
	private MenuItem        miLastPoint;
	private	MenuItem		miDirectionChange;
	private MenuItem		miLawOfCosines;


	private bool			fDrawInsertionPoint = false;
	private RendererEx.InsertionPointType insertionPointType = RendererEx.InsertionPointType.None;
    private bool            fDrawStrokeId = false;
    private bool            fDrawPoints = false;
    private RendererEx.StrokePointType strokePointType =
                        RendererEx.StrokePointType.Polyline;
    private bool            fDrawCusps = false;
    private RendererEx.StrokeCuspType strokeCuspType =
                        RendererEx.StrokeCuspType.Polyline;
    private bool            fDrawBoundingBox = false;
    private BoundingBoxMode bboxMode = BoundingBoxMode.Default;
    private bool            fDrawIntersections = false;
    private RendererEx.StrokeIntersectionType
                        strokeIntersectionType =
                        RendererEx.StrokeIntersectionType.Stroke;

    // Entry point of the program
    [STAThread]
    static void Main() 
    {
        Application.Run(new frmMain());
    }

    // Main form setup
    public frmMain()
    {
        SuspendLayout();

        // Create the main menu
        Menu = new MainMenu();

        MenuItem miFile = new MenuItem("&File");
        Menu.MenuItems.Add(miFile);

		MenuItem miClear = new MenuItem("&Clear");
		miClear.Click += new EventHandler(miClear_Click);
		Menu.MenuItems[0].MenuItems.Add(miClear);

		Menu.MenuItems[0].MenuItems.Add(new MenuItem("-"));

        MenuItem miExit = new MenuItem("E&xit");
        miExit.Click += new EventHandler(miExit_Click);
        Menu.MenuItems[0].MenuItems.Add(miExit);

        MenuItem miView = new MenuItem("&View");
        miView.Popup += new EventHandler(miView_Popup);
        Menu.MenuItems.Add(miView);

        miStrokeId = new MenuItem("Stroke Id");
        miStrokeId.Click += new EventHandler(miStrokeId_Click);
        Menu.MenuItems[1].MenuItems.Add(miStrokeId);

        Menu.MenuItems[1].MenuItems.Add(new MenuItem("-"));

        MenuItem miPoints = new MenuItem("Points");
        miPoints.Popup += new EventHandler(miPoints_Popup);
        Menu.MenuItems[1].MenuItems.Add(miPoints);

        miNoPoints = new MenuItem("None");
        miNoPoints.Click += new EventHandler(miNoPoints_Click);
        Menu.MenuItems[1].MenuItems[2].MenuItems.Add(miNoPoints);

        Menu.MenuItems[1].MenuItems[2].MenuItems.Add(new MenuItem("-"));

        miPolylinePoints = new MenuItem("Polyline");
        miPolylinePoints.Click +=
            new EventHandler(miPolylinePoints_Click);
        Menu.MenuItems[1].MenuItems[2].MenuItems.Add(miPolylinePoints);

        miBezierPoints = new MenuItem("Bezier");
        miBezierPoints.Click += new EventHandler(miBezierPoints_Click);
        Menu.MenuItems[1].MenuItems[2].MenuItems.Add(miBezierPoints);

        miFlattenedBezierPoints = new MenuItem("Flattened Bezier");
        miFlattenedBezierPoints.Click +=
            new EventHandler(miFlattenedBezierPoints_Click);
        Menu.MenuItems[1].MenuItems[2].MenuItems.Add(
            miFlattenedBezierPoints);

        MenuItem miCusps = new MenuItem("Cusps");
        miCusps.Popup += new EventHandler(miCusps_Popup);
        Menu.MenuItems[1].MenuItems.Add(miCusps);

        miNoCusps = new MenuItem("None");
        miNoCusps.Click += new EventHandler(miNoCusps_Click);
        Menu.MenuItems[1].MenuItems[3].MenuItems.Add(miNoCusps);

        Menu.MenuItems[1].MenuItems[3].MenuItems.Add(new MenuItem("-"));

        miPolylineCusps = new MenuItem("Polyline");
        miPolylineCusps.Click +=
            new EventHandler(miPolylineCusps_Click);
        Menu.MenuItems[1].MenuItems[3].MenuItems.Add(miPolylineCusps);

        miBezierCusps = new MenuItem("Bezier");
        miBezierCusps.Click += new EventHandler(miBezierCusps_Click);
        Menu.MenuItems[1].MenuItems[3].MenuItems.Add(miBezierCusps);

        MenuItem miBoundingBox = new MenuItem("Bounding Box");
        miBoundingBox.Popup += new EventHandler(miBoundingBox_Popup);
        Menu.MenuItems[1].MenuItems.Add(miBoundingBox);

        miNoBoundingBox = new MenuItem("None");
        miNoBoundingBox.Click += new EventHandler(miNoBoundingBox_Click);
        Menu.MenuItems[1].MenuItems[4].MenuItems.Add(miNoBoundingBox);

        Menu.MenuItems[1].MenuItems[4].MenuItems.Add(new MenuItem("-"));

        miDefaultBoundingBox = new MenuItem("Default");
        miDefaultBoundingBox.Click +=
            new EventHandler(miDefaultBoundingBox_Click);
        Menu.MenuItems[1].MenuItems[4].MenuItems.Add(
            miDefaultBoundingBox);

        miCurveFitBoundingBox = new MenuItem("CurveFit");
        miCurveFitBoundingBox.Click +=
            new EventHandler(miCurveFitBoundingBox_Click);
        Menu.MenuItems[1].MenuItems[4].MenuItems.Add(
            miCurveFitBoundingBox);

        miNoCurveFitBoundingBox = new MenuItem("NoCurveFit");
        miNoCurveFitBoundingBox.Click +=
            new EventHandler(miNoCurveFitBoundingBox_Click);
        Menu.MenuItems[1].MenuItems[4].MenuItems.Add(
            miNoCurveFitBoundingBox);

        miPointsOnlyBoundingBox = new MenuItem("PointsOnly");
        miPointsOnlyBoundingBox.Click +=
            new EventHandler(miPointsOnlyBoundingBox_Click);
        Menu.MenuItems[1].MenuItems[4].MenuItems.Add(
            miPointsOnlyBoundingBox);

        miUnionBoundingBox = new MenuItem("Union");
        miUnionBoundingBox.Click +=
            new EventHandler(miUnionBoundingBox_Click);
        Menu.MenuItems[1].MenuItems[4].MenuItems.Add(
            miUnionBoundingBox);

        MenuItem miIntersections = new MenuItem("Intersections");
        miIntersections.Popup +=
            new EventHandler(miIntersections_Popup);
        Menu.MenuItems[1].MenuItems.Add(miIntersections);

        miNoIntersections = new MenuItem("None");
        miNoIntersections.Click +=
            new EventHandler(miNoIntersections_Click);
        Menu.MenuItems[1].MenuItems[5].MenuItems.Add(
            miNoIntersections);

        Menu.MenuItems[1].MenuItems[5].MenuItems.Add(new MenuItem("-"));

        miSelfIntersections = new MenuItem("Self");
        miSelfIntersections.Click +=
            new EventHandler(miSelfIntersections_Click);
        Menu.MenuItems[1].MenuItems[5].MenuItems.Add(
            miSelfIntersections);

        miStrokeIntersections = new MenuItem("Stroke");
        miStrokeIntersections.Click +=
            new EventHandler(miStrokeIntersections_Click);
        Menu.MenuItems[1].MenuItems[5].MenuItems.Add(
            miStrokeIntersections);

        miBoundingBoxIntersections = new MenuItem("BoundingBox");
        miBoundingBoxIntersections.Click +=
            new EventHandler(miBoundingBoxIntersections_Click);
        Menu.MenuItems[1].MenuItems[5].MenuItems.Add(
            miBoundingBoxIntersections);

		MenuItem miInsertionPoint = new MenuItem("Insertion Point");
		miInsertionPoint.Popup += new EventHandler(miInsertionPoint_Popup);
		Menu.MenuItems[1].MenuItems.Add(miInsertionPoint);

		miNoInsertionPoint = new MenuItem("None");
		miNoInsertionPoint.Click +=
			new EventHandler(miNoInsertionPoint_Click);
		Menu.MenuItems[1].MenuItems[6].MenuItems.Add(
			miNoInsertionPoint);

		Menu.MenuItems[1].MenuItems[6].MenuItems.Add(new MenuItem("-"));

		miLastPoint = new MenuItem("Last Point");
		miLastPoint.Click +=
			new EventHandler(miLastPoint_Click);
		Menu.MenuItems[1].MenuItems[6].MenuItems.Add(
			miLastPoint);

		miFirstVerticalSlope = new MenuItem("First Vertical Slope");
		miFirstVerticalSlope.Click +=
			new EventHandler(miFirstVerticalSlope_Click);
		Menu.MenuItems[1].MenuItems[6].MenuItems.Add(
			miFirstVerticalSlope);

		miDirectionChange = new MenuItem("Direction Change");
		miDirectionChange.Click +=
			new EventHandler(miDirectionChange_Click);
		Menu.MenuItems[1].MenuItems[6].MenuItems.Add(
			miDirectionChange);

		miLawOfCosines = new MenuItem("Law Of Cosines");
		miLawOfCosines.Click +=
			new EventHandler(miLawOfCosines_Click);
		Menu.MenuItems[1].MenuItems[6].MenuItems.Add(
			miLawOfCosines);
		//private	MenuItem		miFirstVerticalSlope;

        // Create and place all of our controls
        inkCtl = new InkControl2(new Size(880, 550));
        inkCtl.Location = new Point(8, 40);
        
		Label windowLabel = new Label();
		windowLabel.Text = "Sliding Window Size:";
		windowLabel.AutoSize = true;
		windowLabel.Location = new Point(8,8);

		windowSizeCombo = new NumericUpDown();
		windowSizeCombo.Name = "Sliding Window Size:";
		windowSizeCombo.Location = new Point(windowLabel.Left + windowLabel.Size.Width + 10,8);	
		windowSizeCombo.Minimum = 3;
		windowSizeCombo.Maximum = 99;
		windowSizeCombo.Increment = 2;
		windowSizeCombo.Value = 3;
		windowSizeCombo.ValueChanged += new EventHandler(miwindowSizeCombo_SelectedIndexChanged);

        // Configure the form itself
        ClientSize = new Size(900, 600);
        Controls.AddRange(new Control[] { windowLabel, windowSizeCombo, inkCtl });
        //FormBorderStyle = FormBorderStyle.FixedDialog;
        //MaximizeBox = false;
        Text = "StrokeDataViewer";

        ResumeLayout(false);

        // Hook up to the InkOverlay's event handlers
        inkCtl.InkOverlay.Painted +=
            new InkOverlayPaintedEventHandler(inkCtl_Painted);
        inkCtl.InkOverlay.Ink.InkAdded +=
            new StrokesEventHandler(inkCtl_InkAdded);
        inkCtl.InkOverlay.Ink.InkDeleted +=
            new StrokesEventHandler(inkCtl_InkDeleted);

        // Set the ink color to something other than black so it's
        // easier to see the data
        inkCtl.InkOverlay.DefaultDrawingAttributes.Color =
            Color.Red;

		inkCtl.InkOverlay.DefaultDrawingAttributes.Width= 65;

        // We're now set to go, so turn on tablet input
        inkCtl.InkOverlay.Enabled = true;
    }

	private void miClear_Click(object sender, EventArgs e)
	{
		// clean it out
		inkCtl.InkOverlay.Ink.DeleteStrokes();
		inkCtl.InkInputPanel.Invalidate();
	}

    // Handle the "Exit" menu item being clicked
    private void miExit_Click(object sender, EventArgs e)
    {
        Application.Exit();
    }

    // Handle the "View" submenu popping up
    private void miView_Popup(object sender, EventArgs e)
    {
        miStrokeId.Checked = fDrawStrokeId;
    }

    // Handle the "Stroke Id" menu being clicked
    private void miStrokeId_Click(object sender, EventArgs e)
    {
        fDrawStrokeId = !fDrawStrokeId;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Points" submenu popping up
    private void miPoints_Popup(object sender, EventArgs e)
    {
        miNoPoints.Checked = !fDrawPoints;
        miPolylinePoints.Checked = fDrawPoints && 
            strokePointType ==
            RendererEx.StrokePointType.Polyline;
        miBezierPoints.Checked = fDrawPoints &&
            strokePointType ==
            RendererEx.StrokePointType.Bezier;
        miFlattenedBezierPoints.Checked = fDrawPoints &&
            strokePointType ==
            RendererEx.StrokePointType.FlattenedBezier;
    }

    // Handle the "NoPoints" menu item being clicked
    private void miNoPoints_Click(object sender, EventArgs e)
    {
        fDrawPoints = false;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Polyline" menu item being clicked
    private void miPolylinePoints_Click(object sender, EventArgs e)
    {
        fDrawPoints = true;
        strokePointType = RendererEx.StrokePointType.Polyline;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Bezier" menu item being clicked
    private void miBezierPoints_Click(object sender, EventArgs e)
    {
        fDrawPoints = true;
        strokePointType = RendererEx.StrokePointType.Bezier;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "FlattenedBezier" menu item being clicked
    private void miFlattenedBezierPoints_Click(
        object sender, EventArgs e)
    {
        fDrawPoints = true;
        strokePointType =
            RendererEx.StrokePointType.FlattenedBezier;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Cusps" submenu popping up
    private void miCusps_Popup(object sender, EventArgs e)
    {
        miNoCusps.Checked = !fDrawCusps;
        miPolylineCusps.Checked = fDrawCusps &&
            strokeCuspType == RendererEx.StrokeCuspType.Polyline;
        miBezierCusps.Checked = fDrawCusps &&
            strokeCuspType == RendererEx.StrokeCuspType.Bezier;
    }

    // Handle the "None" menu item being clicked
    private void miNoCusps_Click(object sender, EventArgs e)
    {
        fDrawCusps = false;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Polyline" menu item being clicked
    private void miPolylineCusps_Click(object sender, EventArgs e)
    {
        fDrawCusps = true;
        strokeCuspType = RendererEx.StrokeCuspType.Polyline;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Bezier" menu item being clicked
    private void miBezierCusps_Click(object sender, EventArgs e)
    {
        fDrawCusps = true;
        strokeCuspType = RendererEx.StrokeCuspType.Bezier;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Bounding Box" submenu popping up
    private void miBoundingBox_Popup(object sender, EventArgs e)
    {
        miNoBoundingBox.Checked = !fDrawBoundingBox;
        miDefaultBoundingBox.Checked = fDrawBoundingBox &&
            bboxMode == BoundingBoxMode.Default;
        miCurveFitBoundingBox.Checked = fDrawBoundingBox &&
            bboxMode == BoundingBoxMode.CurveFit;
        miNoCurveFitBoundingBox.Checked = fDrawBoundingBox &&
            bboxMode == BoundingBoxMode.NoCurveFit;
        miPointsOnlyBoundingBox.Checked = fDrawBoundingBox &&
            bboxMode == BoundingBoxMode.PointsOnly;
        miUnionBoundingBox.Checked = fDrawBoundingBox &&
            bboxMode == BoundingBoxMode.Union;
    }

    // Handle the "None" menu item being clicked
    private void miNoBoundingBox_Click(object sender, EventArgs e)
    {
        fDrawBoundingBox = false;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Default" menu item being clicked
    private void miDefaultBoundingBox_Click(object sender, EventArgs e)
    {
        fDrawBoundingBox = true;
        bboxMode = BoundingBoxMode.Default;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "CurveFit" menu item being clicked
    private void miCurveFitBoundingBox_Click(object sender, EventArgs e)
    {
        fDrawBoundingBox = true;
        bboxMode = BoundingBoxMode.CurveFit;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "NoCurveFit" menu item being clicked
    private void miNoCurveFitBoundingBox_Click(
        object sender, EventArgs e)
    {
        fDrawBoundingBox = true;
        bboxMode = BoundingBoxMode.NoCurveFit;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "PointsOnly" menu item being clicked
    private void miPointsOnlyBoundingBox_Click(
        object sender, EventArgs e)
    {
        fDrawBoundingBox = true;
        bboxMode = BoundingBoxMode.PointsOnly;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Union" menu item being clicked
    private void miUnionBoundingBox_Click(object sender, EventArgs e)
    {
        fDrawBoundingBox = true;
        bboxMode = BoundingBoxMode.Union;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Intersections" submenu popping up
    private void miIntersections_Popup(object sender, EventArgs e)
    {
        miNoIntersections.Checked = !fDrawIntersections;
        miSelfIntersections.Checked = fDrawIntersections &&
            strokeIntersectionType ==
            RendererEx.StrokeIntersectionType.Self;
        miStrokeIntersections.Checked = fDrawIntersections &&
            strokeIntersectionType ==
            RendererEx.StrokeIntersectionType.Stroke;
        miBoundingBoxIntersections.Checked = fDrawIntersections &&
            strokeIntersectionType ==
            RendererEx.StrokeIntersectionType.BoundingBox;
    }

    // Handle the "None" menu item being clicked
    private void miNoIntersections_Click(object sender, EventArgs e)
    {
        fDrawIntersections = false;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Self" menu item being clicked
    private void miSelfIntersections_Click(object sender, EventArgs e)
    {
        fDrawIntersections = true;
        strokeIntersectionType =
            RendererEx.StrokeIntersectionType.Self;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "Stroke" menu item being clicked
    private void miStrokeIntersections_Click(object sender, EventArgs e)
    {
        fDrawIntersections = true;
        strokeIntersectionType =
            RendererEx.StrokeIntersectionType.Stroke;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the "BoundingBox" menu item being clicked
    private void miBoundingBoxIntersections_Click(object sender, EventArgs e)
    {
        fDrawIntersections = true;
        strokeIntersectionType =
            RendererEx.StrokeIntersectionType.BoundingBox;
        inkCtl.InkInputPanel.Invalidate();
    }

    // Handle the InkOverlay having been painted
    private void inkCtl_Painted(object sender, PaintEventArgs e)
    {
        // Draw stroke IDs if needed
        if (fDrawStrokeId)
        {
            RendererEx.DrawStrokeIds(
                e.Graphics, Font, inkCtl.InkOverlay.Ink);
        }

        // Draw the stroke points if needed
        if (fDrawPoints)
        {
            RendererEx.DrawPoints(inkCtl.InkOverlay.Renderer,
                e.Graphics, inkCtl.InkOverlay.Ink.Strokes,
                Brushes.Red, strokePointType);
        }

        // Draw the stroke cusps if needed
        if (fDrawCusps)
        {
			RendererEx.DrawCusps(inkCtl.InkOverlay.Renderer,
				e.Graphics, inkCtl.InkOverlay.Ink.Strokes,
				Pens.Blue, strokeCuspType);


        }

        // Draw the stroke bounding box if needed
        if (fDrawBoundingBox)
        {
			RendererEx.DrawBoundingBoxes(inkCtl.InkOverlay.Renderer,
				e.Graphics, inkCtl.InkOverlay.Ink.Strokes,
				Pens.LightGreen, bboxMode);


        }

        // Draw the stroke intersections if needed
        if (fDrawIntersections)
        {
			RendererEx.DrawIntersections(inkCtl.InkOverlay.Renderer,
				e.Graphics, inkCtl.InkOverlay.Ink.Strokes,
				Pens.DarkRed, strokeIntersectionType); 

        }

		// Draw the stroke insertion point if needed
		if(fDrawInsertionPoint)
		{
			RendererEx.DrawInsertionPoint(inkCtl.InkOverlay.Renderer,
				e.Graphics, inkCtl.InkOverlay.Ink.Strokes,
				Pens.Blue, insertionPointType, windowSize); 
		}
    }

	

    // Handle ink having been added
    private void inkCtl_InkAdded(object sender, StrokesEventArgs e)
    {
        inkCtl.InkInputPanel.Invalidate();
    }

	private void InitializeComponent()
	{
		// 
		// frmMain
		// 
		this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
		this.ClientSize = new System.Drawing.Size(904, 486);
		this.Name = "frmMain";

	}

    // Handle ink having been deleted
    private void inkCtl_InkDeleted(object sender, StrokesEventArgs e)
    {
        inkCtl.InkInputPanel.Invalidate();
    }

	// Handle the "InsertionPoint" submenu popping up
	private void miInsertionPoint_Popup(object sender, EventArgs e)
	{
		miNoInsertionPoint.Checked = !fDrawInsertionPoint;
		
		miLastPoint.Checked = fDrawInsertionPoint &&
			insertionPointType ==
			RendererEx.InsertionPointType.LastPoint;

		miFirstVerticalSlope.Checked = fDrawInsertionPoint &&
			insertionPointType ==
			RendererEx.InsertionPointType.FirstVertical;

		miDirectionChange.Checked = fDrawInsertionPoint &&
			insertionPointType ==
			RendererEx.InsertionPointType.DirectionChange;

		miLawOfCosines.Checked = fDrawInsertionPoint &&
			insertionPointType ==
			RendererEx.InsertionPointType.LawOfCosines;
	}
		
	// Handle the "None" menu item being clicked
	private void miNoInsertionPoint_Click(object sender, EventArgs e)
	{
		fDrawInsertionPoint = false;
		insertionPointType = RendererEx.InsertionPointType.None;
		inkCtl.InkInputPanel.Invalidate();
	}

	// Handle "Last Point" menu item being clicked
	private void miLastPoint_Click(object sender, EventArgs e)
	{
		fDrawInsertionPoint = true;
		insertionPointType = RendererEx.InsertionPointType.LastPoint;
		inkCtl.InkInputPanel.Invalidate();
	}

	// Handle "First Vertical Slope" menu item being clicked
	private void miFirstVerticalSlope_Click(object sender, EventArgs e)
	{
		fDrawInsertionPoint = true;
		insertionPointType = RendererEx.InsertionPointType.FirstVertical;
		inkCtl.InkInputPanel.Invalidate();
	}

	// Handle "Direction Change" menu item being clicked
	private void miDirectionChange_Click(object sender, EventArgs e)
	{
		fDrawInsertionPoint = true;
		insertionPointType = RendererEx.InsertionPointType.DirectionChange;
		inkCtl.InkInputPanel.Invalidate();
	}

	// Handle "Law Of Cosines" menu item being clicked
	private void miLawOfCosines_Click(object sender, EventArgs e)
	{
		fDrawInsertionPoint = true;
		insertionPointType = RendererEx.InsertionPointType.LawOfCosines;
		inkCtl.InkInputPanel.Invalidate();
	}

	private void miwindowSizeCombo_SelectedIndexChanged(object sender, EventArgs e) 
	{
		NumericUpDown box = (NumericUpDown)sender;
		
		windowSize = Int32.Parse(box.Value.ToString());
		inkCtl.InkInputPanel.Invalidate();
	}
}
