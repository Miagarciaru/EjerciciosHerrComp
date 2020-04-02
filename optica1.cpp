#include <iostream>
#include <cmath>

const double h=10.0;
const double d=15.0;
const double f=8.0;

double cam_optico (double x);
double ray_oblicuo (double x);

int main ()
{
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);
  
  double dx=0.01;
  double x=d;
  double eps=1e-1;
  
  for (double x=d-dx; std::abs(cam_optico(x)-ray_oblicuo(x))>=eps; x-=dx )
    {
      x-=dx;
      std::cout<<x<<"\t"<<cam_optico(x)<<"\t"<<ray_oblicuo(x)<<"\n";
    }
  return 0;
}

double cam_optico (double x)
{
  double y=0.0;

  if (x>0)
    {
      y=h;
    }

  else if (x<=0)
    {
      y=(h/f)*x+h;
    }
  return y;
}

double ray_oblicuo (double x)
{
  double y=0.0;

  y=(h/d)*x;

  return y;
}
