#include <iostream>
#include <unordered_set>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
double dist_p(Point p, Point q);

namespace std {
template <> struct hash<std::pair<double, double>> {
    inline size_t operator()(const std::pair<double, double> &v) const {
        std::hash<int> int_hasher;
        return int_hasher(v.first) ^ int_hasher(v.second);
    }
};
}

class Edge {
public:
    Point p;
    Point q;
    double length;

    Edge() {

    }

    Edge(Point p, Point q) {
        this->p = p;
        this->q = q;
        length = dist_p(p, q);
    }
};

class Point {
public:
    double x;
    double y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
}


class Triangle {
public:
    Point vertex[3];
    Edge edge[3];
    Triangle(Point p1, Point p2, Point p3) {
        vertex[0] = p1;
        vertex[1] = p2;
        vertex[2] = p3;
        Edge edge1(p1, p2);
        Edge edge2(p1, p3);
        Edge edge3(p2, p3);
        edge[0] = edge1;
        edge[1] = edge2;
        edge[2] = edge3;
    }
};

class Circle {
public:
    double radius;
    Point center;
    Circle(Point center, double radius) {
        this->center = center;
        this->radius = radius;
    }
    Circle() {}
};

bool acute_triangle(Triangle& triangle);
bool p_circle(Circle& circle, Point& p);
Circle circumcenter(Triangle& triangle);
Circle circle_long_edge(Triangle& triangle, unordered_multiset<Point>& R);
Point mid_point(Point p, Point q);
Circle Welzl_algorithm(unordered_multiset<Point> P, unordered_multiset<Point>& R);
Circle calcDiskDirectly(unordered_multiset<Point> R);
unordered_multiset<Point>::iterator choose_random(unordered_multiset<Point>, size_t n);
void refreshR(Circle& circle, unordered_multiset<Point>& R);

int main() {
    std::unordered_multiset<int> s { 1, 2, 2, 3, 3, 3 };
    const auto it = s.find(2);
    if (it != s.end())
        s.erase(it);
    cout << s.size() << endl;
    unordered_multiset<Point> P; 
    unordered_multiset<Point> R;
    P.insert(make_pair(5, 7));
    P.insert(make_pair(3, 4));
    P.insert(make_pair(4, 2));
    P.insert(make_pair(5, 10));
    cout << rand() % P.size() << endl;
    auto random_it = next(begin(s), rand() % s.size());
    cout << R.empty() << endl;
    Circle circle;
    circle = Welzl_algorithm(P, R);
    cout << circle.radius << endl;
    return 0;
}

Circle Welzl_algorithm(unordered_multiset<Point> P, unordered_multiset<Point>& R) {
    Circle circle(make_pair(0, 0), 0);
    if (P.empty() || R.size() == 3) {
        circle = calcDiskDirectly(R);
    }
    else {
        auto random_it = next(begin(P), rand() % P.size());
        Point p = *random_it;
        cout << "RANDOM SELECTION - x: " << p.x << " y: " << p.y << endl;
        P.erase(random_it);
        cout << "P set: ";
        for (unordered_multiset<Point>::iterator it = P.begin(); it != P.end(); ++it) {
            cout << " x: " << (*it).x << " y: " << (*it).y;
        }
        cout << endl;
        circle = Welzl_algorithm(P, R);
        cout << "Circle = C(" << circle.center.x << ", " << circle.center.y << "), r: " << circle.radius << endl;
        refreshR(circle, R);
        if (!p_circle(circle, p)) {
            cout << "Point p(" << p.x << ", " << p.y << ") is not in Circle" << endl;
            R.insert(p);
            cout << "R  set: ";
            for (unordered_multiset<Point>::iterator it = R.begin(); it != R.end(); ++it) {
                cout << " x: " << (*it).x << " y: " << (*it).y;
            }
            cout << endl;
            circle = Welzl_algorithm(P, R);
        }
        cout << "Point p(" << p.x << ", " << p.y << ") LIES in the Circle" << endl;
    }
    return circle;
}

