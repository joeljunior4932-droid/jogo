#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void limpar_buffer(){
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}
void libera_matriz(int ***mat, int n, int m){
  for(int i =0; i<n;i++){
    free((*mat)[i]);
  }
  free(mat);
}
void implementa_matriz(int ***sec, int p, int q){
  sec =malloc(p*sizeof(int*));
  for(int i =0; i<p;i++){
    (*mat)[i]= malloc(q*sizeof(int));
  }
}

int main(){
  int n, m;
  printf("digite o numero de linhas da matriz: ");
  scanf("%d", &n);
  printf("digite o numero de colunas da matriz: ");
  scanf("%d", &m);
  int **mat;
  int **sec;
  mat =malloc(n*sizeof(int*));
  for(int i =0; i<n;i++){
    mat[i]= malloc(m*sizeof(int));
  }
  printf("Digite os elementos da matriz: ");
  for(int i =0; i< n; i++){
    for(int j =0; j< m; j++){
      scanf("%d", &mat[i][j]);
    }
  }
  char parada;
  int opcao;
  do{
    do{
      printf("Digite sua ação: ");
      printf("(1): Inserir linha ou coluna\n");
      printf("(2): Remover linha ou coluna\n");
      printf("(3): Trocar linha ou coluna\n");
      scanf("%d", &opcao);
      if(opcao == 1){
        do{
          char opcao2;
          printf("Qual vai querer inserir linha(l) ou coluna(c): ");
          scanf("%c", &opcao2);
          if(opcao2 == 'l'){
            implementa_matriz(&sec, (n+1), m);
            printf("em qual posição vai querer implementar a linha");
            int opcao3;
            scanf("%d", &opcao3);
            if(opcao3 <0 || opcao3>n)
              printf("invalido!!");
            else{
              for(int i =0; i<opcao3; i++){
                for(int j =0; j<opcao3; j++){
                sec[i][j] = mat[i][j];
                }
              }
              if(opcao3 != n){
                for(int i = opcao3; i<(n+1); i++){
                  for(int j = 0; j<m; j++){
                    sec[i+1][j] = mat[i][j];
                  }
    
                }
              }
              printf("Digite os %d valores dessa linha: ");
              for(int j =0; j<m;j++){
                scanf("%d", &sec[opcao3][j]);
              }
              libera_matriz(&mat, n, m);
              printf("A nova matriz eh: \n");
              for(int i =0; i< (n+1); i++){
                for(int j =0; j< m; j++){
                  printf("%d ", sec[i][j]);
                }
                printf("\n");
              }
              libera_matriz(&sec, n+1, m);
            }
          }
          else if(opcao2 =='c'){
          
          }
          else
            printf("opção não válida!!");
        }while(opcao2 <1 || opcao2 >2);
        
      }
    }while(opcao <1 || opcao >3);
    
    printf("Quer continuar? (s)/(n): ");
    scanf("%c", &parada);
    printf("\n");
  }while(parada == 'n');

  return 0;
}
