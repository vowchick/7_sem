#ifndef HEADER_H
#define HEADER_H
#include <functional>
#include <vector>
#include <utility>
#include "structs.h"
double u_0 (double x);
double rho_0 (double x);
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
void Sxema (const P_gas &p_g, const P_she &p_s, std::vector<double> &curr_V, std::vector<double> &curr_H, res &result, int bound, bool first);
void read_params (P_gas &p_g, P_she &p_s, char *argv[]);
void init_vectors (const P_gas &p_g, const P_she &p_s, std::vector<double> &curr_V, std::vector<double> &curr_H);
double L2_norm (const std::vector<double> &v, double h, int st);
double W2_1h_norm (const std::vector<double> &v, double h, int st);
void write_table (const char *name, double residual, const P_she &p_s);
void write_table_for_tex (const char *name, const res &result, const P_she &p_s);
void write_for_plot (const char *name, const res &result, const P_she &p_s, const P_gas &p_g);
double m (double h, const std::vector<double> &H);
double dm (double m, double m0);
double norm_for_second_task (const std::vector <double> &v);
bool norm_for_fourth_task (const std::vector <double> &v, const std::vector <double> &v_prev, double eps);
std::ostream & operator << (std::ostream &s, const res &Res);
#endif // HEADER_H
