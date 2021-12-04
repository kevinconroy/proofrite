////////////////////////////////////////////////////////////////////
//
// LassoUI.cs
//
// (c) 2002 Microsoft Press
// by Rob Jarrett
//
// This class implements drawing of the lasso selection tool.
//
////////////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;

namespace MSPress.BuildingTabletApps
{
    public class LassoUI
    {
        private int         nDotSpacing = 7;
        private int         nDotSize = 4;
        private Brush       brDotColor = Brushes.Orange;

        private ArrayList   arrPts;
        private Point       ptLast;
        private Rectangle   rcBounds;

        public LassoUI()
        {
            arrPts = new ArrayList();
            ptLast = new Point(0, 0);
            rcBounds = new Rectangle(0, 0, 0, 0);
        }

        // Start up a lasso
        public void Start(Graphics g, Point ptStart)
        {
            arrPts = new ArrayList();
            arrPts.Add(ptStart);
            ptLast = ptStart;
            rcBounds = new Rectangle(ptStart, new Size(0, 0));

            // Draw the first dot of the lasso
            DrawLassoDot(g, ptStart);
        }

        // Continue creating a lasso
        public bool Continue(Graphics g, Point ptNew)
        {
            // Compute how far the new point is from the last drawn dot
            int a = (ptNew.X - ptLast.X);
            int b = (ptNew.Y - ptLast.Y);
            double c = Math.Sqrt(a * a + b * b);

            // Is that distance less than the dot spacing? If so, we
            // can throw away this point
            if (c < (double)nDotSpacing)
                return false;

            // Compute how many dots will need to be drawn
            int nSegments = (int)(c / nDotSpacing);

            // Compute new rise and run values "snapped" to dot spacing
            double ap = a * ((nSegments*nDotSpacing) / c);
            double bp = b * ((nSegments*nDotSpacing) / c);

            // Draw lasso dots until the new endpoint is reached
            Point ptCurr = new Point(ptLast.X, ptLast.Y);
            for (int i = 1; i <= nSegments; i++)
            {
                double ratio = (double)i / nSegments;
                ptCurr = new Point(
                    ptLast.X + (int)Math.Round(ap * ratio),
                    ptLast.Y + (int)Math.Round(bp * ratio));

                DrawLassoDot(g, ptCurr);
            }

            // Update the lasso's bounding rectangle
            if (ptCurr.X < rcBounds.X)
            {
                rcBounds.Width += rcBounds.X - ptCurr.X;
                rcBounds.X = ptCurr.X;
            }
            else if (ptCurr.X > rcBounds.Right)
            {
                rcBounds.Width = ptCurr.X - rcBounds.X;
            }
            if (ptCurr.Y < rcBounds.Y)
            {
                rcBounds.Height += rcBounds.Y - ptCurr.Y;
                rcBounds.Y = ptCurr.Y;
            }
            else if (ptCurr.Y > rcBounds.Bottom)
            {
                rcBounds.Height = ptCurr.Y - rcBounds.Y;
            }

            // Add the endpoint to the polyline
            arrPts.Add(ptCurr);
            ptLast = ptCurr;

            return true;
        }

        // Draw the entire lasso in one shot
        public void Render(Graphics g)
        {
            Render(g, new Rectangle());
        }

        // Draw the entire lasso in one shot, using a clipping area to
        // improve performance
        public void Render(Graphics g, Rectangle rcClip)
        {
            if (arrPts.Count > 0)
            {
                // Draw the first point
                Point ptPrev = (Point)arrPts[0];
                DrawLassoDot(g, ptPrev);

                foreach (Point ptNext in arrPts)
                {
                    // Compute how far the new point is from the last
                    // drawn dot
                    int a = (ptNext.X - ptPrev.X);
                    int b = (ptNext.Y - ptPrev.Y);
                    double c = Math.Sqrt(a * a + b * b);

                    // Compute how many dots need to be drawn within
                    // this line
                    int nSegments = (int)Math.Round(c / nDotSpacing);

                    // Draw dots until the line's endpoint is reached
                    Point ptCurr = new Point(ptPrev.X, ptPrev.Y);
                    for (int i = 1; i <= nSegments; i++)
                    {
                        double ratio = (double)i / nSegments;
                        ptCurr = new Point(
                            ptPrev.X + (int)Math.Round(a * ratio),
                            ptPrev.Y + (int)Math.Round(b * ratio));

                        // See if we need to bother drawing the dot
                        Rectangle rcDot = new Rectangle(
                            new Point(ptCurr.X - nDotSize/2,
                            ptCurr.Y - nDotSize/2),
                            new Size(nDotSize, nDotSize));
                        if (rcClip.IsEmpty || 
                            rcClip.IntersectsWith(rcDot))
                        {
                            DrawLassoDot(g, ptCurr);
                        }
                    }

                    ptPrev = ptNext;
                }
            }
        }

        // Get the current lasso polyline
        public Point[] Points
        {
            get
            {
                return (Point[])arrPts.ToArray(typeof(Point));
            }
        }

        // Get the current bounding rectangle of the dots drawn
        public Rectangle BoundingRect
        {
            get
            {
                Rectangle rcResult =
                    new Rectangle(rcBounds.Location, rcBounds.Size);

                // Inflate the result by the dot size, taking into
                // account an odd-numbered size. i.e. if we just
                // performed an Inflate(nDotSize/2,nDotSize/2) and
                // the dot size were e.g. 5, the bounds would only
                // increase by 5/2*2 = 4. So we'll use our own
                // inflation method.
                rcResult.Offset(-nDotSize/2, -nDotSize/2);
                rcResult.Width += nDotSize;
                rcResult.Height += nDotSize;

                return rcResult;
            }
        }

        // Get or set the dot spacing of the lasso
        public int DotSpacing
        {
            get
            {
                return nDotSpacing;
            }

            set
            {
                if (nDotSpacing < 1)
                {
                    throw new ArgumentOutOfRangeException();
                }
                nDotSpacing = value;
            }
        }

        // Get or set the dot size of the lasso
        public int DotSize
        {
            get
            {
                return nDotSize;
            }

            set
            {
                if (nDotSize < 1)
                {
                    throw new ArgumentOutOfRangeException();
                }
                nDotSize = value;
            }
        }

        // Get or set the brush used to draw the lasso dots
        public Brush DotBrush
        {
            get
            {
                return brDotColor;
            }

            set
            {
                brDotColor = value;
            }
        }

        // Render a single lasso dot
        private void DrawLassoDot(Graphics g, Point pt)
        {
            pt.Offset(-nDotSize/2, -nDotSize/2);
            g.FillEllipse(brDotColor,
                new Rectangle(pt, new Size(nDotSize, nDotSize)));
        }
    }
}
