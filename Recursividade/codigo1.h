#ifndef _CODIGOUM_H_
#define _CODIGOUM_H_

#include <stdio.h>
int multiplicacaoPorSoma(int numero, int vezes);
int imprimeMultipl(void);

int multiplicacaoPorSoma(int numero, int vezes) {

  if(vezes >= 1) {

    
    return (numero + multiplicacaoPorSoma(numero, vezes - 1));
    
  }
  
  return 0;
}
int imprimeMultipl(void) {
	printf("==== MULTIPLICACAO POR SOMA ====\n\n");

	int i;
	for (i = 0; i <= 10; i++) {
		printf("5 * %d => %d\n", i, multiplicacaoPorSoma(5, i));
	}

	printf("\n\n");
	return 0;
}
#endif