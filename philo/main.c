#include "philo.h"

int 	main(int argc, char **argv)
{
	t_philosopher	*philo;
	t_simulation	sim;
	pthread_t		monitor_thread;

	if (argc != 5 && argc != 6)
		return (error_sel(0), 1);
	philo = malloc(sizeof(t_philosopher) * atoi(argv[1]));
	if (!philo)
		return (error_sel(1), 1);
	if (!init_all(&sim, philo, argc, argv))
		return (1);
	pthread_create_all(philo, &sim);
	pthread_create(&monitor_thread, NULL, monitor_death_complete, philo);
	pthread_join_all(&sim);
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&sim.mutex);
	free_all(philo, &sim);
	return (0);
}