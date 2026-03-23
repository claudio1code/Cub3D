/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:14:53 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/23 11:37:16 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char **argv)
{
	t_infoMaps	data;

	if (argc != 2)
	{
		(void)write(2, "Error\nInvalid number of arguments.\n", 36);
		return (1);
	}
	valid_args(argv, data);
	(void)data;
	return (0);
}
