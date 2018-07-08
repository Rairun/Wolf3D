/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaprono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:18:45 by psaprono          #+#    #+#             */
/*   Updated: 2018/06/10 12:18:47 by psaprono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woof.h"

static bool	get_map_width(t_woof *wof, int *width)
{
	char	*find;
	char	*find1;
	int		check;

	check = 0;
	if (get_next_line(wof->fd, &find) > 0)
	{
		if (ft_strnstr(find, "width:", 7) == NULL)
		{
			ft_putendl("can't find -> width");
			check = 0;
		}
		else
		{
			find1 = ft_strchr(find, ':');
			if ((*width = ft_atoi(find1 + 1)) > 0)
			{
				// ft_putendl("correct width");
				check = 1;
			}
			else
			{
				ft_putendl("incorrect width");
				check = 0;
			}
		}
		ft_strdel(&find);
	}
	return (check);
}

static bool	get_map_height(t_woof *wof, int *height)
{
	char	*find;
	char	*find1;
	int		check;

	check = 0;
	if (get_next_line(wof->fd, &find) > 0)
	{
		if (ft_strnstr(find, "height:", 8) == NULL)
		{
			ft_putendl("can't find -> height");
			check = 0;
		}
		else
		{
			find1 = ft_strchr(find, ':');
			if ((*height = ft_atoi(find1 + 1)) > 0)
			{
				// ft_putendl("correct height");
				check = 1;
			}
			else
			{
				// ft_putendl("incorrect height");
				check = 0;
			}
		}
		ft_strdel(&find);
	}
	return (check);
}

static bool	set_size_of_map(t_woof *wof, int width, int height)
{
	if ((wof->map = (t_map *)malloc(sizeof(t_map))) == NULL)
	{
		ft_putendl("Error: malloc map");
		return (0);
	}
	wof->map->width = width;
	wof->map->height = height;
	// ft_putendl("Map size is set");
	return (1);
}

static bool	get_size_of_map(t_woof *wof)
{	
	int		height;
	int		width;

	if (get_map_height(wof, &(height)) && get_map_width(wof, &(width)))
	{
		// ft_putendl("can find size of map");
		return (set_size_of_map(wof, width, height));
	}
	else
	{
		ft_putendl("can't find size of map");
		return (0);
	}
}

bool	    get_map_data(t_woof *wof, char *line)
{
	if (ft_strnstr(line, "#map", 4) == NULL)
	{
		ft_putendl("can't find -> #map");
		ft_strdel(&line);
		return (0);
	}
	else
	{
		// ft_putendl("can find -> #map");
		ft_strdel(&line);
		get_size_of_map(wof);
		return (1);
	}
}
