#include "header.h"
#include <iostream>
#define PRINT(x) std::cout << #x << " = " << x << "\n";
void read_params (P_gas &p_g, P_she &p_s, char *argv[])
{
  p_g.fill (atof (argv[1]), atof (argv[2]), atof (argv[3]),
            atof (argv[4]));
  p_s.fill (atoi (argv[5]), atoi (argv[6]), p_g);
}

void P_gas::print_params ()
{
  PRINT (Segm_T)
  PRINT (Segm_X)
  PRINT (p_gamma)
  PRINT (mu)
}
void P_she::print_params ()
{
  PRINT (M_x)
  PRINT (N)
  PRINT (Dim)
  PRINT (h_x)
  PRINT (tau)
}
