#include "header.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#define PRINT(x) std::cout << #x << " = " << x << "\n";
void read_params (P_gas &p_g, P_she &p_s, char *argv[])
{
  p_g.fill (atof (argv[1]),
            atof (argv[2]));
  p_s.fill (atoi (argv[3]), atoi (argv[4]), atoi (argv[5]), p_g);
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
void write_table_for_tex (const char *name, const res &result, const P_she &p_s, const P_gas &p_g)
{
  std::ofstream outfile;
  outfile.open(name, std::ios_base::app);
  if (p_s.K == 1 && fabs (p_g.mu - 0.1) < 1e-16)
    {
      outfile << "\\begin{center}\n"
      << "  \\begin{tabular}{| l | l | l | l |}\n"
      << "    \\hline\n"
      << "      \\backslashbox{$K$}{$\\mu$} & 0.1 & 0.01 & 0.001 \\\\ \\hline \n";
    }
  if (fabs (p_g.mu - 0.1) < 1e-16)
    {
      outfile << p_s.K;
    }
  outfile << " & " << result.num * p_s.tau;
  if (fabs (p_g.mu - 0.001) < 1e-16)
    {
      outfile << " \\\\ \\hline\n";
      if (p_s.K == 10)
        {
          outfile << "  \\end{tabular}\n  "
                        "$ \\text {Время выхода на стационар }$\n"
                      "\\end{center}\n"
                      "\\vfill" << std::endl;
        }
    }



}
std::ostream & operator << (std::ostream &s, const res &Res)
{
  s << Res.num << " " << Res.time_st << " "
    << Res.resids[3] << " "
    << Res.resids[2] << " "
    << Res.resids[1] << " "
    << Res.resids[0]
    << "\n";
  return s;
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
