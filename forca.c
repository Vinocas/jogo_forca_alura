// Projeto de Jogo de Adivinhação, desenvolvido por Vinicius Ferreira Florencio como parte do curso "C: Avançando na Linguagem" da plataforma Alura.
// Curso disponível em https://cursos.alura.com.br/course/introducao-a-programacao-com-c-parte-2

// Inserção de bibliotecas e header.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

// Criação de variáveis globais.
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

// Função que verifica se a letra chutada existe na palavra secreta.
int verificaletra(char letra)
{

    for (int j = 0; j < strlen(palavrasecreta); j++)
    {
        if (letra == palavrasecreta[j])
        {
            return 1;
        }
    }

    return 0;
}

// Função que retorna a quantidade de chutes errados pelo usuário.
int chuteserrados()
{
    int erros = 0;

    for (int i = 0; i < chutesdados; i++)
    {

        if (!verificaletra(chutes[i]))
        {
            erros++;
        }
    }

    return erros;
}

// Função de que classifica a derrota do usuário.
int derrota()
{
    return chuteserrados() >= 5;
}

// Função que classifica a vitória do usuário.
int vitoria()
{
    for (int i = 0; i < strlen(palavrasecreta); i++)
    {
        if (!jachutou(palavrasecreta[i]))
        {
            return 0;
        }
    }

    return 1;
}

// Função de boas-vindas ao jogo de forca.
void inicio()
{
    printf("/******************************/\n");
    printf("/ Bem-vindo ao Jogo de Forca! */\n");
    printf("/******************************/\n\n");
}

// Função que pede o chute do usuário e classifica se a letra existe na palavra secreta.
void chuta()
{
    char chute;
    printf("Adivinhe uma letra da palavra secreta: ");
    scanf(" %c", &chute);

    if (verificaletra(chute))
    {
        printf("A palavra secreta contem a letra %c\n\n", chute);
    }
    else
    {
        printf("\nA palavra secreta nao contem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

// Função que guarda a letra chutada pelo usuário.
int jachutou(char letra)
{
    int achou = 0;
    for (int j = 0; j < chutesdados; j++)
    {
        if (chutes[j] == letra)
        {
            achou = 1;
            break;
        }
    }

    return achou;
}

// Função que desenha o personagem a medida que vai sendo enforcado (nº de erros).
void desenho()
{

    int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for (int i = 0; i < strlen(palavrasecreta); i++)
    {

        if (jachutou(palavrasecreta[i]))
        {
            printf("%c ", palavrasecreta[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

// Função que escolhe uma palavra aleatóriamente do banco de dados 'db.txt'.
void selecaopalavra()
{
    FILE *f;

    f = fopen("db.txt", "r");
    if (f == 0)
    {
        printf("O banco de dados nao esta disponivel. Avise o Vinicius!\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for (int i = 0; i <= randomico; i++)
    {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

// Função que adiciona uma palavra inserida pelo usuário ao banco de dados 'palavra.txt'.
void adicionarpalavra()
{
    char quer;

    printf("Voce deseja adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer);

    if (quer == 'S')
    {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiusculas: ");
        scanf("%s", novapalavra);

        FILE *f;

        f = fopen("db.txt", "r+");
        if (f == 0)
        {
            printf("Banco de dados de palavras nao disponivel\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

// Função principal.
int main()
{

    inicio();
    selecaopalavra();

    do
    {

        desenho();
        chuta();

    } while (!vitoria() && !derrota());

    if (vitoria())
    {
        printf("\nParabens, voce ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }
    else
    {
        printf("\nPuxa, voce foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionarpalavra();
}