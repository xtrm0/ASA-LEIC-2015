import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

/*Pequena Descrição do Código: Através de um grafo não direccionado contar o número de Pontos de 
Articulação (Articulation points). Para tal criamos um grafo das adjacências, neste caso, um ArrayList 
com N listas cada uma descrevendo um vértice do grafo. Ao adicionarmos uma ligação, adicionamos cada um dos
vértices à lista do outro. A função principal AP() tem o objetivo de fazer a inicialização de variáveis, 
começar o algoritmo DFS no grafo e fazer as contagens e medições necessárias à resolução do enunciado.*/

public class Graph{
    private int N;   
    private ArrayList<Integer> adj[];
    private int time = 0;
 
    public Graph(int n){
        N = n;
        adj = new ArrayList[n];
        for (int i=0; i<n; ++i)
            adj[i] = new ArrayList<Integer>();
    }
    //Adição de uma aresta através de dois vértices
    public void addEdge(int u, int v){
        adj[u].add(v); 
        adj[v].add(u); 
    }
 
    public void DFS(int u, boolean visited[], int start[], int end[], int parent[], boolean ap[]){
        int children = 0;
        visited[u] = true;  //Marcação do Vértice Atual como Visitado
        start[u] = end[u] = ++time;

        //Percorre os vértices adjacentes a u
        Iterator<Integer> i = adj[u].iterator();
        while (i.hasNext()){
            int v = i.next();
            //Se v não tenha sido visitado marca-o como filho de u e é efetuado o algoritmo DFS nele 
            if (!visited[v]){
                children++;
                parent[v] = u;
                DFS(v, visited, start, end, parent, ap);
                //Verifica se os vértices após v têm ligação com algum antecessor de u
                end[u]  = Math.min(end[u], end[v]);
                // u é raiz da árvore e tem 2 ou mais filhos
                if (parent[u] == -1 && children > 1)
                    ap[u] = true;
                // u não é raiz mas o tempo final de um dos seus filhos é maior do que o tempo de descoberta de dele
                if (parent[u] != -1 && end[v] >= start[u]) 
                    ap[u] = true;
            }
            else if (v != parent[u])
                end[u]  = Math.min(end[u], start[v]);
        }
    }
 
    public void AP(){
        //Inicialização das estruturas da DFS
        boolean visited[] = new boolean[N+1];
        int start[] = new int[N+1];
        int end[] = new int[N+1];
        int parent[] = new int[N+1];
        boolean ap[] = new boolean[N+1];
 
        for (int i = 0; i < N; i++){
            parent[i] = -1;
            visited[i] = false;
            ap[i] = false;
        }

        //Variáveis de Apoio ao Projeto
        int count = 0;
        int m = -1;
        int M = -1;
 
        //Inicializa o algortimo DFS
        for (int i = 0; i < N; i++){
            if (visited[i] == false)
                DFS(i, visited, start, end, parent, ap);
        }

        //Determinação do m e do M, bem como fazer a contagem total de APs
        for (int i = 1; i < N; i++){
            if (ap[i]){
                count++;
                if(m == -1)
                    m = i;
                M = i;
            }
        }

        //Imprime resultados
        System.out.println(count);
        System.out.println(m + " " + M);
    }
 
    public static void main(String args[]){

        //Processamento de Input
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int l = input.nextInt();
        Graph g = new Graph(n+1);
        for(int i = 0; i < l; i++)
            g.addEdge(input.nextInt(), input.nextInt());

        /*Chamada à função principal*/
        g.AP();
    }
}