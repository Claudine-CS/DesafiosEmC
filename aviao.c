#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <unistd.h>

int cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, totalPessoas = 0;
int opcao, i, j, aviaoEscolhido, numDePassagens, consultaAviao, achou = 0;
int avioes[4] = {0, 0, 0, 0}, assentos[4] = {0, 0, 0, 0};
int pass1[100], pass2[100], pass3[100], pass4[100];
int passagensPorPessoa[200];

char cpfs1[50][11], cpfs2[50][11], cpfs3[50][11], cpfs4[50][11];
char nome[50], cpf[20], consultaPassageiro[50], consultaCpf[12];
char todosOsNomes[200][50], todosOsCpfs[200][20];
char passageiros1[100][50], passageiros2[100][50];
char passageiros3[100][50], passageiros4[100][50];

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

int lerInt(const char* mensagem) {
    int numero, valido = 0;

    while (!valido) {
        printf("%s", mensagem);
        if (scanf("%d", &numero) == 1) { 
            valido = 1;
        } else {
            printf("\nEntrada inválida! Digite apenas números inteiros.\n");
            limparBuffer();
        }
    }

    return numero;
}

int acharIndicePorCPF(char cpf[]) {
    for (int i = 0; i < totalPessoas; i++) {
        if (strcmp(todosOsCpfs[i], cpf) == 0) {
            return i;
        }
    }
    return -1;
}

void esperarEnter() {
    limparBuffer();
    printf("\nPressione Enter para continuar...");
    getchar();
}

