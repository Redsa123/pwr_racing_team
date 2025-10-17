#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "algorythm.h"

using namespace std;

vector<Point> load_points(const string&filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Cannot open file " << filename << endl;
        return {};
    }

    int n;
    file >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++)
    {
        file >> points[i].x >> points[i].y;
        points[i].index = i;
    }
    file.close();

    cout << "Loaded " << n << " points from file " << filename << endl;
    return points;
}

void first_ring(vector<Point> points)
{
    vector<Point> ring = build_ring(points);

    cout << "Otoczka: (";
    for (size_t i = 0; i < ring.size(); ++i)
    {
        cout << ring[i].x << ", " << ring[i].y << ")";
        if (i < ring.size() - 1)
            cout << ", (";
    }
    cout << endl;
}

void second_parallels(vector<Point> points)
{
    vector<Point> ring = build_ring(points);
    double min_d = minimal_parallel_width(ring);

    cout << fixed << setprecision(4);
    cout << "Proste: d=" << min_d << endl;
}

void third_pairs(vector<Point> points)
{
    Result closest_res = find_closest_pair(points);

    cout << fixed << setprecision(3);
    cout << "Najblizsze Punkty: [(" << closest_res.p1.x << ", " << closest_res.p1.y << "), ("
         << closest_res.p2.x << ", " << closest_res.p2.y << ")] d=" << closest_res.distance << endl;
}

int main()
{
    string filename = "punkty.txt";

    vector<Point> points = load_points(filename);
    if (points.empty())
    {
        cerr << "Failed to load points. Program terminated." << endl;
        return 1;
    }

    first_ring(points);

    second_parallels(points);

    third_pairs(points);
    return 0;
}