/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_liblp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 02:20:43 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/21 02:22:16 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

char	*lp_strchr(char const *s, int c)
{
	size_t	i;

	if (*s == (unsigned char)c)
		return ((char *)s);
	i = 0;
	while (s[i])
	{
		i++;
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	}
	return (NULL);
}

size_t	lp_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

long long	lp_get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}