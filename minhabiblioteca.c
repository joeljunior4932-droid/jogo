//Paulo Gabriel Marques Jardim
//25.1.4011
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "minhabiblioteca.h"
int converterCINT(char c){
  int n;
  switch(c){
    case 'a':
      n = 0;
      break;
    case 'b':
      n = 1;
      break;
    case 'c':
      n = 2;
      break;
    case 'd':
      n = 3;
      break;
    case 'e':
      n =4;
      break;
    case 'f':
      n=5;
      break;
    case '1':
      n = 0;
      break;
    case '2':
      n = 1;
      break;
    case '3':
      n = 2;
      break;
    case '4':
      n = 3;
      break;
    case '5':
      n=4;
      break;
    case '6':
      n=5;
      break;
    
  }
  return n;

}

int alocaMatriz(int ***matriz, int tam){
  *matriz = NULL; //vetor auxilia na comparação da matriz
  *matriz = malloc(tam*sizeof(int*));
  if(*matriz == NULL)
    return 0;
  
  for(int i =0; i<tam; i++){
    (*matriz)[i] = NULL;
    (*matriz)[i] = malloc(tam*sizeof(int));
    if((*matriz)[i] == NULL){
      if(i>=0){
        for(int k =i-1; k>=0;k--)
          free((*matriz)[k]);
        free((*matriz));
      }
      return 0;
    }
  }
  return 1;

}

void liberaMatriz(int ***matriz, int tam){

  for(int i =0; i<tam; i++){
      free((*matriz)[i]);
  }
  free(*matriz);
}


void imprimirTab(int ***mat, int tam, int tamDinamico, int aux, int nPontuacao, int nDesfazer, int nTrocar){
  printf(" "); 
  for (int i = 1; i <= tam; i++) { // imprime a parte do índice das colunas do tabuleiro
        
    printf(" %*d ", tamDinamico-1, i);  //esse * é pra indicar uma quantidade que pode variar de espaçamento
  }
  printf("\n");
    
  printf(" " TAB_TL);
  for (int i = 1; i < tam; i++) {
    for(int j = 0; j< tamDinamico; j++){
      printf(TAB_HOR);
    }
    printf(TAB_TJ);                                     // imprime a parte de cima do tabuleiro
  }
  for(int j = 0; j< tamDinamico; j++){
    printf(TAB_HOR);
  }
  printf(TAB_TR "   Pontos: %d\n", nPontuacao); // último bloquinho da parte de cima do tabuleiro
    
  int contador = 0; // para aumentar o indice das linhas 
  for (int i = 0; i < (7 + aux); i++) { // impressão vertical
    if (i % 2 == 0) {          //se a linha for par imprime assim
      printf("%c", 'a' + contador);
      for (int j = 0; j < tam; j++) { // impressão horizontal
        int achouCor =0;
        if ((*mat)[contador][j] != 0) {
          printf(TAB_VER);
          int p = 40;
          for(int k =2; k<=65536; k = k*2){       //para mudança das cores para cada bloquinho que tenha valor superior
            if((*mat)[contador][j] ==k){
              printf("\x1b[%dm%*d \x1b[0m", p, tamDinamico-1, (*mat)[contador][j]);
              achouCor =1;
            }
            else
              p++;
            
            if(p==48)
              p = 100;
              
          }
          if(achouCor ==0)
            printf("\x1b[107m%*d \x1b[0m", tamDinamico-1, (*mat)[contador][j]);
        } 
        else {
          printf(TAB_VER);
          for(int k=0; k<tamDinamico; k++){           //se for igual a zero imprime espaços
            printf(" ");
          }
        }
      }
      printf(TAB_VER "\n");
      contador++;
    } 
    else {  // se for uma linha impar imprime assim
      printf(" " TAB_ML);
      for (int j = 1; j < tam; j++) {
      
        for(int k=0; k<tamDinamico; k++){
          printf(TAB_HOR);
        }
        printf(TAB_MJ); // linhas ímpares
      } 
      for(int k=0; k<tamDinamico; k++){
        printf(TAB_HOR);
      }
      printf(TAB_MR "\n");
      
    }
    
  }
    
  printf(" " TAB_BL);
  for (int i = 1; i < tam; i++) {
    for(int k=0; k<tamDinamico; k++){
      printf(TAB_HOR);
    }
    printf(TAB_BJ);                           // parte de baixo
  }
  for(int k=0; k<tamDinamico; k++){
    printf(TAB_HOR);
  }
  printf(TAB_BR "    Cartas Desfazer: %d\n", nDesfazer);
  printf("  ");
  for (int i = 1; i < tam; i++) {
    for(int k=0; k<tamDinamico; k++){
      printf(" ");
    }
    printf(" ");
  }
  for(int k=0; k<tamDinamico; k++){
      printf(" ");
  }
  printf("     Cartas Trocar: %d\n", nTrocar);
}
int maiorValor(int **matriz, int tam){
  int maior = matriz[0][0];
  for(int i =0; i<tam; i++){
    for(int j =0; j<tam; j++){
      if(matriz[i][j] > maior){
        maior = matriz[i][j];
      }
    }
  }
  return maior;

}
int calcDigitos(int digito){
  int contador=0;      
  while(digito>0){
    contador++;
    digito = digito/10;
  }
  return contador;
  
}

