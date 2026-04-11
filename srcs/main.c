/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:14:53 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/30 16:54:22 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	extract_confs(t_list **lst, t_infoMaps *data)
{
	while (*lst)
	{
		if (data->no_texture && data->so_texture && data->ea_texture
			&& data->we_texture && data->ceiling_color != -1
			&& data->floor_color != -1)
			return (1);
		if (!parser_elements((char *)(*lst)->content, data))
		{
			printf("Error\nInvalid configuration element.\n");
			return (0);
		}
		*lst = (*lst)->next;
	}
	return (1);
}

static int	parse_core(t_list *lst, t_infoMaps *data)
{
	if (!lst)
		return (0);
	if (!extract_confs(&lst, data))
		return (0);
	lst = find_map_start(lst);
	if (!lst || ! extract_map(lst, data))
	{
		printf("Error\nMap extraction failed.\n");
		return (0);
	}
	if (!validate_map_char(data))
	{
		printf("Error\nInvalid map characters or wrong number of players.\n");
		return (0);
	}
	if (!validate_wall(data))
	{
		printf("Error\nMap is not enclosed by walls (Leak detected).\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_infoMaps	data;
	t_list		*file;

	if (!validate_args(argc, argv))
		return (1);
	init_maps(&data);
	file = read_cub_file(argv[1]);
	if (!file)
		return (1);
	if (!parse_core(file, &data))
	{
		free_info_maps(&data);
		return (ft_lstclear(&file, free, 1));
	}
	init_game(&data);
	free_info_maps(&data);
	return (ft_lstclear(&file, free, 0));
}
