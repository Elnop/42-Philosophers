/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:58:41 by lperroti          #+#    #+#             */
/*   Updated: 2023/05/24 03:41:07 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	print_status(t_philo philo)
{
	pthread_mutex_lock(&philo.app->write_mutex);
	if (philo.status == TAKING_A_FORK)
		lp_printf("%d %d has taken a fork",
			lp_get_timestamp(), philo.my_index + 1);
	if (philo.status == EATING)
		lp_printf("%d %d is eating",
			lp_get_timestamp(), philo.my_index + 1);
	if (philo.status == SLEEPING)
		lp_printf("%d %d is sleeping",
			lp_get_timestamp(), philo.my_index + 1);
	if (philo.status == THINKING)
		lp_printf("%d %d is thinking",
			lp_get_timestamp(), philo.my_index + 1);
	if (philo.status == DIED)
		lp_printf("%d %d died",
			lp_get_timestamp(), philo.my_index + 1);
	pthread_mutex_unlock(&philo.app->write_mutex);
}

void	change_status(t_philo *philo, enum e_philo_status status)
{
	if (is_finish(philo->app))
		return ;
	if (status == EATING)
		philo->last_meal = lp_get_timestamp();
	philo->status = status;
	print_status(*philo);
}

bool	is_finish(t_app	*app)
{
	bool	out;

	pthread_mutex_lock(&app->is_finish_mutex);
	out = app->is_finish;
	pthread_mutex_unlock(&app->is_finish_mutex);
	return (out);
}