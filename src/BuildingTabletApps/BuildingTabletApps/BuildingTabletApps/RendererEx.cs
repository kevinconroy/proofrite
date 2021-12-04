////////////////////////////////////////////////////////////////////
//
// RendererEx.cs
//
// (c) 2002 Microsoft Press
// by Rob Jarrett
//
// This class implements various functions that are related to
// rendering ink.
//
////////////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Drawing;
using System.Diagnostics;
using NUnit.Framework;
using Microsoft.Ink;

namespace MSPress.BuildingTabletApps
{
	[TestFixture]
    public class RendererEx
    {
        // Convert a rectangle in ink space to pixels
        public static void InkSpaceToPixel(
            Renderer renderer, Graphics g, ref Rectangle rcRect)
        {
            Point ptTopLeft = rcRect.Location;
            Point ptBtmRght = new Point(rcRect.Right, rcRect.Bottom);

            renderer.InkSpaceToPixel(g, ref ptTopLeft);
            renderer.InkSpaceToPixel(g, ref ptBtmRght);

            rcRect.Location = ptTopLeft;
            rcRect.Size = new Size(ptBtmRght.X - ptTopLeft.X,
                ptBtmRght.Y - ptTopLeft.Y);
        }

        // Convert a rectangle in pixels to ink space
        public static void PixelToInkSpace(
            Renderer renderer, Graphics g, ref Rectangle rcRect)
        {
            Point ptTopLeft = rcRect.Location;
            Point ptBtmRght = new Point(rcRect.Right, rcRect.Bottom);

            renderer.PixelToInkSpace(g, ref ptTopLeft);
            renderer.PixelToInkSpace(g, ref ptBtmRght);

            rcRect.Location = ptTopLeft;
            rcRect.Size = new Size(ptBtmRght.X - ptTopLeft.X,
                ptBtmRght.Y - ptTopLeft.Y);
        }

        // Draw a strokes collection in a selected state
        public static void DrawSelected(
            Renderer renderer, Graphics g, Strokes strokes)
        {
            foreach (Stroke s in strokes)
            {
                if (!s.Deleted)
                {
                    DrawSelected(renderer, g, s);
                }
            }
        }

        // Draw a stroke in a selected state
        public static void DrawSelected(
            Renderer renderer, Graphics g, Stroke s)
        {
            // Compute selection ink thickness
            Point ptThickness = new Point(4, 4);
            renderer.PixelToInkSpace(g, ref ptThickness);

            // Copy the DrawingAttributes since we’ll be modifying them
            DrawingAttributes da = s.DrawingAttributes.Clone();

            // Turn off pressure so thickness draws uniformly
            da.IgnorePressure = true;

            // Draw the thick outer stroke - the "outline"
            da.Width += ptThickness.X;
            da.Height += ptThickness.Y;
            renderer.Draw(g, s, da);

            // Draw the inner "transparent" stroke
            da.Width -= ptThickness.X;
            da.Height -= ptThickness.Y;
            da.Color = Color.White;
            renderer.Draw(g, s, da);
        }

        // Draw the stroke IDs in the top-left corner of each stroke's
        // bounding rectangle for an Ink object
        public static void DrawStrokeIds(Graphics g, Font font, Ink ink)
        {
            DrawStrokeIds(new Renderer(), g, font, ink.Strokes);
        }

        // Draw the stroke IDs for a Strokes collection
        public static void DrawStrokeIds(
            Renderer renderer, Graphics g, Font font, Strokes strokes)
        {
            // Iterate through every stroke referenced by the collection
            foreach (Stroke s in strokes)
            {
                // Make sure each stroke has not been deleted
                if (!s.Deleted)
                {
                    // Draw the stroke's ID at its starting point
                    string str = s.Id.ToString();
                    Point pt = s.GetPoint(0);
                    renderer.InkSpaceToPixel(g, ref pt);
                    g.DrawString(
                        str, font, Brushes.White, pt.X-1, pt.Y-1);
                    g.DrawString(
                        str, font, Brushes.White, pt.X+1, pt.Y+1);
                    g.DrawString(
                        str, font, Brushes.Black, pt.X, pt.Y);
                }
            }
        }

