//https://floobits.com/cfangelq/Proyecto_intermedio/file/
//gcc -wall random_m_2.cpp:88:14: warning: comparison of integer expressions of different signedness: ‘Eigen::DenseCoeffsBase<Eigen::Matrix<int, -1, -1>, 1>::Scalar’ {aka ‘int’} and ‘const unsigned int’ [-Wsign-compare]
//   88 |   if( M(n,m) == cluster_id ) ---->>> quitandole el unsigned

#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <vector>
/*struct cluster_attributes{ //generacion de una variable que tenga los atributos de un cluster
  const int cluster_id;
  int cluster_size;
  bool percolate;
  }*/
void randomly_fill_matrix (Eigen::MatrixXi & M, const float prob, const int seed, std::vector<bool> & visit);
void dfs (Eigen::MatrixXi & M, std::vector<bool> & visit, std::vector<int> & cl_id_vect, std::vector<int> cl_size_vect);
void dfs_aux (Eigen::MatrixXi & M, std::vector<bool> & visit, const  int & cluster_id, int n, int m, unsigned int & cluster_size, int array_coef);

int main(void)
{
  int seed=1;
  int N=50;
  float prob=0.4;
  Eigen::MatrixXi X (N,N);
  std::vector<bool> visited (X.size(), false); //generacion de un vector tamaño nxn tipo bool que se usa como check para el dfs
  std::vector<int> cl_id_vect; //vector de atributo id del cluster
  std::vector<int> cl_size_vect;//vector de atributo tamaño del cluster
  randomly_fill_matrix (X, prob, seed, visited);
  dfs (X, visited, cl_id_vect, cl_size_vect);
  std::cout<< X << std::endl;
  std::vector<bool>().swap(visited); //forma sugerida por google para liberar la memoria de un vector
  return 0;
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


void dfs (Eigen::MatrixXi & M, std::vector<bool> & visit, std::vector<int> & cl_id_vect, std::vector<int> cl_size_vect)
{
  unsigned int cluster_id = 1; //declaracion del id para los cluster
  for (int i=0; i<M.size(); i++)
    {
      
      if ( visit[i] == false)
	{
	  unsigned int cluster_size = 0; // inizaliacion del contador de tamaño
	  cluster_id+=1; //cambio del id del cluster
	  int col_coef = i/M.cols(); //conversion de la posicion actual i a (n , m)
	  int row_coef = i%M.rows();
	  
	  dfs_aux(M, visit, cluster_id, col_coef, row_coef, cluster_size, i);//llamado al explorador de clusters
	  
	  cl_id_vect.push_back (cluster_id);// añade una entrada igual al id del cluster al final del vector
	  
	  cl_size_vect.push_back (cluster_size);// añade una entradada igual al tamaño del cluster al final del vector
	}
      else continue;
    }
}
	  

void dfs_aux (Eigen::MatrixXi & M, std::vector<bool> & visit, const  int & cluster_id, int n, int m, unsigned int & cluster_size, int array_coef)
{
  /*int aux_mtoa_coef = (n*M.cols())+m;*/ //array_coef esta haciendo el trabajo //conversion de los coeficientes tipo matriz a tipo array
  /*bool aux_top = false; 
    bool aux_bottom = false; */ //todavia no implementado, revisa si el cluster es percolante
  if(n < 0 || n >= M.cols() || m < 0 || m >= M.rows()) //condicion para las fronteras de la matriz
    {
      return;
    }

  if(visit[array_coef] == true) //evita las casillas visitadas
    {
      return;
    }
  if( M(n,m) == cluster_id )
    {
      return;
    }
  
  visit[array_coef] = true; //escribe la casilla como visitada
  
  M(n,m) = cluster_id; //escribe la entrada actual en la matriz con el id
  
  cluster_size += 1; //añade 1 al tamaño cada vez que se cumple la orden


  
  dfs_aux (M, visit, cluster_id, n+1, m, cluster_size, array_coef+M.cols());
  dfs_aux (M, visit, cluster_id, n-1, m, cluster_size, (array_coef-M.cols()));
  dfs_aux (M, visit, cluster_id, n, m+1, cluster_size, array_coef+1);
  dfs_aux (M, visit, cluster_id, n, m-1, cluster_size, array_coef-1);
  //^^ busca en las casillas adyacentes
}
