#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//recebe dois indices e trocas os respectivos elementos num vetor
void troca(long v[], long a, long b){
    long aux;
    aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

//sorteia n elementos de 0 a 2048
void cria_vetor(long v[], long n){ 
    long i;
    for(i = 0; i<n; i++)
        v[i] = rand() % (2048+1);
}

//copia o vetor original para poder ordenar
void copia_vetor(long v1[], long v2[], long n) { 
    for (long i = 0; i < n; i++) 
        v2[i] = v1[i];
}

//imprime o vetor completo
void imprime_v(long v[], long a0, long n){
    long i;
    for(i = a0; i < n; i++)
        printf("%ld ", v[i]);
    printf("\n");
}

// Função para encontrar o valor mediano entre 3 valores
long mediano(long v[], long i, long j, long k) {
    if (((v[i] > v[j]) && (v[i] < v[k])) || ((v[i] < v[j]) && (v[i] > v[k])))
        return i; 
    else if (((v[j] > v[i]) && (v[j] < v[k])) || ((v[j] < v[i]) && (v[j] > v[k])))
        return j;  
    else
        return k; 
}

//divide em termos antes e depois do vetor
long particiona(long v[], long esq, long dir, long *trocas, long *comp){
    long pivo, pivoi, i, j;
    pivoi = esq;
    pivo = v[pivoi];
    i = esq;
    j = dir;
    while(j > i){
        (*comp)++;
        while(v[i] <= pivo && i < dir){
            i++;
            (*comp)++;
        }
        while(v[j] > pivo){
            j--;
            (*comp)++;
        }
        if(j > i){
            troca(v, i, j);
            (*trocas)++;
        }
    }
    troca(v, j, pivoi);
    (*trocas)++;
    return j;
}


//sorteia 3 valores, escolhe o mediano, coloca na primeira posição e chama particiona
long particiona_aleat(long v[], long esq, long dir, long *trocas, long *comp){
    long i, j, k, valor_m;
    i = esq + rand() % (dir - esq + 1);  // Índice aleatório entre esq e dir
    j = esq + rand() % (dir - esq + 1);
    k = esq + rand() % (dir - esq + 1);
    valor_m = mediano(v, i, j, k);
    troca(v, esq, valor_m);
    return particiona(v, esq, dir, trocas, comp);
}


//algoritmo do quick com pivô no primeiro elemento
void quick(long v[], long esq, long dir, long *trocas, long *comp){
    long pivoi;
    if (dir >= esq){
        pivoi = particiona(v, esq, dir, trocas, comp);//faz a partição
        quick(v, esq, pivoi-1, trocas, comp); //chama recursivamente para cada metade
        quick(v, pivoi+1, dir, trocas, comp);
    }
}

//identico ao outro só que com pivô aleatório
void quick_aleat(long v[], long esq, long dir, long *trocas, long *comp){
    long pivoi;
    if (dir >= esq){
        pivoi = particiona_aleat(v, esq, dir, trocas, comp); 
        quick_aleat(v, esq, pivoi-1, trocas, comp); 
        quick_aleat(v, pivoi+1, dir, trocas, comp);
    }
}

//selection sort simples
void selection(long v[], long n, long *trocas, long *comp){
    long i, j, menori, v_aux[1025];
    copia_vetor(v, v_aux, 1025);
    *trocas = 0;
    *comp = 0;
    for (i = 0;i < n-1;i++){
        menori = i;
        for (j =i+1;j<n;j++){
            (*comp)++;
            if (v_aux[j] < v_aux[menori])
                menori = j;
        }
        troca(v_aux, menori, i);
        (*trocas)++;
    }
}

//shell sort
void shell(long v[], int x,  long n, long *trocas, long *comp){ //buscar entender
    long i, j, aux, k=1, v_aux[1025];
    *trocas = 0;
    *comp = 0;
    copia_vetor(v, v_aux, n);
    do
        k = k*x + 1;
    while(k<=n);
    do{
        k = (k-1)/x;
        for(i = k;i<n;i++){
            aux = v_aux[i];
            j = i;
            while(j>=k && v_aux[j-k]>aux){
                (*comp)++;
                (*trocas)++;
                v_aux[j] = v_aux[j-k];
                j = j-k;
            }
            (*comp)++; //comparação que quebrou o while
            v_aux[j] = aux;
        }
    }
    while(k != 1);
}

//busca binária recursiva
long busbin_rec(long v[], long esq, long dir, long x, long *comp){
	if(esq>dir)
		return -1;
	long meio = (dir + esq)/2;
    (*comp)++;
	if (v[meio] == x)
		return meio;
	else if(v[meio] < x)
		return busbin_rec(v, meio + 1, dir, x, comp);
	else
		return busbin_rec(v, esq, meio-1, x, comp);
}

//busca sequencial com sentinela
long sequencial(long v[], long n, long x, long *comp){
    v[n] = x; //sentinela
    long i = 0;
    *comp = 0;
    while(v[i] != x){
        i++;
        (*comp)++;
    }
    (*comp)++; //achou
    if(i == n)
        return -1;
    else
        return i;
}

//calcula o desvio padrão das comparações dentro de um vetor
double desvio(long comp_d[], long n){
    long j;
    double soma = 0, soma_d = 0, media, desvio_padrao;
    for (j = 0; j < n; j++) {
        soma += comp_d[j];
    }
    media = soma / n;
    for (j = 0; j < n; j++) {
        soma_d += pow(comp_d[j] - media, 2);
    }
    desvio_padrao = sqrt(soma_d/ n);

    return desvio_padrao;
}



//um void só para exibir uma linha bonitinha x vezes
void linha(int x){
    int i;
    for(i=0;i<x;i++)
        printf("-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n");
}
