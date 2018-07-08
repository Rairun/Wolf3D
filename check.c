/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaprono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 10:39:44 by psaprono          #+#    #+#             */
/*   Updated: 2018/06/09 10:39:46 by psaprono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woof.h"

bool	check_arg(int argc, char **argv, int *fd)
{
	if (argc != 2)
	{
		ft_putendl("Usage: ./wolf3d <filename>");
		return (0);
	}
	else
	{
		if ((*fd = open(argv[1], O_RDONLY)) < 0)
		{
			ft_putstr("No file ");
			ft_putendl(argv[1]);
			return (0);
		}
	}
	return (1);
}

bool	allocate_map_array(t_woof *wof)
{
	int	*map;

	if ((map = (int *)malloc(wof->map->width *
		wof->map->height * sizeof(int))) == NULL)
	{
		ft_putendl("Error: malloc map of textures");
		return (0);
	}
	wof->map->map = map;
	return (1);
}

bool	check_height(t_woof *wof, int height)
{
	if (wof->map->height >= height)
		return (1);
	return (0); 
}

int		get_width_of_line(char *line)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (*(line + i))
	{
		if (*(line + i) >= '0' && *(line + i) <= '9')
		{
			len++;
			while (*(line + i) && *(line + i) != ' ')
				i++;
		}
		if (*(line + i))
			i++;
	}
	return (len);
}

bool	check_width(t_woof *wof, char *line)
{
	if (wof->map->width == get_width_of_line(line))
		return (1);
	return (0);
}

bool	set_line(t_woof *wof, char *line, int height)
{
	int		i;
	int		*mas;
	int		width;
	char	**arr;

	if ((arr = ft_strsplit(line, ' ')) == NULL)
	{
		ft_putendl("Error: split");
		return (0);
	}
	i = -1;
	mas = wof->map->map;
	width = wof->map->width;
	while (arr[++i])
		mas[(height - 1) * width + i] = ft_atoi(arr[i]);
	ft_arrfree(arr);
	return (1);
}

bool	get_textures(t_woof	*wof)
{
	int		height;
	char	*line;

	height = 0;
	while (get_next_line(wof->fd, &line) > 0)
	{
		if (!check_height(wof, ++height) || !check_width(wof, line) ||
			!set_line(wof, line, height))
		{
			// ft_putstr("Mismatch or crash ->");
			// ft_putnbr(height);
			// ft_putendl(" line");
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (height != wof->map->height)
	{
		ft_putendl("Mismatch height");
		return (0);
	}
	// ft_putendl("Textures are OK");
	return (1);
}

bool	get_inside_data(t_woof *wof)
{
	char	*line;
	int		check;

	check = 0;
	if (get_next_line(wof->fd, &line) > 0)
	{
		if (ft_strnstr(line, "#inside", 7) == NULL)
			ft_putendl("can't find map filling");
		else
		{
			if (allocate_map_array(wof) && get_textures(wof))
				check = 1;
		}
		ft_strdel(&line);
	}
	return (check);
}

bool	get_file_data(t_woof *wof)
{
	int		res;
	char	*line;

	if ((res = get_next_line(wof->fd, &line)) > 0)
	{
		// ft_putendl("Can read file");
		if (get_map_data(wof, line) && get_inside_data(wof))
			return (1);
		else
			return (0);
	}
	if (res == -1)
	{
		ft_putendl("Can't read file");
		return (0);
	}
	return (1);
}
