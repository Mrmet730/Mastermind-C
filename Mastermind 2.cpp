#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

void caricamento();
void play();
void istruzioni();
void displayName();
void displayHotbar();
const char* toColor(int); //in base al numero del colore scelto dal giocatore che viene passato come parametro, la funzione ritorna "la stringa" del colore corrispondente (in realtà ritorna un puntatore al primo elemento della stringa)
void control(int[], int[], char *punttentati, bool *win);

int main()
{
	system("color 0a");
	srand(time(NULL)); //inizializzazione srand per la generazione dei numeri casuali
	int scelta;
	bool errScelta=false;
	do{
		system("cls");
		displayName();
		printf("\t\t\t                         MENU'                          \n\n");
		printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
		printf("\t\t\t\t\t\t1. Single-player\n");
		printf("\t\t\t\t\t\t2. Instruction\n");
		printf("\t\t\t\t\t\t3. Exit\n\n");
		printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
		if(errScelta)
			{
				printf("\t\t\tError, unvalid choose!\n"); 
			}
		printf("\t\t\tChoose an action -> ");
		scanf("%d", &scelta);
		switch (scelta)
		{
			case 1:
				errScelta=false;
				caricamento();
				play();
				break;
			case 2:
				errScelta=false;
				istruzioni();
				break;
			default:
				errScelta=true;
				break;
		}
	}while (scelta!=3);
	system("cls");
	return 0;
}

void play()
{
	system("cls");
	int estratti[4], tentati[12][4]; //estratti= array con il codice segreto estratto casualmente; tentati=matrice con 12 righe (una per ogni possibile tentativo) e 4 colonne (che conterranno i colori scelti dal player in un determinato tentativo)
	int tentativo=0; //contatore del tentativo attuale
	char punttentati[12][45]; //array di stringhe che conterrà per ogni possibile tentativo(max 12) una stringa di massimo 30 caratteri che indica il punteggio conseguito in quel determinato tentativo
	char stringtentati[5]; //stringa per l'acquisizione del tentativo
	int span, suppspan;
	bool win=false, correctin=false;
	int i, j;
	for(i=0; i<4; i++) //riempimento dell'array di interi "estratti"
	{
		estratti[i] = (rand() % 6) + 1; //intero random tra (0 e 5) + 1 (tra 1 e 6) 
	}
	do
	{
		displayName();
		displayHotbar();
		/*
		for (i=0; i<4; i++)
		{
			printf("%d ", estratti[i]);
		}
		printf("\n");
		*/
		for (i=0; i<tentativo; i++)
		{
			span=0;
			printf("\t\t\t");
			for(j=0; j<4; j++)
			{
				printf("%s ", toColor(tentati[i][j]));
				span+=strlen(toColor(tentati[i][j]));
			}
			span+=4;
			for(suppspan=32-span; suppspan>0; suppspan--)
			{
				printf(" ");
			}
			printf("| %s", punttentati[i]);
			printf("\n");
		}
		if(win)
		{
			printf("\t\t\t                    YOU WIN\n");
			system("pause");
		//	displayScore
			break;
		}
		printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
		printf("\t\t\tATTEMPT N. %i: \n\n", tentativo+1);
		printf("\t\t\t1. RED\n");
		printf("\t\t\t2. YELLOW\n");
		printf("\t\t\t3. GREEN\n");
		printf("\t\t\t4. BLUE\n");
		printf("\t\t\t5. WHITE\n");
		printf("\t\t\t6. BLACK\n");
		do
		{
			printf("\t\t\tYOUR GUESS -> ");
			scanf("%s", stringtentati);
			for(i=0; i<4; i++)
			{
				if(strlen(stringtentati)!=4)
				{
					printf("\n\t\t\tERROR, UNVALID SEQUENCE!\n\n");
					correctin=false;
					break;
				}
				if(stringtentati[i]-'0'<1 || stringtentati[i]-'0'>6)
				{
					printf("\n\t\t\tERROR, UNVALID SEQUENCE!\n\n");
					correctin=false;
					break;
				}
				else
				{
					tentati[tentativo][i]=stringtentati[i]-'0';
					correctin=true;
				}
			}
		} while(!correctin);
		control(estratti, tentati[tentativo], punttentati[tentativo], &win);
		system("cls");
		tentativo++;
	} while(tentativo<11 || !win);
}

