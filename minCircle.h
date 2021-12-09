
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"
#include <set>

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

// calling Welzl's recursive algorithm to find the smallest-circle,
// using vector of points and shuffle the points order in the vector to optimize the running time.
Circle findMinCircle(Point** points,size_t size);

// Using Welzl's recursive algorithm, to solve the smallest-circle problem.
Circle welzlAlgoithm(const vector<Point> &p, vector<Point> r, size_t pSize);

// returns true if the given point is inside the circle, otherwise returns false
bool isPointInCircle(const Circle &circle, const Point &point);

// returns the minimum circle by the different points from the r vector
Circle minCircleTrivial(const vector<Point> &r);

// returns the circle that 2 different points create
Circle getCircleByPoints(const Point &point1, const Point &point2);

// returns the circle that 3 different points create
Circle getCircleByPoints(const Point &point1, const Point &point2, const Point &point3);

// returns the center point of the circle that 3 different points create
Point getCircleCenter(float dis2to1X, float dis2to1Y, float dis3to1X, float dis3to1Y);

// returns the distance between two points
float distanceOfTwoPoints(const Point &a, const Point &b);

#endif /* MINCIRCLE_H_ */
