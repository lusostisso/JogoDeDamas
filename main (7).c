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


void exibeTabuleiro(char *tabuleiro);

void leCoordenada(char *coordenada);

ErroMov moveDama(char* tabuleiro, char* inicio, char* fim);

int main(void)
{
   char tabuleiro[LIN][COL]={{' ','a',' ','a',' ','a',' ','a'},
                             {'a',' ','a',' ','a',' ','a',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '},
                             {' ',' ',' ',' ',' ',' ',' ',' '}};
                             
    char coordIni[TAM_COORD]={'0','0','\0'}, coordFim[TAM_COORD]={'0','0','\0'};
         
    ErroMov status;
    status=MINVALIDO;

	setlocale(LC_ALL,"");

	printf("Jogo de Damas\n");
	printf("Coordenadas no formato coluna linha\n\n");

do{
  exibeTabuleiro(*tabuleiro);
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

  /*
  * Insira aqui o código resposável pela identificação da funcao
  * de análise de movimento a ser chamada e
  * exiba o resultado desta análise, em caso de erro.
  * Não é necessario exibir o tabuleiro.
  */
  

 status=moveDama(*tabuleiro, coordIni, coordFim);
 
    if (status==OK){
	    printf("Feito !\n");
	}
    
    if (status==MINVALIDO){
	    printf("Movimento Invalido !\n");
	}
	
	if(status==OCUPADO){
		printf("Destino Ocupado !\n");
	}
	
	if(status==VAZIO){
		printf("Casa vazia !\n");
	}


}while(coordIni[1]!='0' && coordFim[1]!='0');

}// fim

/**
*@brief exibe o tabuleiro com as pecas na tela
*@param ponteiro para a matriz tabuleiro
*/

/**
*@brief lê, via teclado as coordenadas do tabuleiro
*@param ponteiro para o vetor coordenadas, formato coluna,linha
* coordenadas : vetor caractere com 2 elementos.
*               primeiro elemento => coluna : A a H
*               segundo  elemento => linha  : 1 a 8
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

    printf(" A  B  C  D  E  F  G  H\n");
    
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

ErroMov moveDama(char* tabuleiro, char* inicio, char* fim)
{
	int key=0;
	int clear=0;
	
	int in_hor = *inicio-'A';
	int in_ver = *(inicio+1)-'1';
	int fim_hor = *fim-'A';
	int fim_ver = *(fim+1)-'1';
	
	int delta_hor = fim_hor-in_hor;
	int delta_ver = fim_ver-in_ver;

	
	if(abs(delta_ver)==abs(delta_hor)){
		clear=1;
	}
	
	if(*(tabuleiro+in_ver*COL+in_hor)=='a'){
		if(clear==0||delta_ver<=0||delta_ver>=2){
		    return MINVALIDO;
		    key++;
		}
	}
	
	if(*(tabuleiro+in_ver*COL+in_hor)=='@'){
		if(clear==0){
		    return MINVALIDO;
		    key++;
		}	
	}
	
	if(*(tabuleiro+fim_ver*COL+fim_hor)=='@'||*(tabuleiro+fim_ver*COL+fim_hor)=='a'){
		return OCUPADO;
		key++;
	}
	
	if(*(tabuleiro+in_ver*COL+in_hor)=='#'||*(tabuleiro+in_ver*COL+in_hor)==' '){
		return VAZIO;
		key++;
	}
	
	if(key==0){
	    if(*(tabuleiro+in_ver*COL+in_hor)=='a'){
		    *(tabuleiro+fim_ver*COL+fim_hor)='a';
	    }		
	    
		if(fim_ver==7){
		    *(tabuleiro+fim_ver*COL+fim_hor)='@'; //dama no final do tabuleiro
	    }
	    if(*(tabuleiro+in_ver*COL+in_hor)=='@'){
		    *(tabuleiro+fim_ver*COL+fim_hor)='@';
	    }
	    *(tabuleiro+in_ver*COL+in_hor)='#';
		// não conseguimos usar ponteiro duplo então copiamos o formato usado na função exibe.
		// era possivel fazer com ponteiro duplo?
        return OK;
	}

}
