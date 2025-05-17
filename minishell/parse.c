#include "./libft/libft.h"
#include "minishell.h"
#include "./get_next_line/get_next_line.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
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


typedef struct node_en 
{
	char *data;
	struct node_en* next;
} node_env;


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

t_command *parser(t_token *tokens, int tokens_index, StringArray *env_)
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
		else 
		{
			/*if (ft_strcmp(tokens[i].data, "export") == 0)*/
			/*{*/
			/*	if (i < tokens_index - 1  && ft_strchr(tokens[i + 1].data, '='))*/
			/*	{*/
			/*		strarr_push(env_, tokens[i + 1].data);*/
			/*		for (i = 0; env_->data[i]; i++)*/
			/*			printf("%s---\n", env_->data[i]);*/
			/*		i++;*/
			/*	}*/
			/*	else {*/
			/*		current->args[args_index++] = tokens[i].data;*/
			/*	}*/
			/*}*/
			/*else {*/
			/*	if (ft_strchr(tokens[i].data, '$') && (ft_strlen(tokens[i].data) > 1))*/
			/*	{*/
			/*		char *tmp = grep */
			/*	}*/
			/*}*/
			/*else */
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

int get_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return 0;
	return i;
}

char *get_env(StringArray *env_, char *target)
{
	size_t end;
	int i;
	char *result;

	i = 0;
	while (env_->data[i])
	{
		printf("is this the line of env --> %s\n", env_->data[i]);
		end = get_equal(env_->data[i]);
		if (ft_strncmp((env_->data[i]), target, end) == 0 &&
			ft_strlen(target) == end)
		{
			result = ft_strdup(env_->data[i] + (end + 1));
			return result;
		}
		i++;
	}
	return NULL;
}

void expansion(t_command *cmds, StringArray *env_)
{
	t_command *current = cmds;
	char *tmp;
	int i ;
	while (current)
	{
		i = 0;
		while (current->args[i])
		{
			if ((ft_strcmp(current->args[i], "export") == 0) && current->args[i + 1] !=
				NULL && (ft_strchr(current->args[i + 1], '=') != 0))
			{
				printf("ll-----------------------------------------\n");
				i++;
				while (current->args[i] && strchr(current->args[i], '='))
				{
					strarr_push(env_, current->args[i]);
					i++;
				}
				for (int j = 0; env_->data[j]; j++)
					printf("%s---\n", env_->data[j]);
			}
			else if (ft_strchr(current->args[i], '$') && 
				(ft_strlen(current->args[i]) > 1))
			{
				tmp = get_env(env_, (current->args[i] + 1));
				if (tmp)
				{
					current->args[i]
					printf("%s\n", tmp);
				}
			}
			i++;
		}
		current = current->next;
	}
}

void tockenizer(char *cmds, StringArray *env_)
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
	expansion(parsed, env_);
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
	StringArray tokens;
	StringArray env_;
	(void)ac;
	(void)av;
	int i;
	
	strarr_init(&tokens, 0);
	strarr_init(&env_, 0);
	i = 0;
	/*cmds = merge_args(av, ac);*/
	while (env[env_.size])
	{
		printf("env --> %zu\n", env_.size);
		strarr_push(&env_, env[env_.size]);
	}
	for (i = 0; env_.data[i]; i++)
		printf("%s---\n", env_.data[i]);
	while (1)
	{
		cmds = readline("minishell> ");
		if (!cmds)
			break;
		tockenizer(cmds, &env_);
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
