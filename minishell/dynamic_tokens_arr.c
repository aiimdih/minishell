#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"


void tokenarr_init(token_array *arr, size_t init_capacity) {
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = init_capacity;
    
    if (init_capacity > 0) {
        arr->data = malloc(init_capacity * sizeof(char*));
        if (!arr->data) exit(EXIT_FAILURE);
    }
}

void tokenarr_push(token_array *arr,t_token_type type, char *str) {
    if (arr->size >= arr->capacity) {
		size_t new_capacity;
		if (arr->capacity == 0) 
			new_capacity = 1;
		else
			new_capacity = arr->capacity * 2;
        t_token *new_data = realloc(arr->data, new_capacity * sizeof(t_token));
        if (!new_data) 
			exit(EXIT_FAILURE);
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
	arr->data[arr->size].type = type;
    arr->data[arr->size].data = str;
    arr->size++;
}

void tokenarr_free(token_array *arr) {
    for (size_t i = 0; i < arr->size; i++)
        free(arr->data[i].data);  
    free(arr->data);         
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}
