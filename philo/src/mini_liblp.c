/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_liblp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 01:41:58 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/28 02:23:44 by lperroti         ###   ########.fr       */
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

char	*lp_strdup(const char *s)
{
	char	*dup;
	int		i;

	dup = (char *)malloc((lp_strlen((char *)s) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*lp_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*cpy;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	cpy = lp_strdup(s);
	if (!cpy)
		return (cpy);
	i = 0;
	while (cpy[i])
	{
		cpy[i] = f(i, cpy[i]);
		i++;
	}
	return (cpy);
}

long long	lp_get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}