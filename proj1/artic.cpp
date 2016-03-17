#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*Variáveis globais para diminuir overhead em function calls*/
int N, L;
int ts;
vector<vector<int> > G; //graph
vector<int> disco; //discovery time
vector<int> low; //minimum non-parent acessible starting time
vector<int> parent; //parent
vector<bool> AP; //É Articulation Point?

/* dfs: Corre o dfs-visit do algoritmo de Tarjan
 * Devolve: O número de filhos na àrvore DFS

 * Baseado no biconnected components algorithm descrito em http://doi.acm.org/10.1145/362248.362272
 */
int dfs(int u) {
  int ret=0;
  low[u] = disco[u] = ts; //define o start time do vértice
  ++ts;
  for (vector<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
    int v = *it;
    if (disco[v] == 0) { //Se ainda não foi visitado:
      ret++; //aumenta o numero de filhos na arvore dfs do vértice u
      parent[v] = u; //define o pai de v como sendo u
      dfs(v); //corre o dfs-visit em v
      if (low[v] >= disco[u]) //Condição suficiente para ser AP para vértices que não sejam a raíz
        AP[u] = true;
      low[u] = min(low[u], low[v]);
    } else if (v != parent[u]) {
      low[u] = min(low[u], disco[v]);
    }
  }
  return ret;
}

int main() {
  /* Faz o IO ser mais rápido: */
  ios_base::sync_with_stdio(0);cin.tie(0);

  /* Processa o input */
  cin >> N >> L;
  G = vector<vector<int> >(N+1, vector<int>());
  for (int i=1; i<=L; i++) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  /* Inicializa as estruturas da DFS: */
  disco  = vector<int>(N+1, 0);
  low    = vector<int>(N+1, 0);
  parent = vector<int>(N+1, -1);
  AP     = vector<bool>(N+1, false);
  ts     = 1;

  /* Chama a DFS:
    Como temos a garantia de apenas 1 componente fica assim:  */
  AP[1] = dfs(1) > 1; //Condição de articulation point para raízes de àrvore

  /* Imprime os resultados: */
  int apCount = 0;
  int first=-1, last=-1;
  for (int u=1; u<=N; u++) {
    if (AP[u]) {
      apCount++;
      if (first == -1) first = u;
      last = u;
    }
  }

  cout << apCount << endl;
  if (apCount != 0)
    cout << first << " " << last << endl;
  else
    cout << "-1" << " " << "-1" << endl;
}
