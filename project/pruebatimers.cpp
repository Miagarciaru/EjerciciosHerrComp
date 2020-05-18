#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <gsl/gsl_statistics_double.h>
#include <chrono>

struct cluster_attributes{ //generacion de una variable que tenga los atributos de un cluster
  int cluster_id;
  unsigned int cluster_size;
  double percolate;//tipo double para hacer calculos luego sin hacer conversion
};
struct percolate_tf{ //auxiliar de la percolacion
  bool aux_top;
  bool aux_bottom;
  bool aux_right;
  bool aux_left;
  bool aux_perc;
};
struct statistics{ //estructura para las estadisticas
  double lcl_mean; //media cluster grande
  double lcl_dvi; //desv cluster
  double perc_mean;// prob perc
  double perc_dvi; //desv prob perc
  float probab;
  unsigned int size;
};

void cluster_series_generate (int seed, unsigned int N, float prob, std::vector<cluster_attributes> & cl_att_vect, double * percol_a);
void randomly_fill_matrix (Eigen::MatrixXi & M, const float prob, const int seed, std::vector<bool> & visit);
void dfs (Eigen::MatrixXi & M, std::vector<bool> & visit, percolate_tf & perc, std::vector<cluster_attributes> & cl_att_vect);
void dfs_aux (Eigen::MatrixXi & M, std::vector<bool> & visit, int n, int m, int array_coef, percolate_tf & perc, cluster_attributes & cl_att, std::vector<int> & dfs_buff);
double largest_perc_cluster(std::vector<cluster_attributes>  cl_att_v);
void print_system (int seed, unsigned int N, float prob, const Eigen::MatrixXi & X, std::vector<cluster_attributes> & cl_att_vect);
void gen_stat (double * larg_cl, double * percol_a, int sample_size, float prob, std::vector<statistics> & stat_vect, unsigned int N);
void print_stat (std::vector<statistics> & stat_vect, unsigned int N);
void print_elapsed(auto start, auto end );


const int sample_size=20;
int main(void)
{
  unsigned int N=0;
  std::vector<statistics> stat_vect;
  for (int i = 5; i<= 9; i++)
    {
      N = std::pow(2,i);
      float prob = 0.0;
      double * larg_cl= new double[sample_size] {0.0}; //array para los clusters percolantes mas grandes de cada matriz (normalizado)
      double * percol_a= new double[sample_size] {0.0};//array para la percolacion de matrices
      while (prob <= 1.0)
	{
	  
	 auto start = std::chrono::steady_clock::now();
	  
	  if (prob < 0.53){
	    prob += 0.054;
	  }
	  if ((prob>=0.53) && (prob<=0.65)){
	    prob += 0.01;
	  }
	  if (prob>0.65){
	    prob += 0.035;
	  }

	  if (prob > 1.0){
	    break;
	  }
	  for (int seed=0; seed<sample_size; seed++)
	    {
	      std::vector<cluster_attributes> cl_att_vect; //vector de atributos del cluster
	      cluster_series_generate(seed, N, prob, cl_att_vect, percol_a);
	      larg_cl[seed]= (largest_perc_cluster(cl_att_vect)/(N*N));
	      std::vector<cluster_attributes>().swap(cl_att_vect);
      
	    }
	  gen_stat(larg_cl, percol_a, sample_size, prob, stat_vect, N);
    
    auto end = std::chrono::steady_clock::now();

    print_elapsed(start, end);

	}
      delete [] larg_cl;
      delete [] percol_a;
    }
  print_stat(stat_vect, N);
  std::vector<statistics>().swap(stat_vect);

  return 0;
}


