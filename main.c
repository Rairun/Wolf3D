/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaprono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 10:32:53 by psaprono          #+#    #+#             */
/*   Updated: 2018/06/09 10:33:49 by psaprono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woof.h"

int     main(int ar, char **av)
{
	t_woof	*wof;

	if ((wof = (t_woof *)malloc(sizeof(t_woof))) == NULL)
	{
		ft_putendl("Error: malloc wof");
		return (0);
	}
	if (check_arg(ar, av, &(wof->fd)))
	{
		// ft_putendl("OK");
		if (get_file_data(wof))
		{
			ft_putstr("width = ");
			ft_putnbr(wof->map->width);
			ft_putstr(", height = ");
			ft_putnbr(wof->map->height);
			ft_putchar('\n');
			int *mas = wof->map->map;
			for (int i = 0; i < wof->map->height; i++)
			{
				for (int j = 0; j < wof->map->width; j++)
					printf("%d ", mas[wof->map->width * i + j]);
				printf("\n");
			}
			init_default(wof);
			lets_play(wof);
			mlx_loop(wof->mlx);
		}
	}
	// system("leaks wolf3d");
	return (0);
}
