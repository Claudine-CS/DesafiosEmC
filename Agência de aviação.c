#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <unistd.h>

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int haAvioesDisponiveis(int assentos[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (assentos[i] > 0) {
            return 1;
        }
    }
    return 0;
}

void esperarEnter() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
}

int main (){
    setlocale(LC_ALL, "pt_PT.UTF-8"); 
    int opcao, i, j, aviaoEscolhido, numDePassagens, consultaAviao;
    int cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, totalNomes = 0, achou = 0, mostrouCabecalho = 0;
    int pass1[100], pass2[100], pass3[100], pass4[100], passagensPorPessoa[160];
    int avioes[4] = {0, 0, 0, 0}, assentos[4] = {0, 0, 0, 0};
    char nome[50], passageiros1[100][50], passageiros2[100][50], passageiros3[100][50], passageiros4[100][50];
    char nomeParaConsulta[50], consultaPassageiro[50], todosOsNomes[160][50];

    printf("\nBem vindo a Agência de Aviação Sweet Flight!");
    do{
        //Criar o menu
        printf("\n-------------------- MENU ------------------");
        printf("\n1: Registrar número do avião.");
        printf("\n2: Registrar número de assentos.");
        printf("\n3: Reservar passagem aérea.");
        printf("\n4: Realizar consulta por avião.");
        printf("\n5: Realizar consulta por passageiro.");
        printf("\n6: Sair.\n");
        printf("\nDigite qual opção deseja realizar: ");
        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada inválida! Apenas números são permitidos. Encerrando o programa.\n");
            return 1;
        }
        limparBuffer();


        switch (opcao){
            case 1: {
                //Mostrando os aviões disponíveis 
                if (avioes[3] == 0){
                    printf ("\n");
                    for(i = 0; i < 4; i++){
                        printf ("Cadastre o %d° aviao (apenas números): ", i + 1);
                        if (scanf("%d", &avioes[i]) != 1) {
                            printf("\nEntrada inválida! Apenas números são permitidos. Encerrando o programa.\n");
                            return 1;
                        }
                        limparBuffer();
                    }    
                    printf("\nProcessando...\n");
                    sleep(2);
                    printf("\033[1A\033[2K");
                    printf("\nConcluído!\n");
                    esperarEnter();
                    system("clear");

                }else{
                    printf("\nAviões disponíveis: \n");
                    for(i = 0; i < 4; i++){
                        printf("Avião %d: #%04d\n",i + 1, avioes[i]);
                    }
                }
            }
            break;

            case 2: {
                if (avioes[0] != 0) {
                    int todosTemAssentos = 1;
                    for(i = 0; i < 4; i++) {
                        if (assentos[i] == 0) {
                            todosTemAssentos = 0;
                            break;
                        }
                    }
                    if (todosTemAssentos) {
                        printf("\nAssentos disponíveis por avião:\n");
                        for(i = 0; i < 4; i++) {
                            printf("Avião %d: #%04d: %d assentos.\n", i + 1, avioes[i], assentos[i]);
                        }
                    } else {
                        for (i = 0; i < 4; i++) {
                            int entradaValida = 0;
                            while (!entradaValida) {
                                printf("\nDigite quantos assentos terá o avião %d (Max 100): ", avioes[i]);
                                if (scanf("%d", &assentos[i]) != 1) {
                                    printf("\nEntrada inválida! Apenas números são permitidos.\n");
                                    limparBuffer();
                                    continue;
                                }
                                limparBuffer();
                                if (assentos[i] > 100 || assentos[i] <= 0) {
                                   printf("\nErro! O número deve ser entre 1 e 100!\n");
                                   continue;
                                }
                                entradaValida = 1;
                            }
                        }
                        printf("\nProcessando...\n");
                        sleep(2);
                        printf("\033[1A\033[2K");
                        printf("\nConcluído!\n");
                        esperarEnter();
                        system("clear");
                    }
                } else {
                    printf("\nAinda não há aviões cadastrados!\n");
                }
            }
            break;

            case 3:
                if (haAvioesDisponiveis(assentos, 4)) {
                    printf("\nPassagens disponíveis por avião:\n");
                    for (i = 0; i < 4; i++) {
                        if (assentos[i] != 0) {
                            printf("%d - %04d: %d\n", i + 1, avioes[i], assentos[i]);
                        } else {
                            printf("%d - %04d: Sem passagens disponíveis.\n", i + 1, avioes[i]);
                        }
                    }
                } else {
                    printf("\nNão há aviões com assentos disponíveis!\n");
                    break;
                }

                printf("\nEm qual avião deseja comprar a passagem? ");
                if (scanf("%d", &aviaoEscolhido) != 1) {
                    printf("\nEntrada inválida! Apenas números são permitidos. Encerrando o programa.\n");
                    return 1;
                }
                limparBuffer();
                
                if (aviaoEscolhido >= 1 && aviaoEscolhido <= 4 && assentos[aviaoEscolhido - 1] != 0) {
                    int valido = 0;

                    while (!valido) {
                        printf("\nDigite o seu nome (Apenas letras): ");
                        scanf(" %49[^\n]", nome);
                        limparBuffer();
                        valido = 1;
                        for (int i = 0; i < strlen(nome); i++) {
                            if (!isalpha((unsigned char)(nome[i])) && nome[i] != ' ') {
                                valido = 0;
                                printf("Nome inválido! Use apenas letras (sem números ou símbolos).\n");
                                break;
                            }
                        }
                    }

                    printf("Nome aceito: %s\n", nome);

                    int indicePessoa = -1;
                    for (i = 0; i < totalNomes; i++) {
                        if (strcasecmp(nome, todosOsNomes[i]) == 0) {
                            indicePessoa = i;
                            break;
                        }
                    }

                    printf("\nQuantas passagens deseja comprar neste avião? (MAX 20 no total por pessoa): ");
                    if (scanf("%d", &numDePassagens) != 1) {
                        printf("\nEntrada inválida! Apenas números são permitidos. Encerrando o programa.\n");
                        return 1;
                    }
                    limparBuffer();

                    if (numDePassagens < 1 || numDePassagens > 20) {
                        printf("\nErro! O número de passagens deve estar entre 1 e 20.\n");
                        break;
                    }

                    if (indicePessoa != -1 && passagensPorPessoa[indicePessoa] + numDePassagens > 20) {
                        printf("\nErro! Cada passageiro pode comprar no máximo 20 passagens no total.\n");
                        printf("\nVocê já comprou %d e tentou comprar mais %d.\n", passagensPorPessoa[indicePessoa], numDePassagens);
                        break;
                    }

                    if (numDePassagens <= assentos[aviaoEscolhido - 1]) {
                        if (indicePessoa == -1) {
                            strcpy(todosOsNomes[totalNomes], nome);
                            passagensPorPessoa[totalNomes] = 0;
                            indicePessoa = totalNomes;
                            totalNomes++;
                        }
                        assentos[aviaoEscolhido - 1] -= numDePassagens;
                        passagensPorPessoa[indicePessoa] += numDePassagens;

                        if (aviaoEscolhido == 1) {
                            strcpy(passageiros1[cont1], nome);
                            pass1[cont1] = numDePassagens;
                            cont1++;
                        } else if (aviaoEscolhido == 2) {
                            strcpy(passageiros2[cont2], nome);
                            pass2[cont2] = numDePassagens;
                            cont2++;
                        } else if (aviaoEscolhido == 3) {
                            strcpy(passageiros3[cont3], nome);
                            pass3[cont3] = numDePassagens;
                            cont3++;
                        } else if (aviaoEscolhido == 4) {
                            strcpy(passageiros4[cont4], nome);
                            pass4[cont4] = numDePassagens;
                            cont4++;
                        }

                        printf("\nPassagem comprada com sucesso!");
                    } else {
                        printf("\nNão há assentos suficientes nesse avião.\n");
                    }
                } else {
                    printf("\nEsse avião não existe, ou não está disponível.\n");
                }
                break;
            
            case 4:
                if (avioes[0] == 0 && avioes[1] == 0 && avioes[2] == 0 && avioes[3] == 0){
                    printf("\nAinda não há aviões cadastrados!\n");
                }else if(cont1 == 0 && cont2 == 0 && cont3 == 0 && cont4== 0){
                    printf("\nAinda não há passagens compradas!");
                }else {
                    printf("\nDeseja consultar qual avião? ");
                    if (scanf("%d", &consultaAviao) != 1) {
                        printf("\nEntrada inválida! Apenas números são permitidos. Encerrando o programa.\n");
                        return 1;
                    }
                    limparBuffer();

                    if (consultaAviao > 0 && consultaAviao <= 4) {
                        if (consultaAviao == 1 && cont1 > 0) {
                            printf("\nHá %d reserva(s) feita(s) para esse avião.\n", cont1);
                            printf ("Há %d passagens restantes!", assentos[0]);
                        } else if (consultaAviao == 2 && cont2 > 0) {
                            printf("\nHá %d reserva(s) feita(s) para esse avião.\n", cont2);
                            printf ("Há %d passagens restantes!", assentos[1]);
                        } else if (consultaAviao == 3 && cont3 > 0) {
                            printf("\nHá %d reserva(s) feita(s) para esse avião.\n", cont3);
                            printf ("Há %d passagens restantes!", assentos[2]);
                        } else if (consultaAviao == 4 && cont4 > 0) {
                            printf("\nHá %d reserva(s) feita(s) para esse avião.\n", cont4);
                            printf ("Há %d passagens restantes!", assentos[3]);
                        } else {
                            printf("\nNão há reservas feitas para este avião.\n");
                            break;
                        }

                    } else {
                        printf("\nNúmero de avião inválido!\n");
                    }
                }    
                break;

            case 5: {
                if (todosOsNomes[0][0] == '\0') {
                    printf("\nNenhum nome foi cadastrado ainda.\n");
                }else{
                    achou = 0;
                    int valido1 = 0;
                    while (!valido1) {
                        printf("\nDigite o nome do passageiro que deseja consultar: ");
                        scanf(" %49[^\n]", consultaPassageiro);
                        limparBuffer();
                        valido1 = 1;
                        for (int i = 0; i < strlen(consultaPassageiro); i++) {
                            if (!isalpha(consultaPassageiro[i]) && consultaPassageiro[i] != ' ') {
                                valido1 = 0;
                                printf("Nome inválido! Use apenas letras (sem números ou símbolos).\n");
                                break;
                            }
                        }
                    }

                    for (j = 0; j < totalNomes; j++) {
                        if (strcasecmp(consultaPassageiro, todosOsNomes[j]) == 0) {
                            achou = 1;
                            printf("\nPassagens de %s:\n", consultaPassageiro);

                            printf("\nPassagens de %s:\n", consultaPassageiro);

                            for (i = 0; i < cont1; i++) {
                                if (strcasecmp(consultaPassageiro, passageiros1[i]) == 0)
                                    printf("- Avião 1 (#%04d): %d passagens\n", avioes[0], pass1[i]);
                            }
                            for (i = 0; i < cont2; i++) {
                                if (strcasecmp(consultaPassageiro, passageiros2[i]) == 0)
                                    printf("- Avião 2 (#%04d): %d passagens\n", avioes[1], pass2[i]);
                            }
                            for (i = 0; i < cont3; i++) {
                                if (strcasecmp(consultaPassageiro, passageiros3[i]) == 0)
                                    printf("- Avião 3 (#%04d): %d passagens\n", avioes[2], pass3[i]);
                            }
                            for (i = 0; i < cont4; i++) {
                                if (strcasecmp(consultaPassageiro, passageiros4[i]) == 0)
                                    printf("- Avião 4 (#%04d): %d passagens\n", avioes[3], pass4[i]);
                            }
                        }
                    }

                    if (!achou)
                    printf("\nEsse passageiro não existe ou ainda não fez reservas!\n");
                }
                break;
            }    
            case 6:
                printf("\nEncerrando programa!");   
                break; 
            default:
                printf("\nOpção Inválida! Tente novamente.\n");
                break;
        }

    }while (opcao != 6);


    return 0;
}