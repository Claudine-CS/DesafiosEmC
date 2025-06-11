#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>


void mostra_boneco(int erro) {
	printf(" +-------+\n");
	printf(" |       %c\n", erro >= 1 ? 'O' : ' ');
	printf(" |      %c%c%c\n",
	       erro >= 3 ? '/' : ' ',
	       erro >= 2 ? '|' : ' ',
	       erro >= 4 ? '\\' : ' ');
	printf(" |      %c %c\n",
	       erro >= 5 ? '/' : ' ',
	       erro >= 6 ? '\\' : ' ');
	printf(" |\n");
	printf("_|_\n\n");
}
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
	setlocale(LC_ALL, "pt_PT");
	int vida = 7, opcao, teraDicas, indice = 0;
	int tamanho, v = 0;
	char letra, tentativas[26], lacuna[20] = {0};
	char *palavras[7] = {
		"pterodactilo",
		"jaguatirica",
		"ornitorrinco",
		"lontra",
		"leopardo",
		"velociraptor",
		"babuino"
	};
	
	char *dicas[7] = {
	    "Réptil extinto voador.",
	    "Mamífero carnívoro, da familia dos felídeos.",
	    "Mamífero semiaquático.",
	    "Animal nadador, da subfamilia Lutrinae.",
	    "Felídeo nativo da África e da Ásia.",
	    "É um gênero de dinossauros terópodes",
	    "Animal semi-quadrúpede da ordem dos primatas."
	};
	
	srand(time(NULL));
	int i = rand() % 7;
	char *palavra_da_vez = palavras[i];
	char *dica_da_vez = dicas[i];

	tamanho = strlen(palavra_da_vez);

    printf ("---------------------------------\n");
    printf ("|  Bem vindo ao jogo da forca!  |\n");
    printf ("|-------------------------------|\n");
    printf ("|             MENU              |\n");
    printf ("|1 - Jogar                      |\n");
    printf ("|2 - Consultar regras do jogo   |\n");
    printf ("|3 - Sair                       |\n");
    printf ("---------------------------------\n");
    printf (" Digite uma opção: ");
    scanf ("%d", &opcao);
    
    switch (opcao){
        case 1: {
            printf (" Deseja ter dica adcional? (1 - sim, 2 - não): ");
        	scanf ("%d",  &teraDicas);
        	if (teraDicas == 1) {
                printf("\n A dica é: %s\n", dica_da_vez);
        		printf (" Boa sorte! \n");
        		printf("\n Pressione Enter para continuar...");
        		getchar();
        		getchar();
        	}else {
        	    printf (" Tudo bem. Boa sorte! \n");
        		printf("\n Pressione Enter para continuar...");
        		getchar();
        		getchar();
        	}   
        	while (vida > 0 && v == 0) {

        		system("clear");
                
                if (teraDicas == 1){
        		    printf("Dica: %s\n", dica_da_vez);
                }else;
                    printf ("Dica: é um animal.\n");
        
        		mostra_boneco(7 - vida);
        
        		printf("Quantidade de letras: %d\n", tamanho);
        
        		for (int i = 0; i < tamanho; i++) {
        			if (lacuna[i] == '\0') printf("_ ");
        			else printf("%c ", lacuna[i]);
        		}
                
                if (indice > 0){
                    printf ("\n\nLetras tentadas: ");
                    for (int j = 0; j < indice; j++) {
                        printf (" %c", tentativas[j], " ");
                    }
                }   
                
        		printf("\n\nDigite a letra: ");
        		scanf(" %c", &letra);
                limparBuffer();
                
        		int count = 0;
        		for (int i = 0; i < tamanho; i++) {
        			if (palavra_da_vez[i] == letra && lacuna[i] != letra) {
        				lacuna[i] = letra;
        				count++;
                    }    
        		}
        
        		if (count == 0) {
        			printf("Letra errada. Tente outra vez.\n");
        			vida--;
                    tentativas[indice] = letra;
                    indice++;
        		} else {
        			printf("Parabéns, acertou!\n");
        		}
        
        		if (strcmp(palavra_da_vez, lacuna) == 0) {
        			v = 1;
        		}
                
        
        		printf("\nPressione ENTER para continuar...");
        		getchar();
        		
        	}
        
        	if (v == 1) {
        		printf("\nParabéns! Você venceu com %d vidas restantes.\n", vida);
        	} else {
        		printf("\nVocê perdeu! A palavra era: %s\n", palavra_da_vez);
        	}
        }
    }
    
    	return 0;
}
    