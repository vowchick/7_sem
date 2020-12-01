#ifndef HEADER_H
#define HEADER_H
#include <functional>
#include <vector>
#include "structs.h"
double rho (double t, double x);
double u (double t, double x);
double ddx_rho_u (double t, double x);
double ddt_u (double t, double x);
double ddx_u (double t, double x);
double ddx_rho (double t, double x);
double d_2dx_2_u (double t, double x);
double f0 (double t, double x);
double f (double t, double x, double mu, double C);
void check ();
void solve_tridiagonal (std::vector<double> &bottom, std::vector<double> &middle, std::vector<double> &top, std::vector<double> &rhs, int n);
void Sxema (const P_gas &p_g, const P_she &p_s, std::vector<double> &curr_V, std::vector<double> &curr_H);
void read_params (P_gas &p_g, P_she &p_s, char *argv[]);
void init_vectors (const P_gas &p_g, const P_she &p_s, std::vector<double> &curr_V, std::vector<double> &curr_H);
double L2_norm (const std::vector<double> &v, double h, int st);
void write_table (const char *name, double residual, const P_she &p_s);
void write_table_for_tex (const char *name, double residual, const P_she &p_s);
#endif // HEADER_H
