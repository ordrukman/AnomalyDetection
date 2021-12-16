/*
 * Or Drukman 209090000
 * Yotam Levin 313248916
 */

#include "minCircle.h"
#include <random>
#include <vector>
#include <math.h>
#include <time.h>
#include <algorithm>    // std::random_shuffle

// calling Welzl's recursive algorithm to find the smallest-circle,
// using vector of points and shuffle the points order in the vector to optimize the running time.
Circle findMinCircle(Point** points, size_t size){
    vector<Point> pointsVector;
    pointsVector.reserve(size);
    for (int i = 0; i < size; ++i) {
        pointsVector.push_back(*points[i]);
    }
    vector<Point> pointsVector_copy = pointsVector;
    // shuffle the points order, using the <algorithm> library
    shuffle(pointsVector_copy.begin(), pointsVector_copy.end(), std::mt19937(std::random_device()()));
    vector<Point> r = {};
    Circle minCircle = welzlAlgoithm(pointsVector_copy, r, size);
    return minCircle;
}

// Using Welzl's recursive algorithm, to solve the smallest-circle problem.
Circle welzlAlgoithm(const vector<Point> &p, vector<Point> r, size_t pSize){
    if (pSize == 0 || (r.size() == 3)){
        return minCircleTrivial(r);
    }
    Circle newCircle = welzlAlgoithm(p, r, pSize - 1);
    if (isPointInCircle(newCircle, p[pSize - 1])){
        return newCircle;
    }
    r.push_back(p[pSize - 1]);
    return welzlAlgoithm(p, r, pSize - 1);
}

// returns true if the given point is inside the circle, otherwise returns false
bool isPointInCircle(const Circle &circle, const Point &point) {
    return (distanceOfTwoPoints(circle.center, point) <= circle.radius);
}

// returns the minimum circle by the different points from the r vector
Circle minCircleTrivial(const vector<Point> &r) {
    switch (r.size()) {
        case 0:
            return {{0, 0}, 0};
        case 1:
            return {r[0], 0};
        case 2:
            return getCircleByPoints(r[0], r[1]);
        case 3:
            return getCircleByPoints(r[0], r[1], r[2]);
    }
}

// returns the circle that 2 different points create
Circle getCircleByPoints(const Point &point1, const Point &point2){
    float xCenter = (point1.x + point2.x)/2;
    float yCenter = (point1.y + point2.y)/2;
    Point center = {xCenter, yCenter};
    float radius = distanceOfTwoPoints(point1, point2)/2;
    return {center, radius};
}

// returns the circle that 3 different points create
Circle getCircleByPoints(const Point &point1, const Point &point2, const Point &point3){
    Point p = getCircleCenter(point2.x - point1.x, point2.y - point1.y,
                                point3.x - point1.x, point3.y - point1.y);
    p.x += point1.x;
    p.y += point1.y;
    return { p, distanceOfTwoPoints(p, point1) };
    }

// returns the center point of the circle that 3 different points create
Point getCircleCenter(float dis2to1X, float dis2to1Y, float dis3to1X, float dis3to1Y){
    float B = pow(dis2to1X, 2) + pow(dis2to1Y, 2);
    float C = pow(dis3to1X, 2) + pow(dis3to1Y, 2);
    float D = dis2to1X * dis3to1Y - dis2to1Y * dis3to1X;
    return { ((dis3to1Y * B) - (dis2to1Y * C)) / (2 * D),
             ((dis2to1X * C) - (dis3to1X * B)) / (2 * D) };
}

// returns the distance between two points
float distanceOfTwoPoints(const Point &a, const Point &b){
    return sqrt(pow(a.x - b.x, 2)
                + pow(a.y - b.y, 2));
}