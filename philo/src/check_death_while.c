#include "../includes/philo.h"

bool	philo_is_starving(t_philo *philo)
{
	if (lp_get_timestamp() - philo->last_meal >= philo->app->time_to_die)
	{
		change_status(philo, DIED);
		pthread_mutex_lock(&(philo->app->is_finish_mutex));
		philo->app->is_finish = true;
		pthread_mutex_unlock(&(philo->app->is_finish_mutex));
		return (true);
	}
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

    while (true)
    {
		usleep(120);
		i = 0;
        while (i < app->philo_count)
		{
			if (is_finish(app->philo_list + i) || philo_is_starving(app->philo_list + i))
				return ;
			i++;
		}
    }
}