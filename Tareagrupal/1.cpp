//Inicialmente reduce el dominio de cualquier x en radianes a -pi/2<x<pi/2.

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

double reducedominio (double x);

int main ()
{
  std::cout.precision(16);
  std::cout.setf(std::ios::scientific);

  double x=0.0;
  double dx=0.1;

  for (int ii=0; ii<=50; ii++)
    {
      std::cout<<x<<"\t"<<reducedominio(x)<<"\n";
      x+=dx;
    }
  return 0;
}

double reducedominio (double x)
{
  int centinela=0;
  int ii=0;
  double valor=x;
  
  while (centinela!=1) //Limita a x a un x entre -pi/2 a pi/2.
    {
      
      if (std::abs(valor)<=M_PI_2)
	{
	  centinela=1;
	}

      else if (std::abs(valor)>=M_PI_2)
	{
	  ii++;
	  valor=valor-ii*M_PI;
	}
    }
  
  return valor;
}
