/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:12:41 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/18 21:13:08 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	check_args_handler(unsigned int i, char c)
{
	(void)i;
	if (lp_isdigit(c))
		return (c);
	return ('x');
}

bool	check_args(int argc, char const *argv[])
{
	char	*tmp;
	int		i;

	if (argc != 5 && argc != 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		tmp = lp_strmapi(argv[i++], check_args_handler);
		if (lp_strchr(tmp, 'x'))
			return (free(tmp), false);
		free(tmp);
	}
	return (true);
}
