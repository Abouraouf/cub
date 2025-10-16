/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:02:28 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/16 13:14:41 by eabourao         ###   ########.fr       */
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

int	ft_check_duplicates(int	*flags)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 6)
	{
		j = i + 1;
		while (j < 6)
		{
			if (flags[i] == flags[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	find_nswe(char *str, t_cub3d *info, int i)
{
	if (!ft_strncmp(str, "NO ", 3))
		return (1);
	if (!ft_strncmp(str, "SO ", 3))
		return (2);
	if (!ft_strncmp(str, "WE ", 3))
		return (3);
	if (!ft_strncmp(str, "EA ", 3))
		return (4);
	if (info)
	{
		if (!ft_strncmp(str, "F ", 2))
			return (info->floor = i, 5);
		if (!ft_strncmp(str, "C ", 2))
			return (info->ceiling = i, 6);
	}
	return (0);
}

void	skip_spaces(char *str, int *i)
{
	if (!str)
		return ;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

void	order_xpm(t_cub3d *info)
{
	int	i;
	int	j;
	int placement;

	i = 0;
	info->xpm_inorder = malloc(sizeof(char *) * 5);
	if (!info->xpm_inorder)
		return (free_in_case(info, 1));
	while (info->first_lines[i])
	{
		placement = find_nswe(info->first_lines[i], NULL,j);
		j = 0;
		skip_spaces(info->first_lines[i], &j);
		if (placement > 0 && placement < 5)
		{
			info->xpm_inorder[placement - 1] = info->xpm_files[i];
		}
		i++;
	}
	info->xpm_inorder[4] = NULL;
}