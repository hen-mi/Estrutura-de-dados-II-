#include <malloc.h>
#include <stdio.h>

typedef struct No {
  int valor;
  struct No *noDir;
  struct No *noEsq;
  int altura;
} NO;
int getAltura(NO* raiz){
  if(raiz == NULL)
    return 0;
  return raiz->altura;
}

int maior(int x, int y){
  
  return (x > y) ? x : y;
  
}

int getBalanceamento(NO* raiz){
  if(raiz == NULL)
    return 0;
  return getAltura(raiz->noEsq) - getAltura(raiz->noDir);
}

NO *procurarComPai(NO *raiz, int value, NO **paiAtual) {
  NO *atual = raiz;
  *paiAtual = NULL;

  while (atual != NULL) {
    if (atual->valor == value)
      return atual;

    *paiAtual = atual;
    if (value > atual->valor)
      atual = atual->noDir;
    else
      atual = atual->noEsq;
  }

  return NULL;
}

// Se o no for filho da direita do pai, retorna 1
int isFilhoDireita(NO *no, NO *pai) {
  if (pai != NULL)
    return no->valor > pai->valor ? 1 : 0;

  return 0;
}

// Se o no for filho da esquerda do pai, retorna 1
int isFilhoEsquerda(NO *no, NO *pai) {
  if (pai != NULL)
    return no->valor < pai->valor ? 1 : 0;

  return 0;
}

NO *deleteNoChild(NO *node, NO *father, NO *root) {
  free(node);

  if (father != NULL) {
    if (isFilhoDireita(node, father) == 1)
      father->noDir = NULL;
    else if (isFilhoEsquerda(node, father) == 1)
      father->noEsq = NULL;

    return root;
  }

  return NULL;
}

NO *deleteOneChildDir(NO *node, NO *father, NO *root) {
  if (father != NULL) {
    if (isFilhoDireita(node, father) == 1)
      father->noDir = node->noDir;
    else if (isFilhoEsquerda(node, father) == 1)
      father->noEsq = node->noDir;

    free(node);
    return root;
  }

  NO *returnValue = node->noDir;
  free(node);

  return returnValue;
}

NO *deleteOneChildEsq(NO *node, NO *father, NO *root) {
  if (father != NULL) {
    if (isFilhoDireita(node, father) == 1)
      father->noDir = node->noEsq;
    else if (isFilhoEsquerda(node, father) == 1)
      father->noEsq = node->noEsq;

    free(node);
    return root;
  }

  NO *returnValue = node->noEsq;
  free(node);

  return returnValue;
}

NO *deleteTwoChild(NO *node, NO *father, NO *root) {
  // Pegar o elemento mais a direita dos filhos a esquerda
  NO *fatherPromoted = node;
  NO *promoted = node->noEsq;

  while (promoted->noDir != NULL) {
    fatherPromoted = promoted;
    promoted = promoted->noDir;
  }

  if (fatherPromoted != node) {
    fatherPromoted->noDir = promoted->noEsq;
    promoted->noEsq = node->noEsq;
  }

  promoted->noDir = node->noDir;

  if (father != NULL) {
    if (isFilhoDireita(node, father) == 1)
      father->noDir = promoted;
    else if (isFilhoEsquerda(node, father) == 1)
      father->noEsq = promoted;

    free(node);

    return root;
  }

  free(node);
  return promoted;
}

NO *removerNo(NO *root, int value) {
  NO *curr, *father;

  if (root == NULL)
    return NULL;
  curr = procurarComPai(root, value, &father);

  // 0 FILHOS
  if (curr->noDir == NULL && curr->noEsq == NULL) {
    return deleteNoChild(curr, father, root);
  }

  // 1 FILHO
  if (curr->noDir != NULL && curr->noEsq == NULL) { // FILHO A DIREITA
    return deleteOneChildDir(curr, father, root);
  }

  if (curr->noEsq != NULL && curr->noDir == NULL) { // FILHO A ESQUERDA
    return deleteOneChildEsq(curr, father, root);
  }

  // 2 FILHOS
  return deleteTwoChild(curr, father, root);
}

NO *rotacaoEsquerda(NO *raiz){
  //LL
  NO* aux = raiz->noDir;
  NO* aux2 = aux->noEsq;

  aux->noEsq = raiz;
  raiz->noDir = aux2;
  
  raiz->altura = maior(getAltura(raiz->noEsq), getAltura(raiz->noDir)) + 1;
  aux->altura = maior(getAltura(raiz->noEsq), getAltura(raiz->noDir)) + 1;
  
  return aux;
  
}


