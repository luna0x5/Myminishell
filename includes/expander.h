/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:12:24 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/27 01:30:06 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/parser.h"

// the structure of the list of environment variables
typedef struct s_env
{
	char			*key;
	char			*value;
	char			*data;
	struct s_env	*next;
}					t_env;

// the structure used in expanding
typedef struct s_expander
{
	t_env			*env;
	unsigned char	exit_s;
}					t_expander;

// added for norminette since multiple variables are used in quotes fcts
typedef struct s_quote
{
	char	**result;
	char	*arg;
	int		*i;
	char	quote_type;
}			t_quote;

// check if the character is a valid character for expanding
int		ft_isvalid(char c);

// used to make the functions smaller
void	initialize_quote(t_quote *quote, int *i, char **result, char *arg);
char	*append_string(char *result, const char *to_append);
void	append_single_char(t_quote *quote, int *i, char **result);

// utils used in expanding
char	*get_value(char *data);
char	*ft_getenv(char *name, t_expander *exp);
char	*expand_var(char *arg, t_expander *exp);

// the expander handlers
void	handle_heredoc_ex(t_parser *ast, t_expander *exp);
void	handle_quoted_string(t_quote *q, t_expander *exp);
char	*handle_variable_expansion(char *arg, int *i, t_expander *exp);
void	process_string(t_parser *ast, t_expander *exp);

// calculating the len of the key and the value
int		count_equal_len(char *data);
int		count_value_len(char *data);

// the main function of the expander
void	expand_ast(t_parser *ast, t_expander *exp);

// to free 2d strings
void	free_args(char **args);

#endif