        // Draw the bounding rect of each stroke in an Ink object
        public static void DrawBoundingBoxes(Graphics g, Ink ink)
        {
            DrawBoundingBoxes(new Renderer(), g, ink.Strokes,
                Pens.LightGreen, BoundingBoxMode.Default);
        }

        // Draw the various bounding rects of each stroke in a strokes
        // collection
        public static void DrawBoundingBoxes(Renderer renderer,
            Graphics g, Strokes strokes, Pen pen, BoundingBoxMode mode)
        {
            foreach (Stroke s in strokes)
            {
                // Make sure each stroke has not been deleted
                if (!s.Deleted)
                {
                    Rectangle rcBounds = s.GetBoundingBox(mode);
                    RendererEx.InkSpaceToPixel(renderer, g, ref rcBounds);
                    g.DrawRectangle(pen, rcBounds);
                }
            }
        }

        public enum StrokePointType
        {
            Polyline,
            Bezier,
            FlattenedBezier
        }


        // Draw the polyline points each stroke has in an Ink object
        public static void DrawPoints(Graphics g, Ink ink)
        {
            DrawPoints(new Renderer(), g, ink.Strokes, Brushes.Red,
                StrokePointType.Polyline);
        }

        // Draw the various kinds of points each stroke has in a
        // strokes collection
        public static void DrawPoints(Renderer renderer, Graphics g,
            Strokes strokes, Brush brush, StrokePointType type)
        {
            foreach (Stroke s in strokes)
            {
                // Make sure each stroke has not been deleted
                if (!s.Deleted)
                {
                    DrawPoints(renderer, g, s, brush, type);
                }
            }
        }

        // Draw the various kinds of points for a stroke
        public static void DrawPoints(Renderer renderer, Graphics g,
            Stroke stroke, Brush brush, StrokePointType type)
        {
            // Get the array of points according to the type desired
            Point [] pts = null;
            switch (type)
            {
                case StrokePointType.Bezier:
                    pts = stroke.BezierPoints;
                    break;

                case StrokePointType.FlattenedBezier:
                    pts = stroke.GetFlattenedBezierPoints();
                    break;

                case StrokePointType.Polyline:
                    pts = stroke.GetPoints();
                    break;
            }

            // Render the points if they were retrieved
            if (pts != null)
            {
                renderer.InkSpaceToPixel(g, ref pts);
                foreach (Point pt in pts)
                {
                    g.FillEllipse(brush, pt.X-1, pt.Y-1, 4, 4);
                }
            }
        }

        public enum StrokeIntersectionType
        {
            Self,
            Stroke,
            BoundingBox
        }

        // Draw the stroke intersections for the strokes in an Ink object
        public static void DrawIntersections(Graphics g, Ink ink)
        {
            DrawIntersections(new Renderer(), g, ink.Strokes, 
                Pens.DarkRed, StrokeIntersectionType.Stroke);
        }

        // Draw the various intersections for the strokes in a Strokes
        // collection
        public static void DrawIntersections(
            Renderer renderer, Graphics g, Strokes strokes,
            Pen pen, StrokeIntersectionType type)
        {
            foreach (Stroke s in strokes)
            {
                // Make sure each stroke has not been deleted
                if (!s.Deleted)
                {
                    if (type == StrokeIntersectionType.BoundingBox)
                    {
                        // Draw bounding box intersections
                        DrawIntersections(renderer, g, s, pen);
                    }
                    else
                    {
                        // Compute either self or stroke intersections
                        float[] fResults = null;
                        switch (type)
                        {
                            case StrokeIntersectionType.Self:
                                fResults = s.SelfIntersections;
                                break;

                            case StrokeIntersectionType.Stroke:
                                fResults = s.FindIntersections(null);
                                break;
                        }

                        // Draw the intersections (if any)
                        if (fResults != null)
                        {
                            DrawIntersection(
                                renderer, g, s, fResults, pen);
                        }
                    }
                }
            }
        }

