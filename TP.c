//Paulo Gabriel Marques Jardim
//Cientista de Computação
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "minhabiblioteca.h"

int main(){
  
  char c[40]; //para receber a opção do menu
  char confirm[40]; //para receber se ele quer sair ou não do programa
  int **mat;
  int n; // tamannho das linhas da matriz para poder liberar memoria
  int parada; //condição para finalizar o loop + externo
  Loop teste[4]; //variáveis que vão condicionar os próximos do-while
  Jogo cadastro; //registrar cadastro em novo jogo
  int validacao =0; //o usuario nao pode salvar um jogo sem ter entrado antes em um novo jogo ou jogo salvo
  do{
    parada =1; //começa setada para 1
    menu();
        
        //parte estética do MENU está acima
        
    fgets(c, 40, stdin);
    trataN(c); //trata o \n do buffer
    printf("\n");
    minuscula(c);
    if(tiraEspaco(c)){         //trata os espaços no começo e fim e texto vazio
      printf(BG_RED(WHITE("Voce digitou espaços indevidamente"))); 
      printf("\n\n");
    }
    else if(strcmp("a", c) && strcmp("m", c) && strcmp("s", c) && strcmp("c", c) && strcmp("j", c) && strcmp("n", c) && 
    strcmp("r", c)){
      printf(RED("Comando não reconhecido!!\n\n")); //se não for nenhuma das letras, volta pro loop, pois la no começo 
    }                                                 //da main a variável 'parada' ta setada pra 1
    else if(!strcmp("r", c)){
      parada = desejaSair(confirm, teste);
    }
    else if(!strcmp("n", c)){
            //parte real do jogo
      do{
        teste[1].parar =0;
        printf(WHITE("Qual seu nome de usuário? "));
        fgets(cadastro.user, 27, stdin);
        printf("\n");
        trataN(cadastro.user);
        if(tiraEspaco(cadastro.user)){
          printf(RED("Você digitou espaços indevidamente!!"));
          printf("\n\n");
          teste[1].parar =1;
        }
        else{
          printf(WHITE("Qual modo de jogo você deseja jogar (4x4), (5x5), (6x6): "));
          fgets(cadastro.modo, 41, stdin);
          printf("\n");
          trataN(cadastro.modo);
          minuscula(cadastro.modo);
          if(tiraEspaco(cadastro.modo)){
            printf(RED("Você digitou espaços indevidamente!!"));
            printf("\n\n");
            teste[1].parar =1;
          }
          int tam;
          if(strcmp("4x4", cadastro.modo) == 0) {
            tam = 4;
            n = tam;
          }
          else if (strcmp("5x5", cadastro.modo) == 0) {
            tam = 5;
            n = tam;
          } 
          else if (strcmp("6x6", cadastro.modo) == 0) {
            tam = 6;
            n = tam;
          }
          else
            tam = 8; //numero aleatorio pra dar erro
          
          int resultado = tabuleiro(tam, cadastro.user, &mat, 1);
          if(resultado == 0){
            printf(BG_RED("Falha de alocação de memoria na execução do programa !!"));
            printf("\n");
          }
          else if(resultado == 2){
            printf(BG_RED("COMANDO INVÁLIDO!!"));
            printf("\n");
          }
          else if(resultado == 3){
            printf(BG_RED("FALHA NA CRIAÇÃO DE ARQUIVOS DE SALVAMENTO DO JOGO!"));
            printf("\n");
          }
          else{
            liberaMatriz(&mat, n);
            validacao =1;
          }
        }
      }while(teste[1].parar == 1);
    }
    else if(!strcmp("j", c)){
      continuarJogo(&validacao, &mat, &n, cadastro.user);
    }
    else if(!strcmp("c", c)){
      do{
        teste[3].parar =0;
        printf(WHITE("Digite o nome do arquivo: "));
        char nomeArq[41];
        fgets(nomeArq, 41, stdin);
        trataN(nomeArq);
        int tam = strlen(nomeArq);
        
        for(int i = (tam-1); i>=0; i--){
          if(nomeArq[i] != ' '){                        //aqui ele procura o ultimo caracter e já finaliza a palavra ali
            nomeArq[i+1]=0;                                     //ou seja tira todos os espaços do final
            break;
          }           
        }
        
        tam = strlen(nomeArq);
        if(tam<=4){
          printf(RED("O nome do arquivo tem que ser no estilo nome.txt!\n"));
          teste[3].parar =1;
        }
        else{
          if(nomeArq[tam-4] == '.' && nomeArq[tam-3] == 't' && nomeArq[tam-2] == 'x' && nomeArq[tam-1] == 't'){
            FILE *entrada =NULL;
            FILE *saida=NULL;
            entrada = fopen(nomeArq, "r");
            saida = fopen("salvamento.txt", "w");
            if(saida ==NULL){
              printf(RED("Não conseguimos acessar um arquivo do jogo\n"));
              teste[3].parar =1;
            }
            if(entrada ==NULL){
              printf(RED("Não conseguimos acessar o arquivo que voce salvou!\n"));
              teste[3].parar =1;
            }
            if(entrada != NULL && saida != NULL){
              char carac;
              while ((carac = fgetc(entrada)) != EOF) {
                fputc(carac, saida);
              }
              fseek(entrada, 0, SEEK_SET);
              
              fscanf(entrada, "%d", &tam);
              
              fclose(saida);
              fclose(entrada);
              
              int resultado = tabuleiro(tam, cadastro.user, &mat, 2);
              //passei apenas um vetor para o nome qualquer pois ela vai ser lido la
              if(resultado == 0){
                printf(BG_RED("Falha de alocação de memoria na execução do programa !!"));
                printf("\n");
              }
              else if(resultado == 3){
                printf(BG_RED("FALHA NA CRIAÇÃO DE ARQUIVOS DE SALVAMENTO DO JOGO!"));
                printf("\n");
              }
              else{
                n = tam;
                liberaMatriz(&mat, n);
                validacao =1;
              }
            }
          }
          else{
                teste[3].parar =1;
                printf(RED("a terminação do arquivo deve ser '.txt'\n"));
          }
        }
      }while(teste[3].parar);
    }
    else if(!strcmp("s", c)){
      salvarJogo(validacao, teste);
    }
    else if(!strcmp("m", c)){
      gerarRanking();
    }
    else if(!strcmp("a", c)){   
      ajuda(); //função para listar as regras pro usuário
    }
  }while(parada);
  printf("\n");
  return 0;
}