void gen_stat (double * larg_cl, double * percol_a, int sample_size, float prob , std::vector<statistics> & stat_vect, unsigned int N)
{
  statistics stat = {};
  stat.lcl_mean = gsl_stats_mean(larg_cl, 1, sample_size); //media del cluster mas grande
  stat.lcl_dvi = gsl_stats_variance_m(larg_cl, 1, sample_size, stat.lcl_mean); //desviacion de los datos para el cluster mas grande
  stat.perc_mean = gsl_stats_mean(percol_a, 1, sample_size); //prob para la percolacion
  stat.perc_dvi = gsl_stats_variance_m(percol_a, 1, sample_size, stat.perc_mean); //desv de la perc
  stat.probab = prob;
  stat.size = N;
  stat_vect.push_back (stat); //añadido del ciclo de estadistica para una probabilidad al vector 
}

void print_stat (std::vector<statistics> & stat_vect, unsigned int N){
  std::string fname="stats_full.txt";
  std::ofstream fout(fname, std::ofstream::out);
  fout.precision(8); fout.setf(std::ios::scientific);
  fout <<"size \t"<<"Prob \t"<< "l_cl_mean \t" << "l_cl_dvi \t" << "perc_mean \t"<< "perc_dvi \n";
  for (const auto statis : stat_vect)
    fout<< statis.size <<"\t"<< statis.probab << "\t"<< statis.lcl_mean << "\t" << statis.lcl_dvi <<"\t " <<statis.perc_mean<<"\t"<<statis.perc_dvi<<"\n";
}

void print_system (int seed, unsigned int N, float prob, const Eigen::MatrixXi & X, std::vector<cluster_attributes> & cl_att_vect)
{
  std::string fname="data_" + std::to_string(N) +"_" + std::to_string(prob) + "_" + std::to_string(seed) + ".txt";
  std::ofstream fout(fname, std::ofstream::out);

  fout<<X<<"\n \n"<< "id \t"<< "size \n";
  
  for (const auto cluster : cl_att_vect){
    fout<<cluster.cluster_id<<"\t"<<cluster.cluster_size<<"\t"<<cluster.percolate<<"\n";
  }
  fout.close();
}


void cluster_series_generate (int seed, unsigned int N, float prob, std::vector<cluster_attributes> & cl_att_vect, double * percol_a )
{
  Eigen::MatrixXi X (N,N);
  std::vector<bool> visited (X.size(), false); //generacion de un vector tamaño nxn tipo bool que se usa como check para el dfs
  percolate_tf perc = {}; //declaracion de un struct auxiliar que indica si hubo percolacion
  randomly_fill_matrix (X, prob, seed, visited);
  dfs (X, visited, perc, cl_att_vect);

  if ( (( N == 128 && (prob > 0.54) && (prob < 0.58)) && seed == 10) || (( N == 512 && (prob > 0.54) && (prob < 0.559) && (seed == 9 || seed== 11) )) ){
    print_system (seed, N, prob, X, cl_att_vect);
  }

  if (perc.aux_perc==true){
    percol_a[seed] = 1;
  }
  /*std::cout<< X <<"\n"<< std::endl;
   std::cout<<"id \t"<< "size \t"<<std::endl;
      
  for (const auto cluster : cl_att_vect){
    std::cout<<cluster.cluster_id<<"\t"<<cluster.cluster_size<<"\t"<<cluster.percolate<<std::endl; //check de output a consola
    }
    std::cout<<"percola:"<<perc.aux_perc<<std::endl;*/
  
  std::vector<bool>().swap(visited); //forma sugerida por google para liberar la memoria de un vector
  
     
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
	  }while (dfs_buff.size() != 0);
	  cl_att_vect.push_back (cl_att);
	  std::vector<int>().swap(dfs_buff);
	}

	  
	  
    
      else continue;
    }
}
	  

void dfs_aux (Eigen::MatrixXi & M, std::vector<bool> & visit, int n , int m, int array_coef, percolate_tf & perc, cluster_attributes & cl_att, std::vector<int> & dfs_buff)
{


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

void print_elapsed(auto start, auto end )
{
  std::cout << "Elapsed time in ms: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
            << "\n";
}
