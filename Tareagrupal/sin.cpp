//Implementar el método de Pade
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

double sin_pade (double x);
double sin_aux (double u);

int main()
{
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);

  double x=0.01;
  double dx=0.01;
  
  for (int ii=1; x<=M_PI_2; x+=dx)
    {
      std::cout<<x<<"\t"<<std::abs(std::sin(x)-sin_pade(x))/std::sin(x)<<"\n";
    }
  
  return 0;
}

double sin_pade (double x)
{
  double sinpade=0.0;
  
  if (std::abs(x)<=1e-8)
    {
      sinpade=x;
    }

  if (std::abs(x)<=M_PI/6)
    {
      double u=x/3;
      sinpade=(3-4*sin_aux(u)*sin_aux(u))*sin_aux(u);
    }

  if ((std::abs(x)<=1e-8) && (M_PI/6<=std::abs(x)))
    {
      sinpade=sin_aux(x);
    }
    
  return sinpade;
}

double sin_aux (double u)
{
  double sinaux=0.0;
  double num=(5324.0+(34911.0/1430)*pow(u,4))-((29593.0/39)*pow(u,2)+(479249.0/2162169)*pow(u,6));
  double den=5324.0+(1671.0/13)*pow(u,2)+(97.0/66)*pow(u,4)+(2623.0/308880)*pow(u,6);
  sinaux=u*(num/den);

  return sinaux;
}
