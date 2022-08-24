/*
    For finding the length of an arc in a range
    L = integrate(ds) from start to end of range
    where ds = sqrt(1+(d/dy(x))^2)dy
*/
const double SIMPSON_TERMINAL_EPS = 1e-12;
/// Function whose integration is to be calculated
double F(double x);
double simpson(double minx, double maxx)
{
    return (maxx - minx) / 6 * (F(minx) + 4 * F((minx + maxx) / 2.) + F(maxx));
}
double adaptive_simpson(double minx, double maxx, double c, double EPS)
{
//    if(maxx - minx < SIMPSON_TERMINAL_EPS) return 0;

    double midx = (minx + maxx) / 2;
    double a = simpson(minx, midx);
    double b = simpson(midx, maxx);

    if(fabs(a + b - c) < 15 * EPS) return a + b + (a + b - c) / 15.0;

    return adaptive_simpson(minx, midx, a, EPS / 2.) + adaptive_simpson(midx, maxx, b, EPS / 2.);
}
double adaptive_simpson(double minx, double maxx, double EPS)
{
    return adaptive_simpson(minx, maxx, simpson(minx, maxx, i), EPS);
}

