#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

void rand_seed(uint32_t);
void rand_autoseed();

uint32_t rand_range(uint32_t, uint32_t);

#endif /* RAND_H_ */
