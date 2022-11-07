#ifndef _CODIGOTRES_H_
#define _CODIGOTRES_H_

#include <malloc.h>
#include <stdio.h>

typedef struct node {
	int valor;
	struct node *prox;
} NODE;

NODE* inserirProx(NODE *inicio, int valor);
int iniciaLista(void);
void imprimeLista(NODE *inicio);

NODE* inserirProx(NODE *inicio, int valor) {
	NODE *aux = inicio;

	if(aux->prox == NULL) {
    
  		NODE *novo = (NODE *)malloc(sizeof(NODE));
		novo->valor = valor;
		novo->prox = NULL;
		aux->prox = novo;
    
  		return novo;
    
	}else{
    
    	inserirProx(aux->prox, valor);    
  	}
  
  return aux;
}

void imprimeLista(NODE *inicio) {
	NODE *aux = inicio;
  
	if(aux != NULL){
		printf("[ %d ] -> ", aux->valor);
		aux = aux->prox;
    	imprimeLista(aux); 
	}

}


int iniciaLista(void) {
	printf("==== LISTA ENCADEADA ====\n\n");

	NODE inicio;
	inicio.valor = 0;
	inicio.prox = NULL;

	int i;
	for (i = 1; i < 11; i++) {
		inserirProx(&inicio, i);
	}

	imprimeLista(&inicio);

	printf("\n");
	return 0;
}
#endif