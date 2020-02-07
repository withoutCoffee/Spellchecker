#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "HashTable.h"
#include "Node.h"
#include <time.h>

//Função para inserir com o quadratic probing
void quadratic_insert(char *word, struct HashTable *hash_table){

    unsigned int i = 0;
    unsigned int hashs = hash(word, strlen(word));//hash da string


    struct Node * new_node = (struct Node*) malloc(sizeof(struct Node));

    new_node->word = (char*) malloc(sizeof(char)*(strlen(word)+1));

    strcpy(new_node->word,word);

    new_node->next = NULL;

    //verifica se a posição está vaiza
    if(hash_table->nodes[(hashs+(i*i))%hash_table->buckets] == NULL){

        hash_table->nodes[(hashs+(i*i))%hash_table->buckets] = new_node;

    }else{//Se não estiver vazia procura a proxima vazia
        while(hash_table->nodes[(hashs+(i*i))%hash_table->buckets] != NULL){
            ++i;
        }
        hash_table->nodes[(hashs+(i*i))%hash_table->buckets] = new_node;
    }
}
//Funcao de busca de palavra no dicionário com quadratic probing
int quadratic_word_search(char* word, struct HashTable *hash_table){

    unsigned int i = 0;
    unsigned int hashs = hash(word,strlen(word));//Hash da palavra

    if(hash_table->nodes[(hashs+(i*i))%hash_table->buckets] == NULL){
        return 1;
    }else{
        while(hash_table->nodes[(hashs+(i*i))%hash_table->buckets] != NULL){

            if(strcmp(hash_table->nodes[(hashs+(i*i))%hash_table->buckets]->word,word) == 0){
                return 0;
            }else{
                ++i;//contador para quadratic probing
            }
        }
        return 1;
    }
}
//Pesquisa todas as palavras de um arquivo com quadratic probing
void quadratic_search(struct HashTable * hash_table, char *path){
    FILE *stream = NULL;
    stream = fopen(path, "r");
    char * token = NULL;
    if(stream == NULL){
        printf("Nao foi possivel abrir o arquivo!!\n");
        fclose(stream);
        return;
    }else{
        unsigned int fails = 0;
        unsigned int cont = 0;//Contador de palavras do texto
        const char *s = " ()\n";//Caracteres que vou ignorar na leitura
        char line[1024];//tamanho máximo de uma linha no bloco de notas

        FILE *stream2 = NULL;
        stream2 = fopen("words.txt", "w");

        clock_t start, end;
        start = clock();

        while(fgets(line, sizeof(line),stream) != NULL){
            token = strtok(line,s);//Transforma a linha em um array de strings
            while(token != NULL){
                ++cont;
                //pesquisa palavra no dicionário e marca palavras erradas
                if(quadratic_word_search(token,hash_table) == 0){

                }else{
                    fprintf(stream2,"%s\n",token);/**Escrita dos dados em arquivo**/
                    ++fails;
                }
                token = strtok(NULL,s);
            }
            token = NULL;
        }
        fclose(stream);
        fclose(stream2);

        end = clock();
        float time = ((float)(end-start))/(CLOCKS_PER_SEC/1000);
        printf("Tempo total da verificacao: %f ms\n",time);

        /**Escrita dos dados em arquivo**/
        stream2 = fopen("erros.txt", "w");
        stream = fopen("words.txt", "r");

        fprintf(stream2,"Numero total de palavras do texto: %i\n",cont);
        fprintf(stream2,"Tempo total da verificacao: %f ms\n",time);
        fprintf(stream2,"Numero de palavras que falharam no spell check: %i\n", fails);
        fprintf(stream2,"Lista de palavras que falharam no spell check:\n\nNum. Ocorrencia - Palavra\n-----------------\n");
        cont = 1;
        while(fscanf(stream,"%s",line)!=EOF){
            fprintf(stream2,"%i - %s\n",cont,line);
            ++cont;
        }
        fclose(stream);
        fclose(stream2);
    }
}
//Carregar dicionário na memória RAM com quadratic probing
void load_hash_table_quadratic_probing(struct HashTable *hash_table, char * path){
    FILE * stream = NULL;
    stream = fopen(path,"r");

    if(stream == NULL){
        printf("Nao foi possivel abrir o arquivo!!\n");
        fclose(stream);
        return;
    }else{
        char string[47];//46 é o tamanho da maior palavra do dicionário

        while(fscanf(stream,"%s",&string)!=EOF){
            //printf("%s\n",string);
            quadratic_insert(string,hash_table);
        }
        fclose(stream);
    }
}
