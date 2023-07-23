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
		if (is_finish(philo) || philo_is_starving(philo))
			return ;
		usleep(PHILO_WAIT_USLEEP);
	}
}

static bool	print_status(t_philo *philo)
{
	if (philo->status != DIED && (is_finish(philo) || philo_is_starving(philo)))
		return (false);
	pthread_mutex_lock(&philo->app->write_mutex);
	if (philo->status != DIED && (is_finish(philo) || philo_is_starving(philo)))
	{
		pthread_mutex_unlock(&philo->app->write_mutex);
		return (false);
	}
	if (philo->status == TAKING_A_FORK)
		printf("%lld %d has taken a fork\n",
			lp_get_timestamp() - philo->start_timestamp,
			philo->my_index + 1);
	if (philo->status == EATING)
		printf("%lld %d is eating\n",
			lp_get_timestamp() - philo->start_timestamp,
			philo->my_index + 1);
	if (philo->status == SLEEPING)
		printf("%lld %d is sleeping\n",
			lp_get_timestamp() - philo->start_timestamp,
			philo->my_index + 1);
	if (philo->status == THINKING)
		printf("%lld %d is thinking\n",
			lp_get_timestamp() - philo->start_timestamp,
			philo->my_index + 1);
	if (philo->status == DIED)
		printf("%lld %d died\n",
			lp_get_timestamp() - philo->start_timestamp,
			philo->my_index + 1);
	pthread_mutex_unlock(&philo->app->write_mutex);
	return (true);
}

bool	change_status(t_philo *philo, enum e_philo_status status)
{
	philo->status = status;
	if (status == EATING)
	{
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = lp_get_timestamp();
		pthread_mutex_unlock(&philo->last_meal_mutex);
	}
	if (!print_status(philo))
		return (false);
	if (status == DIED)
	{
		pthread_mutex_lock(&philo->app->is_finish_mutex);
		philo->app->is_finish = true;
		pthread_mutex_unlock(&philo->app->is_finish_mutex);
	}
	return (true);
}

