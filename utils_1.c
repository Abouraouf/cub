/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabourao <eabourao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:40:08 by eabourao          #+#    #+#             */
/*   Updated: 2025/10/19 15:34:32 by eabourao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_open_xpm(t_cub3d *info)
{
	int		fd[4];
	int		i;

	i = 0;
	while (info->xpm_files[i])
	{
		fd[i] = open(info->xpm_files[i], O_RDONLY);
		if (fd[i] < 0)
		{
			close(fd[0]);
			close(fd[1]);
			close(fd[2]);
			close(fd[3]);
			info->error = 1;
		}
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
}

int	skip_from_end(char *str, int *i)
{
	while (str[(*i)++])
	{
	}
	(*i)--;
	while (*i > 0 && str[(*i)--] == ' ')
	{
	}
	return (*i);
}

void	trim_xpm(t_cub3d *info)
{
	int	i;
	int	j;
	int	start;
	int	finish;
	int	counter;

	if (!info->first_lines)
		return ;
	finish = 0;
	counter = 0;
	i = 0;
	info->xpm_files = malloc(sizeof(char *) * 5);
	while (counter < 4)
	{
		j = 0;
		skip_spaces(info->first_lines[i], &j);
		if (find_nswe(info->first_lines[i] + j, info, j) == 5
			|| find_nswe(info->first_lines[i] + j, info, j) == 6)
		{
			i++ ;
			continue ;
		}
		while (info->first_lines[i][j] && info->first_lines[i][j] != ' ')
			j++;
		skip_spaces(info->first_lines[i], &j);
		start = j;
		finish = skip_from_end(info->first_lines[i], &j);
		info->xpm_files[counter] = ft_substr(info->first_lines[i], start, finish);
		counter++;
		i++;
	}
	info->xpm_files[counter] = NULL;
	// for (int i = 0; i < 4; i++)
	// {
	// 	printf("%s\n", info->xpm_files[i]);
	// }
	// if (info->xpm_files[4] == NULL)
	// 	printf("done\n");
	// printf("%d", counter);
	// exit(0);
	return (info->xpm_files[counter] = NULL, ft_open_xpm(info), order_xpm(info),
		find_player_l(info));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t				i;
	size_t				lenght;
	char				*sub;

	if (!s)
		return (NULL);
	lenght = ft_strlen(s);
	if (start >= lenght)
		return (ft_strdup(""));
	if (lenght - start < len)
		i = lenght - start;
	else
		i = len;
	sub = (char *)malloc (sizeof(char) * i + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, i + 1);
	return (sub);
}

void	ft_read_all(int fd, t_cub3d *info)
{
	char	*tmp;
	char	*tmp_join;

	tmp_join = NULL;
	info->map_coord = NULL;
	info->fd = fd;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		tmp_join = info->map_coord;
		info->map_coord = ft_strjoin(info->map_coord, tmp);
		free(tmp);
		free(tmp_join);
		tmp = NULL;
	}
}
