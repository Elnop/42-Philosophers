#include "../includes/philo.h"

bool	philo_is_starving(t_philo *philo)
{
	if (is_finish(philo))
		return (true);
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (lp_get_timestamp() - philo->last_meal >= philo->app->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		change_status(philo, DIED);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (false);
}

bool	is_finish(t_philo *philo)
{
	bool	out;

	pthread_mutex_lock(&(philo->app->is_finish_mutex));
	out = philo->app->is_finish;
	pthread_mutex_unlock(&(philo->app->is_finish_mutex));
	return (out);
}

void    check_death_while(t_app *app)
{
	int		i;

	if (!(app->philo_count % 2) && app->time_to_die > app->time_to_eat + app->time_to_sleep)
		return ;
	pthread_mutex_lock(&app->start_mutex);
	pthread_mutex_unlock(&app->start_mutex);
	usleep(100 * app->philo_count);
    while (true)
    {
		usleep(1000);
		i = 0;
        while (i < app->philo_count)
		{
			if (is_finish(app->philo_list + i) || philo_is_starving(app->philo_list + i))
				return ;
			i++;
		}
    }
}