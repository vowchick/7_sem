#include <iostream>
#include <vector>
#include "header.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
int main(int argc, char *argv[])
{
  if (argc != 8)
    {
      printf ("Usage: %s Segm_T Segm_X p_gamma mu "
              "M_x N a.txt\n", argv[0]);
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
  double t = p_g.Segm_T;
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

      v_residuals.push_back (val_v);
      h_residuals.push_back (val_h);
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
  residual_h = L2_norm (h_residuals, p_s.h_x, 1);
  residual_v = L2_norm (v_residuals, p_s.h_x, 0);
  std::ofstream outfile;
  outfile.open(argv[7], std::ios_base::app); // append instead of overwrite
  outfile << std::scientific << "Residual_V = " << residual_v << "   |   "
          << std::scientific << "Residual_h = " << residual_h << "   |   "
          << std::scientific << "h = " << p_s.h_x << "   |   "
          << std::scientific << "tau = " << p_s.tau << "   |   "
          << std::scientific << "n = " << p_s.N << "   |   "
          << std::scientific << "m = " << p_s.M_x << std::endl;
  return 0;
}
