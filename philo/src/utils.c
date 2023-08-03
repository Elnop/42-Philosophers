/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:58:41 by lperroti          #+#    #+#             */
/*   Updated: 2023/08/03 22:28:22 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_wait(t_philo	*philo, long long ms)
{
	long long const	target = lp_get_timestamp() + ms;

	while (lp_get_timestamp() < target)
	{
		if (is_finish(philo))
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

static void	swap_forks(pthread_mutex_t **left_fork,
				pthread_mutex_t **right_fork)
{
	pthread_mutex_t	*tmp;

	tmp = *left_fork;
	*left_fork = *right_fork;
	*right_fork = tmp;
}

void	set_forks(t_philo *philo,
			pthread_mutex_t **left_fork, pthread_mutex_t **right_fork)
{
	*left_fork = &philo->fork_mutex;
	if (philo->my_index + 1 < philo->app->philo_count)
		*right_fork = &philo->app->philo_list[philo->my_index + 1].fork_mutex;
	else
		*right_fork = &philo->app->philo_list[0].fork_mutex;
	if (philo->my_index + 1 == philo->app->philo_count)
		swap_forks(left_fork, right_fork);
}
