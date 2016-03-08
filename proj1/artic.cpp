#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*Variáveis globais para diminuir overhead em function calls*/
int N, L;
int ts;
vector<vector<int> > G; //graph
vector<int> d; //starting time
vector<int> low; //minimum non-parent acessible starting time
vector<int> pi; //parent
vector<bool> AP; //É Articulation Point?

/* dfs: Corre o dfs-visit do algoritmo de Tarjan
 * Devolve: O número de filhos na àrvore DFS */
int dfs(int u) {
  int ret=0;
  low[u] = d[u] = ts;
  ++ts;
  for (vector<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    int v = *it;
    if (d[v]==0) {
      ret++;
      pi[v] = u;
      dfs(v);
      if (low[v] >= d[u]) //Condição suficiente para ser AP para nós que não sejam a raíz
        AP[u] = true;
      low[u] = min(low[u], low[v]);
    } else if (v != pi[u]) {
      low[u] = min(low[u], d[v]);
    }
  }
  return ret;
}

int main() {
  /* Processa o input */
  cin >> N >> L;
  G = vector<vector<int> >(N, vector<int>());
  for (int i=0; i<L; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  /* Inicializa as estruturas da DFS: */
  d    = vector<int>(N, 0);
  low  = vector<int>(N, 0);
  pi   = vector<int>(N, -1);
  AP   = vector<bool>(N, false);
  ts   = 1;

  /* Chama a DFS: */
  for (int u=0; u<N; u++)
    if (d[u] == 0)
      AP[u] = dfs(u) > 1; //Condição de aticulation point para raízes de àrvore

  /* Imprime os resultados: */
  int apCount = 0;
  int first=-1, last=-1;
  for (int u=0; u<N; u++) {
    if (AP[u]) {
      apCount++;
      if (first==-1) first = u;
      last = u;
    }
  }
  first++; last++;

  cout << apCount << endl;
  if (apCount != 0)
    cout << first << " " << last << endl;
  else
    cout << "-1" << " " << "-1" << endl;
}
