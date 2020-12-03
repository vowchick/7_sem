#include "header.h"
#include <cmath>
void
init_vectors ([[maybe_unused]]const P_gas &p_g, const P_she &p_s, std::vector<double> &curr_V, std::vector<double> &curr_H)
{
  int M = p_s.M_x;
  double h = p_s.h_x;
  double x_v = 0., x_h = h / 2.;
  for (int i = 0; i < M; i++)
    {
      x_v = i * h;
      x_h = h / 2. + i * h;
      curr_V[i] = u (0, x_v);
      curr_H[i] = rho (0, x_h);
    }
  curr_V[M] = u (0, M * h);
}
void
solve_tridiagonal (std::vector<double> &bottom, std::vector<double> &middle, std::vector<double> &top, std::vector<double> &rhs, int n)
{
  /*
  source: https://gist.github.com/nlw0/8edc1241bd05d5a9e5483bee763696a8
  // n is the number of unknowns
  |b0 c0 0 ||x0| |d0|
  |a1 b1 c1||x1|=|d1|
  |0  a2 b2||x2| |d2|
  1st iteration: b0x0 + c0x1 = d0 -> x0 + (c0/b0)x1 = d0/b0 ->
      x0 + g0x1 = r0               where g0 = c0/b0        , r0 = d0/b0
  2nd iteration:     | a1x0 + b1x1   + c1x2 = d1
      from 1st it.: -| a1x0 + a1g0x1        = a1r0
                  -----------------------------
                        (b1 - a1g0)x1 + c1x2 = d1 - a1r0
      x1 + g1x2 = r1               where g1=c1/(b1 - a1g0) , r1 = (d1 - a1r0)/(b1 - a1g0)
  3rd iteration:      | a2x1 + b2x2   = d2
      from 2nd it. : -| a2x1 + a2g1x2 = a2r2
                     -----------------------
                     (b2 - a2g1)x2 = d2 - a2r2
      x2 = r2                      where                     r2 = (d2 - a2r2)/(b2 - a2g1)
  Finally we have a triangular matrix:
  |1  g0 0 ||x0| |r0|
  |0  1  g1||x1|=|r1|
  |0  0  1 ||x2| |r2|
  Condition: ||bi|| > ||ai|| + ||ci||
  in this version the c matrix reused instead of g
  and             the d matrix reused instead of r and x matrices to report results
  Written by Keivan Moradi, 2014
  */
  n--; // since we start from x0 (not x1)
  top[0] /= middle[0];
  rhs[0] /= middle[0];
  for (int i = 1; i < n; i++)
    {
      top[i] /= middle[i] - bottom[i] * top[i - 1];
      rhs[i] = (rhs[i] - bottom[i] * rhs[i - 1]) / (middle[i] - bottom[i] * top[i - 1]);
    }
  rhs[n] = (rhs[n] - bottom[n] * rhs[n - 1]) / (middle[n] - bottom[n] * top[n - 1]);
  for (int i = n; i-- > 0;)
    {
      rhs[i] -= top[i] * rhs[i + 1];
    }
}
void Sxema (const P_gas &p_g, const P_she &p_s, std::vector<double> &curr_V, std::vector<double> &curr_H)
{
  int M = p_s.M_x, N = p_s.N;
  double tau = p_s.tau, h = p_s.h_x,
      mu = p_g.mu, gamma = p_g.p_gamma;
  std::vector<double> next_V (M + 1), next_H (M),
      bottom (M + 1), middle (M + 1), top (M + 1);
  init_vectors (p_g, p_s, curr_V, curr_H);
  [[maybe_unused]]auto solve_for_v = [M, h, mu, tau, gamma, &top, &bottom, &middle,
                     &curr_H, &curr_V, &next_V] (double t)
  {
      next_V[0] = 0.;
      middle[0] = 1.;
      top[0] = 0.;

      for (int m = 1; m < M; m++)
        {
          double x_v = m * h;
          double H_s_ = curr_H[m] + curr_H[m - 1];
          if ((H_s_ <= 0) &&(H_s_ >= 0))
            {
              next_V[m] = 0.;
              middle[m] = 1.;
              bottom[m] = 0.;
              top[m] = 0.;
            }
          else
            {
              bottom[m] = -tau * (curr_V[m] + fabs (curr_V[m])) *
                                  (H_s_) / (4. * h)
                  - tau * mu / (h * h);
              middle[m] = (H_s_) / 2. +
                  tau * fabs (curr_V[m]) * (H_s_) / (2. * h)
                  + 2. * mu * tau / (h * h);
              top[m] = tau * (curr_V[m] - fabs (curr_V[m])) * (H_s_) / (4. * h)
                  - tau * mu / (h * h);
              next_V[m] = curr_V[m] * (H_s_) / 2.
                  - tau * gamma * (std::pow (curr_H[m], gamma - 1.) - std::pow (curr_H[m - 1], gamma - 1.)) * H_s_
                  / (2. * (gamma - 1.) * h) + tau * f (t, x_v, mu, gamma) * (H_s_) / 2.;
            }
        }
      next_V[M] = 0.;
      middle[M] = 1.;
      bottom[M] = 0.;

      solve_tridiagonal (bottom, middle, top, next_V, M + 1);
//      for (int m = 1; m < M; m++)
//        {
//          if ((curr_H[m] + curr_H[m - 1] <= 0) &&
//              (curr_H[m] + curr_H[m - 1] >= 0))
//            next_V[m] = 0.;
//        }
    };

  [[maybe_unused]]auto solve_for_h = [M, h, tau, &top, &bottom, &middle,
                     &curr_H, &next_H, &next_V] (double t)
  {
    for (int m = 0; m < M; m++)
      {
        double x_h = h / 2. + m * h;
        bottom[m] = -tau * (next_V[m] + fabs (next_V[m])) / (2. * h);
        middle[m] = 1. + tau * (next_V[m + 1] + fabs (next_V[m + 1])
                                - next_V[m] + fabs (next_V[m])) / (2. * h);
        top[m] = tau * (next_V[m + 1] - fabs (next_V[m + 1])) / (2. * h);
        next_H[m] = curr_H[m] + tau * f0 (t, x_h);
      }
    solve_tridiagonal (bottom, middle, top, next_H, M);
    };
  for (int n = 0; n < N; n++)
    {
      [[maybe_unused]]double t = n * tau, t2 = (n + 1) * tau;
      solve_for_v (t);
//      for (int i = 0; i <= M; i++)
//        {
//          next_V[i] = u (t2, i * h);
//        }
      solve_for_h (t);
//      for (int i = 0; i < M; i++)
//        {
//          next_H[i] = rho (t2, h / 2. + i * h);
//        }

      std::swap (curr_V, next_V);
      std::swap (curr_H, next_H);
    }

}
double L2_norm (const std::vector<double> &v, double h, int st)
{
  double scal = 0.;
  int size = static_cast<int> (v.size ());
  for (int i = st; i < size - 1; i++)
    scal += v[i] * v[i];
  for (int i = 0; i < st; i++)
    scal += (1./2. * v[i] * v[i]);
  scal += (v[size - 1] * v[size - 1] / 2.);
  return sqrt (h * scal);
}
double W2_1h_norm (const std::vector<double> &v, double h, int st)
{
  double first = L2_norm (v, h, st);
  double second = 0.;
  int size = static_cast<int> (v.size ());
  for (int i = 1; i < size; i++)
    {
      second += (v[i] - v[i - 1]) * (v[i] - v[i - 1]);
    }
  second /= h;
  return sqrt (first * first + second);
}
