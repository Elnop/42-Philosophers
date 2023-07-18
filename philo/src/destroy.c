/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 04:36:39 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/28 04:37:25 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_forks_mutex(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->philo_count)
		pthread_mutex_destroy(&app->philo_list[i++].fork_mutex);
}

void	destroy_all(t_app *app)
{
	destroy_forks_mutex(app);
	free(app->philo_list);
	pthread_mutex_destroy(&app->start_mutex);
	pthread_mutex_destroy(&app->is_finish_mutex);
	pthread_mutex_destroy(&app->write_mutex);
}