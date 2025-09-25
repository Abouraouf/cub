/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:12:00 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/25 15:13:50 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free(str);
}

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (j == 0 && *str != c)
		{
			j = 1;
			i++;
		}
		else if (j == 1 && *str == c)
			j = 0;
		str++;
	}
	return (i);
}

static int	ft_sstrlen(const char *str, char c, int *i)
{
	int	s;

	s = 0;
	while (str[*i] == c && str[*i])
		(*i)++;
	while (str[*i] != c && str[*i])
	{
		s++;
		(*i)++;
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		j;
	int		a;
	int		co;

	co = ft_count_words(s, c);
	j = 0;
	dest = (char **)malloc(sizeof(char *) * (co + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (j < co)
	{
		a = ft_sstrlen(s, c, &i);
		dest[j] = malloc(sizeof(char) * a + 1);
		if (!dest[j])
		{
			ft_free(dest);
			return (NULL);
		}
		ft_strlcpy(dest[j++], s + (i - a), a + 1);
	}
	dest[j] = NULL;
	return (dest);
}
