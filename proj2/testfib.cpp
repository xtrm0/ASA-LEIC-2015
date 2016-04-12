#include <bits/stdc++.h>
using namespace std;
#include "./fibHeap.hpp"
#define lspace(l) for(int asd=0; asd<l; asd++) cout << " "
void printNode(Node<int>*r, int l) {
  if (!r) return;
  lspace(l);
  cout << (r->mark ? "-" : "+ ") << r->key << endl;
  Node<int> * aux = r->c;
  if (!aux) return;
  do {
    printNode(aux, l+1);
    aux = aux->r;
  } while(aux!=r->c);
}

void printFib(FibHeap<int> &H) {
  lspace(10) << "===="; cout<<endl;
  if (!H.getTop()) {
    cout << "empty" << endl;
    return;
  }
  Node<int> * aux = H.getTop();
  do {
    printNode(aux, 0);
    aux = aux->r;
  } while(aux!=H.getTop());
}

#define MAX 100
int main() {
  FibHeap<int> H;
  for(int i=MAX; i>=0; i--) {
    H.insert(i);
    if (H.top()!=i) {
      cout << "ShIt" << i << ":" << H.top() << endl;
    }
    printFib(H);
  }

  for(int i=0; i<=MAX; i++) {
    if (H.top()!=i) {
      cout << "ShIt" << i << ":" << H.top() << endl;
    }
    H.pop();
    printFib(H);
  }

}
