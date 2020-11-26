#include <iostream>
#include <vector>
#include "header.h"
#include <iostream>
#include <cmath>
int main(int argc, char *argv[])
{
  if (argc != 7)
    {
      printf ("Usage: %s Segm_T Segm_X p_gamma mu "
              "M_x N\n", argv[0]);
      return 0;
    }
  P_gas p_g;
  P_she p_s;
  read_params (p_g, p_s, argv);
//  p_g.print_params ();
//  p_s.print_params ();
//  check ();

  std::vector<double> curr_V (p_s.M_x + 1), curr_H (p_s.M_x);
  Sxema (p_g, p_s, curr_V, curr_H);
  double t = p_s.N * p_s.tau;
  double residual_v = 0.;
  double residual_h = 0.;

  std::vector<double> v_residuals, h_residuals;

  for (int m = 0; m < p_s.M_x; m++)
    {
      double x_v = m * p_s.h_x,
             x_u = p_s.h_x / 2. + x_v;

      double app_v = curr_V[m];
      double ori_v = u (t, x_v);
      double val_v = fabs (app_v - ori_v);

      double app_h = curr_H[m];
      double ori_h = rho (t, x_u);
      double val_h = fabs (app_h - ori_h);

      residual_v = std::max (residual_v, val_v);
      residual_h = std::max (residual_h, val_h);

      v_residuals.push_back (residual_v);
      h_residuals.push_back (residual_h);
    }

  double x_v = p_s.M_x * p_s.h_x;
  double app_v = curr_V[p_s.M_x];
  double ori_v = u (t, x_v);
  double val_v = fabs (app_v - ori_v);

  residual_v = std::max (residual_v, val_v);

  if (residual_v <= 0.)
    {
      residual_v = NAN;
    }

  if (residual_h <= 0.)
    {
      residual_h = NAN;
    }
//  residual_h = L2_norm (h_residuals, p_s.h_x, 1);
//  residual_v = L2_norm (v_residuals, p_s.h_x, 0);
  printf ("Residual_V = %e    |    Residual_h = %e    |    h = %e    |    tau = %e "
          "   |    n = %d    |    m = %d\n",
          residual_v, residual_h, p_s.h_x, p_s.tau, p_s.N, p_s.M_x);
  return 0;
}
