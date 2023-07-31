/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 08:25:53 by lperroti          #+#    #+#             */
/*   Updated: 2023/08/01 01:33:02 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	destroy_philos_mutex(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->philo_count)
	{
		if (app->philo_list[i].app)
		{
			pthread_mutex_destroy(&app->philo_list[i].fork_mutex);
			pthread_mutex_destroy(&app->philo_list[i].last_meal_mutex);
		}
		i++;
	}
}

void	destroy_app(t_app *app)
{
	destroy_philos_mutex(app);
	pthread_mutex_destroy(&app->is_finish_mutex);
	pthread_mutex_destroy(&app->write_mutex);
}
