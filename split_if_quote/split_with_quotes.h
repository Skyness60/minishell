/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:08:27 by sperron           #+#    #+#             */
/*   Updated: 2024/10/21 02:32:07 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_WITH_QUOTES_H
# define SPLIT_WITH_QUOTES_H
# include "../minishell.h"
# include <stdio.h>

int			is_quote(char c, int *status_quotes);
int			is_separator(char c, char *sep);
char		**valid(char **result, char *s, int count);
char		**split_with_quotes(char *str, char *sep);
void		valid2(char **result, char *s, int count, int i);
void		trim_newline(char *str);
char		*allocate_result(char *result);
char		*concat_result(char *result_and_str, char *str, int is_last_line);
char		*prompt_command_singlequote(char *result);
char		*prompt_command_doublequote(char *result);
void		remove_char_from_string(char *read, char *write, \
			char char_to_remove, int i);
size_t		get_word_len(char *str, char *sep);
void		count_word_spe(char *str, char *sep, int *count);
void		tab_str(char **result, char *str, char *sep, int *j);
void		validpipe(char **result, char *s, int i);
char		**split_pipe(char *str, char *sep);
#endif // !SPLIT_WITH_QUOTES_H