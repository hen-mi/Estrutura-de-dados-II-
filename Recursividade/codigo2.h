#ifndef _CODIGODOIS_H_
#define _CODIGODOIS_H_

#include <stdio.h>

double fatorial(int numero);
int imprimeFat(void);

double fatorial(int numero) {
  double resultado = 1;

      while(numero > 1) {
        resultado *= numero;
        numero--;    
      }

  return resultado;
}

int imprimeFat(void) {
	printf("==== FATORIAL ====\n\n");

	int i;
	for (i = 0; i <= 10; i++) {
		printf("%d! => %lf\n", i, fatorial(i));
	}

	printf("\n\n");
	return 0;
}
#endif