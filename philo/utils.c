#include "philo.h"

void	pthread_create_all(t_philosopher *philo, t_simulation *sim)
{
	size_t	i;

	i = 0;
	while (i < sim->number_of_philosophers)
	{
		pthread_create(&sim->threads[i], NULL, philo_routine, &philo[i]);
		i++;
	}
}

void	pthread_join_all(t_simulation *sim)
{
	size_t	i;

	i = 0;
	
	while (i < sim->number_of_philosophers)
		pthread_join(sim->threads[i++], NULL);
}

long	get_current_timestamp()
{
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	safe_atoi(char *str)
{
	size_t	i;

	i = 0;
	if (!str || *str == '\0')
		return (printf("Error: Empty or NULL argument\n"), -1);
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (printf("Error: Non-numeric argument '%s'\n", str), -1);
		i++;
	}
	return (atoi(str));
}

void	free_all(t_philosopher *philosophers, t_simulation *sim)
{
	free(sim->forks);
	free(sim->threads);
	free(philosophers);
}
