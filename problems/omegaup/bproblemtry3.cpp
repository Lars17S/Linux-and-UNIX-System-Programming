#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef vector<point> vector_point;
double dist_p(Point p1, Point p2);

class Point {
    double x;
    double y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
}

class Edge {
public:
	Point p;
	Point q;
	double length;

	Edge(Point p, Point q) {
		this->p = p;
		this->q = q;
		length = dist_p(p, q);
	}

	Edge() {};
};


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

bool acute_triangle(Triangle&);
bool p_in_circle(Circle&, Point&);
Circle circumscribed_circle(Triangle&);
Circle circle_long_edge(Triangle&, vector_point&);
Point mid_point(Point, Point);
Circle Welzl_algorithm(vector_point&, vector_point&);
Circle calcDiskDirectly(vector_point&);
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
	Circle circle(make_pair(0, 0), -1);
	if (P.empty() || R.size() == 3) {
		circle = calcDiskDirectly(R);
	}

	else {
		auto random_it = next(P.begin(), rand() % P.size());
		Point p = *random_it;
		P.erase(random_it);
		circle = Welzl_algorithm(P, R);
		if (circle.radius == -1 || !p_in_circle(circle, p)) {
			R.push_back(p);
			circle = Welzl_algorithm(P, R);
		}
	}
	return circle;
}

// Algorithm to decide which action take according to size of R set (|R|)
Circle calcDiskDirectly(vector_point& R) {
	/*cout << "CalcDiskDirectly entry---------" << endl;
	for (vector_point::iterator it = R.begin(); it != R.end(); ++it) {
		cout << "Point: (" << (*it).first << ", " << (*it).second << ") " << endl;
	}
	cout << endl;*/
	Circle circle(make_pair(0, 0), -1);
	if (R.empty()) {
		return circle;
	}
	else if (R.size() == 1) {
		circle.center = *(R.begin());
		circle.radius = 0;
		return circle;
	}
	else if (R.size() == 2) {
		Point p1 = *(R.begin());
		Point p2 = *(next(R.begin(), 1));
		circle.center = mid_point(p1, p2);
		circle.radius = dist_p(p1, p2) / 2;
		return circle;
	}
	else if (R.size() == 3) {
		Point p1 = *(R.begin());
		Point p2 = *(next(R.begin(), 1));
		Point p3 = *(next(R.begin(), 2));
		/*cout << "Points: (" << p1.first << ", " << p1.second << ") | (" << p2.first << ", " << p2.second << ") | (" << 
			p3.first << ", " << p3.second << ") " << endl;*/
		Triangle t(p1, p2, p3);
		circle = (acute_triangle(t)) ? circumscribed_circle(t) : circle_long_edge(t, R);
		return circle;
	}
	else {
		Point Q = *prev(R.end(), 1);
		vector_point S;
		double max_distance = -1;
		for (vector_point::iterator it = R.begin(); it != prev(R.end(), 1); ++it) {
			if (max_distance < dist_p(Q, *it)) {
				S.clear();
				S.push_back(*it);
				max_distance = dist_p(Q, *it);
			}
			else if (max_distance == dist_p(Q, *it))
				S.push_back(*it);
		}
		S.push_back(Q);
		R = S;
		/*for (vector_point::iterator it = R.begin(); it != R.end(); ++it) {
			cout << "Point: (" << (*it).first << ", " << (*it).second << ") " << endl;
		}*/
		return calcDiskDirectly(R);
	}
}

// Check if the triangle is acute triangle
bool acute_triangle(Triangle& triangle) {
	vector<double> dists{ pow(triangle.edge[0].length, 2), pow(triangle.edge[1].length, 2), pow(triangle.edge[2].length, 2) };
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
	double Ax = triangle.vertex[0].x, Ay = triangle.vertex[0].y;
	double Bx = triangle.vertex[1].x, By = triangle.vertex[1].y;
	double Cx = triangle.vertex[2].x, Cy = triangle.vertex[2].y;
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
	vector<Edge> dists{ triangle.edge[0], triangle.edge[1], triangle.edge[2] };
	Edge max_edge(make_pair(0, 0), make_pair(0, 0));
	for (vector<Edge>::iterator it = dists.begin(); it != dists.end(); ++it)
		if (max_edge.length <= (*it).length)
			max_edge = *it;
	circle.radius = dist_p(max_edge.p, max_edge.q) / 2;
	circle.center = mid_point(max_edge.p, max_edge.q);
	return circle;
}

// Returns the distance between point p1 and p2
double dist_p(Point p1, Point p2) {
	return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

// Return mid point coordinates between two points
Point mid_point(Point p, Point q) {
	return make_pair((p.x + q.x) / 2, (p.y + q.y) / 2);
}

// Check if p point is inside circle
bool p_in_circle(Circle& circle, Point& p) {
	// Check if actually is <= condition
	return dist_p(circle.center, p) <= circle.radius;
}

// Function to refresh R set
void refreshR(Circle& circle, vector_point& R) {
	for (vector_point::iterator it = R.begin(); it != R.end();) {
		if (dist_p(circle.center, *it) < circle.radius) {
			R.erase(it);
			it = R.begin();
		}
		else
			++it;
	}			
}