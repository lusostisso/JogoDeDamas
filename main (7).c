/**
*@file TeDamas.c
*@author Marcos Zuccolotto
*@date 13/10
*@version 0.1
*@brief Programa para movimentar peca em tabuleiro de damas
*
*
* Matrizes e ponteiros
* Objetivo � desenvolver um programa que avalie os movimentos
* das pecas de um jogo de damas
*/

/*
* O codigo abaixo apresenta as fun��es iniciais de interface
* exibi��o do tabuleiro e entrada de coordenadas
* A tarefa � implementar as fun��es prototipadas abaixo que
* analisam o movimento de uma pe�a dadas as coordenadas iniciais e finais
* As fun��es retornam um c�digo de erro definido pelo tipo enumera��o ErroMov
*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define LIN 8 //! Numero de linhas do tabuleiro
#define COL 8 //! Numero de colunas do tabuleiro
#define TAM_COORD 3 //! tamanho do vetor de coordenadas

//!
typedef enum {  OK=0,        //! exito
                OCUPADO,   //! posicao destino ocupada
                MINVALIDO, //! movimento invalido
                OBSTRUIDO, //! trajeto obstruido
                FORA,      //! coordenadas fora do tabuleiro
                VAZIO      //! posicao inicial vazia
             }ErroMov;


void exibeTabuleiro(char* tabuleiro);

void leCoordenada(char *coordenada);

ErroMov moveDama(char *tabulerio,char*incio, char*fim);




int main(void)
{
   char tabuleiro[LIN][COL]={{' ','@',' ','@',' ','@',' ','@'},
                             {'@',' ','@',' ','@',' ','@',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '}};


    char coordIni[TAM_COORD]={'0','0','\0'}, //coordenada inicial
         coordFim[TAM_COORD]={'0','0','\0'}; //coordenada final
ErroMov status;

         status=MINVALIDO;


setlocale(LC_ALL,"");

printf("Jogo de Damas\n");
printf("Coordenadas no formato coluna linha\n\n");

do{
  exibeTabuleiro(tabuleiro);
  // Entrada de dados
  printf("\nPosicao Inicial:");
  leCoordenada(coordIni);
   if (coordIni[1]=='0')
   {
        puts("\nEncerrando o programa !!");
        return -1;           // Goodbye, cruel world !

   }
  printf("\nPosicao Final:");
  leCoordenada(coordFim);

   printf("\nMovimento %s -> %s \n",coordIni,coordFim);

   ErroMov moveDama(char* tabuleiro, char* inicio, char* fim)
    {
        //casas de partida
        int hor_ini;
        int vert_ini;

        //casas de destino
        int hor_fim;
        int vert_fim;

        hor_ini = *(inicio+1)-'1';
        vert_ini = *inicio-'A';

        hor_fim = *(fim+1)-'1';
        vert_fim = *fim-'A';


        //conferindo jogadas
        if(hor_fim!=hor_ini+1){ //nao podendo andar mais de uma linha no tabuleiro
            return MINVALIDO;
        }

        if(vert_fim!=vert_ini+1 && vert_fim!=vert_ini-1){ //nao volta para tras e nao anda mais de uma coluna de cada vez
            return MINVALIDO;
        }

        if(*(tabuleiro+hor_ini*COL+vert_ini)==' '){ //n�o tem pe�a na casa de partida
            return VAZIO;
        }

        if(*(tabuleiro+hor_fim*COL+vert_fim)=='@'){ //se j� houver pe�a na casa de destino
            return OCUPADO;
        }

        *(tabuleiro+hor_ini*COL+vert_ini)='#'; //anotar espa�os livres no tabuleiro
        *(tabuleiro+hor_fim*COL+vert_fim)='@'; //anotas aonde as pe�as estao

        return OK;

    }

  /*
  * Insira aqui o c�digo respos�vel pela identifica��o da funcao
  * de an�lise de movimento a ser chamada e
  * exiba o resultado desta an�lise, em caso de erro.
  * N�o � necessario exibir o tabuleiro.
  *
  */

status=moveDama(tabuleiro,coordIni, coordFim); //atribuindo ao status da pe�a a ser movida a fun��o de mover a pe�a

switch(status) //testando as jogadas
{
case 0: //se a posi��o estiver OK
    printf("Feito!\n");
    break;
case 1: //se a posi��o estiver ocupada
    printf("Posi��o destino ocupada! Tente novamente.\n");
    break;
case 2: //se o movimento a ser executado � inv�lido
    printf("Movimento inv�lido! Tente novamente.\n");
case 3: //se o trajeto estiver obstru�do
    printf("Trajeto obstru�do! Tente novamente.\n");
    break;
case 4: //se as coordenadas digitadas estiverem fora do tabuleiro
    printf("Coordenadas fora do tabuleiro! Tente novamente.\n");
    break;
case 5: //se a posi��o inicial estiver vazia
    printf("Posi��o inicial vazia! Tente novamente.\n");
    break;

} //fim dos testes

}while(coordIni[1]!='0' && coordFim[1]!='0');

}// fim

/**
*@brief exibe o tabuleiro com as pecas na tela
*@param ponteiro para a matriz tabuleiro
*/
void exibeTabuleiro(char *tabuleiro)
{
   static const char desenho[LIN][COL]={  {' ','#',' ','#',' ','#',' ','#'},
                            {'#',' ','#',' ','#',' ','#',' '},
                            {' ','#',' ','#',' ','#',' ','#'},
                            {'#',' ','#',' ','#',' ','#',' '},
                            {' ','#',' ','#',' ','#',' ','#'},
                            {'#',' ','#',' ','#',' ','#',' '},
                            {' ','#',' ','#',' ','#',' ','#'},
                            {'#',' ','#',' ','#',' ','#',' '}};

    int lin,col;

    printf("   A  B  C  D  E  F  G  H\n");
    for(lin=0;lin<LIN;lin++)
    {
        printf("%1d ",lin+1);
        for(col=0;col<COL;col++)
        {
            if(*(tabuleiro+lin*COL+col)==' ')
                printf("[%c]",desenho[lin][col]);
            else
                printf("[%c]",*(tabuleiro+lin*COL+col));
        }
        printf("\n");
    }
}

/**
*@brief l�, via teclado as coordenadas do tabuleiro
*@param ponteiro para o vetor coordenadas, formato coluna,linha
* coordenadas : vetor caractere com 2 elementos.
*               primeiro elemento => coluna : A a H
*               segundo  elemento => linha  : 1 a 8
*/
void leCoordenada(char *coordenada)
{
    char tecla;
    do{
        tecla=getch();
        tecla=toupper(tecla);
    }while(tecla<'A' ||tecla>'H');
    *coordenada=tecla;
    coordenada++;
    printf("%c",tecla);
    do{
        tecla=getch();
    }while(tecla<'0' || tecla>'8');
    *coordenada=tecla;
    printf("%c",tecla);
    return;
}

ErroMov moveDama(char *tabulerio,char*incio, char*fim)
{
    return OK;
}
