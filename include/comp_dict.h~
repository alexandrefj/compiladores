typedef struct comp_dict
{
	int key;
	char* value;
	struct comp_dict* next;
}DICT;


DICT* dict_init(void); // Initializes The dictionary

DICT* dict_insert(DICT* dictionary,int key_in, char* value_in);

void dict_print(DICT* dictionary);

char* dict_lookup(DICT* dictionary,int key_in);

DICT* dict_remove(DICT* dictionary,int key_in);

DICT* dict_replace(DICT* dictionary,int key_in,char* value_in);
