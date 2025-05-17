/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiimdih <aiimdih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:03:35 by aiimdih           #+#    #+#             */
/*   Updated: 2024/12/02 15:35:12 by aiimdih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_dynstr {
    char *data;      
    size_t len;      
    size_t capacity; 
} t_dynstr;

typedef struct {
    char **data;    
    size_t size;    
    size_t capacity; 
} StringArray;

void strarr_init(StringArray *arr, size_t init_capacity);
void strarr_push(StringArray *arr, const char *str);
void strarr_free(StringArray *arr);
t_dynstr *dynstr_new(void);
int dynstr_push_str(t_dynstr *str, const char *s);
void dynstr_free(t_dynstr *str);
int dynstr_push_char(t_dynstr *str, char c);

#endif
