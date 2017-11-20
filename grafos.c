#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAXVALOR 999;

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

void inserir_aresta_peso(nodes *list, int node_adjacente, int peso) {
	nodes *aux;
	nodes *tmp;

	aux = (nodes*) malloc((int)sizeof(nodes));
	aux->vertice = node_adjacente;
	aux->peso = peso;
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

void create_list_peso(nodes *list, int num_nodes, float sparsity) {
	int peso;
	for (int node = 0; node < num_nodes; node++) {
		for (int node_adjacente = (node + 1); node_adjacente < num_nodes; node_adjacente++) {
			if(create_binary(sparsity) == 1) {
				peso = rand() % 200;
				inserir_aresta_peso(&list[node], node_adjacente, peso);
				inserir_aresta_peso(&list[node_adjacente], node, peso);
			}
		}
	}
}

void exibir_list_peso(nodes *lista, int num_nodes) {
	nodes * tmp;
	for(int index = 0; index < num_nodes; index++) {
		tmp = lista[index].prox;
		printf("%2d: (%d) -> ", index, lista[index].vertice);
		while (tmp != NULL) {
			printf("%d  ", tmp->vertice);
			printf("Peso: %d  -> ", tmp->peso);
			tmp = tmp->prox;
		}
		printf("\n");
	}
}

void dantzig_busca(nodes *lista, int num_nodes, int raiz) {
	int matriz[num_nodes][3];
	int aux[num_nodes][num_nodes];
	nodes *tmp;
	nodes *tmp2;

	for (int linha = 0; linha < num_nodes; linha++) {
		for (int coluna = 0; coluna < num_nodes; coluna++) {
			aux[linha][coluna] = MAXVALOR;
		}
	}
	
	for (int linha = 0; linha < num_nodes; linha++) {
		for (int coluna = 0; coluna < 3; coluna++) {
			matriz[linha][coluna] = 0;
		}
		matriz[linha][1] = MAXVALOR; //valor de infinito.
	}
	
	matriz[raiz][2] = -1;  //insere o antecessor.
	matriz[raiz][1] = 0;  //insere custo zero na raiz.
	matriz[raiz][0] = 1; //insere a tag de fechado.  
	
	for (int index = 0; index < num_nodes; index++) {
		
		tmp = &(lista[raiz]);
		tmp2 = &(lista[raiz]);
		
		tmp2 = tmp2->prox;
		
		while (tmp2 != NULL) {
			aux[index][tmp2->vertice] = tmp2->peso;
			tmp2 = tmp2->prox;
		}
		
		
		
		tmp = tmp->prox;
		while (tmp != NULL) {
			if (matriz[tmp->vertice][0] == 0 && matriz[raiz][0] == 1) {
				if (matriz[raiz][1] + tmp->peso < matriz[tmp->vertice][1]) {
					matriz[tmp->vertice][1] = matriz[raiz][1] + tmp->peso;
					matriz[tmp->vertice][2] = raiz;
				}
			}
			tmp = tmp->prox;
		}
		
		
		
		
		int menor = MAXVALOR;
		for (int linha = 0; linha < index+1; linha++) {
			for (int coluna = 0; coluna < num_nodes; coluna++) {
				if (menor > aux[linha][coluna] && matriz[coluna][0] == 0) {
					menor = aux[linha][coluna];
					raiz = coluna;
				}
			}
		}
		matriz[raiz][0] = 1;
		
	}
	
	for (int linha = 0; linha < num_nodes; linha++) {
		if (linha == 0) {
			printf("|Vertice | Antecessor | Custo|\n");
		}
		printf("|   %d   |     %d     |  %d  |\n", linha, matriz[linha][2], matriz[linha][1]); 
	}
	
}

void disjkstra_busca(nodes *lista, int num_nodes, int raiz) {
	int matriz[num_nodes][3];
	nodes *tmp;
	
	for (int linha = 0; linha < num_nodes; linha++) {
		for (int coluna = 0; coluna < 3; coluna++) {
			matriz[linha][coluna] = 0;
		}
		matriz[linha][1] = MAXVALOR; //valor de infinito.
	}
	
	matriz[raiz][2] = -1;  //insere o antecessor.
	matriz[raiz][1] = 0;  //insere custo zero na raiz.
	matriz[raiz][0] = 1; //insere a tag de fechado.  
	
	for (int index = 0; index < num_nodes; index++) {
		
		tmp = &(lista[raiz]);	
		
		tmp = tmp->prox;
		while (tmp != NULL) {
			if (matriz[tmp->vertice][0] == 0 && matriz[raiz][0] == 1) {
				if (matriz[raiz][1] + tmp->peso < matriz[tmp->vertice][1]) {
					matriz[tmp->vertice][1] = matriz[raiz][1] + tmp->peso;
					matriz[tmp->vertice][2] = raiz;
				}
			}
			tmp = tmp->prox;
		}
		
		
		
		
		int menor = MAXVALOR;
		for (int linha = 0; linha < num_nodes; linha++) {
			if (menor > matriz[linha][1] && matriz[linha][0] == 0) {
				menor = matriz[linha][1];
				raiz = linha;
			}
		}
		matriz[raiz][0] = 1;
		
	}
	
	for (int linha = 0; linha < num_nodes; linha++) {
		if (linha == 0) {
			printf("|Vertice | Antecessor | Custo|\n");
		}
		printf("|   %d   |     %d     |  %d  |\n", linha, matriz[linha][2], matriz[linha][1]); 
	}
	
}

void busca_grafo_peso(nodes *list,int num_nodes) {
	int opcao, raiz;;
	printf("\n");
	printf("1. exibir o grafo. \n2. para DANTZIG. \n3. para DIJKSTRA NORMAL. \n4. para DIJKSTRA HEAP. \n5. para PRIM. \n6. para KRUSKAL\n0. para sair.\nDigite uma das opções acima: ");
	scanf("%d", &opcao);
	do {
		if (opcao != 0) {
			if (opcao == 1) {
				exibir_list_peso(list, num_nodes);
			}
			if (opcao == 2) {
				printf("\n\nGrafo originalmente armazenado.\n\n");
				exibir_list_peso(list, num_nodes);
				printf("Escolha o nó raiz: ");
				scanf("%d", &raiz);
				dantzig_busca(list, num_nodes, raiz);
				//Dantzig
			}
			if (opcao == 3) {
				printf("\n\nGrafo originalmente armazenado.\n\n");
				exibir_list_peso(list, num_nodes);
				printf("Escolha o nó raiz: ");
				scanf("%d", &raiz);
				disjkstra_busca(list, num_nodes, raiz);
				//disjkstra normal
			}
			if (opcao == 4) {
				printf("\n\nGrafo originalmente armazenado.\n\n");
				exibir_list_peso(list, num_nodes);
				printf("Escolha o nó raiz: ");
				scanf("%d", &raiz);
				//disjkstra heap
			}
			if (opcao == 5) {
				printf("\n\nGrafo originalmente armazenado.\n\n");
				exibir_list_peso(list, num_nodes);
				printf("Escolha o nó raiz: ");
				scanf("%d", &raiz);
				//PRIM
			}
			if (opcao == 6) {
				printf("\n\nGrafo originalmente armazenado.\n\n");
				exibir_list_peso(list, num_nodes);
				printf("Escolha o nó raiz: ");
				scanf("%d", &raiz);
				//KRUSKAL
			}
		}
	} while (opcao == 0);
}

//Código para as buscas.
void insere_fila(lista_busca **fila, int raiz) {
	lista_busca *novo = (lista_busca*) malloc((int)sizeof(lista_busca));
	novo->prox = NULL;
	novo->num = raiz;
	lista_busca *tmp = (*fila);

	if (*fila == NULL){
		*fila = novo;
	} else {
		while (tmp->prox != NULL) tmp = tmp->prox;
		
		tmp->prox = novo;
	}

}

void retira_node(lista_busca **fila) {
    lista_busca *tmp;
    tmp = *fila;
    
    *fila = (*fila)->prox;
    
    free(tmp);
}

void mostra (lista_busca *fila){
	if (fila!=NULL){
		while (fila!=NULL){
			printf ("%d\t",fila->num);
			fila = fila->prox;
		}
	} else printf ("VAZIO");
	
	printf ("\n\n");
	
}

void bfs_busca(nodes *lista, int num_nodes, int raiz) {
	lista_busca *fila;
	nodes *aux;
	fila = NULL;
	int matriz[num_nodes][2], vertice_selecionado;
	for (int linha = 0; linha < num_nodes; linha++) {
		for (int coluna = 0; coluna < 2; coluna++) {
			matriz[linha][coluna] = 0;
		}
	}

	insere_fila(&fila, raiz);
	matriz[raiz][0] = 1;  //teg.
	matriz[raiz][1] = -1; //antecessor.

	while (fila != NULL) {
        vertice_selecionado = fila->num;
        retira_node(&fila);
        aux = lista[vertice_selecionado].prox;
        while (aux != NULL) {
            int temp = aux->vertice;
            if(matriz[temp][0] == 0) {
                insere_fila(&fila, temp);
                matriz[temp][0] = 1;  //teg.
                matriz[temp][1] = vertice_selecionado; //antecessor.
            }
            
            aux = aux->prox;
        }
        //mostra(fila);
	}

	printf("\n\n Árvore gerada.\n\n");
	for (int linha = 0; linha < num_nodes; linha++) {
        printf("Vertice: %d - antecessor: %d\n", linha, matriz[linha][1]);
    }

}

//DFS
void dfs_recursivo(nodes *lista, int raiz, int matriz[num_nodes][2]) {
	nodes *tmp;
	tmp = &lista[raiz];
	int aux;
	matriz[raiz][0] = 1;
	tmp = tmp->prox;
	while (tmp != NULL) {
		printf("passou aqui");
		if (matriz[tmp->vertice][0] == 0) {
			
			aux = tmp->vertice;
			matriz[aux][1] = raiz;
			matriz[aux][0] = 1;
			dfs_recursivo(lista, tmp->vertice, matriz);
			
		}
		tmp = tmp->prox;
	}
}

void dfs_busca(nodes *lista, int raiz, int num_nodes) {
	int matriz[num_nodes][2];
	for (int linha = 0; linha < num_nodes; linha++) {
		for (int coluna = 0; coluna < 2; coluna++) {
			matriz[linha][coluna] = 0;
		}
	}
	matriz[raiz][1] = -1;
	dfs_recursivo(lista, raiz, matriz);

	printf("\n\n Árvore gerada.\n\n");
	for (int linha = 0; linha < num_nodes; linha++) {
        printf("Vertice: %d - antecessor: %d\n", linha, matriz[linha][1]);
    }
}


void busca_grafo_simples(nodes *list,int num_nodes) {
	int opcao, raiz;;
	printf("\n");
	printf("1. exibir o grafo. \n2. para BFS. \n3. para DFS. \n0. para sair.\nDigite uma das opções acima: ");
	scanf("%d", &opcao);
	do {
		if (opcao != 0) {
			if (opcao == 1) {
				exibir_list(list, num_nodes);
			}
			if (opcao == 2) {
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
				printf("Escolha o nó raiz: ");
				scanf("%d", &raiz);
				dfs_busca(list, raiz, num_nodes);
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
					sparsity = 0.5;
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
				num_nodes = tamanho(num_nodes);
				sparsity = 0.5;
				for(int i=0; i < num_nodes; i++){
					list[i].vertice = 0;
					list[i].prox = NULL;
				}
				create_list_peso(list, num_nodes, sparsity);
				busca_grafo_peso(list, num_nodes);
			}
			else {
				opcao = menu(opcao);
			}
		}
	} while (opcao != 0);

	return 0;
}
