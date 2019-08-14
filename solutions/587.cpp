#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5;
const double EPS = 1e-8;

double r = 1;
double dist(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
double area(double a, double b, double c)
{
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
double b_area(double x0, double y0, double x1, double y1, double x2, double y2)
{
    double a = r, b = r, c = 0;
    c = dist(x1, y1, x2, y2);
    double s = area(a, b, c);
    double alfa = asin(2.0 * s / r / r);
    return alfa * r * r * 0.5 - s;
}
main()
{
    for (int n = 1;; n++) {

        int x1 = -r, y1 = -r, x2 = x1 + 2 * r * n, y2 = y1 + 2 * r;
        int A = y2 - y1;
        int B = x1 - x2;
        int C = x2 * y1 - x1 * y2;

        double a = A, b = B, c = C;

        double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);

        double d = r * r - c * c / (a * a + b * b);
        double mult = sqrt(d / (a * a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

        double l = dist(0, -r, ax, ay);

        double concave = area(l, dist(x1, y1, ax, ay), dist(x1, y1, 0, -r)) - b_area(0, 0, ax, ay, 0, -r);
        double l_section = area(dist(ax, ay, -r, 0), dist(x1, y1, ax, ay), dist(-r, 0, x1, y1)) - b_area(0, 0, ax, ay, -r, 0);

        if (100. * concave / (concave + l_section) < 0.1) {
            cout << n;
            return 0;
        }
    }
}
