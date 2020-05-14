//https://floobits.com/cfangelq/Proyecto_intermedio/file/random_m_4.cpp:22?new_workspace=1
#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <vector>
#include "project.h"

int main(void)
{
  float number_of_perc=0; //variable para la cantidad de clusters percolantes en la muestra
  unsigned int N=20;
  float prob=0.6;
  float sum_l_cl=0; //variable para la sumatoria de los clusters
  for (int seed=0; seed<N; seed++)
    {
      cluster_series_generate(seed, N, number_of_perc, sum_l_cl, prob);
    }
  float perc_prob = number_of_perc/N;
  float average = sum_l_cl/N;
  std::cout<<"largest cluster avg. "<<average<<std::endl;
  std::cout<<"perc prob "<<perc_prob<<std::endl;
  return 0;
}
