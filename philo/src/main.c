/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:37:01 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/18 20:28:16 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	start_philos(t_app *app)
{
	long	i;

	i = 0;
	while (i < app->philo_count)
	{
		pthread_create(
			&app->philo_list[i].thread, NULL, philo_routine,
			app->philo_list + i);
		i++;
	}
}

// static void	is_finish_while(t_app *app)
// {
// 	int	i;

// 	i = 0;
// 	while (i < app->philo_count)
// 	{
// 		if (lp_get_timestamp() - app->philo_list[i].last_meal
// 			> app->time_to_die)
// 		{
// 			pthread_mutex_lock(&app->is_finish_mutex);
// 			app->is_finish = true;
// 			pthread_mutex_unlock(&app->is_finish_mutex);
// 		}
// 		i++;
// 	}
// }

static void	destroy_forks_mutex(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->philo_count)
		pthread_mutex_destroy(&app->philo_list[i++].fork_mutex);
}

static void	destroy_all(t_app *app)
{
	destroy_forks_mutex(app);
	free(app->philo_list);
	pthread_mutex_destroy(&app->is_finish_mutex);
	pthread_mutex_destroy(&app->write_mutex);
}

static void	wait_philos(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->philo_count)
		pthread_join(app->philo_list[i++].thread, NULL);
}

int	main(int argc, char const *argv[])
{
	t_app	app;

	if (!check_args(argc, argv))
	{
		lp_printf("Philosophers\n./philo number_of_philosophers ");
		lp_printf("time_to_die time_to_eat time_to_sleep ");
		lp_printf("[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (!init_app(&app, argc, argv) || !app.philo_count)
	{
		lp_printf("Error\n");
		return (0);
	}
	start_philos(&app);
	//is_finish_while(&app);
	wait_philos(&app);
	destroy_all(&app);
	return (0);
}
