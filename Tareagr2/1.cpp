#include <cstdio> // for printf
#include <cmath>

double myatan(double x, int n);

int main(void)
{
  const int NSTEPS = 53;
  const double X = 4.2;
  const double EXACT = std::atan(X);
  for(int n = 1; n <= NSTEPS; n+=2) {
    double my = myatan(X, n);
    double diff = std::fabs(1-my/EXACT);
    std::printf("%25d\t%25.16e\n", n, diff);
  }
  
  return 0;
}

double myatan(double x, int n)
{
  double f=0.0;
  double a=1.0/pow(2, n/2);
  double b=x/(1+std::sqrt(1+x*x));
  double c=1.0;
  double d=1.0;
  double eps=1.0/pow(2,n);
  do
    {
      c=2*c/(1+a);
      d=2*a*b/(1+b*b);
      d=d/(1+std::sqrt(1-d*d));
      d=(b+d)/(1-b*d);
      b=d/(1+std::sqrt(1+d*d));
      a=2*std::sqrt(a)/(1+a);

      f=c*std::log((1+b)/(1-b));
  }
  while ((1-a)>eps);

  return f;
}
