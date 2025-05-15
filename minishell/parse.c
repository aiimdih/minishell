#include "./libft/libft.h"
#include "minishell.h"
#include "./get_next_line/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>

/**/
/*typedef struct {*/
/*    char **data;*/
/*    int size;*/
/*    int capacity;*/
/*} t_push_back;*/
/**/
/*void push_back(t_push_back *arr)*/
/*{*/
/**/
/*}*/
/**/
/*int main() */
/*{*/
/*    StringArray arr;*/
/*	push_back(arr, "hello");*/
/*    return 0;*/
/*}*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 1024

typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC
} t_token_type;

typedef struct s_command {
	char **args;
	char *infile;
	char *outfile;
	struct s_command *next;
} t_command;

typedef struct s_token {
    t_token_type type;
    char *data;
} t_token;

// Define the struct for the dynamic string array
typedef struct {
    char **data;
    int size;
    int capacity;
} StringArray;

typedef struct s_env {
    char **env_list;
    int env_index;
    int size;
} t_env;

typedef struct node_en 
{
	char *data;
	struct node_en* next;
} node_env;

// Initialize the dynamic string array with a given capacity
void initStringArray(StringArray *arr, int capacity) {
    arr->data = (char **)malloc(capacity * sizeof(char *));
    if (arr->data == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    arr->size = 0;
    arr->capacity = capacity;
}

// Add a string to the dynamic array (make a copy of the string)
void addString(StringArray *arr, const char *str) {
    // Resize if necessary
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        char **temp = (char **)realloc(arr->data, arr->capacity * sizeof(char *));
        if (temp == NULL) {
            fprintf(stderr, "Memory reallocation failed!\n");
            exit(EXIT_FAILURE);
        }
        arr->data = temp;
    }
    arr->data[arr->size] = strdup(str);
    if (arr->data[arr->size] == NULL) {
        fprintf(stderr, "String duplication failed!\n");
        exit(EXIT_FAILURE);
    }
    arr->size++;
}

// Get a string from the array at the given index
char *getString(StringArray *arr, int index) {
    if (index < 0 || index >= arr->size) {
        fprintf(stderr, "Index out of bounds!\n");
        return NULL;
    }
    return arr->data[index];
}

// Free all allocated memory associated with the string array
void freeStringArray(StringArray *arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->data[i]);  // Free each string
    }
    free(arr->data);  // Free the array of pointers
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

char	*push_str(char *str, char c)
{
	int i;
	int len;
	char *new_ptr;

	if (c == '\0')
		return (str);
	i = 0;
	len = 0;
	if (str)
		len = ft_strlen(str);
	new_ptr = ft_realloc(str, len, len + 2);
	new_ptr[len] = c;
	new_ptr[len + 1] = '\0';
	return new_ptr; 
}

int lexer(char *cmds, t_token *tokens, int tokens_index)
{
	int i;
	/*int end;*/
	int start;
	i = 0;

	while (cmds[i])
	{
		if (isspace(cmds[i]))
		{
			i++;
			continue;
		}
		if (cmds[i] == '|')
		{
			tokens[tokens_index].type = TOKEN_PIPE; 
			tokens[tokens_index].data = strdup("|");
			tokens_index++;
			i++;
		}
		else if (cmds[i] == '>')
		{
			if (cmds[i + 1] == '>')
			{
				tokens[tokens_index].type = TOKEN_APPEND; 
				tokens[tokens_index].data = strdup(">>");
				i++;
			}
			else
			{
				tokens[tokens_index].type = TOKEN_REDIR_OUT; 
				tokens[tokens_index].data = strdup(">");
			}
			tokens_index++;
			i++;
		}
		else if (cmds[i] == '<')
		{
			if (cmds[i + 1] == '<')
			{
				tokens[tokens_index].type = TOKEN_APPEND; 
				tokens[tokens_index].data = strdup("<<");
				i++;
			}
			else 
			{
				tokens[tokens_index].type = TOKEN_REDIR_IN; 
				tokens[tokens_index].data = strdup("<");
			}
			tokens_index++;
			i++;
		}
		/*else if (cmds[i] == '=')*/
		/*{*/
		/*	start = i;*/
		/*	if (i <= 0)*/
		/*		exit(EXIT_FAILURE);*/
		/*	while (ft_strchr("><| ", cmds[start]) == 0)*/
		/*		start--;*/
		/*	end = start;*/
		/*	while (cmds[end] && ft_strchr("><| ", cmds[end]) == 0)*/
		/*		end++;*/
		/*	env_lis	= ft_realloc(env_list, (size - 1) * sizeof(char *), */
		/*			size * sizeof(char *));*/
		/*	env_list[env_index] = ft_substr(cmds, start, end - start);*/
		/*}*/
		else 
		{
			tokens[tokens_index].type = TOKEN_WORD; 
			start = i;
			while (cmds[i] && ft_strchr("><| ", cmds[i]) == 0)
				i++;
			tokens[tokens_index].data = strndup(cmds + start, i - start);
			tokens_index++;
		}
	}
	return tokens_index;
}

