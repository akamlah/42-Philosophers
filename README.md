# 42-Philosophers
Didactic project from Ecole-42. Two different solutions for an extended version of the famous 'Dining Philosophers' problem, the first as a multithreaded program ruled by mutexes, the second featuring multiple processes synchronised by semaphores.

## Building
### Version 1 - posix threads

at the root of the folder "philo":

```
$ make
$ ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

The last argument is optional. The maximum number of philosophers the program is tested for is 200 (i.e. 200 concurrent threads)

### Version 2 - unix processes

at the root of the folder "philo_bonus":

```
$ make
$ ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

The last argument is optional. The maximum number of philosophers the program is tested for is 200 (i.e. 200 concurrent processes)


## The simulation

One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
There are also forks on the table. There are as many forks as philosophers.
Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
Every philosopher needs to eat and should never starve.
Philosophers don’t speak with each other.
Philosophers don’t know if another philosopher is about to die.

The user gets a log printed on the terminal that informs whenever a philosopher has taken one of the following actions:
* taking a fork
* started eating
* started thining
* started sleeping
* died

Preceeded by a timestamp corresponding to the elapsed milliseconds from the start of the simulation. The main goal in this program was to optimize it in a way that as little delay as possible is accumulated, so that even for large numbers of threads/processes, if the parameters would ensure that the simulation runs infinitely (i.e. time to eat shorter that time to die for example), the implementation actually does run as long as possible, and is stopped only by system limitations.
Also another key point is the management of shared memory resources, and avoiding race conditions between threads.

