//Hacer un programa que calcule la constante de Euler para la serie armónica 1/k.

#include <iostream>
#include <cmath>

const int N=5000;

double harmonicseries (int n);

int main ()
{
  std::cout.precision(8);
  std::cout.setf(std::ios::scientific);

  double conseuler=0.0;
  
  for (int ii=1; ii<=N; ii+=100)
    {
      conseuler=harmonicseries(ii)-std::log(ii);
      std::cout<<ii<<"\t"<<conseuler<<"\n";
    }
  return 0;
}

double harmonicseries (int n)
{
  double suma=1.0;
  for (int ii=2; ii<=n; ii++)
    {
      suma+=1.0/ii;
    }
  return suma;
}
