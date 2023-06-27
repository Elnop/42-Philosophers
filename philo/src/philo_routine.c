/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:12 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/19 03:10:25 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks_and_eat(t_philo *philo)
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;

	fork_left = &philo->fork_mutex;

	if (philo->my_index + 1 < philo->app->philo_count)
		fork_right = &philo->app->philo_list[philo->my_index + 1].fork_mutex;
	else
		fork_right = &philo->app->philo_list[0].fork_mutex;
	if (philo->my_index % 2)
		pthread_mutex_lock(fork_left);
	else
		pthread_mutex_lock(fork_right);
	change_status(philo, TAKING_A_FORK);
	if (philo->my_index % 2)
		pthread_mutex_lock(fork_right);
	else
		pthread_mutex_lock(fork_left);
	change_status(philo, TAKING_A_FORK);
	change_status(philo, EATING);
	philo->meal_count += 1;
	philo_wait(philo, philo->app->time_to_eat);
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);
}

bool	am_i_starving(t_philo *philo)
{
	if (is_finish(philo->app))
		return (true);
	if (lp_get_timestamp() - philo->last_meal > philo->app->time_to_die)
	{
		change_status(philo, DIED);
		pthread_mutex_lock(&(philo->app->is_finish_mutex));
		philo->app->is_finish = true;
		pthread_mutex_unlock(&(philo->app->is_finish_mutex));
		return (true);
	}
	return (false);
}

bool	check_all_philo_eat_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->total_satiated_mutex);
	if (philo->meal_count == philo->app->max_meal)
			philo->app->total_satiated += 1;
	if (philo->app->total_satiated == philo->app->philo_count)
	{
		pthread_mutex_unlock(&philo->app->total_satiated_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->app->total_satiated_mutex);
	return (false);
}

void	smart_start_routine(t_philo *philo)
{
	if (philo->my_index % 2)
		philo_wait(philo, philo->app->time_to_eat);
}

void	*philo_routine(void *props)
{
	t_philo	*philo;

	philo = (t_philo *)props;
	smart_start_routine(philo);
	while (true)
	{
		if (is_finish(philo->app) || am_i_starving(philo))
			return (NULL);
		take_forks_and_eat(philo);
		if (check_all_philo_eat_enough(philo))
			return (NULL);
		change_status(philo, SLEEPING);
		philo_wait(philo, philo->app->time_to_sleep);
		change_status(philo, THINKING);
	}
	return (NULL);
}

// ====== Smart Think ======
// if (philo->app->time_to_eat >= philo->app->time_to_sleep)
// 	philo_wait(philo,
// 		philo->app->time_to_eat - philo->app->time_to_sleep);
