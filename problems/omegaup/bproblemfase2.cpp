#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef pair<double, double> point;
typedef vector<point> vector_point;
double dist_p(point p1, point p2);

class Edge {
public:
    point p;
    point q;
    double length;

    Edge() { }

    Edge(point p, point q) {
        this->p = p;
        this->q = q;
        length = dist_p(p, q);
    }
};


class Triangle {
public:
    point vertex[3];
    Edge edge[3];
    Triangle(point p1, point p2, point p3) {
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
    point center;
    Circle(point center, double radius) {
        this->center = center;
        this->radius = radius;
    }
    Circle() {}
};

bool acute_triangle(Triangle&);
bool p_in_circle(Circle&, point&);
Circle circumscribed_circle(Triangle&);
Circle circle_long_edge(Triangle&, vector_point&);
point mid_point(point, point);
Circle Welzl_algorithm(vector_point&, vector_point&);
Circle calcDiskDirectly(vector_point);
void refreshR(Circle&, vector_point&);

int main() {
    long long n, m, l, q;
    cin >> n >> m >> l;
    vector_point S; 
    for (long long i = 0; i < l; ++i) {
        double x, y;
        cin >> x >> y;
        S.push_back(make_pair(x, y));
    }
    cin >> q;
    for (long long i = 0; i < q; ++i) {
        long long k;
        cin >> k;
        vector_point P;
        vector_point R;
        for (long long j = 0; j < k; ++j) {
            long long input;
            cin >> input;
            P.push_back(S[input - 1]);
        }
        Circle circle;
        circle = Welzl_algorithm(P, R);
        cout << setprecision(10);
        cout << circle.radius << endl;
    }
    return 0;
}

// MAIN Algorithm
Circle Welzl_algorithm(vector_point& P, vector_point& R) {
    Circle circle;
    if (P.empty() || R.size() == 3)
        circle = calcDiskDirectly(R);
    else {
        auto random_it = next(P.begin(), rand() % P.size());
        point p = *random_it;
        P.erase(random_it);
        circle = Welzl_algorithm(P, R);
        if (!p_in_circle(circle, p)) {
            if (R.size() == 3)
                R.clear();
            R.push_back(p);
            circle = Welzl_algorithm(P, R);
        }
    }
    return circle;
}

// Algorithm to decide which action take according to size of R set (|R|)
Circle calcDiskDirectly(vector_point R) {
    Circle circle(make_pair(0, 0), 0);
    if (R.empty()) {
        return circle;
    }
    else if (R.size() == 1) {
        circle.center = *(R.begin());
        circle.radius = 0;
    }
    else if (R.size() == 2) {
        point p1 = *(R.begin());
        point p2 = *(next(R.begin(), 1));
        circle.center = mid_point(p1, p2);
        circle.radius = dist_p(p1, p2) / 2;
    }
    else if (R.size() == 3) {
        point p1 = *(R.begin());
        point p2 = *(next(R.begin(), 1));
        point p3 = *(next(R.begin(), 2));
        Triangle t(p1, p2, p3);
        circle = (acute_triangle(t)) ? circumscribed_circle (t): circle_long_edge(t, R);
    }
    refreshR(circle, R);
    return circle;
}

// Check if the triangle is acute triangle
bool acute_triangle(Triangle& triangle) {
    vector<double> dists {pow(triangle.edge[0].length, 2), pow(triangle.edge[1].length, 2), pow(triangle.edge[2].length, 2)};
    vector<double>::iterator max_it = max_element(dists.begin(), dists.end());
    double max_dist = *max_it;
    dists.erase(max_it);
    double sum_ab = 0;
    for (vector<double>::iterator it = dists.begin(); it != dists.end(); ++it)
        sum_ab += *it;
    return sum_ab > max_dist;
}

// Get the circumscribed circle (coordinates and radius) for given three points
Circle circumscribed_circle(Triangle& triangle) {
    Circle circle;
    double Ax = triangle.vertex[0].first, Ay = triangle.vertex[0].second;
    double Bx = triangle.vertex[1].first, By = triangle.vertex[1].second;
    double Cx = triangle.vertex[2].first, Cy = triangle.vertex[2].second;
    double D = 2 * (Ax * (By - Cy) + Bx * (Cy - Ay) + Cx * (Ay - By));
    double Ux = ((pow(Ax, 2) + pow(Ay, 2)) * (By - Cy) + (pow(Bx, 2) + 
        pow(By, 2)) * (Cy - Ay) + (pow(Cx, 2) + pow(Cy, 2)) * (Ay - By)) / D;
    double Uy = ((pow(Ax, 2) + pow(Ay, 2)) * (Cx - Bx) + (pow(Bx, 2) + 
        pow(By, 2)) * (Ax - Cx) + (pow(Cx, 2) + pow(Cy, 2)) * (Bx - Ax)) / D;
    circle.center = make_pair(Ux, Uy);
    circle.radius = dist_p(triangle.vertex[0], circle.center);
    return circle;
}

// If the triangle is not a acute triangle, then calculate the longest edge and then get the mid point
// Circumnscribed circle has coordinates (mid-point) and radius equal to half length of longest edge
Circle circle_long_edge(Triangle& triangle, vector_point& R) {
    Circle circle;
    vector<Edge> dists {triangle.edge[0], triangle.edge[1], triangle.edge[2]};
    Edge max_edge(make_pair(0, 0), make_pair(0, 0));
    for (vector<Edge>::iterator it = dists.begin(); it != dists.end(); ++it)
        if (max_edge.length <= (*it).length)
            max_edge = *it;
    circle.radius = dist_p(max_edge.p, max_edge.q) / 2;
    circle.center = mid_point(max_edge.p, max_edge.q);
    return circle;
}

// Returns the distance between point p1 and p2
double dist_p(point p1, point p2) {
    return sqrt(pow((p1.first - p2.first), 2) + pow((p1.second - p2.second), 2));
}

// Return mid point coordinates between two points
point mid_point(point p, point q) {
    return make_pair((p.first + q.first) / 2, (p.second + q.second) / 2);
}

// Check if p point is inside circle
bool p_in_circle(Circle& circle, point& p) {
    return dist_p(circle.center, p) < circle.radius;
}

// Function to refresh R set
void refreshR(Circle& circle, vector_point& R) {
    for(vector_point::iterator it = R.begin(); it != R.end(); ++it)
        if (dist_p(circle.center, *it) < circle.radius)
            R.erase(it);
}