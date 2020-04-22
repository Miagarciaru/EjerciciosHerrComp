#include <iostream>
#include <cmath>

const int f=200;
const int t=5;
double nl=1.52;

double raizp (double a, double b, double c);
double raizn (double a, double b, double c);

int main ()
{
  std::cout.precision(15);
  std::cout.setf(std::ios::scientific);

  double a[3]={0.0};
  double b[3]={0.0};
  double c[3]={0.0};
  int t[3]={5, 3, 3};
  int f[3]={200, 20, -20};

  std::cout<<"Foco"<<"\t"<<"Grosor"<<"\t"<<"Radio mayor"<<"\t"<<"Radio menor"<<"\n";
  for (int ii=0; ii<=2; ii++)
    {
      a[ii]=1.0/f[ii];
      b[ii]=-1.04;
      c[ii]=1.0*t[ii]*(0.52*0.52)/1.52;

      std::cout<<f[ii]<<"\t"<<t[ii]<<"\t"<<raizp (a[ii], b[ii], c[ii])<<"\t"<<raizn (a[ii], b[ii], c[ii])<<"\n";
    }
  
  return 0;
}

double raizp (double a, double b, double c)
{
  double x=0.0;
  x=(-b+sqrt(b*b-4*a*c))/(2*a);
  return x;
}

double raizn (double a, double b, double c)
{
  double x=0.0;
  x=(-b-sqrt(b*b-4*a*c))/(2*a);
  return x;
}
