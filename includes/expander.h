/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:12:24 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/10 01:12:35 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/parser.h"

typedef struct s_env
{
	char			*data;
	int				has_value;
	struct s_env	*next;
}					t_env;

typedef struct s_expander
{
	t_env			*env;
	unsigned int	exit_s;
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
void	expand_ast(t_parser *ast, t_expander *exp);

void	free_args(char **args);

#endif