/*int io_redirect(t_token tokens, int i)*/
/*{*/
/*	if (tokens[i].type == TOKEN_REDIR_IN && tokens[i + 1].type != TOKEN_WORD)*/
/*		return 0;*/
/*	return 1;*/
/*}*/
/**/
/*int simple_command(t_token tokens, int i)*/
/*{*/
/*	if (!io_redirect(tokens, i))*/
/*		return 0;*/
/*	else if (tokens[i].type == TOKEN_WORD)*/
/*			return 1;*/
/*	else*/
/*		return 0;*/
/*}*/
/**/
/*int pipeline(t_token tokens, int i)*/
/*{*/
/*	simple_command(tokens, i);*/
/*}*/

int grammer(t_token *tokens, int tokens_index)
{
	int i;
	i = 0;

	while (i < tokens_index)
	{
		printf("index --> %d number of tokens -> %d\n",i,  tokens_index );
		if (tokens[i].type == TOKEN_REDIR_IN || tokens[i].type == TOKEN_REDIR_OUT 
			||tokens[i].type == TOKEN_APPEND || tokens[i].type == TOKEN_HEREDOC) 
		{
			printf("l\n");
			if (i > tokens_index - 2|| tokens[i + 1].type != TOKEN_WORD)
				return 0;
		}
		else if (i == 0 && tokens[i].type != TOKEN_WORD && (tokens[i].type != TOKEN_REDIR_IN ||
			tokens[i].type != TOKEN_REDIR_OUT || tokens[i].type != TOKEN_HEREDOC || 
			tokens[i].type != TOKEN_APPEND))
			return 0;
		else if (tokens[i].type == TOKEN_PIPE && (i == tokens_index - 1 
				|| tokens[i - 1].type != TOKEN_WORD || tokens[i + 1].type != TOKEN_WORD))
				return 0;
		i++;
	}
	printf("numer of tockens --> %d\n", tokens_index);
	return 1;
}

t_command *create_command() 
{
    t_command *cmd = malloc(sizeof(t_command));
    cmd->args = malloc(sizeof(char *) * 100);
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->next = NULL;
    return cmd;
}

t_command *parser(t_token *tokens, int tokens_index, t_env *env_)
{
	t_command *head =  create_command();
	t_command *current = head;
	(void)env_;
	/*int start;*/
	/*int end;*/
	int args_index = 0;
	int i;
	i = 0;

	/*printf("%d ->>\n", tokens_index);*/
	while (i < tokens_index)
	{
		

		if (tokens[i].type == TOKEN_PIPE)
		{
			current->args[args_index] = NULL;
			current->next = create_command();
			current = current->next;
			args_index = 0;
		}
		else if (tokens[i].type == TOKEN_REDIR_OUT) 
		{
			current->outfile = tokens[++i].data; 
		}
		else if (tokens[i].type == TOKEN_REDIR_IN) 
		{
			current->infile = tokens[++i].data; 
		}
		else {
			if (ft_strcmp(tokens[i].data, "export") == 0)
			{
				if (i < tokens_index - 1  && ft_strchr(tokens[i + 1].data, '='))
				{
					env_->env_list	= ft_realloc(env_->env_list, (env_->size - 1) * sizeof(char *), 
								env_->size * sizeof(char *));
					env_->size ++;
					env_->env_list[env_->env_index++] = strdup(tokens[i + 1].data);
					for (i = 0; env_->env_list[i]; i++)
						printf("%s---\n", env_->env_list[i]);
					i++;
				}
			}
			else 
				current->args[args_index++] = tokens[i].data;
			/*}*/
			/*printf("%s ->>\n", tokens[i].data);*/
		}
		i++;
	}
	current->args[args_index] = NULL;
	return head;
}

