#ifndef ALGORYTHM_H
#define ALGORYTHM_H

#include <vector>
#include <limits>

using namespace std;

const double ZERO = 1e-9;

struct Point
{
    double x, y;
    int index;
};

struct Result
{
    double distance;
    Point p1, p2;
};

double vector_dir(Point p0, Point p1, Point p2);
double distance(Point p1, Point p2);

vector<Point> build_ring(vector<Point> &points);

double point_line_distance(Point P, Point P1, Point P2);
double minimal_parallel_width(const vector<Point> &ring);

Result find_closest_pair(vector<Point> &points);

#endif