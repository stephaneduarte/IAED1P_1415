/*PROJETO 1 - IAED

  MARÇO 2015 - v1.0

  81186 - Stephane Oliveira Duarte 
  81530 - Renato Paulo Da Costa Cardoso
  81858 - Joao Ricardo Caseiro Oliveira*/

#include <stdio.h>
#include <stdlib.h>

/* Definicao de Constantes */
#define MAU 0
#define BOM 1

/* Definicao de Variaveis */
int classif, ref, ref1, ref2, valor, tipo;
char nome[41];
int matriz[1000][1000]; /*Matriz utilizada para controlar os emprestimos*/
int ponteiro = 0; /*Controla o numero de bancos na base de dados*/
int bons = 0;
int flag_K = 0;
int outVMK = 0;
int pos_pior = 0;

/* Funcoes */
int executa_a();
void executa_k();
void executa_r();
void executa_e();
void executa_p();
void executa_l();
void executa_0();
void executa_1();
void executa_2();
void executa_K();
int ref_para_posicao(int ref);
void in_out(int v, int pos1);

/* Estrutura de Dados */
typedef struct{
  char nome[41]; /*Nome do banco*/
  int classif; /*Classificacao*/
  int ref; /*Referencia*/
  int inP; /*Numero de bancos a quem o banco tem divida*/
  int outP; /*Numero de bancos a quem o banco forneceu emprestimo*/
  int parc; /*Numero total de parceiros*/
  int outV; /*Valor emprestado a outros bancos*/
  int outVM; /*Valor emprestado a bancos maus*/
  int inV; /*Valor emprestado ao banco em questao*/
  int inVM; /*Valor emprestado por bancos maus*/
}Banco;
  
Banco bancos[1000];

/*CORPO PRINCIPAL DO CODIGO*/

/*A funcao tem como objetivo interpretar o comando do utilizador e direciona-lo para a respetiva funcao.*/
int main()
{	
	char comando;
	while (1)
	{
		comando = getchar(); /*O comando e dado pelo utilizador atraves do primeiro caracter*/
		switch (comando){
			case 'a':
				executa_a();
				break;
			case 'k':
				executa_k();
				break;
			case 'r':
				executa_r();
				break;
			case 'e':
				executa_e();
				break;
			case 'l':
				executa_l();
				break;
			case 'p':
				executa_p();
				break;
			case 'K':
				executa_K();
				break;
			case 'x': /*A funcao devolve o numero de bancos na base de dados e o numero de bancos classificados como bons.*/
        printf("%d %d\n", ponteiro, bons);
				return EXIT_SUCCESS;
			default:
				printf("ERRO: Comando desconhecido.\n");
		}
		getchar(); /* le o /n introduzido pelo utilizador*/
	}
	return EXIT_FAILURE;
}

/*Funcao de comando 'a' - Adiciona na base de dados um novo banco*/
int executa_a()
{
  scanf("%s%d%d", bancos[ponteiro].nome, &bancos[ponteiro].classif, &bancos[ponteiro].ref);
  if (bancos[ponteiro].classif == 1)
  	bons++;
  ponteiro++;
  return ponteiro;
}

/*Funcao de comando 'k' - classifica um banco com rating mau*/
void executa_k()
{
  int pos;
  scanf("%d", &ref); /*Le referencia introduzida pelo utilizador*/
  pos = ref_para_posicao(ref);
  bancos[pos].classif = MAU;
  bons--;
}

/*Funcao de comando 'r' - promove um banco ao rating bom*/
void executa_r()
{
  int pos;
  scanf("%d", &ref); /*Le referencia introduzida pelo utilizador*/
  pos = ref_para_posicao(ref);
  bancos[pos].classif = BOM;
  bons++;
}

/* Funcao de comando 'e' - adiciona um emprestimo*/
void executa_e()
{
  int pos1;
  int pos2;
  scanf("%d%d%d", &ref1, &ref2, &valor); /*Le as referencias e o valor do emprestimo (ref1 - banco que fornece, ref2 - banco que recebe)*/
  pos1 = ref_para_posicao(ref1);
  pos2 = ref_para_posicao(ref2);
  /*Condicoes para atualizar valores de parceiras*/
  if (matriz[pos1][pos2] == 0)
  {
  	bancos[pos1].outP++;
  	bancos[pos2].inP++;
  	if (matriz[pos2][pos1] == 0)
  	{
  		bancos[pos1].parc++;
  		bancos[pos2].parc++;
  	}
  }
  matriz[pos1][pos2] += valor; /*Adiciona ao valor ja na matriz o valor do emprestimo*/
}

/*Funcao de comando 'p' - adiciona amortizacao ao emprestimo*/
void executa_p()
{	
  int pos1;
  int pos2;
  scanf("%d%d%d", &ref1, &ref2, &valor); /*Le as referencias e o valor do emprestimo (ref1 - banco que paga, ref2 - banco que recebe)*/
  pos1 = ref_para_posicao(ref1);
  pos2 = ref_para_posicao(ref2);
  /*Condicoes para atualizar valores de parceiras*/
  if (valor >= matriz[pos2][pos1])
  {  
    matriz[pos2][pos1] = 0;
    bancos[pos2].outP--;
    bancos[pos1].inP--;
    if (matriz[pos1][pos2] == 0)
    {
    	bancos[pos1].parc--;
    	bancos[pos2].parc--;
    }
  }
  else
    matriz[pos2][pos1] -= valor;
}

