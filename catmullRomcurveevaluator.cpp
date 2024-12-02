#include "catmullromcurveevaluator.h"
#include "mat.h"
#include "vec.h"
#include <cassert>

void CatmullRomCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
    std::vector<Point>& ptvEvaluatedCurvePts,
    const float& fAniLength,
    const bool& bWrap) const
{
    ptvEvaluatedCurvePts.clear();

    std::vector<Point> newControlPoints;

    if (!bWrap) {
        // Add duplicates of the first and last points for boundary conditions
        newControlPoints.push_back(Point(ptvCtrlPts[0].x, ptvCtrlPts[0].y));
        newControlPoints.insert(newControlPoints.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
        newControlPoints.push_back(Point(ptvCtrlPts.back().x, ptvCtrlPts.back().y));
        ptvEvaluatedCurvePts.push_back(Point(0.0, ptvCtrlPts[0].y));
        ptvEvaluatedCurvePts.push_back(Point(fAniLength, ptvCtrlPts.back().y));
    }
    else {
        // Wrapping logic
        float x0 = ptvCtrlPts[0].x;
        float x1 = ptvCtrlPts.back().x + fAniLength;
        float y0 = ptvCtrlPts[0].y;
        float y1 = ptvCtrlPts.back().y;
        float m = (y1 - y0) / (x1 - x0);
        float new_y = y1 + m * (fAniLength - x1);
        newControlPoints.push_back(Point(0.0, new_y));
        newControlPoints.push_back(Point(0.0, new_y));
        //newControlPoints.push_back(Point(ptvCtrlPts.back().x - fAniLength, y0));
        newControlPoints.insert(newControlPoints.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
        //newControlPoints.push_back(Point(ptvCtrlPts[0].x + fAniLength, y1));
        newControlPoints.push_back(Point(fAniLength, new_y));
        newControlPoints.push_back(Point(fAniLength, new_y));
    }

    // Catmull-Rom basis matrix
    Mat4f basisMatrix = Mat4f(
        -0.5f, 1.5f, -1.5f, 0.5f,
        1.0f, -2.5f, 2.0f, -0.5f,
        -0.5f, 0.0f, 0.5f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f
    );

    float step = 0.05f; // Adjustable resolution
    for (size_t i = 0; i + 3 < newControlPoints.size(); i++) {
        Vec4f px(newControlPoints[i].x, newControlPoints[i + 1].x, newControlPoints[i + 2].x, newControlPoints[i + 3].x);
        Vec4f py(newControlPoints[i].y, newControlPoints[i + 1].y, newControlPoints[i + 2].y, newControlPoints[i + 3].y);

        for (float t = 0; t <= 1.0; t += step) {
            Vec4f T(t * t * t, t * t, t, 1);
            float x = (T * basisMatrix) * px;
            float y = (T * basisMatrix) * py;
            ptvEvaluatedCurvePts.push_back(Point(x, y));
        }
    }
}
