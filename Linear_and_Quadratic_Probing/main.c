#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "HashTable.h"

int main(){
    struct HashTable table;
    table.buckets = MAX_BUCKETS;//Total de palavras do arquivo do dicion�ro
    table.words = MAX_BUCKETS;
    unsigned int i = 0;
    for(i=0;i<table.buckets;i++){
        table.nodes[i] = NULL;
    }

    clock_t start, end;

    start = clock();
    load_hash_table_quadratic_probing(&table,"ascii.txt");//Carregar dicion�rio na memoria ram
    //load_hash_table(&table,"ascii.txt");//Carregar dicion�rio na memoria ram
    end = clock();

    float time = ((float)(end-start))/(CLOCKS_PER_SEC/1000);
    printf("Tempo gasto para carregar o dicionario: %f ms\n",time);

    quadratic_search(&table,"text.txt");//Busca no dicion�rio
    //linear_search(&table,"text.txt");//Busca no dicion�rio

    return 0;
}