NO *rotacaoDireita(NO *raiz){
  //RR
  NO* aux = raiz->noEsq;
  NO* aux2 = aux->noDir;

  aux->noDir = raiz;
  raiz->noEsq = aux2;
  
  raiz->altura = 1 + maior(getAltura(raiz->noEsq), getAltura(raiz->noDir));
  aux->altura = 1 + maior(getAltura(raiz->noEsq), getAltura(raiz->noDir));
  
  return aux;
}

NO *rotacaoDuplaEsquerda(NO *raiz){
  //RL
  raiz->noDir = rotacaoDireita(raiz->noDir);
  return rotacaoEsquerda(raiz);
}

NO *rotacaoDuplaDireita(NO *raiz){
  //LR
  raiz->noEsq = rotacaoEsquerda(raiz->noEsq);
  return rotacaoDireita(raiz);
  
}

NO *inserirNo(NO *raiz, NO *filho) {
  printf("\n\n================================\n");
  printf("INICIANDO FUNCAO\n");
  printf("NO FILHO: %d\n", filho->valor);

  if (raiz != NULL) {
    printf("RAIZ: %d\n", raiz->valor);
  } else {
    printf("MINHA RAIZ E NULA\n");
  }

  if (raiz == NULL) {
    printf("\nENTRANDO NA CONDICAO DE PARADA\n");
    printf("NO: %d\n\n", filho->valor);
    printf("FINALIZANDO FUNCAO\n");
    return filho;
  }

  if (filho->valor > raiz->valor) {
    printf("\nFILHO MAIOR QUE RAIZ\n");
    printf("NO: %d\n", filho->valor);
    printf("RAIZ: %d\n\n", raiz->valor);
    raiz->noDir = inserirNo(raiz->noDir, filho);

    printf("\nNO %d INSERIDO NA DIREITA\n", raiz->valor);
  } else {
    printf("\nFILHO MENOR QUE RAIZ\n");
    printf("NO: %d\n", filho->valor);
    printf("RAIZ: %d\n", raiz->valor);
    raiz->noEsq = inserirNo(raiz->noEsq, filho);
    
    printf("\nNO %d INSERIDO NA ESQUERDA\n", raiz->valor);
  }
    //att de altura
    raiz->altura = 1 + maior(getAltura(raiz->noEsq), getAltura(raiz->noDir));
    // verificação de balanço
    int balanceamento = getBalanceamento(raiz);
  
    //pesando para direita

    if(balanceamento < -1){
      if(getBalanceamento(raiz->noDir) <= 0){
        return rotacaoEsquerda(raiz);
      } else{
          return rotacaoDuplaEsquerda(raiz);  //RL

        }
    }

    //pesando para esquerda
  
  else if(balanceamento > 1) {
      if(getBalanceamento(raiz->noEsq) >= 0){
         return rotacaoDireita(raiz); 
      } else{
        return rotacaoDuplaDireita(raiz); // LF

      }
    }

  printf("\nFINALIZANDO FUNCAO\n");
  printf("NO: %d\n", filho->valor);
  printf("RAIZ: %d\n", raiz->valor);
  printf("ALTURA RAIZ: %d\n", raiz->altura);
  return raiz;
}

void imprimir(NO *raiz) {
  if (raiz != NULL) {
    printf("%d", raiz->valor);
    printf("(");
    imprimir(raiz->noEsq);
    imprimir(raiz->noDir);
    printf(")");
  }
}

int main(void) {
  NO *raiz = NULL;
  
  int i;
  for (i = 0; i < 3; i++) {
    int valorDigitado;
    printf("DIGITE UM VALOR\n");
    scanf("%d", &valorDigitado);

    NO *pFilho = (NO *)malloc(sizeof(NO));
    pFilho->valor = valorDigitado;
    pFilho->noEsq = NULL;
    pFilho->noDir = NULL;
    pFilho->altura = 1;
    raiz = inserirNo(raiz, pFilho);

  }

  imprimir(raiz);
  printf("\n");
  //funciona apenas para 3 valores
  printf("        %d\n", raiz->valor);
  printf("       / \\\n");
  printf("      /   \\\n");
  printf("     %d      %d\n", raiz->noEsq->valor, raiz->noDir->valor);
  return 0;
}