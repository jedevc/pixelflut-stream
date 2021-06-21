#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "rand.h"

#define RAND_STATE_SIZE 256
static char rand_state[RAND_STATE_SIZE];

void rand_seed(uint32_t seed) {
	initstate(seed, rand_state, RAND_STATE_SIZE);
}

void rand_autoseed() {
	uint32_t seed;            
	int fd = open("/dev/random", O_RDONLY);
	if (fd == -1) {
		strerror(errno);
		exit(1);
	}

	if (read(fd, &seed, sizeof(seed)) != sizeof(seed)) {
		strerror(errno);
		exit(1);
	}

	close(fd);
	rand_seed(seed);
}

uint32_t rand_range(uint32_t lower, uint32_t higher) {
	return lower + (random() % (higher - lower));
}
