#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philosopher {
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long last_meal_time;
    int meals_eaten; 
    struct s_simulation *sim;
} t_philosopher;

typedef struct s_simulation {
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meal_limit;
    int all_meals_completed;
    int philosopher_died;
    pthread_mutex_t mutex;
    pthread_mutex_t *forks;
    pthread_t *threads;
} t_simulation;

//action
void *philosopher_routine(void *arg);
void ft_eat(t_philosopher *philo);
void ft_sleep(t_philosopher *philo);
void	take_forks(t_philosopher *philo);

//philo
void init_philo(t_philosopher *philo,  pthread_mutex_t *left_fork, pthread_mutex_t *right_fork);
void	initialize_philo(t_philosopher *philosophers, t_simulation *sim);
void init_sim(t_simulation *sim, char *number_of_philosophers, char *time_to_die, char *time_to_eat, char *time_to_sleep, char *meal_limit);
void *monitor_death(void *arg);

//utils
long	get_current_timestamp();
int ft_safe_atoi(char *str);

#endif
