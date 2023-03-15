/*
To measure time for decoding and writing one byte / one char.
Copy - comment original rbyte function - paste this one, run.
*/

struct timespec start_time;

void ft_rbyte(int sig) {
  static char	binary[9];
	static int	i = 0;
	
 	if (i == 0) {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
  } 

  if (sig == SIGUSR1)
  {
    binary[i] = '0';
    i++;
  }
   else if (sig == SIGUSR2) {
    binary[i] = '1';
    i++;
  }

  if (i == 8) {
    binary[i] = '\0';
    char c = ft_bintoc(binary);
	write(1, &c, 1);

    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1e9;
    elapsed_time = (elapsed_time + (end_time.tv_nsec - start_time.tv_nsec)) * 1e-9;

    
    printf("\nElapsed time: %lf seconds\n", elapsed_time);
    i = 0;
  } 
}