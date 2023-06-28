/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:58:41 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/28 03:17:27 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_finish(t_app	*app)
{
	bool	out;

	pthread_mutex_lock(&(app->is_finish_mutex));
	out = app->is_finish;
	pthread_mutex_unlock(&(app->is_finish_mutex));
	return (out);
}

static void	print_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->write_mutex);
	if (is_finish(philo->app))
		return ((void)pthread_mutex_unlock(&philo->app->write_mutex));
	if (philo->status == TAKING_A_FORK)
		printf("%lld %d has taken a fork\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	if (philo->status == EATING)
		printf("%lld %d is eating\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	if (philo->status == SLEEPING)
		printf("%lld %d is sleeping\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	if (philo->status == THINKING)
		printf("%lld %d is thinking\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	if (philo->status == DIED)
		printf("%lld %d died\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	pthread_mutex_unlock(&philo->app->write_mutex);
}

void	change_status(t_philo *philo, enum e_philo_status status)
{
	if (status == EATING)
		philo->last_meal = lp_get_timestamp();
	philo->status = status;
	print_status(philo);
}

bool	check_all_philo_eat_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->app->total_satiated_mutex);
	if (philo->app->total_satiated == philo->app->philo_count)
	{
		pthread_mutex_lock(&(philo->app->is_finish_mutex));
		philo->app->is_finish = true;
		pthread_mutex_unlock(&(philo->app->is_finish_mutex));
		pthread_mutex_unlock(&philo->app->total_satiated_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->app->total_satiated_mutex);
	return (false);
}