#ifndef STRUCTS_H
#define STRUCTS_H

struct P_gas
{
    double Segm_T;
    double Segm_X;
    double p_ro;
    double p_gamma;
    double mu;
    void fill (double _T, double _X, double _ro, double _gamma, double _mu)
    {
      Segm_T = _T;
      Segm_X = _X;
      p_ro = _ro;
      p_gamma = _gamma;
      mu = _mu;
    }
    void print_params ();
};

struct P_she
{
    int M_x;
    int N;
    int Dim;
    double h_x;
    double tau;
    void fill (int _M, int _N,
               const P_gas &p_g)
    {
      M_x = _M;
      N = _N;
      Dim = _M + 1;
      h_x = p_g.Segm_X / _M;
      tau = p_g.Segm_T / N;
    }
    void print_params ();
};

#endif // STRUCTS_H
