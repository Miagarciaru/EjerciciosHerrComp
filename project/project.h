struct cluster_attributes{ //generacion de una variable que tenga los atributos de un cluster
  int cluster_id;
  unsigned int cluster_size;
};
struct percolate_tf{
  bool aux_top;
  bool aux_bottom;
  bool aux_right;
  bool aux_left;
  bool aux_perc;
};
void randomly_fill_matrix (Eigen::MatrixXi & M, const float prob, const int seed, std::vector<bool> & visit);
void dfs (Eigen::MatrixXi & M, std::vector<bool> & visit, percolate_tf & perc, std::vector<cluster_attributes> & cl_att_vect);
void dfs_aux (Eigen::MatrixXi & M, std::vector<bool> & visit, int n, int m, int array_coef, percolate_tf & perc, cluster_attributes & cl_att);
double largest_cluster(std::vector<cluster_attributes>  cl_att_v);
void cluster_series_generate (int seed, unsigned int N, float & number_of_perc, float & sum_l_cl, float prob);
