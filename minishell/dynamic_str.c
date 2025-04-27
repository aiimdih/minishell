#include "./libft/libft.h"
#include "minishell.h"
#define INIT_CAPACITY 16

t_dynstr *dynstr_new(void)
{
    t_dynstr *str = malloc(sizeof(t_dynstr));
    if (!str)
        return NULL;
    str->data = malloc(INIT_CAPACITY);
    if (!str->data)
    {
        free(str);
        return NULL;
    }
    str->len = 0;
    str->capacity = INIT_CAPACITY;
    str->data[0] = '\0';
    return str;
}

void dynstr_free(t_dynstr *str)
{
    if (str)
    {
        free(str->data);
        free(str);
    }
}

int dynstr_expand(t_dynstr *str, size_t needed)
{
    if (str->len + needed + 1 > str->capacity)
    {
        size_t new_capacity = str->capacity * 2;
        while (new_capacity < str->len + needed + 1)
            new_capacity *= 2;

        char *new_data = realloc(str->data, new_capacity);
        if (!new_data)
            return 0;

        str->data = new_data;
        str->capacity = new_capacity;
    }
    return 1;
}

int dynstr_push_char(t_dynstr *str, char c)
{
    if (!dynstr_expand(str, 1))
        return 0;

    str->data[str->len++] = c;
    str->data[str->len] = '\0';
    return 1;
}

int dynstr_push_str(t_dynstr *str, const char *s)
{
    size_t slen = ft_strlen(s);
    if (!dynstr_expand(str, slen))
        return 0;

    ft_memcpy(str->data + str->len, s, slen);
    str->len += slen;
    str->data[str->len] = '\0';
    return 1;
}