void mostrarPassagensPorCPF(char cpf[]) {
    int indice = acharIndicePorCPF(cpf);

    if (indice == -1) {
        printf("\nCPF não encontrado.\n");
        return;
    }

    int encontrou = 0;
    char* nome = todosOsNomes[indice];
    
    for (int i = 0; i < cont1; i++) {
        if (strcmp(cpf, cpfs1[i]) == 0 && pass1[i] > 0) {
            printf("- Avião 1 (#%04d): %d passagens\n", avioes[0], pass1[i]);
            encontrou = 1;
        }
    }
    for (int i = 0; i < cont2; i++) {
        if (strcmp(cpf, cpfs2[i]) == 0 && pass2[i] > 0) {
            printf("- Avião 2 (#%04d): %d passagens\n", avioes[1], pass2[i]);
            encontrou = 1;
        }
    }
    for (int i = 0; i < cont3; i++) {
        if (strcmp(cpf, cpfs3[i]) == 0 && pass3[i] > 0) {
            printf("- Avião 3 (#%04d): %d passagens\n", avioes[2], pass3[i]);
            encontrou = 1;
        }
    }
    for (int i = 0; i < cont4; i++) {
        if (strcmp(cpf, cpfs4[i]) == 0 && pass4[i] > 0) {
            printf("- Avião 4 (#%04d): %d passagens\n", avioes[3], pass4[i]);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("(Nenhuma passagem encontrada.)\n");
    }
}

int main (){
    setlocale(LC_ALL, "pt_PT.UTF-8"); 
    
    printf("\nBem vindo a Agência de Aviação Sweet Flight!\n");
    do{
        //Criar o menu
        printf("\n-------------------- MENU ------------------");
        printf("\n1: Registrar número do avião.");
        printf("\n2: Registrar número de assentos.");
        printf("\n3: Reservar passagem aérea.");
        printf("\n4: Realizar consulta por avião.");
        printf("\n5: Realizar consulta por passageiro.");
        printf("\n6: Sair.\n");
        opcao = lerInt("\nDigite qual opção deseja realizar: ");

        switch (opcao){
            case 1: {
                if (avioes[3] == 0){
                    printf ("\n");
                    for (i = 0; i < 4; i++) {
                       char mensagem[50];
                       sprintf(mensagem, "Cadastre o %d° avião (apenas números): ", i + 1);
                       avioes[i] = lerInt(mensagem);
                    } 
                    printf("\nProcessando...\n");
                    sleep(2);
                    printf("\033[1A\033[2K");
                    printf("Concluído!\n");
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
                        printf ("\n");
                        for (i = 0; i < 4; i++) {
                           int assento = -1;
                           while (assento < 1 || assento > 50) {
                               char mensagem[100];
                               sprintf(mensagem, "Quantos assentos terá o avião %d? (Max 50): ", avioes[i]);
                               assento = lerInt(mensagem);
                               if (assento < 1 || assento > 50) {
                                   printf("\nErro! O número deve estar entre 1 e 50.\n");
                               }
                           }
                           assentos[i] = assento;
                        }
                        printf("\nProcessando...\n");
                        sleep(2);
                        printf("\033[1A\033[2K");
                        printf("Concluído!\n");
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
                
                printf ("\n");
                aviaoEscolhido = lerInt("Em qual avião deseja comprar a passagem? ");
                
                if (aviaoEscolhido >= 1 && aviaoEscolhido <= 4 && assentos[aviaoEscolhido - 1] != 0) {
                    int valido = 0;

                    while (!valido) {
                        printf("Digite o seu nome (Apenas letras): ");
                        scanf(" %49[^\n]", nome);
                        limparBuffer();
                        valido = 1;
                        for (int i = 0; i < strlen(nome); i++) {
                            if (!isalpha((unsigned char)(nome[i])) && nome[i] != ' ') {
                                valido = 0;
                                printf("\nNome inválido! Use apenas letras (sem números ou símbolos).\n");
                                break;
                            }
                        }
                    }

                    int cpfValido = 0;

                    while (!cpfValido) {
                        printf("Digite seu CPF (somente 11 números): ");
                        scanf(" %19[^\n]", cpf);
                        limparBuffer();

                        if (strlen(cpf) != 11) {
                            printf("\nErro! CPF deve conter exatamente 11 dígitos.\n");
                            continue;
                        }

                        cpfValido = 1;
                        for (i = 0; i < 11; i++) {
                            if (!isdigit((unsigned char)cpf[i])) {
                                printf("\nErro! Use apenas números (sem letras, traços ou pontos).\n");
                                cpfValido = 0;
                                break;
                            }
                        }
                    }

    
                    numDePassagens = lerInt("Quantas passagens nesse avião? (MAX 20 por CPF): ");

                    if (numDePassagens < 1 || numDePassagens > 20) {
                        printf("\nErro! O número de passagens deve estar entre 1 e 20.\n");
                        break;
                    }
                    int indicePessoa = acharIndicePorCPF(cpf);
                    
                    if (indicePessoa != -1 && passagensPorPessoa[indicePessoa] + numDePassagens > 20) {
                        printf("\nErro! Cada passageiro pode comprar no máximo 20 passagens no total.");
                        printf("\nVocê já comprou %d e tentou comprar mais %d.\n", passagensPorPessoa[indicePessoa], numDePassagens);
                        break;
                    }

                    if (numDePassagens <= assentos[aviaoEscolhido - 1]) {
                        if (indicePessoa == -1) {
                            strcpy(todosOsCpfs[totalPessoas], cpf);
                            strcpy(todosOsNomes[totalPessoas], nome);
                            passagensPorPessoa[totalPessoas] = 0;
                            
                            indicePessoa = totalPessoas;
                            totalPessoas++;
                        }
                        assentos[aviaoEscolhido - 1] -= numDePassagens;
                        passagensPorPessoa[indicePessoa] += numDePassagens;

                        if (aviaoEscolhido == 1) {
                            strcpy(passageiros1[cont1], nome);
                            strcpy(cpfs1[cont1], cpf);
                            pass1[cont1] = numDePassagens;
                            cont1++;
                        } else if (aviaoEscolhido == 2) {
                            strcpy(passageiros2[cont2], nome);
                            strcpy(cpfs2[cont2], cpf);
                            pass2[cont2] = numDePassagens;
                            cont2++;
                        } else if (aviaoEscolhido == 3) {
                            strcpy(passageiros3[cont3], nome);
                            strcpy(cpfs3[cont3], cpf);
                            pass3[cont3] = numDePassagens;
                            cont3++;
                        } else if (aviaoEscolhido == 4) {
                            strcpy(passageiros4[cont4], nome);
                            strcpy(cpfs4[cont4], cpf);
                            pass4[cont4] = numDePassagens;
                            cont4++;
                        }

                        printf("\nPassagem comprada com sucesso!\n");
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
                    consultaAviao = lerInt ("\nDeseja consultar qual avião? ");

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
                    break;
                }

                printf("\n1 - Realizar consulta por nome.");
                printf("\n2 - Realizar consulta por CPF.");
                int opc = lerInt("\nDigite a opção que deseja realizar: ");

                if (opc == 1) {
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

                    for (int j = 0; j < totalPessoas; j++) {
                        if (strcasecmp(consultaPassageiro, todosOsNomes[j]) == 0) {
                            achou = 1;
                            printf("\nPassagens de %s | CPF: %.3s.***.***-%c%c\n", todosOsNomes[j], todosOsCpfs[j],
                            todosOsCpfs[j][9], todosOsCpfs[j][10]);
                            mostrarPassagensPorCPF(todosOsCpfs[j]);
                        }
                    }

                    if (!achou) 
                        printf("\nEsse passageiro não existe ou ainda não fez reservas!\n");

                } else if (opc == 2) {
                    int valido = 0;
                    while (!valido) {
                        printf("\nDigite o CPF que deseja consultar (somente 11 números, sem pontos ou traços): ");
                        scanf(" %19[^\n]", consultaCpf);
                        limparBuffer();

                        if (strlen(consultaCpf) != 11) {
                            printf("Erro! CPF deve conter exatamente 11 dígitos.\n");
                            continue;
                        }

                        valido = 1;
                        for (int i = 0; i < 11; i++) {
                            if (!isdigit((unsigned char)consultaCpf[i])) {
                                printf("Erro! Use apenas números (sem letras, traços ou pontos).\n");
                                valido = 0;
                                break;
                            }
                        }
                    }
                    
                    for (int j = 0; j < totalPessoas; j++) {
                        if (strcmp(consultaCpf, todosOsCpfs[j]) == 0) {
                            achou = 1;
                            printf("\nPassagens de %s | CPF: %.3s.***.***-%c%c\n", todosOsNomes[j], todosOsCpfs[j],
                            todosOsCpfs[j][9], todosOsCpfs[j][10]);
                        }
                        break;
                    }

                } else {
                    printf("Opção inválida!\n");
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