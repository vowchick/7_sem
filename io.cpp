#include "header.h"
#include <iostream>
#include <fstream>
#include <iomanip>
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
void write_table (const char *name, double residual, const P_she &p_s)
{
  std::ofstream outfile;
  outfile.open(name, std::ios_base::app);
  outfile << std::scientific << "Residual = " << residual << "   |   "
          << std::scientific << "h = " << p_s.h_x << "   |   "
          << std::scientific << "tau = " << p_s.tau << "   |   "
          << std::scientific << "n = " << p_s.N << "   |   "
          << std::scientific << "m = " << p_s.M_x << std::endl;
}
void write_table_for_tex (const char *name, double residual, const P_she &p_s)
{
  std::ofstream outfile;
  outfile.open(name, std::ios_base::app);
  if (p_s.M_x == 100 && p_s.N == 10)
    {
      outfile << "\\begin{center}\n  "
                 "\\begin{tabular}{ | l | l | l | l | l |}\n    "
                 "\\hline \n      "
                 "\\backslashbox{$\\tau$}{$h$} & 0.1 & 0.01 &0.001 & 0.0001 \\\\ \\hline" << std::endl;
    }
  if (p_s.M_x == 100)
    outfile << 1. / p_s.N << " & ";
  if (p_s.M_x != 100000)
    outfile << std::scientific << residual << " & ";
  else
    outfile << std::scientific << residual << " \\\\ \\hline" << std::endl;

  if (p_s.M_x == 100000 && p_s.N == 10000)
    {
      outfile << "\\end{tabular}\n  "
                    "$ \\text { Таблица 1: Ошибка решения для } H \\text { при } \\mu=10^{-3}$\n    "
                  "\\end{center}" << std::endl;
    }
}

//\begin{center}
//  \begin{tabular}{ | l | l | l | l | l |}
//    \hline
//    \backslashbox{$\tau$}{$h$} & 0.1 & 0.01 &0.001 & 0.0001 \\ \hline
//    0.1 & 1.219743e-03 & $1\mathrm{e}{-10}$ & $1\mathrm{e}{-10}$ & $1\mathrm{e}{-10}$\\ \hline
//    0.01 & 5 & 6 & 7 & 8 \\ \hline
//    0.001 & 5 & 6 & 7 & 8 \\ \hline
//    0.0001 & 5 & 6 & 7 & 8 \\ \hline

//  \end{tabular}
//  $
//  \text { Таблица 1: Опибка решения для } V \text { при } \mu=10^{-1} \text {и } C=10^{\circ}$
//\end{center}
