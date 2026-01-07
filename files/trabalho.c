#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "functions.c"

#define cleanscr() printf("\e[1;1H\e[2J") //pula espaços no terminal


//PROGRAMA PRINCIPAL
int main(){
    long v[1025], v_aux[1025], comp_d[1000], i, n=1024, trocas=0, comp=0, seq, rseq, bin, rbin;
    long comp_s=0,  comp_q=0, comp_qa=0,  comp_sh=0,  comp_sk=0;
    int x=2, y, z;

    srand(time(NULL)); //para gerar seeds aleatórias de rand
    cria_vetor(v, n); //cria o vetor inicial
    cleanscr(); //abre espaço no terminal
    inicio: //label inicial
    linha(x); //exibe uma linha para estética
    printf("[0] Sair do Programa\n");
    printf("[1] Uma vez\n"); 
    printf("[2] Mil vezes\n"); 
    printf("Quantas vezes você quer rodar os algoritmos de busca/ordenação? "); //primeira opção
    scanf("%d", &y);
    switch (y) 
    {
    case 0:
        return 0; //sai do programa
    case 1:
        cleanscr();
        desordenado: //label
        linha(x);
        printf("[0] Voltar para o menu\n");
        printf("[1] Criar novo vetor\n");
        printf("[2] Mostrar uma parte do vetor\n");
        printf("[3] Pesquisar um termo por Pesquisa Sequecial\n");
        printf("[4] Ordenar e pesquisar por Busca Binária\n");
        printf("[5] Rodar mecanismos de ordenação\n");
        printf("O que você deseja fazer? "); //segunda opção
        scanf("%d", &z);
        switch (z)
        {
        case 0: //volta para o menu inicial
            cleanscr();
            goto inicio; 
        case 1: //gera um vetor novo
            cria_vetor(v, n);
            cleanscr();
            linha(x);
            printf("Novo vetor criado com sucesso!\n");
            goto desordenado;
        case 2: //mostra o início e fim do vetor desordenado
            cleanscr();
            linha(x);
            printf("Início do vetor: ");
            imprime_v(v, 0, 5);
            printf("Fim do vetor: ");
            imprime_v(v, 1019, n);

            goto desordenado;
            break;
        case 3: //busca sequencial
            printf("- Digite um número negativo, para buscar aleatoriamente -\n");
            printf("Que número você deseja buscar no vetor? ");
            scanf("%ld", &seq);
            if (seq < 0)
                seq = rand() % (2048+1);
            rseq = sequencial(v, n, seq, &comp);
            cleanscr();
            linha(x);

            if(rseq == -1)
                printf("O número %ld não está no vetor\n", seq);
            else
                printf("Achou o número %ld na posição %ld\n", seq, rseq);
            printf("%ld comparações foram feitas\n", comp);
            goto desordenado;
            
        case 4:
            printf("- Digite um número negativo, para buscar aleatoriamente -\n");
            printf("Que número você deseja buscar no vetor ordenado? ");
            scanf("%ld", &bin);
            if (bin < 0)
                bin = rand() % (2048+1);
            quick_aleat(v, 0, n, &trocas, &comp);
            comp = 0;
            rbin = busbin_rec(v, 0, n, bin, &comp);
            cleanscr();
            linha(x);

            if(rbin == -1)
                printf("O número %ld não está no vetor\n", bin);
            else
                printf("Achou o número %ld na posição %ld\n", bin, rbin);
            printf("%ld comparações foram feitas\n", comp);
            goto desordenado;
        case 5: //todos os algoritmos de ordenação
            cleanscr();
            linha(x);
            printf("Selection Sort\n");
            selection(v, n, &trocas, &comp);
            printf("Comparações: %ld\n", comp);
            printf("Trocas: %ld\n", trocas);
            linha(x);

            trocas = 0;
            comp = 0;
            printf("Quick Sort:\n");
            printf("Pivô = Primeiro termo\n");
            copia_vetor(v, v_aux, n);
            quick(v_aux, 0, n, &trocas, &comp);
            printf("Comparações: %ld\n", comp);
            printf("Trocas: %ld\n", trocas);
            linha(x);

            trocas = 0;
            comp = 0;
            printf("Quick Sort:\n");
            printf("Pivô = Mediano entre 3 aleatórios\n");
            copia_vetor(v, v_aux, n);
            quick_aleat(v_aux, 0, n, &trocas, &comp);
            printf("Comparações: %ld\n", comp);
            printf("Trocas: %ld\n", trocas);
            linha(x);

            printf("Shell Sort:\n");
            printf("Espaçamento = Sequência de Hibbard (k = 2)\n");
            shell(v, 2, n, &trocas, &comp);
            printf("Comparações: %ld\n", comp);
            printf("Trocas: %ld\n", trocas);
            linha(x);

            printf("Shell Sort:\n");
            printf("Espaçamento = Sequência de Knuth (k = 3)\n");
            shell(v, 3, n, &trocas, &comp);
            printf("Comparações: %ld\n", comp);
            printf("Trocas: %ld\n", trocas);

            quick_aleat(v, 0, n, &trocas, &comp); //vai arrumar o vetor para poder exibir ordenado
            goto desordenado;
        
        default: //erro input
            cleanscr();
            linha(x);
            printf("Opção inválida, tente novamente!\n");
            goto desordenado;
        }
        break;
    case 2: //roda 1000 vezes
        cleanscr();
        linha(x);
        comp_s=0;  
        comp_q=0; 
        comp_qa=0;  
        comp_sh=0;
        comp_sk=0;

        for (i = 0; i < 1000; i++) { //selection
            cria_vetor(v, n);
            selection(v, n, &trocas, &comp);
            comp_d[i] = comp;
            comp_s += comp;
        }
        printf("Selection Sort:\n");
        printf("Média comparações: %.2f\n", (double)comp_s/1000.0);
        printf("Desvio Padrão: %.2f\n", desvio(comp_d, 1000));
        linha(x);
        for (i = 0; i < 1000; i++) { //quick com pivô igual ao primeiro termo da partição
            comp = 0;
            cria_vetor(v, n);
            quick(v, 0, n, &trocas, &comp);
            comp_d[i] = comp;
            comp_q += comp;
        }
        printf("Quick Sort: Pivô = Primeiro Termo\n");
        printf("Média comparações: %.2f\n", (double)comp_q/1000.0);
        printf("Desvio Padrão: %.2f\n", desvio(comp_d, 1000));
        linha(x);
        for (i = 0; i < 1000; i++) { //quick com pivô mediano entre os 3 aleatórios
            comp = 0;
            cria_vetor(v, n);
            quick_aleat(v, 0, n, &trocas, &comp);
            comp_d[i] = comp;
            comp_qa += comp;
        }
        printf("Quick Sort: Pivô = Mediano entre 3 aleatórios\n");
        printf("Média comparações: %.2f\n", (double)comp_qa/1000.0);
        printf("Desvio Padrão: %.2f\n", desvio(comp_d, 1000));
        linha(x);

        for (i = 0; i < 1000; i++) { //shell com k sendo a Sequência de Hibbard
            cria_vetor(v, n);
            shell(v, 2, n, &trocas, &comp);
            comp_d[i] = comp;
            comp_sh += comp;
        }
        printf("Shell Sort: Sequência de Hibbard (k = 2)\n");
        printf("Média comparações: %.2f\n", (double)comp_sh/1000.0);
        printf("Desvio Padrão: %.2f\n", desvio(comp_d, 1000));
        linha(x);

        for (i = 0; i < 1000; i++) { //shell com k sendo a Sequência de Knuth
            cria_vetor(v, n);
            shell(v, 3, n, &trocas, &comp);
            comp_d[i] = comp;
            comp_sk += comp;
        }
        printf("Shell Sort: Sequência de Knuth (k = 3)\n");
        printf("Média comparações: %.2f\n", (double)comp_sk/1000.0);
        printf("Desvio Padrão: %.2f\n", desvio(comp_d, 1000));
        goto inicio;

    default: //erro de input
        cleanscr();
        linha(x);
        printf("Opção inválida, tente novamente!\n");
        goto inicio;
    }
return 1;
}
