#ifndef STRUCTS_H
#define STRUCTS_H
struct P_gas
{
    double Segm_T = 1.;
    double Segm_X = 10.;
    double p_gamma;
    double mu;
    void fill (double _gamma, double _mu)
    {
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
    double v_tilde;
    double rho_tilde;
    void fill (int _M, int _N, double v_, double rho_,
               const P_gas &p_g)
    {
      v_tilde = v_;
      rho_tilde = rho_;
      M_x = _M;
      N = _N;
      Dim = _M + 1;
      h_x = p_g.Segm_X / _M;
      tau = p_g.Segm_T / _N;
    }
    void print_params ();
};

struct res
{
  int num;
  std::vector<double> V;
  std::vector<double> H;
  double time_st;
  double tau;
  void set_time_st (int number)
  {
    time_st = tau * number;
  }
};

#endif // STRUCTS_H
