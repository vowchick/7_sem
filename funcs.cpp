#include "header.h"
#include <math.h>
#include <iostream>
#include <cmath>
#include <cassert>
//constexpr double M_PI / 10.  = M_PI / 10.,
//                 2. * M_PI = 2. * M_PI,
//                 M_PI / 50.  = M_PI / 50.,
//                 M_PI / 100. = M_PI / 100.;

double u (double t, double x)
{
  return cos (2. * M_PI * t) * sin (M_PI * x * x / 100.);
}
double rho (double t, double x)
{
  return exp (t) * (cos (M_PI * x / 10.) + 1.5);
}

double ddx_rho_u (double t, double x)
{
  return ddx_u (t, x) + ddx_rho (t, x);
}

double ddt_u (double t, double x)
{
  return -2. * M_PI * sin (2. * M_PI * t) * sin (M_PI * x * x / 100.);
}
double ddx_u (double t, double x)
{
  return M_PI * x * cos (2. * M_PI * t) * cos (M_PI * x * x / 100.) / 50.;
}
double ddx_rho (double t, double x)
{
  return -M_PI * sin (M_PI  * x / 10.) * exp (t) / 10.;
}
double d_2dx_2_u (double t, double x)
{
  double constant = M_PI * cos (2. * M_PI * t) / 50.;
  double first = cos (M_PI * x * x / 100.);
  double second = M_PI * x * x * sin (M_PI * x * x / 100.) / 50.;

  return constant * first - constant * second;
}

double f0 (double t, double x)
{
  return rho (t, x) + ddx_rho_u (t, x);
}

double f (double t, double x, double mu, double gamma)
{
 return (rho (t, x) * ddt_u (t, x) + rho (t, x) * u (t, x) * ddx_u (t, x) +
     gamma * std::pow (rho (t, x), gamma - 1) * ddx_rho (t, x) -
     -mu * d_2dx_2_u (t, x)) / rho (t, x);
}

bool is_equal (double x, double y)
{
  return fabs (x - y) < 1e-14;
}
void check ()
{
  assert (is_equal (rho (0, 0), 2.5));

  assert (is_equal (u (0, 5), M_SQRT1_2));

  assert (is_equal (ddx_rho_u (0, 0), 0));
  assert (is_equal (ddx_rho_u (0, 10), -M_PI / 5.));

  assert (is_equal (ddt_u (1, 0), 0));
  assert (is_equal (ddt_u (0.25, 10), 0));
  assert (is_equal (ddt_u (0.25, 5), -M_SQRT1_2 * 2. * M_PI));

  assert (is_equal (ddx_u (0, 0), 0));
  assert (is_equal (ddx_u (1, 10), -2 * M_PI / 10.));

  assert (is_equal (ddx_rho (0, 0), 0));
  assert (is_equal (ddx_rho (0, 5), -M_PI / 10.));

  assert (is_equal (d_2dx_2_u (0, 0), M_PI / 50.));
  assert (is_equal (d_2dx_2_u (1, 10), -M_PI / 50.));
  assert (is_equal (d_2dx_2_u (1, sqrt (50)), -M_PI / 50. * M_PI));
  std::cout << "Function tests are OK!\n";
}
