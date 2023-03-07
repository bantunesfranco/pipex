/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_args.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:47:01 by bfranco       #+#    #+#                 */
/*   Updated: 2022/12/11 12:40:05 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/pipex_bonus.h"

static int	check_quotes(char *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	return (i);
}

static int	get_arr(char **arr, char *str, char sep)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (str[i] != sep)
		{
			j = i;
			while (str[j] && str[j] != sep)
			{
				if (str[j] == 34 || str[j] == 39)
					j = check_quotes(str, str[j], j + 1);
				else
					j++;
			}
			*arr = ft_calloc(sizeof(**arr), j - i + 1);
			if (!*arr)
				return (0);
			ft_memcpy(*arr, str + i, j - i);
			arr++;
			i = j - 1;
		}
	}
	return (1);
}

static int	count_words(char *str, char sep)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (str[i] == sep)
		i++;
	while (str[i])
	{
		if (str[i] != sep)
		{
			nb_words++;
			while (str[i] && str[i] != sep)
			{
				if (str[i] == 34 || str[i] == 39)
					i = check_quotes(str, str[i], i + 1);
				else
					i++;
			}
		}
		if (str[i])
			i++;
	}
	return (nb_words);
}

char	**ft_split_args(char *str, char sep)
{
	char	**arr;

	if (!str)
		return (NULL);
	arr = ft_calloc(sizeof(*arr), count_words(str, sep) + 1);
	if (!arr)
		return (NULL);
	if (!get_arr(arr, str, sep))
		return (ft_free_arr(arr), NULL);
	return (arr);
}