        // Helper function to draw intersections between each stroke's
        // bounding rect and all other strokes
        private static void DrawIntersections(Renderer renderer,
            Graphics g, Stroke s, Pen pen)
        {
            Rectangle rcBounds = renderer.Measure(s);

            // Generate a strokes collection containing all strokes
            // except the one being used for its bounding rect
            Strokes strksToCheck = s.Ink.CreateStrokes();
            strksToCheck.Add(s.Ink.Strokes);
            strksToCheck.Remove(s);

            foreach (Stroke s2 in strksToCheck)
            {
                if (!s2.Deleted)
                {
                    StrokeIntersection[] siResults =
                        s2.GetRectangleIntersections(rcBounds);

                    ArrayList arrResults = new ArrayList();
                    foreach (StrokeIntersection si in siResults)
                    {
                        if (si.BeginIndex >= 0)
                        {
                            arrResults.Add(si.BeginIndex);
                        }
                        if (si.EndIndex > 0)
                        {
                            arrResults.Add(si.EndIndex);
                        }
                    }

                    if (arrResults.Count > 0)
                    {
                        // Fill up a float array with the intersection
                        // indicies
                        float[] fResults =
                            (float[])arrResults.ToArray(typeof(float));

                        // Use a handy helper to draw the intersections
                        DrawIntersection(renderer, g, s2, fResults, pen);
                    }
                }
            }
        }

        // Helper function to draw intersections along a stroke
        private static void DrawIntersection(Renderer renderer,
            Graphics g, Stroke s, float[] fIndicies, Pen pen)
        {
            foreach (float fIndex in fIndicies)
            {
                // Get the whole-number point of the intersection
                int nIndex = (int)fIndex;
                Point pt = s.GetPoint(nIndex);

                // Compute the fractional point of the intersection if
                // possible
                if (nIndex < s.GetPoints().Length - 1)
                {
                    float fFraction = fIndex - nIndex;
                    Point pt2 = s.GetPoint(nIndex+1);
                    pt.X += (int)Math.Round((pt2.X - pt.X) * fFraction);
                    pt.Y += (int)Math.Round((pt2.Y - pt.Y) * fFraction);
                }

                renderer.InkSpaceToPixel(g, ref pt);
                g.DrawEllipse(pen, pt.X-3, pt.Y-3, 7, 7);
            }
        }

        public enum StrokeCuspType
        {
            Bezier,
            Polyline
        }

        // Draw the polyline cusps for the strokes in an Ink object
        public static void DrawCusps(Graphics g, Ink ink)
        {
            DrawCusps(new Renderer(), g, ink.Strokes,
                Pens.Blue, StrokeCuspType.Polyline);
        }

        // Draw the various cusps for the strokes in a strokes
        // collection
        public static void DrawCusps(Renderer renderer, Graphics g,
            Strokes strokes, Pen pen, StrokeCuspType type)
        {
            foreach (Stroke s in strokes)
            {
                // Make sure each stroke has not been deleted
                if (!s.Deleted)
                {
                    DrawCusps(renderer, g, s, pen, type);
                }
            }
        }

        // Draw the various cusps for a stroke
        public static void DrawCusps(Renderer renderer, Graphics g,
            Stroke stroke, Pen pen, StrokeCuspType type)
        {
            // Get the cusp indexes and point array according to the
            // type desired
            int [] cusps = null;
            Point [] pts = null;
            switch (type)
            {
                case StrokeCuspType.Bezier:
                    cusps = stroke.BezierCusps;
                    pts = stroke.BezierPoints;
                    break;

                case StrokeCuspType.Polyline:
                    cusps = stroke.PolylineCusps;
                    pts = stroke.GetPoints();
                    break;
            }

            // Render the points if they were retrieved
            if (cusps != null && pts != null)
            {
                foreach (int n in cusps)
                {
                    Point pt = pts[n];
                    renderer.InkSpaceToPixel(g, ref pt);
                    g.DrawEllipse(pen, pt.X-3, pt.Y-3, 7, 7);
                }
            }
        }

		public enum InsertionPointType
		{
			None,
			LastPoint,
			FirstVertical,
			DirectionChange,
			LawOfCosines
		}

		// Draw the various kinds of points each stroke has in a
		// strokes collection
		public static void DrawInsertionPoint(Renderer renderer, Graphics g,
			Strokes strokes, Pen pen, InsertionPointType type, int windowSize)
		{
			foreach (Stroke s in strokes)
			{
				// Make sure each stroke has not been deleted
				if (!s.Deleted)
				{
					DrawInsertionPoint(renderer, g, s, pen, type, windowSize);
				}
			}
		}

