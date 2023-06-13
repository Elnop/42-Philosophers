/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:12 by lperroti          #+#    #+#             */
/*   Updated: 2023/05/24 03:42:17 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks_and_eat(t_philo *philo)
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;

	fork_left = &philo->fork_mutex;
	change_status(philo, TAKING_A_FORK);
	if (philo->my_index + 1 < philo->app->philo_count)
		fork_right = &philo->app->philo_list[philo->my_index + 1].fork_mutex;
	else
		fork_right = &philo->app->philo_list[0].fork_mutex;
	if (philo->my_index % 2)
		pthread_mutex_lock(fork_left);
	else
		pthread_mutex_lock(fork_left);
	change_status(philo, TAKING_A_FORK);
	if (philo->my_index % 2)
		pthread_mutex_lock(fork_right);
	else
		pthread_mutex_lock(fork_right);
	change_status(philo, TAKING_A_FORK);
	change_status(philo, EATING);
	lp_wait(philo->app->time_to_eat);
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);

}

void	*philo_routine(void *props)
{
	t_philo	*philo;

	philo = (t_philo *)props;
	while (true)
	{
		if (is_finish(philo->app))
			return (NULL);
		take_forks_and_eat(philo);
		change_status(philo, SLEEPING);
		lp_wait(philo->app->time_to_sleep);
		change_status(philo, THINKING);
	}
	return (NULL);
}
