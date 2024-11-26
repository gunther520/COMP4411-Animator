#include "beziercurveevaluator.h"
#include "mat.h"
#include "vec.h"
#include <cassert>

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap) const
{
	ptvEvaluatedCurvePts.clear();

	std::vector<Point> controlPoints;


	if (!bWrap) {
		// Ensure the curve starts and ends at the first and last control points
		ptvEvaluatedCurvePts.push_back(Point(0.0, ptvCtrlPts[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
		controlPoints.insert(controlPoints.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
	}
	else {
		// if wrapping is on, interpolate the y value at xmin and
		// xmax so that the slopes of the lines adjacent to the
		// wraparound are equal.
		float x0 = ptvCtrlPts[0].x;
		float x1 = ptvCtrlPts.back().x + fAniLength;
		float y0 = ptvCtrlPts[0].y;
		float y1 = ptvCtrlPts.back().y;
		float m = (y1 - y0) / (x1 - x0);
		float new_y = y1 + m * (fAniLength - x1);

		ptvEvaluatedCurvePts.push_back(Point(0.0, new_y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, new_y));
		controlPoints.push_back(Point(0.0, new_y));
		controlPoints.insert(controlPoints.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		controlPoints.push_back(Point(fAniLength, new_y));
	}
	




	for (size_t i = 0; i + 3 < controlPoints.size(); i += 3) {
		Point p0 = controlPoints[i];
		Point p1 = controlPoints[i + 1];
		Point p2 = controlPoints[i + 2];
		Point p3 = controlPoints[i + 3];

		for (float t = 0; t <= 1.0; t += 0.05f) {
			float u = 1 - t;
			float tt = t * t;
			float uu = u * u;
			float ttt = tt * t;
			float uuu = uu * u;

			Point p = p0 * uuu; // u^3 * p0
			p += p1 * (3 * uu * t); // 3 * u^2 * t * p1
			p += p2 * (3 * u * tt); // 3 * u * t^2 * p2
			p += p3 * ttt; // t^3 * p3

			ptvEvaluatedCurvePts.push_back(p);
		}
	}

	if (ptvEvaluatedCurvePts.size() <= 3) {
		ptvEvaluatedCurvePts.insert(ptvEvaluatedCurvePts.end(), controlPoints.begin(), controlPoints.end());
	}


	

}
