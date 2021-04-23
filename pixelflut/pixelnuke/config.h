#ifndef CONFIG_H_
#define CONFIG_H_

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 800
#define DEFAULT_TEXTURE_SIZE 1024

#define DEFAULT_PORT 1337

extern int CONFIG_SCREEN_WIDTH;
extern int CONFIG_SCREEN_HEIGHT;
extern int CONFIG_TEXTURE_SIZE;
extern int CONFIG_PORT;

void config_init();

#endif /* CONFIG_H_ */