/*Funcao de comando 'l' - emite listagem*/
void executa_l(int tipo)
{
    scanf("%d", &tipo); /*le o tipo de lista requerido pelo utilizador*/
    switch (tipo) /*redireciona para a respetiva funcao*/
    {
    case 0:
	    executa_0();
	    break;
    case 1:
	    executa_1();
	    break;
    case 2:
	    executa_2();
	    break;
  }
}

/*Funcao de comando 'l' tipo '0'*/
void executa_0()
{
  int i;
  for (i = 0; i < ponteiro; i++)
  {
    printf("%d %s %d\n", bancos[i].ref, bancos[i].nome, bancos[i].classif);
    /*Imprime lista com todos bancos listados (referencia, nome e classificacao)*/
  }
}

/*Funcao de comando 'l' tipo '1'*/
void executa_1()
{
  int pos1;
  for (pos1 = 0; pos1 < ponteiro; pos1++)
  {
  	in_out(1, pos1);
    printf("%d %s %d %d %d %d %d %d %d\n", bancos[pos1].ref, bancos[pos1].nome, bancos[pos1].classif, bancos[pos1].inP, bancos[pos1].outP, bancos[pos1].outV, bancos[pos1].outVM, bancos[pos1].inV, bancos[pos1].inVM);
  	/*Imprime lista com todos os bancos listados (referencia, nome, classificacao e outros dados adicionais)*/
  }
}

/*Funcao de comando 'l' tipo '2'*/
void executa_2()
{
  int i1;
  int i2;
  int cont;
  for (i1 = 0; i1 < ponteiro; i1++) 
  /*Um contador 1 não superior ao numero de bancos existentes para controlar o numero de parcerias maximas*/
  { 
    cont = 0; /*Comeca o contador do numero de bancos com i1 parceiros*/
    for (i2 = 0; i2 < ponteiro; i2++) 
    /*Outro contador não superior ao numero de bancos existentes para percorrer todas as posicoes da matriz*/
    {
      if (bancos[i2].parc == i1)
      /*Se o numero de parceiros do banco com a posicao i2 for igual ao contador 1*/
      {
        cont++;
        /*incrementa o contador.*/
      }
    }
    if (cont != 0)
    printf("%d %d\n", i1, cont);
	/*Imprime lista com o numero de bancos com n parceiros*/
  } 
}

/*Funcao de comando 'K' - despromove o banco com classificacao BOM em maior dificuldades*/
void executa_K()
{ 
  int pos1;
  if (bons != 0) /*Se houver bancos maus*/
  {
    for (pos1 = 0; pos1 < ponteiro; pos1++)
      {
        if (bancos[pos1].classif == BOM)
        {
        in_out(0, pos1); /*Atualiza valores de in e out do banco bom*/
        if (bancos[pos1].outVM != 0) /*Se emprestou dinheiro a bancos classificados com MAU*/
          {
            flag_K = 1;
            if (outVMK <= bancos[pos1].outVM)
              {
                outVMK = bancos[pos1].outVM;
                pos_pior = pos1;
                /*Guarda o valor do montante emprestado e a posicao do banco mais em risco*/
              }
          }
        }
      }
    if (flag_K == 1)
        {
        bancos[pos_pior].classif = MAU; /*despromove o banco*/
          bons--;
          outVMK = 0;
          flag_K = 0;
          in_out(1, pos_pior);
          printf("*%d %s %d %d %d %d %d %d %d\n", bancos[pos_pior].ref, bancos[pos_pior].nome, bancos[pos_pior].classif, bancos[pos_pior].inP, bancos[pos_pior].outP, bancos[pos_pior].outV, bancos[pos_pior].outVM, bancos[pos_pior].inV, bancos[pos_pior].inVM);
          /*Imprime lista com todas as informacoes do banco despromovido*/
        }
      }
      printf("%d %d\n", ponteiro, bons);
      /*Imprime o numero de bancos na base de dados e a quantidade de bancos bons*/
    }



/* Funcoes auxiliares */

int ref_para_posicao(int ref)
/*Funcao que devolve a posicao do banco no vetor bancos atravez da referencia*/
{
  int i = 0;
  while (bancos[i].ref != ref)
  {
    i++;
  }
  return i;
}

void in_out(int var, int pos1)
/* Funcao que calcula/actualiza os varios valores de in ou out de todos os bancos.*/
{
  int pos2;
  bancos[pos1].outVM = 0;
  if (var == 0)
  {
	for (pos2 = 0; pos2 < ponteiro; pos2++)
    { 	
      if (bancos[pos2].classif == MAU)
        bancos[pos1].outVM += matriz[pos1][pos2];
	}
  }
  if (var == 1)
  {
    bancos[pos1].inP = 0;
    bancos[pos1].outP = 0;
    bancos[pos1].outV = 0;
    bancos[pos1].inV = 0;
    bancos[pos1].inVM = 0;
   	/* Inicia os contadores a 0 */
    for (pos2 = 0; pos2 < ponteiro; pos2++)
    { 
      bancos[pos1].outV += matriz[pos1][pos2];
      bancos[pos1].inV += matriz[pos2][pos1];
      if (bancos[pos2].classif == MAU)
        bancos[pos1].inVM += matriz[pos2][pos1];
      if (bancos[pos2].classif == MAU)
        bancos[pos1].outVM += matriz[pos1][pos2];
      if (matriz[pos1][pos2] != 0)
        bancos[pos1].outP++;
      if (matriz[pos2][pos1] != 0)
        bancos[pos1].inP++;
      /*Atualiza todas os valor de in e out percorrendo toda a matriz*/
    }
   }
}