void control(int estratti[], int tentati[], char *punttentati, bool *win)
{
	int contx, conty, contr[4]={0,0,0,0}, contt[4]={0,0,0,0};
	int black=0, white=0;
	char finale[45]=""; 
	for(contx=0; contx<4;contx++)
	{
		if(tentati[contx]==estratti[contx] && contr[contx]!=1 && contt[contx]!=1)
		{
			black++;
			contr[contx]=1;
			contt[contx]=1;
		}
	}
	for(contx=0; contx<4;contx++)
	{
		for (conty=0; conty<4; conty++)
		{
			if(tentati[contx]==estratti[conty] && contr[conty]!=1 && contt[contx]!=1)
			{
				white++;
				contr[conty]=1;
				contt[contx]=1;
				break;
			}
		}
	}
	if(black==4)
	{
		*win = true;
	}
	for(black; black>0; black--)
	{
		strcat(finale, "Black ");
	}
	for(white; white>0; white--)
	{
		strcat(finale, "White ");
	}
	strcpy(punttentati, finale);
}

const char* toColor(int x)
{
	switch(x)
	{
		case 1:
			return "Red";
			break;
		case 2:
			return "Yellow";
			break;
		case 3:
			return "Green";
			break;
		case 4:
			return "Blue";
			break;
		case 5:
			return "White";
			break;
		case 6:
			return "Black";
			break;
		default:
			return "Error";
			break;
	}
}

void caricamento()
{
	int supp;
	system("cls");
	displayName();
	printf("\t\t\t                        LOADING\n");
	printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
	printf("\n\n\n\n");
	printf("\t\t\t             Controls are simple:              \n\n\n");
	printf("\t\t\t       Just type the entire attemptend combination     \n");
	printf("\t\t\t       and then press \"ENTER\".\n");
	printf("\t\t\t       Example: \"Your guess -> 2514 [Enter]\"\n\n\n\t\t\t");
	for(supp=0;supp<10;supp++)
	{
		sleep(1);
		printf("[][][]");
	}
}

void istruzioni()
{
	system("cls");
	displayName();
	printf("\t\t\t                         INSTRUCTIONS                         \n\n");
	printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
	printf("\t\t\tThe game objective is pretty simple: you have to guess\n");
	printf("\t\t\tthe secret combination generated by the computer.\n");
	printf("\t\t\tFor each try, you could receive one or more \"White\" \n");
	printf("\t\t\tand or one or more \"Black\"! \n");
	printf("\t\t\tYou will receive a \"White if one of your guessed color \"\n");
	printf("\t\t\tmatch by type with one of the secret combination.\n");
	printf("\t\t\tYou will instead receive a \"Black\" if one of your\n");
	printf("\t\t\tguessed color match by type and by position with one of\n");
	printf("\t\t\tthe secret combination.\n");
	printf("\t\t\tThe game ends when you obtain 4 \"Black\" or when you\n");
	printf("\t\t\trun out of attempts (12)!\n");
	printf("\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
	printf("\t\t\t");
	system("pause");
}



void displayName()
{
	printf("\t\t\t*   *   **    ***  *****  ***  ***   *   *  *  *   *  ***\n");
	printf("\t\t\t* * *  *  *  *       *    *    *  *  * * *  *  **  *  *  *\n");
	printf("\t\t\t*   *  ****   **     *    ***  ***   *   *  *  * * *  *  *\n");
	printf("\t\t\t*   *  *  *     *    *    *    * *   *   *  *  *  **  *  *\n");
	printf("\t\t\t*   *  *  *  ***     *    ***  *  *  *   *  *  *   *  ***\n\n");
}

void displayHotbar()
{
	printf("\n\t\t\t-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");
	printf("\t\t\t                        SECRET CODE                        \n");
	printf("\t\t\t             ------     ------     ------     -----          \n");
	printf("\t\t\t            |      |   |      |   |      |   |     |         \n");
	printf("\t\t\t            |      |   |      |   |      |   |     |         \n");
	printf("\t\t\t             ------     ------     ------     -----          \n\n");
	printf("\t\t\t            TRY:                |   SCORE:               \n");
	printf("\t\t\t    ------------------------------------------------------- \n");
}


