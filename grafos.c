#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int num_nodes = 0;

typedef struct no { 
	int vertice;
	struct no *prox;
} nodes;

typedef nodes *ponteiro;

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
	srand((unsigned int)time(NULL));
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

void create_list(ponteiro list[num_nodes], int num_nodes, float sparsity){
	for (int node = 0; node < num_nodes; node++) {
		for (int node_adjacente = node + 1; node_adjacente < num_nodes; node_adjacente++) {
			if(create_binary(sparsity) == 1) {
				ponteiro aux;
				aux = (nodes *) malloc(sizeof(nodes));
				aux->vertice = node_adjacente;
				aux->prox = NULL;
				list[node]->prox = aux;
				
				aux->vertice = node;
				aux->prox = NULL;
				list[node_adjacente]->prox = aux;
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

void exibir_list(ponteiro *aux) {
	
	
	
	while (aux->prox != NULL) {
		printf(" -> %d",aux->prox->vertice);
	}
}


void busca_grafo_simples(ponteiro list[num_nodes],int num_nodes,float sparsity) {
	int opcao;
	printf("\n");
	printf("1. exibir o grafo. \n2. para BFS. \n3. para DFS. \n0. para sair.\nDigite uma das opções acima: ");
	scanf("%d", &opcao);
	do {
		if (opcao != 0) {
			if (opcao == 1) {
				
				for(int index = 0; index <num_nodes; index++) {
					printf("\n");
					printf("%d :", index);
					exibir_list(&list[index]);
				}
				//exibir grafo
				busca_grafo_simples(list, num_nodes, sparsity);
			}
			if (opcao == 2) {
				//BFS
				busca_grafo_simples(list, num_nodes, sparsity);
			}
			if (opcao == 3) {
				//DFS
				busca_grafo_simples(list, num_nodes, sparsity);
			}
			else {
				busca_grafo_simples(list, num_nodes, sparsity);
			}
		}
	} while (opcao != 0);
}

int main() {
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
					ponteiro list[num_nodes];
					list[0] = (nodes *) malloc(sizeof(nodes));
					list[0]->vertice = 0;
					list[0]->prox = NULL;
					create_list(list, num_nodes, sparsity);
					busca_grafo_simples(list, num_nodes, sparsity);
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