void print_commands(t_command *cmd) {
    int i = 1;
    while (cmd) {
        printf("Command %d:\n", i++);
        for (int j = 0; cmd->args[j]; j++) {
            printf("  Arg: %s\n", cmd->args[j]);
        }
        if (cmd->infile)
            printf("  Infile: %s\n", cmd->infile);
        if (cmd->outfile)
            printf("  Outfile: %s\n", cmd->outfile);
        cmd = cmd->next;
    }
}

void tockenizer(char *cmds, t_env *env_)
{
	int tokens_index = 0;
	t_token tokens[MAX_TOKENS];
	int i;
	i = lexer(cmds, tokens, tokens_index);
	for (int i = 0; tokens[i].data; i++)
		printf("token --> number %d %s type ==> %d \n", i, tokens[i].data, tokens[i].type);
	if (!grammer(tokens, i))
		printf("error\n");
	t_command *parsed = parser(tokens, i,  env_);
	print_commands(parsed);
}

int	count_args_len(char **args, int ac)
{
	int	len;
	int	j;

	len = 0;
	j = 1;
	while (j < ac)
	{
		len += ft_strlen(args[j]);
		j++;
	}
	return (len + j);
}

char	*merge_args(char **args, int ac)
{
	int		i;
	char	*merged_args;

	merged_args = malloc((count_args_len(args, ac) + 1) * sizeof(char));
	merged_args[0] = '\0';
	i = 1;
	while (i < ac)
	{
		ft_strcat(merged_args, args[i]);
		ft_strcat(merged_args, " ");
		i++;
	}
	return (merged_args);
}

node_env *create_node(const char *env_str)
{
	node_env *new_node = malloc (sizeof(node_env));
	new_node->data = strdup(env_str);
	new_node->next = NULL;
	return new_node;
}

void appendNode(node_env** head_ref, const char *env_str) 
{
	node_env* new_node = create_node(env_str);
	node_env* temp;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    temp = *head_ref;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
	printf("k\n");
}

void printList(node_env* node) {
    while (node != NULL) {
        printf("%s -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main(int ac, char **av, char *env[]) 
{
	char *cmds;
	(void)ac;
	(void)av;
	t_env *env_ = malloc(sizeof(t_env));
	int i;
	env_->size = 2;
	env_->env_index = 0;
	
	i = 0;
	env_->env_list = malloc(sizeof(char *) * env_->size);
	/*cmds = merge_args(av, ac);*/
	while (env[env_->env_index])
	{
		env_->env_list[env_->env_index] = strdup(env[env_->env_index]);
		env_->size++;
		env_->env_list	= ft_realloc(env_->env_list, (env_->size - 1) * sizeof(char *), 
					env_->size * sizeof(char *));
		env_->env_index++;
	}
	for (i = 0; env_->env_list[i]; i++)
		printf("%s---\n", env_->env_list[i]);
	while (1)
	{
		cmds = readline("minishell> ");
		if (!cmds)
			break;
		tockenizer(cmds, env_);
	}
    /*StringArray arr;*/
    /*initStringArray(&arr, 2);*/
    /**/
    /*addString(&arr, "hello");*/
    /**/
    /*// Print out the strings in the array*/
    /*for (int i = 0; i < arr.size; i++) {*/
    /*    printf("%s\n", getString(&arr, i));*/
    /*}*/
    /**/
    /**/
    /*// Clean up the allocated memory*/
    /*freeStringArray(&arr);*/
    return 0;
}
