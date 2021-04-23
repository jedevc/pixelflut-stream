#include "config.h"

#include <stdlib.h>

#define LOAD_CONFIG(name) CONFIG_##name = getenv(#name) == NULL ? DEFAULT_##name : getenv(#name)
#define LOAD_CONFIG_INT(name) CONFIG_##name = getenv(#name) == NULL ? DEFAULT_##name : atoi(getenv(#name))

int CONFIG_SCREEN_WIDTH;
int CONFIG_SCREEN_HEIGHT;
int CONFIG_TEXTURE_SIZE;
int CONFIG_PORT;

void config_init() {
	LOAD_CONFIG_INT(SCREEN_WIDTH);
	LOAD_CONFIG_INT(SCREEN_HEIGHT);
	LOAD_CONFIG_INT(TEXTURE_SIZE);
	LOAD_CONFIG_INT(PORT);
}
