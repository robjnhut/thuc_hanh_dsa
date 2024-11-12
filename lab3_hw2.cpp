//22520251-Nguyen Huu Dinh

#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

struct Point {
    double x, y;
};

// Function to compare points based on x-coordinate
bool compareX(Point a, Point b) {
    return a.x < b.x;
}

// Function to compare points based on y-coordinate
bool compareY(Point a, Point b) {
    return a.y < b.y;
}

// Function to calculate the distance between two points
double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute force method to find the smallest distance between points in a small subset
double bruteForce(Point points[], int n) {
    double minDist = numeric_limits<double>::infinity();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = distance(points[i], points[j]);
            if (dist < minDist)
                minDist = dist;
        }
    }
    return minDist;
}

// Function to find the minimum distance for points close to the line between two halves
double stripClosest(Point strip[], int size, double d) {
    double minDist = d;
    sort(strip, strip + size, compareY);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; ++j) {
            double dist = distance(strip[i], strip[j]);
            if (dist < minDist)
                minDist = dist;
        }
    }
    return minDist;
}

// Recursive function to find the closest pair distance
double closestUtil(Point points[], int n) {
    if (n <= 3)
        return bruteForce(points, n);

    int mid = n / 2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, mid);
    double dr = closestUtil(points + mid, n - mid);

    double d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (fabs(points[i].x - midPoint.x) < d)
            strip[j++] = points[i];

    return min(d, stripClosest(strip, j, d));
}

// Main function to find the closest pair
double closest(Point points[], int n) {
    sort(points, points + n, compareX);
    return closestUtil(points, n);
}

int main() {
    int n;
    cout << "Enter the number of points: ";
    cin >> n;

    Point points[n];
    cout << "Enter the coordinates of the points (x y):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    double minDistance = closest(points, n);
    cout << "The smallest distance between two points is: " << minDistance << endl;

    return 0;
}
