#include "comp_list.h"

List* InvertList(List* list){
	List* aux =list;
	while(list!= NULL){
		list = list->next;
		aux->next = list;
	}
	return aux;
}

List* FunctionParamList(List* AllParams, int function_id){
	int found = 0;
	List* aux = AllParams;
	List* resultant = list_init();
	if(aux!= NULL){
		while(aux != NULL){
			if(aux->tam == function_id){
				while(aux != NULL && (aux->tam == function_id)){ 
					resultant = list_insert(resultant,aux->type,aux->tam,aux->text,0);
					aux = aux->next;
				}
				return resultant;
			}aux = aux->next;
		}
	}
	return NULL;
}

List* TILL_NULL(List* list){
	while(list->next != NULL)
		list = list->next;
	return list;
}

List* JoinGlobalVet(List* global,List* vet){

	List* aux = TILL_NULL(global);
	list_print(aux);
	aux->next = vet;
	return aux;

}


List* list_copy(List* list1, List* list2){
	list1 = (List*)calloc(1,sizeof(List));
	list1 = NULL;
	List* aux;
	while(list2 != NULL){
		List* new  = (List*)calloc(1,sizeof(List));
		new->type = list2->type;
		new->tam = list2->tam;
		new->size = list2->size; 
		new->text = list2->text;
		if(list1==NULL){
			list1 = new;
			aux = list1;
		}
		else{
			list1->next = new;
			list1 = new;
		}
		list2 = list2->next;
	}		
	return aux;
}

List* list_init(void){
	List* list = (List*)calloc(1,sizeof(List));
	list = NULL;
	return list;
}

List* list_insert(List* list, int type,int tam, char* text, int size){
	List* new = malloc(sizeof(List));
	new->tam = tam;	
	new->type = type;
	new->text = text;
	new->size = size;
	new->next = NULL;
	if(list == NULL)
		list = new;
	else{
		List* aux = list;
		while(aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}	
	return list;
}

void list_print(List* list){
	List* aux = list;
	if(list!= NULL){
		while(aux != NULL){
			printf("type = %d ", aux->type);
			printf("tam= %d ", aux->tam);
			printf("text = %s ", aux->text);
			printf("size = %d\n", aux->size);
			aux = aux->next;
		}
	}
	else
		printf("EMPTY LIST\n");
}


List* list_lookup(List* list, char* text){
	if(list == NULL)
		return NULL;
	else{
		List* aux = list;
		while(aux != NULL){	
			if(strcmp(aux->text, text) == 0)
				return aux;
			else
				aux = aux->next;
		}
		return NULL;
	}	
}

List* list_remove(List* list, char* text){
	int found =0;
	if(list != NULL){
		List* aux = list;
		List* aux_ant = list;
		while(aux != NULL && !found){	
			if(strcmp(aux->text, text) == 0){
				found = 1;
				if(aux==list && aux_ant==list && aux->next!=NULL){
					list = aux->next;
					aux = NULL;
				}
				else if(aux==list && aux_ant==list && aux->next==NULL){
					list = NULL;
					aux = NULL;
				}
				else if(aux->next==NULL && aux_ant==list){
					aux_ant->next = aux->next;
					aux = NULL;
					list = aux_ant;
				}				
				else{
					aux_ant->next = aux->next;
					aux = NULL;
				}	
			}
			if(!found){
				if(aux != list ) 		
					aux_ant = aux_ant->next;
				aux = aux->next;
			}
		}
	}	
	return list;
}
