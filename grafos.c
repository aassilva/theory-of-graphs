#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int num_nodes = 0;

//Estrutura de armazenamento para armazenar o grafo.
typedef struct no {
	int vertice;
	int peso;
	struct no *prox;
} nodes;

nodes list[10000];

//Estrutura de armazenamento para a implementação das buscas.
typedef struct Node{
	int num;
	struct Node *prox;
} lista_busca;


//Códigos para a geração e armazenamento do grafo simples.
int tamanho (int num_nodes) {
	printf("\n");
	printf("Entre com a quantidade de vertices: ");
	printf("\n");
	scanf("%d", &num_nodes);
	return num_nodes;
}

int menu(int opcao) {
	printf("\n");
	printf("1. para grafos simples. \n2. para grafos com peso. \n0. para sair.\nDigite uma das opções acima: ");
	scanf("%d", &opcao);
	return opcao;
}

int tipo_grafo(int opcao) {
	printf("\n");
	printf("1. para grafos densos. \n2. para grafos espaços. \n0. para sair.\nDigite uma das opções acima: ");
	scanf("%d", &opcao);
	return opcao;
}

int create_binary(float sparsity) {
	int r = rand();
	if(r < RAND_MAX * sparsity) {
        	return 1;
	} else {
        	return 0;
	}
}

void create_matrix(int matriz[num_nodes][num_nodes], int num_nodes, float sparsity) {
	for (int coluna = 0; coluna < num_nodes; coluna ++) {
		for (int linha = 0; linha < num_nodes; linha ++) {
			if (linha == coluna) {
				matriz[coluna][linha] = 0;
			}
			else {
				int aux = create_binary(sparsity);
				matriz[coluna][linha] = aux;
				matriz[linha][coluna] = aux;
			}
		}
	}
}

void inserir_aresta(nodes *list, int node_adjacente) {
	nodes *aux;
	nodes *tmp;

	aux = (nodes*) malloc((int)sizeof(nodes));
	aux->vertice = node_adjacente;
	aux->prox = NULL;
	list->vertice++;
	if(list->prox == NULL)
	list->prox = aux;
	else {
		tmp = list->prox;
		if (tmp->vertice > node_adjacente) {
			aux->prox = tmp;
			list->prox = aux;
		}
		else if (tmp->prox == NULL) {
			aux->prox = tmp->prox;
			tmp->prox = aux;
		}
		else {
			while((tmp->prox != NULL) &&(tmp->prox->vertice < node_adjacente)) {
				tmp = tmp->prox;
			}
			aux->prox = tmp->prox;
			tmp->prox = aux;
		}
	}
}

void create_list(nodes *list, int num_nodes, float sparsity){
	for (int node = 0; node < num_nodes; node++) {
		for (int node_adjacente = (node + 1); node_adjacente < num_nodes; node_adjacente++) {
			if(create_binary(sparsity) == 1) {
				inserir_aresta(&list[node], node_adjacente);
				inserir_aresta(&list[node_adjacente], node);
			}
		}
	}
}

void exibir_matriz(int tamanhoGrafo, int Matriz[tamanhoGrafo][tamanhoGrafo]) {
	int linha, coluna;
	for (coluna = 0; coluna < tamanhoGrafo; coluna ++) {
		printf("\n");
		for (linha = 0; linha < tamanhoGrafo; linha ++) {
			if (linha == 0) {
				printf("| %d |", Matriz[coluna][linha]);
			} else {
				printf(" %d |", Matriz[coluna][linha]);
			}
		}
	}
}

void exibir_list(nodes *lista, int num_nodes) {
	nodes * tmp;
	for(int index = 0; index < num_nodes; index++) {
		tmp = lista[index].prox;
		printf("%2d: (%d) ->", index, lista[index].vertice);
		while (tmp != NULL) {
			printf("%d  ", tmp->vertice);
			tmp = tmp->prox;
		}
		printf("\n");
	}
}

//Código para as buscas.
void insere_fila(lista_busca *fila, int raiz){
	lista_busca *novo = (lista_busca*) malloc((int)sizeof(lista_busca));
	novo->prox = NULL;
	novo->num = raiz;
	lista_busca *tmp = fila->prox;

	while (tmp->prox != NULL) {
		tmp = tmp->prox;
	}

	tmp->prox = novo;
}

void bfs_busca(nodes list[num_nodes], int num_nodes, int raiz) {
	lista_busca *fila;
	fila = (lista_busca*) malloc((int)sizeof(lista_busca));
	int matriz[num_nodes][2], vertice_selecionado;
	for (int linha = 0; linha < num_nodes; linha++) {
		for (int coluna = 0; coluna < 2; coluna++) {
			matriz[linha][coluna] = 0;
		}
	}
	fila->prox = NULL;
	
	insere_fila(fila, raiz);
	matriz[raiz][1] = 1;  //teg.
	matriz[raiz][2] = -1; //antecessor.

	/*while (!vazia(FILA)) {
		vertice-selecionado = FILA->num;

	}*/
	
}


void busca_grafo_simples(nodes list[num_nodes],int num_nodes) {
	int opcao;
	printf("\n");
	printf("1. exibir o grafo. \n2. para BFS. \n3. para DFS. \n0. para sair.\nDigite uma das opções acima: ");
	scanf("%d", &opcao);
	do {
		if (opcao != 0) {
			if (opcao == 1) {
				exibir_list(list, num_nodes);
			}
			if (opcao == 2) {
				int raiz;
				printf("\n\nGrafo originalmente armazenado.\n\n");
				exibir_list(list, num_nodes);
				printf("Escolha o nó raiz: ");
				scanf("%d", &raiz);
				bfs_busca(list, num_nodes, raiz);
				//BFS
			}
			if (opcao == 3) {
				printf("\n\nGrafo originalmente armazenado.\n\n");
				exibir_list(list, num_nodes);
				//DFS
			}
		}
	} while (opcao == 0);
}





int main() {
	srand((unsigned int)time(NULL));
	int opcao = 0;
	float sparsity;
	do {
		inicio:
		opcao = menu(opcao);
		if (opcao != 0 ) {
			if (opcao == 1) {
				num_nodes = tamanho(num_nodes);
				opcao = tipo_grafo(opcao);
				continua:
				if (opcao == 1) {
					sparsity = 0.7;
					int matrix[num_nodes][num_nodes];
					create_matrix(matrix, num_nodes, sparsity);
					exibir_matriz(num_nodes, matrix);
				}
				if (opcao == 2) {
					sparsity = 0.3;
					for(int i=0; i < num_nodes; i++){
						list[i].vertice = 0;
						list[i].prox = NULL;
					}
					create_list(list, num_nodes, sparsity);
					busca_grafo_simples(list, num_nodes);
				}
				if (opcao == 0) {
					goto inicio;
				}
				else {
					opcao = tipo_grafo(opcao);
					goto continua;
				}
			}
			if (opcao == 2) {
				//Grafos com peso
			}
			else {
				opcao = menu(opcao);
			}
		}
	} while (opcao != 0);

	return 0;
}
