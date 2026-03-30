/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clados-s <clados-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:27:33 by clados-s          #+#    #+#             */
/*   Updated: 2026/03/30 10:27:20 by clados-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments.\n");
		return (0);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
	{
		printf("Error\nFile must have a .cub extension.\n");
		return (0);
	}
	return (1);
}
