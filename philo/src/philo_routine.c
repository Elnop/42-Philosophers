/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:12 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/28 04:35:04 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_wait(t_philo	*philo, long long ms)
{
	long long const	target = lp_get_timestamp() + ms;

	while (lp_get_timestamp() < target)
	{
		if (is_finish(philo->app))
			return ;
		usleep(5);
	}
}

void	inc_and_check_meal_count(t_philo *philo)
{
	philo->meal_count += 1;
	pthread_mutex_lock(&philo->app->total_satiated_mutex);
	if (philo->meal_count == philo->app->max_meal)
			philo->app->total_satiated += 1;
	pthread_mutex_unlock(&philo->app->total_satiated_mutex);
}

static void	take_forks(t_philo *philo,
	pthread_mutex_t *fork_left, pthread_mutex_t	*fork_right)
{
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
}

static void	take_forks_and_eat(t_philo *philo)
{
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;

	fork_left = &philo->fork_mutex;
	if (philo->my_index + 1 < philo->app->philo_count)
		fork_right = &philo->app->philo_list[philo->my_index + 1].fork_mutex;
	else
		fork_right = &philo->app->philo_list[0].fork_mutex;
	take_forks(philo, fork_left, fork_right);
	change_status(philo, EATING);
	philo_wait(philo, philo->app->time_to_eat);
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);
	inc_and_check_meal_count(philo);
}

static void	smart_start(t_philo *philo)
{
	if (philo->my_index % 2)
		philo_wait(philo, philo->app->time_to_eat);
}

void	*philo_routine(void *props)
{
	t_philo	*philo;

	philo = (t_philo *)props;
	pthread_mutex_lock(&(philo->app->start_mutex));
	pthread_mutex_unlock(&(philo->app->start_mutex));

	philo->last_meal = lp_get_timestamp();
	smart_start(philo);
	while (!is_finish(philo->app))
	{
		take_forks_and_eat(philo);
		if (is_finish(philo->app))
			return (NULL);
		change_status(philo, SLEEPING);
		philo_wait(philo, philo->app->time_to_sleep);
		if (is_finish(philo->app))
			return (NULL);
		change_status(philo, THINKING);
	}
	return (NULL);
}


