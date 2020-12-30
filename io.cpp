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
  p_s.fill (atoi (argv[3]), atoi (argv[4]), atof (argv[5]), atof (argv[6]), p_g);
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
void write_table_for_tex (const char *name, const res &result, const P_she &p_s)
{
  std::ofstream outfile;
  outfile.open(name, std::ios_base::app);
  if ((fabs (p_s.v_tilde - 1) < 1e-16) && (fabs (p_s.rho_tilde - 1) < 1e-16))
    {
      outfile << "\\begin{center}\n"
      << "  \\begin{tabular}{| l | l | l | l | l |}\n"
      << "    \\hline\n"
      << "      \\backslashbox{$K$}{$\\mu$} & 1 & 2 & 3 & 4  \\\\ \\hline\n";
    }
  if ((fabs (p_s.v_tilde - 1) < 1e-16))
    outfile << p_s.rho_tilde << " ";
  std::cout << result.tau << std::endl;
  outfile << " & " << result.num * result.tau;
  if ((fabs (p_s.v_tilde - 4) < 1e-16))
    outfile << " \\\\ \\hline\n";

  if ((fabs (p_s.v_tilde - 4) < 1e-16) && (fabs (p_s.rho_tilde - 4) < 1e-16))
    {
      outfile << "  \\end{tabular}\n  "
                    "$ \\text {Время выхода на стационар } \\mu=10^{-1}$\n"
                  "\\end{center}\n"
                  "\\vfill" << std::endl;
    }
}

std::ostream & operator << (std::ostream &s, const res &Res)
{
  s << Res.num << " " << Res.time_st << " "
    << "\n";
  return s;
}
void write_for_plot (const char *name, const res &result, const P_she &p_s, const P_gas &p_g)
{
  std::ofstream outfile;
  outfile.open(name, std::ios_base::app);
  outfile << p_s.v_tilde << " " << p_s.rho_tilde << " " << p_g.mu << "\n";
  int size_v = static_cast<int> (result.V.size ());
  int size_h = static_cast<int> (result.H.size ());
  for (int i = size_v - 1; i >= 0; i--)
    outfile << result.V[i] << " ";
  outfile << std::endl;
  for (int i = size_h - 1; i >= 0; i--)
    outfile << result.H[i] << " ";
  outfile << std::endl;
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
