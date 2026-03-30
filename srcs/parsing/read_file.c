/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:07:56 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/30 10:27:06 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_list	*loop_read(char *line, int fd)
{
	t_list	*new_node;
	t_list	*head;

	head = NULL;
	while (line)
	{
		new_node = ft_lstnew(line);
		if (!new_node)
		{
			free(line);
			ft_lstclear(&head, free);
			break ;
		}
		ft_lstadd_back(&head, new_node);
		line = get_next_line(fd);
	}
	close(fd);
	return (head);
}


t_list	*read_cub_file(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open file.\n");
		return (NULL);
	}
	line = get_next_line(fd);
	return (loop_read(line, fd));
}
