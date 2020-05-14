//https://floobits.com/cfangelq/Proyecto_intermedio/file/random_m_4.cpp:22?new_workspace=1
#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <vector>
#include "project.h"

void cluster_series_generate (int seed, unsigned int N, float & number_of_perc, float & sum_l_cl, float prob)
{
  Eigen::MatrixXi X (N,N);
  std::vector<bool> visited (X.size(), false); //generacion de un vector tamaño nxn tipo bool que se usa como check para el dfs
  std::vector<cluster_attributes> cl_att_vect;
  percolate_tf perc; //declaracion de un struct auxiliar que indica si hubo percolacion
  randomly_fill_matrix (X, prob, seed, visited);
  dfs (X, visited, perc, cl_att_vect);
  std::cout<< X <<"\n"<< std::endl;
  std::cout<<"id \t"<< "size \t"<<std::endl;
      
  for (const auto cluster : cl_att_vect){
    std::cout<<cluster.cluster_id<<"\t"<<cluster.cluster_size<<std::endl;
  }
      
  if (perc.aux_perc==true){
    number_of_perc += 1;
  }
        
      std::cout<<"percola:"<<perc.aux_perc<<std::endl;
      std::vector<bool>().swap(visited); //forma sugerida por google para liberar la memoria de un vector
      sum_l_cl += largest_cluster(cl_att_vect);
}

double largest_cluster(std::vector<cluster_attributes>  cl_att_v)
{
  float max=0;
  for (const auto cluster : cl_att_v)
    {
      if(cluster.cluster_size > max)
	{
	  max = (float)cluster.cluster_size;  
	}
      else continue;
    }
  return max;
}



void randomly_fill_matrix (Eigen::MatrixXi & M, const float prob, const int seed, std::vector<bool> & visit)
{
  std::mt19937 gen(seed);
  std::uniform_real_distribution<float> dis(0, 1.0); //genera numeros distribuidos uniformemente
  M.setZero();
  for (int n = 0; n < M.cols(); n++){
    for (int m = 0; m < M.cols(); m++){
      if (dis(gen) >= (1.0-prob))
	{
	  M(n, m) = 1; //asigna 1 al elemento de matriz si el numero aleatorio se encuentra dentro del rango de probabilidad
	}
      else{
	   visit[(n*M.cols())+m]=true; //asume los elementos 0 de la matriz como visitados
      }
    }
  }
}


void dfs (Eigen::MatrixXi & M, std::vector<bool> & visit, percolate_tf & perc, std::vector<cluster_attributes> & cl_att_vect)
{
  cluster_attributes cl_att;
  perc.aux_perc = false; //inicializacion de las variables
  cl_att.cluster_id = 1;//declaracion del id para los cluster
  for (int i=0; i<M.size(); i++)
    {
      
      if ( visit[i] == false)
	{
	  perc.aux_top = false; 
	  perc.aux_bottom = false;
	  perc.aux_left = false;
	  perc.aux_right = false;
	  cl_att.cluster_size = 0;
	  // inizaliacion del contador de tamaño
	  cl_att.cluster_id+=1; //cambio del id del cluster
	  int col_coef = i/M.cols(); //conversion de la posicion actual i a (n , m)
	  int row_coef = i%M.rows();
	  
	  dfs_aux(M, visit, col_coef, row_coef,  i, perc, cl_att);//llamado al explorador de clusters

	  cl_att_vect.push_back (cl_att);
	  
	}
      else continue;
    }
}
	  

void dfs_aux (Eigen::MatrixXi & M, std::vector<bool> & visit, int n, int m, int array_coef, percolate_tf & perc, cluster_attributes & cl_att)
{
  if(n < 0 || n >= M.cols() || m < 0 || m >= M.rows()) //condicion para las fronteras de la matriz
    {
      return;
    }

  if(visit[array_coef] == true){ //evita las casillas visitadas   
      return;
    }
  if( M(n,m) == cl_att.cluster_id ) {
      return;
    }
  if (n==0){
    perc.aux_left=true;
  }
  if (n==(M.cols()-1)){
    perc.aux_right=true;
    }
  if (m==0){
    perc.aux_top=true;
  }
  if (m==(M.rows()-1)){
    perc.aux_bottom=true;
  }
  
  if ((perc.aux_left && perc.aux_right) || (perc.aux_top && perc.aux_bottom) == true) {
      perc.aux_perc = true; //indica si se encontró un cluster percolante
    }
  
  visit[array_coef] = true; //escribe la casilla como visitada
  
  M(n,m) = cl_att.cluster_id; //escribe la entrada actual en la matriz con el id
  
  cl_att.cluster_size += 1; //añade 1 al tamaño cada vez que se cumple la orden


  dfs_aux (M, visit, n, m+1, array_coef+1, perc, cl_att);
  dfs_aux (M, visit, n, m-1, array_coef-1, perc, cl_att);
  dfs_aux (M, visit, n-1, m, array_coef-M.cols(), perc, cl_att);
  dfs_aux (M, visit, n+1, m, array_coef+M.cols(), perc, cl_att);


  //^^ busca en las casillas adyacentes
}
