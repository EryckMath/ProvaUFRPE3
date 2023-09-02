#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_CLIENTES 500

typedef struct
{
    char nome[50];
    int idade;
    int roteiro;
    int tipo_transporte;
    int ingresso_show;
    float valor_pacote;
} Cliente;

void cadastrar_cliente(Cliente clientes[MAX_CLIENTES], int *qtd_clientes)
{
    int opcao;
    do
    {
        printf("Turismo Legal - Sao Joao\n");
        printf("Cadastrar Cliente\n");
        printf("Nome: ");
        scanf("%s", clientes[*qtd_clientes].nome);
        printf("Idade: ");
        scanf("%d", &clientes[*qtd_clientes].idade);
        printf("Roteiro (1 - Caruaru / 2 - Gravata /3 - Campina Grande): ");
        scanf("%d", &clientes[*qtd_clientes].roteiro);
        printf("Tipo de transporte (1 - Van / 2 - onibus): ");
        scanf("%d", &clientes[*qtd_clientes].tipo_transporte);
        printf("Comprar ingresso para show (1 - sim / 0 - nao)? ");
        scanf("%d", &clientes[*qtd_clientes].ingresso_show);

        float valor_transporte, valor_ingresso;

        switch (clientes[*qtd_clientes].roteiro)
        {
        case 1: // Caruaru
            valor_transporte = (clientes[*qtd_clientes].tipo_transporte == 1) ? 250.0 : 170.0;
            valor_ingresso = 50.0;
            break;
        case 2: // Gravatá
            valor_transporte = (clientes[*qtd_clientes].tipo_transporte == 1) ? 150.0 : 90.0;
            valor_ingresso = 90.0;
            break;
        case 3: // Campina Grande
            valor_transporte = (clientes[*qtd_clientes].tipo_transporte == 1) ? 350.0 : 280.0;
            valor_ingresso = 100.0;
            break;
        default:
            printf("Roteiro invalido.\n");
            return;
        }

        float valor_pacote = valor_transporte;
        if (clientes[*qtd_clientes].ingresso_show)
        {
            valor_pacote += valor_ingresso;
        }

        clientes[*qtd_clientes].valor_pacote = valor_pacote;

        printf("\nValor do pacote de viagem: R$%.2f\n", valor_pacote);

        (*qtd_clientes)++;

        printf("\nCadastrar outro cliente? (1 - Sim / 0 - Nao) ");
        scanf("%d", &opcao);

    } while (opcao == 1 && (*qtd_clientes) < MAX_CLIENTES);
}

void listagem_geral(Cliente clientes[MAX_CLIENTES], int qtd_clientes)
{
    printf("Turismo Legal - Sao Joao\n");
    printf("Listagem Geral\n");
    printf("| %-20s | %-5s | %-15s | %-12s | %-8s | %-12s |\n", "Nome", "Idade", "Roteiro", "Transporte", "Ingresso", "Valor Pacote");
    printf("\n----------------------------------------------------------------------------------------------");
    for (int i = 0; i < qtd_clientes; i++)
    {
        char roteiro[20];
        switch (clientes[i].roteiro)
        {
        case 1:
            strcpy(roteiro, "Caruaru");
            break;
        case 2:
            strcpy(roteiro, "Gravata");
            break;
        case 3:
            strcpy(roteiro, "Campina Grande");
            break;
        default:
            strcpy(roteiro, "Roteiro invalido");
            break;
        }

        char transporte[10];
        switch (clientes[i].tipo_transporte)
        {
        case 1:
            strcpy(transporte, "Van");
            break;
        case 2:
            strcpy(transporte, "Onibus");
            break;
        default:
            strcpy(transporte, "Tipo de transporte invalido");
            break;
        }

        char ingresso[5];
        strcpy(ingresso, (clientes[i].ingresso_show == 1) ? "Sim" : "Nao");

        printf("\n| %-20s | %-5d | %-15s | %-12s | %-8s | R$ %-8.2f |", clientes[i].nome, clientes[i].idade, roteiro, transporte, ingresso, clientes[i].valor_pacote);
        printf("\n----------------------------------------------------------------------------------------------");
    }

    printf("\n\nPressione qualquer tecla para voltar ao menu.");
    getch();
}

void relatorio_estatistico(Cliente clientes[MAX_CLIENTES], int qtd_clientes)
{
    int qtd_show_caruaru = 0;
    int soma_idade_gravata = 0;
    int qtd_pacotes_campina_grande = 0;
    int roteiro_mais_escolhido = 0;

    for (int i = 0; i < qtd_clientes; i++)
    {
        if (clientes[i].roteiro == 1 && clientes[i].ingresso_show == 1)
        {
            qtd_show_caruaru++;
        }

        if (clientes[i].roteiro == 2)
        {
            soma_idade_gravata += clientes[i].idade;
        }

        if (clientes[i].roteiro == 3)
        {
            qtd_pacotes_campina_grande++;
        }
    }

    if (qtd_clientes > 0)
    {
        float percentual_campina_grande = (float)qtd_pacotes_campina_grande / qtd_clientes * 100;

        if (qtd_show_caruaru > qtd_pacotes_campina_grande && qtd_show_caruaru > soma_idade_gravata)
        {
            roteiro_mais_escolhido = 1;
        }
        else if (soma_idade_gravata > qtd_show_caruaru && soma_idade_gravata > qtd_pacotes_campina_grande)
        {
            roteiro_mais_escolhido = 2;
        }
        else
        {
            roteiro_mais_escolhido = 3;
        }

        printf("Turismo Legal - Sao Joao\n");
        printf("Relatorio Estatistico\n");
        printf("Quantidade de pessoas que vao para o show de abertura em Caruaru: %d\n", qtd_show_caruaru);
        printf("Media da idade dos clientes que vao para Gravata: %.2f\n", (float)soma_idade_gravata / qtd_clientes);
        printf("Percentual de clientes que compraram pacotes para Campina Grande: %.2f%%\n", percentual_campina_grande);
        printf("Roteiro mais escolhido: ");

        switch (roteiro_mais_escolhido)
        {
        case 1:
            printf("Caruaru\n");
            break;
        case 2:
            printf("Gravata\n");
            break;
        case 3:
            printf("Campina Grande\n");
            break;
        default:
            printf("Nenhum roteiro escolhido\n");
            break;
        }
    }
    else
    {
        printf("Nao ha clientes cadastrados.\n");
    }

    printf("\nPressione qualquer tecla para voltar ao menu.");
    getch();
}

int main()
{
    Cliente clientes[MAX_CLIENTES];
    int qtd_clientes = 0;
    int opcao;

    do
    {
        system("cls");
        printf("Turismo Legal - Sao Joao\n");
        printf("Opcoes:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listagem Geral\n");
        printf("3. Relatorio Estatistico\n");
        printf("0. Sair\n");
        printf("Informe a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrar_cliente(clientes, &qtd_clientes);
            break;
        case 2:
            listagem_geral(clientes, qtd_clientes);
            break;
        case 3:
            relatorio_estatistico(clientes, qtd_clientes);
            break;
        case 0:
            printf("Encerrando o programa.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}