void minuscula(char nome[]){
  int tam = strlen(nome);
  for(int i =0; i<tam; i++){
    if(nome[i] >= 'A' && nome[i] <= 'Z')
      nome[i] = nome[i] + 32;
  }

}

void limpar_buffer(){
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

int tiraEspaco(char nome[]){
  int tam= strlen(nome);
  
  while(nome[0]== ' '){
    for(int j =0; j<tam; j++){       //se a 1° posição for espaço ele puxa todas as outras posiçoes
      nome[j] = nome[j+1];
      
    }
    tam--;
    //o while so para quando encontrar um caractere, logo tira todos os espaços do começo
  }
  tam = strlen(nome);
  if(nome[0] != 0){
    for(int i = (tam-1); i>=0; i--){
      if(nome[i] != ' '){                             //aqui ele procura o ultimo caracter e já finaliza a palavra ali
        nome[i+1]=0;                                     //ou seja tira todos os espaços do final
        break;
      }           
    }
    tam = strlen(nome);
    for(int i = 0; i< tam; i++){
      if(nome[i]==' '){
        while(nome[i+1] == ' '){
          for(int j =i; j<tam; j++){       //tira os espaços do meio
            nome[j] = nome[j+1];
      
          }
          tam--;
        }           
      }
    }
  }
    
  
  if(nome[0] == '\0') 
    return 1;     
  else
    return 0;  //Isso é pra verificar se a string tem pelo menos 1 caractere
}


void trataN(char c[]){
  if(c[strlen(c)-1] == '\n')
      c[strlen(c)-1] = 0;                   
    else
      limpar_buffer();              
    printf("\n");
}
int tabuleiro(int tam, char nome[], int ***mat, int f) {
  // tam é referente ao tamanho do tabuleiro
  int aux; // para ajudar a imprimir de forma automatica na horizontal
  char comando[40]; // recebe os comandos no jogo
  int nDesfazer =0, nTrocar =0, nPontuacao =0;
  
  
  srand(time(NULL));
  if(f == 1){
    if(tam ==4){
      aux = 0; // nao manda imprimir mais nemnhuma linha a mais
    }
    else if (tam ==5) {
      aux = 2; // manda imprimir mais duas linhas amais pra baixo
    } 
    else if (tam==6) {
      aux = 4; // manda imprimir mais 4 linhas amais pra baixo
    }
    else{
      return 2;
    }
  }
  FILE *arq = NULL;
  
  if(f == 1)
    arq = fopen("salvamento.txt", "w+");          //porque se for um novo jogo o salvamento previo tem que ser sobrescrito
  else
    arq = fopen("salvamento.txt", "r+");
  
  
  if(arq == NULL)
    return 3;
  
  if(alocaMatriz(mat, tam) == 0){
    printf(RED("Seu computador ta sem espaço na memoria!!"));
    printf("\n");
    return 0;
  }
  int **vetAux; //vetor auxilia na comparação da matriz
  if(alocaMatriz(&vetAux, tam) == 0){
    printf(RED("Seu computador ta sem espaço na memoria!!"));
    printf("\n");
    return 0;
  }
  
  
  int **vetSalv; //vetor auxilia no salvamento correto no arquivo
  if(alocaMatriz(&vetSalv, tam) == 0){
    printf(RED("Seu computador ta sem espaço na memoria!!"));
    printf("\n");
    return 0;
  }
  
  if(f==1){
    for (int i = 0; i < tam; i++) {
      for (int j = 0; j < tam; j++) {          //so tem logica iniciar a matriz com 0 se for um novo jogo
        (*mat)[i][j] = 0;
      }
    }
  }
  else{
    fscanf(arq, "%d%d%d", &tam, &nDesfazer, &nTrocar);
    if(tam == 4) {
      aux = 0; // nao manda imprimir mais nemnhuma linha a mais
    }
    else if (tam == 5) {
      aux = 2; // manda imprimir mais duas linhas amais pra baixo
    } 
    else if (tam == 6) {
      aux = 4; // manda imprimir mais 4 linhas amais pra baixo
    }
    
    fscanf(arq, "%d %s", &nPontuacao, nome);
    for(int i =0; i<tam;i++){
      for(int j =0; j<tam;j++){
        fscanf(arq, "%d", &(*mat)[i][j]);
      }                                    
    }
    for(int i =0; i<tam;i++){
      for(int j =0; j<tam;j++){
        fscanf(arq, "%d", &vetAux[i][j]);
      } 
    }
  
  }
//////////////////////////////// parte do jogo////////////////////////
  
  int sorteioI, sorteioJ, sorteioT;     
  int casasVazias;     // verifica se tem casas vazias
  int movValido;     // verifica se o movimento é valido para sortear ou nao peças
  int interromper;  //para encerrar o loop na função voltar
  int ganhou =0 , perdeu =0;
  if(f==1){
    for(int i = 0; i<2; i++){
      sorteioI = rand() % tam;
      sorteioJ = rand() % tam;
      if (tam == 4) {                             //so tem logica sortear de primeira se for um novo jogo
        sorteioT = rand() % 10;
        if (sorteioT < 9)
          sorteioT = 2;
        else
          sorteioT = 4;
      } 
      else if (tam == 5) {
        sorteioT = rand() % 20;
        if (sorteioT < 17)
          sorteioT = 2;
        else
          sorteioT = 4;
      } 
      else {
        sorteioT = rand() % 10;
        if (sorteioT < 8)
          sorteioT = 2;
        else
          sorteioT = 4;
      }

      (*mat)[sorteioI][sorteioJ] = sorteioT;
    }
  }
  int tamDinamico =calcDigitos(maiorValor(*mat, tam)) +2; //calcula quantos digitos tem o maior valor da matriz e soma
                                                         // 2, pois é um espaço a direita e um a esquerda na hora de imprimir
  
  imprimirTab(mat, tam , tamDinamico, aux, nPontuacao, nDesfazer, nTrocar);

  int desfazAnt, trocarAnt, pontuacaoAnt; //para guardar as inf antes do movimento para se desfazer ter a pontuacao antiga
 
  if(f==1){
    for(int i =0; i<tam; i++){
        for(int j =0; j<tam; j++){                    //isso so tem logica se for a primeira vez
                                                     //porque se nao o vetSalv vai copiar a mat[i][j] la na frente
          vetAux[i][j] = (*mat)[i][j];
        }
      
    }
  }
  if(f==1)
    printf("Seja bem vindo %s\n\n", nome);
  else
    printf("Seja bem vindo novamente ao jogo %s\n\n", nome);
  
  
  trocarAnt = nTrocar;
  pontuacaoAnt = nPontuacao;
  desfazAnt = nDesfazer;
  
  do{
    interromper = 1;  
    casasVazias =0;   
    movValido =0;    
    
    fseek(arq, 0, SEEK_SET);
    int casoErro =0;
    printf(WHITE("<a, d, s, w>\n"));
    printf(WHITE("<u>\n"));
    printf(WHITE("<t pos1 pos2>\n"));
    printf(WHITE("<voltar>\n\n"));
    for(int i =0; i<tam; i++){
      for(int j =0; j<tam; j++){
        vetSalv[i][j] = vetAux[i][j];              //copia a situação anterior da jogada
      }
    }
    for(int i =0; i<tam; i++){
      for(int j =0; j<tam; j++){
        vetAux[i][j] = (*mat)[i][j];               //copia a situação atual da jogada
      }
    }

    do{
      printf(WHITE("Digite um dos comandos:\n"));
      fgets(comando, 40, stdin);
      trataN(comando);
      if (tiraEspaco(comando))
        printf(RED("Você digitou espaços indevidamente!!\n\n"));
      minuscula(comando);
    }while(tiraEspaco(comando));
   
    
    if (strcmp("a", comando) == 0) {
      if(perdeu == 0){
        pontuacaoAnt = nPontuacao;
        desfazAnt = nDesfazer;
        trocarAnt = nTrocar;
        for(int i =0;i<tam; i++){
          for(int j=0; j<(tam-1); j++){
              
            if((*mat)[i][j+1] == 0){                      //vai tirando os espaços/zeros
              (*mat)[i][j+1] = (*mat)[i][j];
              (*mat)[i][j] =0;
            }
            else{
              if((*mat)[i][j+1] == (*mat)[i][j]){                   //se encontrar algum numero que da pra somar ele soma
                (*mat)[i][j+1] = (*mat)[i][j+1] + (*mat)[i][j];     //e pula um indice pra nao fazer movimento guloso
                (*mat)[i][j] =0;  
                
                nPontuacao += (*mat)[i][j+1];
                
                if((*mat)[i][j+1] == 256){
                  nDesfazer++;
                  
                }
                else if((*mat)[i][j+1] == 512){
                  
                  nTrocar++;
                  
                }
                else if((*mat)[i][j+1] == 2048)
                  ganhou++;
                j++;
              }
              
            }
          } 
        } 
          
        for(int k =0; k<tam; k++){
          for(int i =0;i<tam; i++){
            for(int j=(tam-1); j>0; j--){
              if((*mat)[i][j-1] == 0){                      //esses for aqui é pra fazer a "batida final"
                (*mat)[i][j-1] = (*mat)[i][j];              // tirando todos os zeros/espaços
                (*mat)[i][j] =0;
              }
            }
          }
        }
      }
      else{
        printf(RED("Comando impossibilitado de usar\n"));
      }
    }
    else if (strcmp("d", comando) == 0) {
      if(perdeu ==0){
        pontuacaoAnt = nPontuacao;
        desfazAnt = nDesfazer;
        trocarAnt = nTrocar;
        ///parte do comando
        for(int i =0;i<tam; i++){
          for(int j=(tam-1); j>0; j--){
            if((*mat)[i][j-1] == 0){                      //vai tirando os espaços/zeros
              (*mat)[i][j-1] = (*mat)[i][j];
              (*mat)[i][j] =0;
            }
            else{
              if((*mat)[i][j-1] == (*mat)[i][j]){                   //se encontrar algum numero que da pra somar ele soma
                (*mat)[i][j-1] = (*mat)[i][j-1] + (*mat)[i][j];     //e pula um indice pra nao fazer movimento guloso
                (*mat)[i][j] =0;
                
                nPontuacao += (*mat)[i][j-1];
    
                if((*mat)[i][j-1] == 256){
                  
                  nDesfazer++;
                }
                else if((*mat)[i][j-1] == 512){
                  
                  nTrocar++;
                  
                }
                else if((*mat)[i][j-1] == 2048)
                  ganhou++;
                j--;
              }
            }
          } 
        }
          
        for(int k =0; k<tam; k++){
          for(int i =0;i<tam; i++){
            for(int j=0; j<(tam-1); j++){
              if((*mat)[i][j+1] == 0){                      //esses for aqui é pra fazer a "batida final"
                (*mat)[i][j+1] = (*mat)[i][j];              // tirando todos os zeros/espaços
                (*mat)[i][j] =0;
              }
            }
          }
        }
      
      }
      else{
        printf(RED("Comando impossibilitado de usar\n"));
      } 
    }
    else if (strcmp("s", comando) == 0 ) {
      if(perdeu == 0){
        pontuacaoAnt = nPontuacao;
        desfazAnt = nDesfazer;
        trocarAnt = nTrocar;
        for(int j=0; j<tam; j++){
          for(int i =(tam-1);i>0; i--){
        
            if((*mat)[i-1][j] == 0){                      //vai tirando os espaços/zeros
              (*mat)[i-1][j] = (*mat)[i][j];
              (*mat)[i][j] =0;
              
            }
            else{
              if((*mat)[i-1][j] == (*mat)[i][j]){                   //se encontrar algum numero que da pra somar ele soma
                (*mat)[i-1][j] = (*mat)[i-1][j] + (*mat)[i][j];     //e pula um indice pra nao fazer movimento guloso
                (*mat)[i][j] =0;
               
                nPontuacao += (*mat)[i-1][j];
                if((*mat)[i-1][j] == 256){
              
                  nDesfazer++;
                }
                else if((*mat)[i-1][j] == 512){
                  nTrocar++;
                  
                }
                else if((*mat)[i-1][j] == 2048)
                  ganhou++;
                i--;
               
              }
            }
          } 
        }

        for(int k =0; k<tam; k++){
          for(int j=0; j<tam; j++){
            for(int i =0;i<(tam-1); i++){
            
              if((*mat)[i+1][j] == 0){                      //esses for aqui é pra fazer a "batida final"
                (*mat)[i+1][j] = (*mat)[i][j];              // tirando todos os zeros/espaços
                (*mat)[i][j] =0;
              }
            }
          }
        } 
      }
      else{
        printf(RED("Comando impossibilitado de usar\n"));
      }
    } 
    else if (strcmp("w", comando) == 0) {
      if(perdeu ==0){
        pontuacaoAnt = nPontuacao;
        desfazAnt = nDesfazer;
        trocarAnt = nTrocar;
        for(int j=0; j<tam; j++){
          for(int i =0;i<(tam-1); i++){
            
            if((*mat)[i+1][j] == 0){                      //vai tirando os espaços/zeros
              (*mat)[i+1][j] = (*mat)[i][j];
              (*mat)[i][j] =0;
                
            }
            else{
              if((*mat)[i+1][j] == (*mat)[i][j]){                   //se encontrar algum numero que da pra somar ele soma
                (*mat)[i+1][j] = (*mat)[i+1][j] + (*mat)[i][j];     //e pula um indice pra nao fazer movimento guloso
                (*mat)[i][j] =0;
                nPontuacao += (*mat)[i+1][j];
                
                if((*mat)[i+1][j] == 256){
                  nDesfazer++;
                  
                }
                else if((*mat)[i+1][j] == 512){
                  nTrocar++;
                  
                }
                else if((*mat)[i+1][j] == 2048)
                  ganhou++;
                  
                i++;
                  
              }
            }
          } 
        } 
        
        for(int k =0; k<tam; k++){
          for(int j=0; j<tam; j++){
            for(int i =(tam-1);i>0; i--){
            
              if((*mat)[i-1][j] == 0){                      //esses for aqui é pra fazer a "batida final"
                (*mat)[i-1][j] = (*mat)[i][j];              // tirando todos os zeros/espaços
                (*mat)[i][j] =0;
              }
            }
          }
        }
      }
      else{
        printf(RED("Comando impossibilitado de usar\n"));
      }
    } 
    else if (comando[0] == 't') {
      if (strlen(comando) == 7) {
        int verifica = 0;
        for (int i = 0; i < tam && verifica == 0; i++) {
          for (int j = 0; j < tam && verifica == 0; j++) {
            for (int k = 0; k < tam && verifica == 0; k++) {
              for (int l = 0; l < tam && verifica == 0; l++) {
                  
                if ((comando[1] == ' ') && (comando[2] == ('a' + i)) && (comando[3] == ('1' + j)) 
                && comando[4] == ' ' && (comando[5] == ('a' + k)) && (comando[6] == ('1' + l)))
                  verifica = 1;
              }
            }
          }
        }
        
        if (verifica == 0) {
          printf(RED("Comando Inválido!!\n"));
          casoErro =1;
        }
        else {
          if(nTrocar >0){
            //parte de config do comando
            int y[4];
            int aux;
            y[0] = converterCINT(comando[2]);
            y[1] = converterCINT(comando[3]);
            y[2] = converterCINT(comando[5]);
            y[3] = converterCINT(comando[6]);
            if((*mat)[y[0]][y[1]] == 0 || (*mat)[y[2]][y[3]] ==0)
              printf(WHITE("Você nao pode trocar posicao de uma peça vazia!!\n"));
            else{
              aux = (*mat)[y[0]][y[1]];
              (*mat)[y[0]][y[1]] = (*mat)[y[2]][y[3]];
              (*mat)[y[2]][y[3]] = aux;
              nTrocar--;
              perdeu =0;
            }
          }
          else{
            printf(RED("você não cartas de trocas disponíveis para usar!!\n")); //se ele nao tiver jogadas suficientes
          }
        }
      }
      else {
        // se não tiver 7 letras no comando <t pos1 pos2>
        printf(RED("Comando Inválido!!\n"));
        casoErro =1;
      }
           
    }
    else if (strcmp("u", comando) == 0) {
      if(nDesfazer>0){
      
        for(int i =0; i<tam; i++){
          for(int j =0; j<tam; j++){              //recebe a ultima jogada
            (*mat)[i][j]= vetSalv[i][j];          //como em cada inicio de loop o vetorAux recebe o mat
                                                  // nao precisa fazer ele receber o mat denovo porque ja recebeu no inicio
          }
        }
        nTrocar = trocarAnt;
        nPontuacao = pontuacaoAnt;
        nDesfazer = desfazAnt;
        if(nDesfazer != 0)
          nDesfazer--;
        if(nTrocar != 0)
          nTrocar--;
        perdeu =0;
        
      }
      else
        printf(RED("Comando Impossibilitado por falta de cartas 'desfazer'\n"));
    } 
    else if (strcmp("voltar", comando) == 0) {
      interromper =0;
      perdeu =0;
    }  
    else {
      printf(RED("Comando Inexistente!!\n")); //se por ventura nemnhum dos comandos acima, <a,d,s,w,u,voltar,t> for digitado
      casoErro =1;                                
    }
  
    for(int i =0;i<tam;i++){
      for(int j =0;j<tam;j++){
        if(vetAux[i][j] != (*mat)[i][j])           //compara se mexeu o comando que voce digitou mexeu ou nao na matriz
          movValido = 1;                         //se mexeu foi um movimento valido
     }
    }
    
    do{
      casasVazias =0;
      for(int i =0; i<tam; i++){ 
        for(int j =0; j<tam; j++){
          if((*mat)[i][j]==0)                     //verifica se tem casas vazias
            casasVazias++; 
        } 
      } 
      sorteioI = rand() %tam; 
      sorteioJ = rand() % tam; 
    }while((*mat)[sorteioI][sorteioJ] != 0 && casasVazias != 0);
    
    
    if(casasVazias != 0 && movValido ==1 && strcmp("u", comando) != 0){
      if(tam == 4){
        sorteioT = rand() % 10; 
        if(sorteioT<9) 
          sorteioT = 2; 
        else 
          sorteioT = 4; 
      } 
      else if(tam ==5){ 
        sorteioT = rand() % 20; 
        if(sorteioT<17) 
          sorteioT = 2; 
        else 
          sorteioT = 4; 
      } 
      else{ 
        sorteioT = rand() % 10; 
        if(sorteioT<8) 
          sorteioT = 2; 
        else 
          sorteioT = 4; 
      } 
      (*mat)[sorteioI][sorteioJ] = sorteioT; 
    }
    
    if(casoErro != 1 && strcmp(comando, "voltar") != 0){
      if(movValido ==0 && casasVazias ==0){
        perdeu =1;
        printf(BG_RED("VOCÊ PERDEU!!"));
        printf("\n");
      }                  //nao é interessante mesmo que se ja tiver uma condição de derrota
    }                    //se o usuario digitar um comando errado ele informar que ele perdeu mesmo o comando sendo errado
                          //por isso tem caso de erro
    if(movValido ==0){

      for(int i =0; i<tam;i++){
        for(int j =0; j<tam;j++){           //se nao for um movimento válido o vetor auxiliar recebe a ultima jogada 
          vetAux[i][j] = vetSalv[i][j];     
        }
      }
    }
    
    fprintf(arq, "%d %d %d\n", tam, nDesfazer, nTrocar);
    fprintf(arq, "%d %s\n", nPontuacao, nome);
    for(int i =0; i<tam;i++){
      for(int j =0; j<tam;j++){
        fprintf(arq, "%d ", (*mat)[i][j]);
      }
      fprintf(arq, "\n");                                     //faz a impressão no arquivo!!
    }
    for(int i =0; i<tam;i++){
      for(int j =0; j<tam;j++){
        fprintf(arq, "%d ", vetAux[i][j]);
      }
      fprintf(arq, "\n");
      
    }
    tamDinamico =calcDigitos(maiorValor(*mat, tam)) +2;
    if(strcmp("voltar", comando) != 0)
      imprimirTab(mat, tam , tamDinamico, aux, nPontuacao, nDesfazer, nTrocar);     
    if(ganhou ==1){
      printf(BG_WHITE("Você ganhou quer continuar (s/n)?"));
      do{
        fgets(comando, 40, stdin);
        trataN(comando);
        if (tiraEspaco(comando))
          printf(RED("Você digitou espaços indevidamente!!\n\n"));
        minuscula(comando);
      }while(tiraEspaco(comando));
      if(strcmp("s", comando)==0)
        ganhou =0;
      else
        interromper = 0;
    }
  }while(interromper == 1);
  fclose(arq);
  liberaMatriz(&vetAux, tam);
  
  liberaMatriz(&vetSalv, tam);
  return 1;
}

void ajuda(){
  printf(BG_WHITE(GREEN("                    Ajuda – Como Jogar 2048                    ")));
  printf("\n\n");
  printf(WHITE("O objetivo do jogo é combinar peças numéricas no tabuleiro até criar uma peça com o número 2048."));
  printf(WHITE("\nO jogo pode ser jogado nos tamanhos 4×4, 5×5 ou 6×6.\n\n"));
  printf(TAB_BL WHITE("Comandos durante o jogo:\n\n"));
  printf(TAB_HOR WHITE("w – Move as peças para cima\n"));
  printf(TAB_HOR WHITE("s – Move as peças para baixo\n"));
  printf(TAB_HOR WHITE("a – Move as peças para a esquerda\n"));
  printf(TAB_HOR WHITE("d – Move as peças para a direita\n"));
  printf(TAB_HOR WHITE("u – Desfaz o último movimento (se houver chances)\n"));
  printf(TAB_HOR WHITE("t pos1 pos2 – Troca duas peças de posição (ex.: t A1 B2)\n"));
  printf(TAB_HOR WHITE("voltar – Retorna ao menu inicial\n\n"));
  printf(TAB_BL WHITE("Regras básicas:\n\n"));
  printf(TAB_HOR WHITE("A cada jogada válida, surge uma nova peça de valor 2 ou 4 em posição aleatória.\n"));
  printf(TAB_HOR WHITE("Quando duas peças de mesmo valor colidem, elas se fundem somando seus valores.\n"));
  printf(TAB_HOR WHITE("Uma peça formada por fusão não pode se fundir novamente na mesma jogada.\n"));
  printf(TAB_HOR WHITE("O jogo termina quando não houver movimentos possíveis.\n\n"));
  printf(TAB_BL BG_GREEN(WHITE("Chances extras:")));
  printf("\n\n");
  printf(TAB_HOR WHITE("Ao criar uma peça de 256, você ganha 1 chance de desfazer.\n"));
  printf(TAB_HOR WHITE("Ao criar uma peça de 512, você ganha 1 chance de trocar posições.\n\n"));
  printf(TAB_BL BG_GREEN(WHITE("Pontuação:")));
  printf("\n\n");
  printf(TAB_HOR WHITE("Sua pontuação é a soma dos valores das peças criadas por fusão.\n"));
  printf(TAB_HOR WHITE("O ranking armazena as 10 maiores pontuações para cada tamanho de tabuleiro.\n\n"));
  printf(WHITE("Boa sorte e tente chegar ao 2048!\n\n"));

}
void menu(){
  printf(BG_CYAN(WHITE(TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR)));
  printf(BG_CYAN(WHITE(TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR " |MENU 2048| ")));
  printf(BG_CYAN(WHITE(TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR)));
  printf(BG_CYAN(WHITE(TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR))"\n\n");
  printf(WHITE("(R) Sair\n"));
  printf(WHITE("(N) Novo jogo\n"));
  printf(WHITE("(J) Continuar o jogo atual\n"));
  printf(WHITE("(C) Carregar um jogo salvo\n"));
  printf(WHITE("(S) Salvar o jogo atual\n"));
  printf(WHITE("(M) Mostrar Ranking\n"));
  printf(WHITE("(A) Ajuda com as instruções de como jogar\n\n"));
        
  for(int i = 0; i< 4; i++){ 
    printf(BG_CYAN(WHITE(TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR )));
  }
  printf(BG_CYAN(WHITE(TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR TAB_HOR))"\n\n");
  printf(WHITE("Digite oque você quer fazer: "));

}
void gerarRanking(){
  int x4, x5,x6;
  FILE *bin = fopen("ranking.dat", "wb");  //esse aqui é o arquivo de ranking final que o puca pediu
  FILE *bin1 = fopen("r4.dat", "rb");      
  fseek(bin1, 0, SEEK_END);                     
  x4 = ftell(bin1)/31;                 //contagem de usuarios salvos no ranking 4x4
  FILE *bin2 = fopen("r5.dat", "rb");
  fseek(bin2, 0, SEEK_END);
  x5 = ftell(bin2)/31;                   //contagem de usuarios salvos no ranking 5x5
  FILE *bin3 = fopen("r6.dat", "rb");
  fseek(bin3, 0, SEEK_END);
  x6 = ftell(bin3)/31;                      //contagem de usuarios salvos no ranking 6x6
  fwrite(&x4, sizeof(int), 1, bin);
  printf("%d ", x4);
  fwrite(&x5, sizeof(int), 1, bin);         //ja escreve a quantidade que tem de cada usuarios salvos de cada modo
  printf("%d ", x5);                         //no arquivo final pedido
  fwrite(&x6, sizeof(int), 1, bin);
  printf("%d\n", x6);
  fseek(bin1, 0, SEEK_SET);
  fseek(bin2, 0, SEEK_SET);                 //volta o cursor pro inicio em todos os arquivos 'auxiliares'
  fseek(bin3, 0, SEEK_SET);
  Rank *vet4 = malloc(x4*sizeof(Rank));
  Rank *vet5 = malloc(x5*sizeof(Rank));      
  Rank *vet6 = malloc(x6*sizeof(Rank));
  for(int i =0;i<x4; i++){
    fread(vet4[i].nome, sizeof(char), 27, bin1);
    fread(&vet4[i].pontuacao, sizeof(int), 1, bin1);
    
  }

  for(int i =0;i<x5; i++){
    fread(vet5[i].nome, sizeof(char), 27, bin2);
    fread(&vet5[i].pontuacao, sizeof(int), 1, bin2);
    
  }
  for(int i =0;i<x6; i++){
    fread(vet6[i].nome, sizeof(char), 27, bin3);
    fread(&vet6[i].pontuacao, sizeof(int), 1, bin3);
    
  }
  int aux;
  char nomeAux[27];
  if(x4>0){
    for(int j = 0; j<x4; j++){
      for(int i =0;i<(x4-1); i++){
        if(vet4[i].pontuacao < vet4[i+1].pontuacao){
          aux = vet4[i+1].pontuacao;
          vet4[i+1].pontuacao = vet4[i].pontuacao;
          vet4[i].pontuacao = aux;
          strcpy(nomeAux, vet4[i+1].nome);                        //ordena na  forma decrescente do maior pro menor
          strcpy(vet4[i+1].nome, vet4[i].nome);                   //o vetor de struct
          strcpy(vet4[i].nome, nomeAux);
          
        }
      }
    }
  }
  if(x5>0){
    for(int j = 0; j<x5; j++){
      for(int i =0;i<(x5-1); i++){
        if(vet5[i].pontuacao < vet5[i+1].pontuacao){
          aux = vet5[i+1].pontuacao;
          vet5[i+1].pontuacao = vet5[i].pontuacao;
          vet5[i].pontuacao = aux;
          strcpy(nomeAux, vet5[i+1].nome);
          strcpy(vet5[i+1].nome, vet5[i].nome);
          strcpy(vet5[i].nome, nomeAux);
          
        }
      }
    }
  }
  if(x6>0){
    for(int j = 0; j<x6; j++){
      for(int i =0;i<(x6-1); i++){
        if(vet6[i].pontuacao < vet6[i+1].pontuacao){
          aux = vet6[i+1].pontuacao;
          vet6[i+1].pontuacao = vet6[i].pontuacao;
          vet6[i].pontuacao = aux;
          strcpy(nomeAux, vet6[i+1].nome);
          strcpy(vet6[i+1].nome, vet6[i].nome);
          strcpy(vet6[i].nome, nomeAux);
          
        }
      }
    }
  }
  fwrite(vet4, sizeof(Rank), x4, bin);
  for(int i =0; i<x4; i++){
    printf("%s - %d\n", vet4[i].nome, vet4[i].pontuacao);
  }
  fwrite(vet5, sizeof(Rank), x5, bin);
  for(int i =0; i<x5; i++){
    printf("%s - %d\n", vet5[i].nome, vet5[i].pontuacao);
  }
  fwrite(vet6, sizeof(Rank), x6, bin);
  for(int i =0; i<x6; i++){
    printf("%s - %d\n", vet6[i].nome, vet6[i].pontuacao);
  }
  fclose(bin);
  fclose(bin1);
  fclose(bin2);
  fclose(bin3);
  free(vet4);
  free(vet5);
  free(vet6);
}

void continuarJogo(int *validacao, int ***mat, int *n, char user[]) {
  int tam;
  FILE *arquivo = fopen("salvamento.txt", "r");
  fscanf(arquivo, "%d", &tam);
  fclose(arquivo);

  if(*validacao == 0){
      printf(WHITE("Você não jogou nenhum jogo para poder continuar um\n"));
  }
  else{
    int resultado = tabuleiro(tam, user, mat, 2);
    if(resultado == 0){
      printf(BG_RED("Falha de alocação de memoria na execução do programa !!"));
      printf("\n");
    }
    else if(resultado == 3){
      printf(BG_RED("FALHA NA CRIAÇÃO DE ARQUIVOS DE SALVAMENTO DO JOGO!"));
      printf("\n");
    }                       //nao tem return 2 porque o return 2 é pra se o tam nao for valido mais como ele ta
    else{                  //continuando um jogo isso ja foi verificado
      *n = tam;
      liberaMatriz(mat, *n); //se ocorreu tudo bem e o usuario clicou em voltar ele cai aqui!!
      *validacao = 1;             
    }
  }
}

void salvarJogo(int validacao, Loop *teste){
  if(validacao == 0){
    printf(RED("Você não jogou nenhum jogo para poder salvar\n"));  
  }
  else{
    do{
      teste[2].parar = 0;
      printf(WHITE("Digite o nome do arquivo que voce quer salvar: "));
      char nomeArq[41];
      fgets(nomeArq, 41, stdin);
      trataN(nomeArq);
      FILE *entrada;      //é o salvamento previo que eu faço do jogo até salvar num arquivo dado pelo usuario
      FILE *saida = NULL;  // vai servir pra salvar o jogo num nome dado pelo usuario em um arquivo
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
        teste[2].parar =1;
      }
      else{
        if(nomeArq[tam-4] == '.' && nomeArq[tam-3] == 't' && nomeArq[tam-2] == 'x' && nomeArq[tam-1] == 't'){
          saida = fopen(nomeArq, "w");
          entrada = fopen("salvamento.txt", "r");
          if(entrada ==NULL){
            printf(RED("Não conseguimos carregar um arquivo do game!!\n"));         //verificações
            teste[2].parar =1;
          }
          if(saida ==NULL){
            printf(RED("Não conseguimos criar o arquivo de save do jogo!!\n"));
            teste[2].parar =1;
          }
          if((saida !=NULL) && (entrada !=NULL)){
            char carac;
            while ((carac = fgetc(entrada)) != EOF) {       //copia o arquivo de salvamento previo no arquivo 
              fputc(carac, saida);                         // que o usuario nomeou
            }
            fclose(saida);
          }
          FILE *bin1 = fopen("r4.dat", "ab");
          FILE *bin2 = fopen("r5.dat", "ab");
          FILE *bin3 = fopen("r6.dat", "ab");
          fseek(entrada, 0, SEEK_SET);
          int modo,ndesf, ntroc, pont;
          char name[27];
          fscanf(entrada, "%d", &modo);
          fscanf(entrada, "%d", &ndesf); //pra descartar
          fscanf(entrada, "%d", &ntroc); //pra descartar          //essa parte é pra pegar as informações que quero
          fscanf(entrada, "%d", &pont); //pra descartar           // modo, nome e pontuação
          fgetc(entrada);//descartar o ' '
          fgets(name, 27, entrada);
          trataN(name);
          if(modo == 4){
            fwrite(name, sizeof(char), 27, bin1);
            fwrite(&pont, sizeof(int), 1, bin1); 
          }
          else if(modo ==5){
            fwrite(name, sizeof(char), 27, bin2);
            fwrite(&pont, sizeof(int), 1, bin2); 
                                                   //a depender do modo do tabuleiro salva em um arquivo .dat especifico
          }
          else{
            fwrite(name, sizeof(char), 27, bin3);
            fwrite(&pont, sizeof(int), 1, bin3); 
             
          }
          fclose(entrada);
          
          fclose(bin1);
          fclose(bin2);
          fclose(bin3);
        }
        else{
          teste[2].parar =1;
          printf(RED("a terminação do arquivo deve ser '.txt'\n"));
        }
      }
    }while(teste[2].parar);
  }
}

int desejaSair(char *confirm, Loop *teste){
  int parada = 1;
  do{
    teste[0].parar = 0;

    printf(WHITE("Você realmente deseja sair(s)/(n)? "));
    fgets(confirm, 40, stdin);
    trataN(confirm);                                //trata o \n do buffer
    minuscula(confirm);

    if(tiraEspaco(confirm)){
      printf(BG_RED(WHITE("Você digitou espaços indevidamente")));
      printf("\n\n");                            //trata os espaços no começo fim e texto vazio
      teste[0].parar = 1;
    }
    else if(strcmp("s", confirm) == 0){
      printf(RED("Até mais!!\n"));  //se for a palavra 'sim' encerra o programa
      parada = 0;
    }
    else if(strcmp("n", confirm) != 0){
      printf(RED("Comando não reconhecido!!\n\n"));
      teste[0].parar = 1;
    }                                           //novamente importante lembrar que a variável 'parada' = 1 no
                                                 //começo da main, logo se não for a palavra 'n/N' vai da comando desconhecido
                                                    // e repetir a pergunta, e se for a palavra 'n/N' volta pro loop do menu
  }while(teste[0].parar);

  return parada; // atualiza a variavel que controle o loop mais externo do programa que é o loop do menu
}
