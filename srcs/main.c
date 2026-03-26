/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:14:53 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/26 10:51:35 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_infoMaps	data;
	t_list		*file_content;

	if (!validate_args(argc, argv))
		return (1);
	init_maps(&data);
	file_content = read_cub_file(argv[1]);
	if (!file_content)
		return (1);
	ft_lstclear(&file_content, free);
	return (0);
}