bool acute_triangle(Triangle& triangle) {
    vector<double> dists {pow(triangle.edge[0].length, 2), pow(triangle.edge[1].length, 2), pow(triangle.edge[2].length, 2)};
    vector<double>::iterator max_it = max_element(dists.begin(), dists.end());
    cout << "p1 - x: " << triangle.vertex[0].x << " y: " << triangle.vertex[0].y << endl;
    cout << "p2 - x: " << triangle.vertex[1].x << " y: " << triangle.vertex[1].y << endl;
    cout << "p3 - x: " << triangle.vertex[2].x << " y: " << triangle.vertex[2].y << endl;
    cout << "edge[0]: " << dists[0] << " edge[1]: " << dists[1] << " edge[2]: " << dists[2] << endl;
    double max_dist = *max_it;
    dists.erase(max_it);
    double sum_ab = 0;
    cout << "edge[0]: " << dists[0] << " edge[1]: " << dists[1] << " edge[2]: " << dists[2] << endl;
    for (vector<double>::iterator it = dists.begin(); it != dists.end(); ++it)
        sum_ab += *it;
    cout << "max_dist: " << max_dist << " sum_ab: " << sum_ab << "BOOL: " << (sum_ab > max_dist) << endl;
    return sum_ab > max_dist;
}

bool p_circle(Circle& circle, Point& p) {
    return dist_p(circle.center, p) <= circle.radius;
}

Circle circumcenter(Triangle& triangle) {
    Circle circle;
    double Ax = triangle.vertex[0].x, Ay = triangle.vertex[0].y;
    double Bx = triangle.vertex[1].x, By = triangle.vertex[1].y;
    double Cx = triangle.vertex[2].x, Cy = triangle.vertex[2].y;
    double D = 2 * (Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By));
    double Ux = ((pow(Ax, 2) + pow(Ay, 2)) * (By - Cy) + (pow(Bx, 2) + 
        pow(By, 2)) * (Cy - Ay) + (pow(Cx, 2) + pow(Cy, 2)) * (Ay - By)) / D;
    double Uy = ((pow(Ax, 2) + pow(Ay, 2)) * (Cx - Bx) + (pow(Bx, 2) + 
        pow(By, 2)) * (Ax - Cx) + (pow(Cx, 2) + pow(Cy, 2)) * (Bx - Ax)) / D;
    circle.center = make_pair(Ux, Uy);
    cout << "Circumcenter x:" << circle.center.x << " y: " << circle.center.y << endl;
    circle.radius = dist_p(triangle.vertex[0], circle.center);
    cout << "Circumcenter calculated " << endl;
    return circle;
}

double dist_p(Point p1, Point p2) {
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

Circle circle_long_edge(Triangle& triangle, unordered_multiset<Point>& R) {
    Circle circle;
    vector<Edge> dists {triangle.edge[0], triangle.edge[1], triangle.edge[2]};
    Edge max_edge(make_pair(0, 0), make_pair(0, 0));
    for (vector<Edge>::iterator it = dists.begin(); it != dists.end(); ++it) {
        if (max_edge.length < (*it).length) {
            max_edge = *it;
        }
    }
    circle.radius = dist_p(max_edge.p, max_edge.q) / 2;
    circle.center = mid_point(max_edge.p, max_edge.q);
    return circle;
}

Point mid_point(Point p, Point q) {
    return make_pair((p.x + q.x) / 2, (p.y + q.y) / 2);
}

Circle calcDiskDirectly(unordered_multiset<Point> R) {
    Circle circle(make_pair(0, 0), 0);
    if (R.empty()) {
        return circle;
    }
    else if (R.size() == 1) {
        unordered_multiset<Point>::iterator it = R.begin();
        circle.center = (*it);
        circle.radius = 0;
    }
    else if (R.size() == 2) {
        unordered_multiset<Point>::iterator it = R.begin();
        Point p1 = *it;
        Point p2 = *(next(it, 1));
        circle.center = mid_point(p1, p2);
        circle.radius = dist_p(p1, p2) / 2;
    }
    else if (R.size() == 3) {
        cout << "R size = 3" << endl;
        cout << "R  set: ";
        for (unordered_multiset<Point>::iterator it = R.begin(); it != R.end(); ++it) {
            cout << " x: " << (*it).x << " y: " << (*it).y;
        }
        unordered_multiset<Point>::iterator it = R.begin();
        Point p1 = *it;
        Point p2 = *(next(it, 1));
        Point p3 = *(next(it, 2));
        cout << "CHECK R pointers: p1(" << p1.x << ", " << p1.y << ") " 
            << "p2(" << p2.x << ", " << p2.y << ") " << "p3(" << p3.x << ", " << p3.y << ") " << endl;
        Triangle t(p1, p2, p3);
        if (acute_triangle(t)) {
            circle = circumcenter(t);
        } 
        else circle = circle_long_edge(t, R);
    }
    return circle;
}

void refreshR(Circle& circle, unordered_multiset<Point>& R) {
    for(unordered_multiset<Point>::iterator it = R.begin(); it != R.end(); ++it) {
        if (dist_p(circle.center, *it) < circle.radius) {
            R.erase(it);
        }
    }
}