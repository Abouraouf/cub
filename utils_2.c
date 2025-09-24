/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:02:28 by eabourao          #+#    #+#             */
/*   Updated: 2025/09/24 12:54:19 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < (n - 1) && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	size_src;
	size_t	i;

	size_src = ft_strlen(src);
	if (size == 0)
		return (size_src);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (size_src);
}

int	ft_check_duplicates(int	*flags)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 5)
	{
		j = i + 1;
		while (j < 5)
		{
			if (flags[i] == flags[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	find_nswe(char *str)
{
	if (!ft_strncmp(str, "NO ", 3))
		return (1);
	if (!ft_strncmp(str, "SO ", 3))
		return (2);
	if (!ft_strncmp(str, "WE ", 3))
		return (3);
	if (!ft_strncmp(str, "EA ", 3))
		return (4);
	if (!ft_strncmp(str, "F ", 2))
		return (5);
	return (0);
}

void	skip_spaces(char *str, int *i)
{
	if (!str)
		return ;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}