#include <bits/stdc++.h>
#include "./fibHeap.hpp"
#include "./binaryHeap.hpp"
#define INFNTY numeric_limits<int>::max()
using namespace std;
typedef pair<int,int> pii;
typedef vector<vector<pii > > Graph;

vector<int> reweight(Graph &G) {
  vector<int> ret = vector<int>(G.size(), 0);
  for (size_t i=1, cnt=1; i<G.size() && cnt; i++) {
    cnt=0;
    for(size_t u=1; u<G.size(); u++) {
      for(size_t l=0; l<G[u].size(); l++) {
        int w = G[u][l].first;
        int v = G[u][l].second;
        if (ret[u] + w < ret[v]) {
          ret[v] = ret[u] + w;
          cnt=1;
        }
      }
    }
  }
  //Nao testamos ciclos nao negativos por causa do enunciado
  for(size_t u=1; u<G.size(); u++) {
    for(size_t l=0; l<G[u].size(); l++) {
      int v = G[u][l].second;
      G[u][l].first += ret[u] - ret[v];
    }
  }
  return ret;
}

//Dijkstra algorithm using STL set as priority_queue
vector<int> dijkstra_set(Graph &G, int s) {
  int w, u;
  set<pii> Q; //no need for multiset
  vector<int> best = vector<int>(G.size(), INFNTY);
  best[s] = 0;
  Q.insert(pii(0,s));

  while(!Q.empty()) {
    w = Q.begin()->first; //find min
    u = Q.begin()->second;
    Q.erase(Q.begin()); //delete min
    vector<pii>::iterator end = G[u].end();
    for (vector<pii>::iterator it=G[u].begin(); it != end; it++) {
      if (w + it->first < best[it->second]) {//update min
        if (best[it->second] != INFNTY)
          Q.erase(Q.find(pii(best[it->second], it->second)));
        best[it->second] = w + it->first;
        Q.insert(pii(best[it->second], it->second));
      }
    }
  }
  return best;
}

//Dijkstra algorithm using STL set as priority_queue (without using decrease_key)
vector<int> dijkstra_set_lazy(Graph &G, int s) {
  int w, u;
  set<pii> Q; //no need for multiset
  vector<int> best = vector<int>(G.size(), INFNTY);
  vector<bool> done = vector<bool>(G.size(), false);
  best[s] = 0;
  Q.insert(pii(0,s));

  while(!Q.empty()) {
    w = Q.begin()->first; //find min
    u = Q.begin()->second;
    Q.erase(Q.begin()); //delete min
    if (done[u]) continue;
    done[u] = true;
    vector<pii>::iterator end = G[u].end();
    for (vector<pii>::iterator it=G[u].begin(); it != end; it++) {
      if (w + it->first < best[it->second]) {//update min
        best[it->second] = w + it->first;
        Q.insert(pii(best[it->second], it->second));
      }
    }
  }
  return best;
}

//Dijkstra algorithm using STL priority_queue as priority_queue (no decrease_key)
vector<int> dijkstra_stl_pq_lazy(Graph &G, int s) {
  int w, u;
  priority_queue<pii, vector<pii>, greater<pii> > Q;
  vector<int> best = vector<int>(G.size(), INFNTY);
  vector<bool> done = vector<bool>(G.size(), false);
  best[s] = 0;
  Q.push(pii(0,s));

  while(!Q.empty()) {
    w = Q.top().first; //find min
    u = Q.top().second;
    Q.pop();
    if (done[u]) continue;
    done[u] = true;
    vector<pii>::iterator end = G[u].end();
    for (vector<pii>::iterator it=G[u].begin(); it != end; it++) {
      if (w + it->first < best[it->second]) {//update min
        best[it->second] = w + it->first;
        Q.push(pii(best[it->second], it->second));
      }
    }
  }
  return best;
}

