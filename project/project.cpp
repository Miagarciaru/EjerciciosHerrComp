#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <vector>
#include <fstream>
#include <string>
#include <gsl/gsl_statistics_double.h>
#include "project.h"

void gen_stat (double * larg_cl, double * percol_a, int sample_size, float prob , std::vector<statistics> & stat_vect)
{
  statistics stat = {};
  stat.lcl_mean = gsl_stats_mean(larg_cl, 1, sample_size); //media del cluster mas grande
  stat.lcl_dvi = gsl_stats_variance_m(larg_cl, 1, sample_size, stat.lcl_mean); //desviacion de los datos para el cluster mas grande
  stat.perc_mean = gsl_stats_mean(percol_a, 1, sample_size); //prob para la percolacion
  stat.perc_dvi = gsl_stats_variance_m(percol_a, 1, sample_size, stat.perc_dvi); //desv de la perc
  stat.probab=prob;
  stat_vect.push_back (stat); //añadido del ciclo de estadistica para una probabilidad al vector 
}

void print_stat (std::vector<statistics> & stat_vect, float prob, unsigned int N){
  std::string fname="stats_Nsize_" + std::to_string(N) +".txt";
  std::ofstream fout(fname, std::ofstream::out);
  fout.precision(8); fout.setf(std::ios::scientific);
  fout << "Prob \t"<< "l_cl_mean \t" << "l_cl_dvi \t" << "perc_mean \n";
  for (const auto statis : stat_vect)
    fout<< statis.probab<< "\t"<< statis.lcl_mean << "\t" << statis.lcl_dvi <<"\t" <<statis.perc_mean<<"\t"<<statis.perc_dvi<<"\n";
}

void print_system (int seed, unsigned int N, float prob, const Eigen::MatrixXi & X, std::vector<cluster_attributes> & cl_att_vect)
{
  std::string fname="data_" + std::to_string(N) +"_" + std::to_string(prob) + "_" + std::to_string(seed) + ".txt";
  std::ofstream fout(fname, std::ofstream::out);

  // fout<<X<<"\n \n"<< "id \t"<< "size \n";
  
  for (const auto cluster : cl_att_vect){
    fout<<cluster.cluster_id<<"\t"<<cluster.cluster_size<<"\t"<<cluster.percolate<<"\n";
  }
  fout.close();
}


void cluster_series_generate (int seed, unsigned int N, float prob, std::vector<cluster_attributes> & cl_att_vect, double * percol_a )
{
  Eigen::MatrixXi X (N,N);
  std::vector<bool> visited (X.size(), false); //generacion de un vector tamaño nxn tipo bool que se usa como check para el dfs
  //std::vector<cluster_attributes> cl_att_vect;
  percolate_tf perc = {}; //declaracion de un struct auxiliar que indica si hubo percolacion
  randomly_fill_matrix (X, prob, seed, visited);
  dfs (X, visited, perc, cl_att_vect);

  print_system (seed, N, prob, X, cl_att_vect);

  if (perc.aux_perc==true){
    percol_a[seed] = 1;
  }
  /*std::cout<< X <<"\n"<< std::endl;
   std::cout<<"id \t"<< "size \t"<<std::endl;
      
  for (const auto cluster : cl_att_vect){
    std::cout<<cluster.cluster_id<<"\t"<<cluster.cluster_size<<"\t"<<cluster.percolate<<std::endl;
    }


        
    std::cout<<"percola:"<<perc.aux_perc<<std::endl;*/
  
  std::vector<bool>().swap(visited); //forma sugerida por google para liberar la memoria de un vector
  
     
}

double largest_perc_cluster(std::vector<cluster_attributes>  cl_att_v)
{
  double max=0;
  for (const auto cluster : cl_att_v)
    {
      if((cluster.cluster_size > max) && (cluster.percolate==1))
	{
	  max = (double)cluster.cluster_size;  
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
  cluster_attributes cl_att = {};
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
	  cl_att.percolate = 0;  // inizaliacion del contador de tamaño
	  cl_att.cluster_id+=1; //cambio del id del cluster

	  std::vector<int> dfs_buff;   
	  dfs_buff.push_back (i);
	  int buf = i;
	  do{
	    int col_coef = buf%M.cols(); //conversion de la posicion actual i a (n , m)
	    int row_coef = buf/M.rows();
	    dfs_aux(M, visit, row_coef, col_coef, buf, perc, cl_att, dfs_buff);//llamado al explorador de clusters
	    buf = dfs_buff.back();
	    dfs_buff.pop_back ();
	    /* if ( (buf%M.rows()) !=0){
	    std::sort(dfs_buff.begin(), dfs_buff.end());
	    std::reverse(dfs_buff.begin(), dfs_buff.end());
	    }*/
	  }while (dfs_buff.size() != 0);
	  cl_att_vect.push_back (cl_att);
	  std::vector<int>().swap(dfs_buff);
	}

	  
	  
    
      else continue;
    }
}
	  

void dfs_aux (Eigen::MatrixXi & M, std::vector<bool> & visit, int n , int m, int array_coef, percolate_tf & perc, cluster_attributes & cl_att, std::vector<int> & dfs_buff)
{

  /*if(visit[array_coef] == true){ //evita las casillas visitadas   
     return;
     }*/

  if( M(n,m) == cl_att.cluster_id ) {
      return;
    }
  if (n==0){
    perc.aux_left=true;
  }
  if (n==(M.rows()-1)){
    perc.aux_right=true;
    }
  if (m==0){
    perc.aux_top=true;
  }
  if (m==(M.cols()-1)){
    perc.aux_bottom=true;
  }
  
  if ((perc.aux_left && perc.aux_right) || (perc.aux_top && perc.aux_bottom) == true) {
      perc.aux_perc = true; //global
      cl_att.percolate = 1; //indica si se encontró un cluster percolante
  }
  
  
  visit[array_coef] = true; //escribe la casilla como visitada
  
  M(n,m) = cl_att.cluster_id; //escribe la entrada actual en la matriz con el id
  
  cl_att.cluster_size += 1; //añade 1 al tamaño cada vez que se cumple la orden

    // dfs_aux (M, visit, n-1, m, array_coef-M.cols(), perc, cl_att);
  if (array_coef+M.cols() < visit.size()){
    if (visit[array_coef+M.cols()] == false){
      dfs_buff.push_back (array_coef + M.cols());
      visit[array_coef+M.cols()] = true;
    }
  }

  // dfs_aux (M, visit, n+1, m, array_coef+M.cols(), perc, cl_att);
  if ( (array_coef-M.cols()) > 0){
    if (visit[array_coef-M.cols()] == false){
      dfs_buff.push_back (array_coef - M.cols());
      visit[array_coef-M.cols()] = true;
    }
  }
  
  //dfs_aux (M, visit, n, m+1, array_coef+1, perc, cl_att);
  if (array_coef-1 > 0){
    if( ((array_coef-1)/M.cols()) == n){   // condicion para que no cruce de fila la condicion al estar contiguos en indice array
      if (visit[array_coef-1] == false){
	dfs_buff.push_back (array_coef - 1);
	visit[array_coef-1] = true;
      }
    }
  }

  //dfs_aux (M, visit, n, m-1, array_coef-1, perc, cl_att);
  if( ((array_coef+1)/M.cols()) == n){
    if (array_coef+1 < visit.size()){
      if (visit[array_coef+1] == false){
	dfs_buff.push_back (array_coef + 1);
	visit[array_coef+1] = true;
      }
    }
  }

  //^^ busca en las casillas adyacentes
}

