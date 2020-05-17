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
};

void randomly_fill_matrix (Eigen::MatrixXi & M, const float prob, const int seed, std::vector<bool> & visit);
void dfs (Eigen::MatrixXi & M, std::vector<bool> & visit, percolate_tf & perc, std::vector<cluster_attributes> & cl_att_vect);
void dfs_aux (Eigen::MatrixXi & M, std::vector<bool> & visit, int n, int m, int array_coef, percolate_tf & perc, cluster_attributes & cl_att, std::vector<int> & dfs_buff);
double largest_perc_cluster(std::vector<cluster_attributes>  cl_att_v);
void cluster_series_generate (int seed, unsigned int N, float prob, std::vector<cluster_attributes> & cl_att_vect, double * percol_a);
void print_system (int seed, unsigned int N, float prob, const Eigen::MatrixXi & X, std::vector<cluster_attributes> & cl_att_vect);
void gen_stat (double * larg_cl, double * percol_a, int sample_size, float prob, std::vector<statistics> & stat_vect);
void print_stat (std::vector<statistics> & stat_vect, float prob, unsigned int N);
