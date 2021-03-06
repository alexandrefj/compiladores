#ifndef COMP_DICT_H
#define COMP_DICT_H

#define DICT_SIZE 997

typedef struct nome_interno{
    char *text;
    int type;
    int intVal;
    char charVal;
    int boolVal;
    struct nome_interno *next;
}DICT_NODE;

void dict_init(DICT_NODE* tabela[]);
int dict_address(char *text);
DICT_NODE *dict_find(char *text,DICT_NODE* tabela[]);
DICT_NODE *dict_insert(char *text, int type,DICT_NODE* tabela[]);
void dict_print(DICT_NODE* tabela[]);

#endif