		// Draw the various kinds of points for a stroke
		public static void DrawInsertionPoint(Renderer renderer, Graphics g,
			Stroke stroke, Pen pen, InsertionPointType type, int windowSize)
		{
			// Get the array of points according to the type desired
			Point pt = Point.Empty;
			switch (type)
			{
				case InsertionPointType.LastPoint:
				{
					pt = _calculateInsertionPoint_LastPoint(stroke);
					break;
				}
				case InsertionPointType.FirstVertical:
				{
					pt = _calculateInsertionPoint_FirstVertical(stroke);
					break;
				}
				case InsertionPointType.DirectionChange:
				{
					pt = _calculateInsertionPoint_DirectionChange(stroke);
					break;
				}
				case InsertionPointType.LawOfCosines:
				{
					pt = _calculateInsertionPoint_LawOfCosines(stroke, windowSize);
					break;
				}
				default:
				{
					pt = Point.Empty;
					break;
				}
			}

			// Render the points if they were retrieved
			if (pt != Point.Empty)
			{
				renderer.InkSpaceToPixel(g, ref pt);
				g.FillEllipse(Brushes.Blue, pt.X-3, pt.Y-3, 7, 7);
				
			}
		}

		private static Point _calculateInsertionPoint_LastPoint(Stroke stroke) 
		{
			Point insertionPoint = Point.Empty;

			// get the points
			Point[] pts = stroke.GetPoints();

			// get the last point
			insertionPoint = pts[pts.GetLength(0) - 1];

			return insertionPoint;
		}

		private static Point _calculateInsertionPoint_FirstVertical(Stroke stroke) 
		{
			Point insertionPoint = Point.Empty;

			// get the points
			Point[] pts = stroke.GetPoints();

			// base case (a dot)
			if(pts.GetLength(0) == 1) 
			{
				return pts[0];
			}

			ArrayList slopes = new ArrayList(pts.GetLength(0));

			Point max = new Point(0, Int16.MinValue);
			Point pt1 = pts[0];			
			Point pt2 = pts[1];
			// do some calculus to find the vertical slopes
			for(int i = 1; i < pts.GetLength(0); i++) 
			{
				pt2 = pts[i];
				

				Point slope = Point.Empty;

				int y = 0;

				// vertical!
				if(pt2.X - pt1.X == 0 && pt2.Y - pt1.Y != 0) 
				{
					y = Int32.MaxValue;
				}
				else 
				{
					if(pt2.X - pt1.X == 0 && pt2.Y - pt1.Y == 0)
					{
						y = 0;
					}
					else 
					{
						// we're just estimating anyways
						y = (int)((pt2.Y - pt1.Y) / (pt2.X - pt1.X));

						if(y < 0) y = y * -1;
					}
				}

				int x = (int)((pt2.X + pt1.X) / 2);
				Point derv = new Point(x, y);
				slopes.Add(derv);

				// if have a bigger Y!
				if(derv.Y > max.Y) 
				{
					max = derv;
					insertionPoint = pt2;
				}

				pt1 = pt2;
			}

			// now find out the first maximum value of the slope
			

			// just use the first vertical slope that we found (it's mid point)

			return insertionPoint;
		}

		// returns the slope between two points
		private static int slope(Point p1, Point p2) 
		{
			// rise over run
			int value = 0;
			
			try 
			{
				/*
				if(p2.X - p1.X == 0) 
				{
					if(p2.Y != p1.Y) 
					{
						value = Int32.MaxValue;
					}
				}
				*/
				if(p2.X != p1.X)
				{
					value = (int)((p2.Y - p1.Y)/(p2.X - p1.X));
				}
			}
			catch(Exception err)
			{
				Console.Out.WriteLine(err);
			}

			return value;
		}

		// returns midpoint between two points
		private static Point midpoint(Point p1, Point p2) 
		{
			Point mid = Point.Empty;

			mid.X = (int)((p1.X + p2.X) / 2);
			mid.Y = (int)((p1.Y + p2.Y) / 2);

			return mid;
		}

