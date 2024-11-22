/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:12:24 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/17 13:38:13 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/parser.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*data;
	struct s_env	*next;
}					t_env;

typedef struct s_expander
{
	t_env			*env;
	unsigned char	exit_s;
}					t_expander;

typedef struct s_quote
{
	char	**result;
	char	*arg;
	int		*i;
	char	quote_type;
}			t_quote;

int		ft_isvalid(char c);
char	*expand_var(char *arg, t_expander *exp);
char	*append_string(char *result, const char *to_append);
void	initialize_quote(t_quote *quote, int *i, char **result, char *arg);
void	append_single_char(t_quote *quote, int *i, char **result);

void	handle_heredoc_ex(t_parser *ast, t_expander *exp);
void	handle_quoted_string(t_quote *q, t_expander *exp);
char	*handle_variable_expansion(char *arg, int *i, t_expander *exp);
void	process_string(t_parser *ast, t_expander *exp);

char	*ft_getenv(char *name, t_expander *exp);
int		count_equal_len(char *data);
int		count_value_len(char *data);
char	*get_value(char *data);

void	expand_ast(t_parser *ast, t_expander *exp);

void	free_args(char **args);

#endif
