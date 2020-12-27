#ifndef STRUCTS_H
#define STRUCTS_H
struct P_gas
{
    double Segm_T = 1.;
    double Segm_X = 1.;
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
    int K;
    double tau;
    void fill (int _M, int _N, int _K,
               const P_gas &p_g)
    {
      M_x = _M;
      N = _N;
      K = _K;
      Dim = _M + 1;
      h_x = p_g.Segm_X / _M;
      tau = p_g.Segm_T / N;
    }
    void print_params ();
};

struct res
{
  int num;
  std::vector<double> resids;
  double time_st;
  void set_time_st (double tau)
  {
    time_st = tau * num;
  }
};

#endif // STRUCTS_H
