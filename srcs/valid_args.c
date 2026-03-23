/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:27:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/23 11:35:52 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	valid(char**argv, t_infoMaps data)
{
	t_list		*head;
	t_list		*new_node;
	int			fd;
	char		*content;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		(void)write(2, "Error\nCould not open file.\n", 28);
		return (1);
	}
	init_maps(&data);
	head = NULL;
	while ((content = get_next_line(fd)))
	{
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			free(content);
			break;
		}
		ft_lstadd_back(&head, new_node);
	}
	close(fd);
	return (0);
}
