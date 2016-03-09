# Análise e Síntese de Algoritmos
## 1º Projeto - Grupo 109

### Introdução
Com este projeto pretendemos expor um algoritmo em tempo linear para o problema proposto, explicar a sua implementação e fazer uma análise teórica e experimental da complexidade temporal e espacial deste.

### Descrição do problema
O problema descrito pedia que, dentro de uma rede social onde a informação pode ser partilhada entre todas as pessoas da rede, encontrar pessoas que são fundamentais para a transmissão de informação. Isto é, pessoas que ao fossem removidas da rede social tornam impossível a transmissão de informação entre todos os membros da rede.

Ora este problema pode ser descrito como um problema num grafo não direcionado, em que:
 + cada pessoa é um vértice da rede;
 + uma ligação entre pessoas corresponde a uma aresta;
 + o grafo é um grafo conexo. ("existe sempre uma
forma de partilha de informação entre qualquer par de pessoas")

Assim, o problema descrito é equivalente ao de encontrar num grafo conexo G(V,E), com N = #V e L = #E, vértices que se forem removidos tornam o grafo desconexo, ou seja, de encontrar vértices de corte (articulation points).

### Algoritmo utilizado
Sendo o problema um cuja solução foi estudada nas aulas, utilizámos o algoritmo dado nas aulas - o algoritmo de Tarjan para encontrar vértices de corte.

### Explicação do algoritmo
> TODO
### Prova de correção do algoritmo
> TODO (provar que o algoritmo funciona)
### Análise assintótica temporal téorica do algoritmo
> TODO
### Análise assintótica temporal experimental do algoritmo
> TODO
### Análise assintótica espacial
> TODO (ez pea z)
### Prova de otimalidade do algoritmo
> TODO (provar que o algoritmo é ótimo assintóticamente) (fácil)

### Notas sobre a implementação
Na implementação do algoritmo, foram feitas algumas modificação ao algoritmo de Tarjan geral. Nomeadamente:
+ Não foi utilizado o vetor color, em vez disso o tempo de começo de todos os vértices foi inicializado a 0, e foi assumida que a cor é branca caso o tempo de começo seja 0 ou preta caso contrário.
+ Não foi guardada informação relativa ao tempos de fim nem incrementado o tempo quando se acaba de processar um vértice, uma vez que esta informação não é necessária para classificar vértices de corte.

### Conclusão
> TODO
