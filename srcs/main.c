/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:14:53 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/17 15:43:32 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	t_infoMaps	data;
	int			fd;
	char		*content;
	(void)argc;
	(void)argv;

	fd = open("maps/default.cub", O_RDONLY);
	init_maps(&data);
	while ((content = get_next_line(fd)))
	{
		ft_lstnew((char *)content);
		free (content);
	}
	return (0);
}
