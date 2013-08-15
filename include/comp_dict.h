typedef struct comp_dict
{
	char* key;
	char* value;
	struct comp_dict* next;
}DICT;


void dict_init(void); // Initializes The dictionary

void dict_insert(char* key_in, char* value_in);

void dict_print(void);

char* dict_lookup(char* key_in);

void dict_remove(char* key_in);

void dict_replace(char* key_in,char* value_in);
