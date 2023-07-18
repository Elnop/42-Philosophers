/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_finish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:35:37 by marvin            #+#    #+#             */
/*   Updated: 2023/06/28 17:35:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	check_starving(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_count_mutex);
	if (philo->meal_count >= philo->app->max_meal)
	{
		pthread_mutex_unlock(&philo->meal_count_mutex);
        return (true);
	}
	pthread_mutex_unlock(&philo->meal_count_mutex);
	return (false);
}

bool	check_eat_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_count_mutex);
	if (lp_get_timestamp() - philo->last_meal >= philo->app->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_count_mutex);
        return (true);
	}
	pthread_mutex_unlock(&philo->meal_count_mutex);
	return (false);
}

bool	check_philos_eat_enough(t_app *app)
{
	long	i;
    long    philos_satisfied;

	i = 0;
	philos_satisfied = 0;
	while (i < app->philo_count)
	{
		if (check_eat_enough(app->philo_list + i))
			philos_satisfied++;
		i++;
	}
	if (philos_satisfied == app->philo_count)
		return (true);
	return (false);
}

void	while_check_philos(t_app *app)
{
	long	i;

	while (true)
	{
		i = 0;
		while (i < app->philo_count)
		{
			if (check_starving(app->philo_list + i))
                return change_status(app->philo_list + i, DIED);
			i++;
		}
        if (check_philos_eat_enough(app))
			return ;
        usleep(CHECK_PHILOS_USLEEP);
	}
	pthread_mutex_lock(&(app->is_finish_mutex));
	app->is_finish = true;
	pthread_mutex_unlock(&(app->is_finish_mutex));
}