		// calculate the length/distance of a line segment from the two end points
		private static double distance(Point p1, Point p2) 
		{
			double hypothenus = 0;

			// make a right triangle out of them!!!
			double side1 = Math.Abs(p1.X - p2.X);
			double side2 = Math.Abs(p1.Y - p2.Y);
			
			// use sqrt(a^2 + b^2) = c
			hypothenus = Math.Sqrt(Math.Pow(side1, 2) + Math.Pow(side2, 2));
			
			return hypothenus;
		}

		// use law of cosines to determine the angle made by
		// line segmenet AB and BC (acute angle between them)
		// can infer line segment AC to make an opaque triangle
		private static double calculateAngle(Point A, Point B, Point C) 
		{
			double angle = 0;

			double numerator = Math.Pow(distance(A, B), 2) + Math.Pow(distance(B, C), 2) - Math.Pow(distance(A, C), 2);
			double denominator = 2 * distance(A, B) * distance(B, C); 
			
			// make sure we don't divide by zero or try to do Acos with something not in 
			//   range -1 <= x <= 1 as either one will result in NaN when we really want
			//   to say that it's just so damn close to being a line that we'll just
			//   say that the angle is 180 degrees and be done with it
			if(denominator != 0 && Math.Abs(numerator / denominator) <= 1) 
			{
				// calculate and convert to degrees from radians
				angle = (180 / Math.PI) * Math.Acos(numerator / denominator);
			}
			else {
				// denom = 0... must be a straight line... say angle is 180!
				angle = 180;
			}
			//angle = Math.Acos(numerator / denominator);

			Trace.Assert(angle >= 0, "Angle not >= 0!");
			Trace.Assert(angle <= 180, "Angle not <= 180!");
			Trace.Assert(angle != Double.NaN, "Angle should be a number!!");

			return angle;
		}


		[Test]
		public void testCalculateAngle() 
		{
			// test a right angle
			Point A = new Point(50,50);
			Point B = new Point(55,55);
			Point C = new Point(60,50);
			Assertion.AssertEquals(90, calculateAngle(A,B,C));

			// test a 60 degree angle
			B = new Point(55,59);		
			Assertion.AssertEquals(58.1092082, Math.Round(calculateAngle(A,B,C), 7));

			A = new Point(5371,1058);
			B = new Point(5424,1217);
			C = new Point(5530,1535);
			Assertion.AssertEquals(179.657184, Math.Round(calculateAngle(A,B,C), 6));
		}

		/** 
		 * Law of Cosines
		 * Given points A, B, and C where the user draw line AB and line BC we can 
		 * infer line AC and obtain a triangle. Since there is no guarantee about the 
		 * type of triangle, we have to assume that it is an oblique triangle. Using the law 
		 * of cosines and arccosine we can determine angle ABC (the angle at B formed by 
		 * AB and BC).
		 * 
		 * Rather than translating this angle into 0 to 360 space, wouldn't it be 
		 * sufficient to simple calculate the angle ABC using a sliding window across 
		 * the stroke data and taking the smallest angle that we find? The most acute 
		 * angle would indicate that there was a very large change in direction from 
		 * AB to BC irrespective of the orientation on the XY axis.
		 * 
		 * Trying to find angle ABC (where u is).
		 * 
		 *         B
		 *        /u\
		 *       /   \
		 *      /     \
		 *     A       C
		 *  
		 * The smallest angle in the stroke is the largest direction change!!!!!
		 */
		private static Point _calculateInsertionPoint_LawOfCosines(Stroke stroke, int window_size) 
		{
			Trace.Assert(window_size >= 3);
			// make sure it's odd
			Trace.Assert(window_size % 2 == 1);

			// the insertion point
			Point insertionPoint = Point.Empty;

			// get the points
			Point[] pts = stroke.GetPoints();

			// should always have at least one point
			Trace.Assert(pts.Length > 0, "Point array is empty!");

			// base case (a dot)
			if(pts.GetLength(0) == 1) 
			{
				// only one point - that must be it!
				insertionPoint = pts[0];
			}
			else 
			{
				// base case (a line with only start and end points)
				if(pts.GetLength(0) == 2) 
				{
					// take the midpoint!
					insertionPoint =  midpoint(pts[0], pts[1]);
				} 
				else // GetLength > 2
				{	
					if(pts.GetLength(0) < window_size) 
					{
						// larger window size than # points; let's decrease the window size
						// and run it on the stroke
						int smaller_window = pts.GetLength(0);

						// make sure it's odd and smaller than the # points
						if(smaller_window % 2 == 0) 
						{
							smaller_window--;
						}

						insertionPoint = _calculateInsertionPoint_LawOfCosines(stroke, smaller_window);	
					}
					else 
					{

						// first, calculate the angle between all of the line segments formed
						double[] angles = new double[pts.GetLength(0) - window_size];

						// for i = 0 to length - window size
						for(int i = 0; i < pts.GetLength(0) - window_size; i++) 
						{
							// calculate the slope and add it to the list
							angles[i] = calculateAngle(pts[i], pts[i+(int)Math.Floor(window_size/2)], pts[i + window_size]);
						}
				
						// now just find the minimum slope!				
						int indexOfMinAngle = 0;

						// now find the maximum difference
						for(int i = 1; i < angles.Length; i++) 
						{
							if(angles[i] < angles[indexOfMinAngle]) 
							{
								// new minimum!
								indexOfMinAngle = i;
							}
						}
					
						// wanted the index, not the min angle because
						// we can translate from the index of the min angle
						// in the array back to the point B in the original array
						// of points to find the point B in smallest angle ABC
						insertionPoint = pts[indexOfMinAngle + (int)Math.Floor(window_size / 2)];
					
						Console.Out.WriteLine(insertionPoint);
					}
				}
			}
			
			Trace.Assert(insertionPoint != Point.Empty, "Insertion point is empty!");
			return insertionPoint;
		}
    
