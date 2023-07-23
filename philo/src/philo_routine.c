/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:12 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/21 05:11:56 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	take_forks_and_eat(t_philo *philo)
{
	pthread_mutex_t	*next_fork;

	if (philo->my_index + 1 < philo->app->philo_count)
		next_fork = &philo->app->philo_list[philo->my_index + 1].fork_mutex;
	else
		next_fork = &philo->app->philo_list[0].fork_mutex;
	pthread_mutex_lock(&philo->fork_mutex);
	if (!change_status(philo, TAKING_A_FORK))
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		return (false);
	}
	pthread_mutex_lock(next_fork);
	if (!change_status(philo, TAKING_A_FORK) || !change_status(philo, EATING))
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(next_fork);
		return (false);
	}
	philo->meal_count += 1;
	philo_wait(philo, philo->app->time_to_eat);
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(next_fork);
	return (true);
}

bool	check_eat_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->total_satiated_mutex);
	if (philo->meal_count == philo->app->max_meal)
			philo->app->total_satiated += 1;
	if (philo->app->total_satiated == philo->app->philo_count)
	{
		pthread_mutex_unlock(&philo->app->total_satiated_mutex);
		pthread_mutex_lock(&(philo->app->is_finish_mutex));
		philo->app->is_finish = true;
		pthread_mutex_unlock(&(philo->app->is_finish_mutex));
		return (true);
	}
	pthread_mutex_unlock(&philo->app->total_satiated_mutex);
	return (false);
}

void	*philo_routine(void *props)
{
	t_philo	*philo;

	philo = (t_philo *)props;
	pthread_mutex_lock(&philo->app->start_mutex);
	pthread_mutex_unlock(&philo->app->start_mutex);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = lp_get_timestamp();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (!(philo->my_index % 2))
		philo_wait(philo, philo->app->time_to_eat);
	while (true)
	{
		if (!take_forks_and_eat(philo))
			return (NULL);
		if (check_eat_enough(philo))
			return (NULL);
		if (!change_status(philo, SLEEPING))
			return (NULL);
		philo_wait(philo, philo->app->time_to_sleep);
		if (!change_status(philo, THINKING))
			return (NULL);
		if (philo->app->time_to_eat > philo->app->time_to_sleep)
			philo_wait(philo,
				(philo->app->time_to_eat - philo->app->time_to_sleep) * 1);

	}
	return (NULL);
}
