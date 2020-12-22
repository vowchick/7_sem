#include <iostream>
#include <vector>
#include "header.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

int main(int argc, char *argv[])
{
  if (argc != 6)
    {
      printf ("Usage: %s p_gamma mu "
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
  std::cout << p_s.M_x << " " << p_s.N << ": ";
  res result;
  Sxema (p_g, p_s, curr_V, curr_H, result, 0, true);
  Sxema (p_g, p_s, curr_V, curr_H, result, (3 * result.num) / 4, false);
  Sxema (p_g, p_s, curr_V, curr_H, result, result.num / 2, false);
  Sxema (p_g, p_s, curr_V, curr_H, result, result.num / 4, false);
  result.set_time_st (p_s.tau);
  write_table_for_tex (argv[5], result, p_s);
  std::cout << result;

  return 0;
}
