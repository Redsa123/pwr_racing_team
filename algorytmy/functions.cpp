#include "./algorythm.h"
#include <algorithm>
#include <cmath>

using namespace std;

Point P0;

double vector_dir(Point p0, Point p1, Point p2)
{
	return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

double distance(Point p1, Point p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool compare_points(Point p1, Point p2)
{
	double dir = vector_dir(P0, p1, p2);
	if (abs(dir) > ZERO)
		return dir > 0;
	return distance(P0, p1) < distance(P0, p2);
}

bool compare_x(const Point&a, const Point&b)
{
	return a.x < b.x;
}

bool compare_y(const Point&a, const Point&b)
{
	return a.y < b.y;
}

vector<Point> build_ring(vector<Point>&points)
{
	int n = points.size();
	if (n < 3)
		return points;

	int min_idx = 0;
	for (int i = 1; i < n; i++)
	{
		if (points[i].y < points[min_idx].y ||
			(abs(points[i].y - points[min_idx].y) < ZERO && points[i].x < points[min_idx].x))
		{
			min_idx = i;
		}
	}

	swap(points[0], points[min_idx]);
	P0 = points[0];

	sort(points.begin() + 1, points.end(), compare_points);

	int m = 1;

	for (int i = 1; i < n; i++)
	{
		while (i <= n && abs(vector_dir(P0, points[i], points[i + 1])) < ZERO)
		{
			i++;
		}
		points[m] = points[i];
		m++;
	}
	if (m < 3)
		return vector<Point>(points.begin(), points.begin() + m);

	vector<Point> ring;
	ring.push_back(points[0]);
	ring.push_back(points[1]);
	ring.push_back(points[2]);

	for (int i = 3; i < m; i++)
	{
		while (ring.size() >= 2 && vector_dir(ring[ring.size() - 2], ring[ring.size() - 1], points[i]) <= ZERO)
		{
			ring.pop_back();
		}
		ring.push_back(points[i]);
	}

	return ring;
}

double point_line_distance(Point P, Point P1, Point P2)
{
	double numerator = abs((P2.x - P1.x) * (P1.y - P.y) - (P1.x - P.x) * (P2.y - P1.y));
	double denominator = distance(P1, P2);

	if (denominator < ZERO)
		return 0.0;

	return numerator / denominator;
}

double minimal_parallel_width(const vector<Point>&ring)
{
	int r = ring.size();
	if (r <= 2)
		return 0.0;

	double min_width = numeric_limits<double>::max();

	int j = 1;

	for (int i = 0; i < r; i++)
	{
		Point P1 = ring[i];
		Point P2 = ring[i + 1];

		while (vector_dir(P1, P2, ring[j + 1]) > vector_dir(P1, P2, ring[j]) + ZERO)
		{
			j = (j + 1) % r;
		}

		double cur_width = point_line_distance(ring[j], P1, P2);
		min_width = min(min_width, cur_width);
	}

	return min_width;
}

Result closest_pair_small(const vector<Point>&points, int start, int end)
{
	Result min_res = {numeric_limits<double>::max(), {}, {}};
	for (int i = start; i <= end; i++)
	{
		for (int j = i + 1; j <= end; j++)
		{
			double dist = distance(points[i], points[j]);
			if (dist < min_res.distance)
			{
				min_res = {dist, points[i], points[j]};
			}
		}
	}
	return min_res;
}

Result closest_pair_strip(const vector<Point>&strip, double d)
{
	Result min_res = {d, {}, {}};

	for (long i = 0; i < strip.size(); i++)
	{
		for (long j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++)
		{
			double dist = distance(strip[i], strip[j]);
			if (dist < min_res.distance)
			{
				min_res = {dist, strip[i], strip[j]};
			}
		}
	}
	return min_res;
}

Result closest_pair(const vector<Point>&Px, const vector<Point>&Py)
{
	int n = Px.size();

	if (n <= 3)
		return closest_pair_small(Px, 0, n - 1);

	int mid = n / 2;
	Point median_point = Px[mid];

	vector<Point> Px_L(Px.begin(), Px.begin() + mid);
	vector<Point> Px_R(Px.begin() + mid, Px.end());

	vector<Point> Py_L, Py_R;
	for (const auto&p : Py)
	{
		if (p.x < median_point.x || (p.x == median_point.x && p.y <= median_point.y))
			Py_L.push_back(p);
		else
			Py_R.push_back(p);
	}

	Result res_L = closest_pair(Px_L, Py_L);
	Result res_R = closest_pair(Px_R, Py_R);

	Result min_res = (res_L.distance < res_R.distance) ? res_L : res_R;

	double d = min_res.distance;

	vector<Point> strip;

	for (const auto&p : Py)
	{
		if (abs(p.x - median_point.x) < d)
			strip.push_back(p);
	}

	Result res_strip = closest_pair_strip(strip, d);

	if (res_strip.distance < min_res.distance)
		return res_strip;
	else
		return min_res;
}

Result find_closest_pair(vector<Point>&points)
{
	vector<Point> Px = points;
	vector<Point> Py = points;

	sort(Px.begin(), Px.end(), compare_x);
	sort(Py.begin(), Py.end(), compare_y);

	return closest_pair(Px, Py);
}