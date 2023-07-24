/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:58:41 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/19 23:52:12 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_wait(t_philo	*philo, long long ms)
{
	long long const	target = lp_get_timestamp() + ms;

	while (lp_get_timestamp() < target)
	{
		if (philo_is_starving(philo))
			return ;
		usleep(PHILO_WAIT_USLEEP);
	}
}

void	set_last_meal(t_philo *philo, long long ms)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = ms;
	pthread_mutex_unlock(&philo->last_meal_mutex);
}