//Dijkstra algorithm using FibHeap as priority_queue
vector<int> dijkstra_fib(Graph &G, int s) {
  int w, u;
  vector<int> best = vector<int>(G.size(), INFNTY);
  vector<Node<pii>*> pos = vector<Node<pii>*>(G.size(), NULL);
  FibHeap<pii> Q;
  best[s] = 0;
  pos[s] = Q.insert(pii(0,s));


  while(!Q.empty()) {
    w = Q.top().first; //find min
    u = Q.top().second;
    Q.pop();
    vector<pii>::iterator end = G[u].end();
    for (vector<pii>::iterator it=G[u].begin(); it != end; it++) {
      if (w + it->first < best[it->second]) {//update min
        if (best[it->second] != INFNTY)
          Q.decrease_key(pos[it->second], pii(w + it->first, it->second));
        else
          pos[it->second] = Q.insert(pii(w + it->first, it->second));
        best[it->second] = w + it->first;
      }
    }
  }
  return best;
}

//Dijkstra algorithm using BinaryHeap as priority_queue
vector<int> dijkstra_binary(Graph &G, int s) {
  int w, u;
  vector<int> best = vector<int>(G.size(), INFNTY);
  vector<list<pair<int, pii> >::iterator> pos = vector<list<pair<int, pii> >::iterator>(G.size(), list<pair<int, pii> >::iterator());
  BinaryHeap<pii> Q;
  best[s] = 0;
  pos[s] = Q.insert(pii(0,s));


  while(!Q.empty()) {
    w = Q.getMin().first; //find min
    u = Q.getMin().second;
    Q.deleteMin();
    vector<pii>::iterator end = G[u].end();
    for (vector<pii>::iterator it=G[u].begin(); it != end; it++) {
      if (w + it->first < best[it->second]) {//update min
        if (best[it->second] != INFNTY)
          Q.decrease_key(pos[it->second], pii(w + it->first, it->second));
        else
          pos[it->second] = Q.insert(pii(w + it->first, it->second));
        best[it->second] = w + it->first;
      }
    }
  }
  return best;
}
//Applies johnson's algorithm on G, using the vertexes in f as sources
//The return vector is an associative version:
//ret[i][j] := minimum distance from f[i] to j
pair<pii, vector<int> > johnsons(Graph &G, vector<int> f, vector<int> (*dij)(Graph &, int)) {

  vector<int> ans = vector<int>(G.size(), 0);
  pair<pii,vector<int> > ret = pair<pii, vector<int> >(pii(INFNTY,INFNTY), vector<int>());
  vector<int> h = reweight(G);//bellman-ford to calc reweight function
  for (size_t i=0; i<f.size(); i++) {
    vector<int> dr = dij(G, f[i]);//run dijkstra
    for (size_t j=1; j<G.size(); j++) {//fix weights:
      if (dr[j] == INFNTY) {
        ans[j] = INFNTY;
      } else if (ans[j] != INFNTY) {
          ans[j] += dr[j] + h[j] - h[f[i]];
      }
    }
  }
  for (size_t i=1; i<G.size(); i++) {
    if (ans[i] < ret.first.second) {
      ret.first.second = ans[i];
      ret.first.first = i;
    }
  }
  if (ret.first.second == INFNTY) return ret;
  for (size_t i=0; i<f.size(); i++) {
    vector<int> dr = dij(G, f[i]);//run dijkstra
    ret.second.push_back(dr[ret.first.first]+ h[ret.first.first] - h[f[i]]);
  }
  return ret;
}

int main() {
  int N, F, C;
  vector<int> f;
  Graph G; //graph representation

  //Input:
  scanf("%d %d %d", &N, &F, &C);
  f = vector<int>();
  for (int i=1, aux; i<=F; i++) {
    scanf("%d", &aux);
    f.push_back(aux);
  }
  G = Graph(N+1, vector<pii>());
  for (int i=1, u, v, w; i<=C; i++) {
    scanf("%d %d %d", &u, &v, &w);
    G[u].push_back(pii(w,v));
  }

  //Obtem distancias minimas
  pair<pii, vector<int> > sp = johnsons(G, f, dijkstra_fib);

  //Imprime os resultados:
  if (sp.first.second == INFNTY) {
    printf("N\n");
  } else {
    printf("%d %d\n", sp.first.first, sp.first.second);
    for (int j=0; j<F; j++)
      printf("%d ", sp.second[j]);
    printf("\n");
  }
}
