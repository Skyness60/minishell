/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:13:09 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/19 14:29:09 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_memory(char **dest)
{
	int	i;

	i = 0;
	while (dest[i] != 0)
	{
		free(dest[i]);
		i++;
	}
	free (dest);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	compteur;

	i = 0;
	compteur = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i])
		{
			if ((s[i] == c && s[i + 1] != c) || (s[i + 1] == '\0'))
				compteur ++;
			i++;
		}
	}
	return (compteur);
}

static char	*ft_write_word(char const *s, char	*dest, char c)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	ft_write_split(char **dest, char const *s, char c)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		j = 0;
		if (s[i] == c)
			i++;
		else
		{
			while (s[i + j] != c && s[i + j] != '\0')
				j++;
			dest[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (!dest[word])
				return (-1);
			ft_write_word(s + i, dest[word], c);
			i += j;
			word++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**dest;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	dest = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dest)
		return (NULL);
	dest[words] = NULL;
	if (ft_write_split(dest, s, c) == -1)
	{
		ft_free_memory(dest);
		return (NULL);
	}
	return (dest);
}

// void main()
// {
// 	int i;
// 	char *s = "   ";
// 	char c = ' ';
// 	char **dest;
// 	i = 0;
// 	dest = ft_split(s, c);
// 	while (dest[i] != 0)
// 		printf("%s\n", dest[i++]);
// 	ft_free_memory(dest);
// }
