using namespace std;
typedef pair<int,int> pii;
typedef vector<vector<pii > > Graph;
void print_graph(Graph &G) {
  for (size_t i=1; i<G.size(); i++) {
    printf("%lu:", i);
    for (size_t j=0; j<G[i].size(); j++) {
      printf(" %d:%d |", G[i][j].first, G[i][j].second);
    }
    printf("\n");
  }
}

void print_iarr(vector<int>&v) {
  for (size_t i=0; i<v.size(); i++) {
    printf("%d ", v[i]);
  }
  printf("\n");
}