		/*
		 * finds the max change in slope between two points
		 * A B C D, slope(A,B) slope(B,C) slope(C,D)
		 *  max(abs(slope(A,B) - slope(B,C)), abs(slope(B,C) - slope(C,D)))
		 *  then use       B                               C
		 * 
		 * So we'll discount the first and last point as these typically won't be the
		 * right ones (i.e. We assume that as long as Points.count >= 3 we'll be fine 
		 * with this calculation! If count <= 2 then pick first or last and move on.) 
		 */
		private static Point _calculateInsertionPoint_DirectionChange(Stroke stroke) 
		{
			// the insertion point
			Point insertionPoint = Point.Empty;

			// get the points
			Point[] pts = stroke.GetPoints();

			// should always have at least one point
			Trace.Assert(pts.Length > 0, "Point array is empty!");

			// base case (a dot)
			if(pts.GetLength(0) == 1) 
			{
				// only one point - that must be it!
				insertionPoint = pts[0];
			}
			else 
			{
				// base case (a line with only start and end points)
				if(pts.GetLength(0) == 2) 
				{
					// take the midpoint!
					insertionPoint =  midpoint(pts[0], pts[1]);
				} 
				else // GetLength > 2
				{
					// first, calculate all of the slopes
					ArrayList slopes = new ArrayList();

					// for i = 0 to length - 1
					for(int i = 0; i < pts.GetLength(0) - 1; i++) 
					{
						// calculate the slope and add it to the list
						slopes.Add(slope(pts[i], pts[i+1]));
					}

					// now find the absolute difference between consecutive slopes
					// (pair this difference with the common point between these slopes)
					// i.e. abs(slope(A,B) - slope(B,C) pairs with B
					// mapping of slopes to slopeDiffs
					// s[i]  point[i]   sD[i]  paired point
					// 0      0 1       --     --
					// 1      1 2       0      pts[1]
					// 2      2 3       1      pts[2]
					// 3      3 4       2      pts[3]
					// 4      4 5       3      pts[4]
					// slopes[i] and slopes[i+1] corresponds to commond point pts[i+1]					
					ArrayList diffs = new ArrayList();
					int maxDiff = -1;
					// now find the maximum difference
					for(int i = 1; i < slopes.Count; i++) 
					{
						int currDiff = Math.Abs(((int)slopes[i-1])-((int)slopes[i]));
						diffs.Add(currDiff);

						// take the first largest directional change
						if(currDiff > maxDiff) 
						{
							maxDiff = currDiff;
							// use the paired point with that difference
							insertionPoint = pts[i];
						}
					}

					Console.Out.Write(insertionPoint);
				}
			}

			Trace.Assert(insertionPoint != Point.Empty, "Insertion point is empty!");
			return insertionPoint;
		}
    }
}
