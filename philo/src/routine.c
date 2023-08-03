/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:12 by lperroti          #+#    #+#             */
/*   Updated: 2023/08/03 22:51:27 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	take_forks_and_eat(t_philo *philo)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	set_forks(philo, &left_fork, &right_fork);
	pthread_mutex_lock(left_fork);
	if (!change_status(philo, TAKING_A_FORK))
	{
		pthread_mutex_unlock(left_fork);
		return (false);
	}
	pthread_mutex_lock(right_fork);
	if (!change_status(philo, TAKING_A_FORK) || !change_status(philo, EATING))
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		return (false);
	}
	philo->meal_count += 1;
	philo_wait(philo, philo->app->time_to_eat);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	return (true);
}

static bool	check_eat_enough(t_philo *philo)
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

void	force_thinking(t_philo *philo)
{
	if (philo->app->philo_count % 2 && philo->app->time_to_eat
		+ philo->app->time_to_sleep < philo->app->time_to_die)
		philo_wait(philo,
			((philo->app->time_to_die - philo->app->time_to_eat
					- philo->app->time_to_sleep) * 0.5));
}

void	*philo_routine(void *props)
{
	t_philo	*philo;

	philo = (t_philo *)props;
	pthread_mutex_lock(&philo->app->start_mutex);
	pthread_mutex_unlock(&philo->app->start_mutex);
	set_last_meal(philo, lp_get_timestamp());
	if (philo->my_index % 2)
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
		force_thinking(philo);
	}
	return (NULL);
}
