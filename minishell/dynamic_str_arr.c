#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;    
    size_t size;    
    size_t capacity; 
} StringArray;

void strarr_init(StringArray *arr, size_t init_capacity) {
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = init_capacity;
    
    if (init_capacity > 0) {
        arr->data = malloc(init_capacity * sizeof(char*));
        if (!arr->data) exit(EXIT_FAILURE);
    }
}

void strarr_push(StringArray *arr, const char *str) {
    if (arr->size >= arr->capacity) {
		size_t new_capacity;
		if (arr->capacity == 0) 
			new_capacity = 1;
		else
			new_capacity = arr->capacity * 2;
        char **new_data = realloc(arr->data, new_capacity * sizeof(char*));
        if (!new_data) exit(EXIT_FAILURE);
        
        arr->data = new_data;
        arr->capacity = new_capacity;
    }
    
    arr->data[arr->size] = strdup(str);
    if (!arr->data[arr->size]) exit(EXIT_FAILURE);
    arr->size++;
}

void strarr_free(StringArray *arr) {
    for (size_t i = 0; i < arr->size; i++)
        free(arr->data[i]);  
    free(arr->data);         
    arr->data = NULL;
    arr->size = arr->capacity = 0;
}
