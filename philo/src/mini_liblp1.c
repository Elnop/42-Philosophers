/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_liblp1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:18:42 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/31 08:26:08 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	lp_atol(const char *nptr)
{
	long long	num;
	long long	sign;

	num = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	sign = 1;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num *= 10;
		num += *nptr - '0';
		nptr++;
	}
	return (num * sign);
}
