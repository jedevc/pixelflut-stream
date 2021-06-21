#include "config.h"
#include "net.h"
#include "canvas.h"
#include "rand.h"

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

unsigned int px_width;
unsigned int px_height;
unsigned int px_pixelcount = 0;
unsigned int px_clientcount = 0;

// User sessions
typedef struct PxSession {
	uint32_t x;
	uint32_t y;
	uint32_t c;
} PxSession;

void px_reset_session(PxSession *session) {
	session->x = rand_range(0, px_width);
	session->y = rand_range(0, px_height);
	session->c = rand_range(0, 0xffffff) << 8 | 0xff;
}

static char *HELP_MESSAGE = "\
LEFT/RIGHT: Move snake horizontally\n\
UP/DOWN: Move snake vertically\n\
COLOR rrggbb(aa): Set snake color (with optional alpha channel)\n\
RESET: Randomly re-position and re-color snake\n\
SIZE: Get canvas size\n\
STATS: Return statistics";

// Helper functions

static inline int fast_str_startswith(const char* prefix, const char* str) {
	char cp, cs;
	while ((cp = *prefix++) == (cs = *str++)) {
		if (cp == 0)
			return 1;
	}
	return !cp;
}

// Decimal string to unsigned int. This variant does NOT consume +, - or whitespace.
// If **endptr is not NULL, it will point to the first non-decimal character, which
// may be \0 at the end of the string.
static inline uint32_t fast_strtoul10(const char *str, const char **endptr) {
	uint32_t result = 0;
	unsigned char c;
	for (; (c = *str - '0') <= 9; str++)
		result = result * 10 + c;
	if (endptr)
		*endptr = str;
	return result;
}

// Same as fast_strtoul10, but for hex strings.
static inline uint32_t fast_strtoul16(const char *str, const char **endptr) {
	uint32_t result = 0;
	unsigned char c;
	while ((c = *str - '0') <= 9 // 0-9
			|| ((c -= 7) >= 10 && c <= 15) // A-F
			|| ((c -= 32) >= 10 && c <= 15)) { // a-f
		result = result * 16 + c;
		str++;
	}
	if (endptr)
		*endptr = str;
	return result;
}

// server callbacks
void px_on_connect(NetClient *client) {
	PxSession *session = malloc(sizeof(PxSession));
	px_reset_session(session);
	net_set_user(client, session);
	if (session == NULL) {
		perror("client malloc failed");
	}

	px_clientcount++;
}

void px_on_close(NetClient *client, int error) {
	PxSession *session = net_get_user(client);
	free(session);

	px_clientcount--;
}

void px_on_read(NetClient *client, char *line) {
	PxSession *session = net_get_user(client);
	if (line[0] == '\0') {
		net_err(client, "No command provided");
	} else if (fast_str_startswith("RESET", line)) {
		px_reset_session(session);
	} else if (fast_str_startswith("LEFT", line)) {
		px_pixelcount++;
		canvas_set_px(session->x, session->y, session->c);
		if (session->x <= 0) {
			session->x = px_width - 1;
		} else {
			session->x--;
		}
	} else if (fast_str_startswith("RIGHT", line)) {
		px_pixelcount++;
		canvas_set_px(session->x, session->y, session->c);
		if (session->x >= px_width - 1) {
			session->x = 0;
		} else {
			session->x++;
		}
	} else if (fast_str_startswith("UP", line)) {
		px_pixelcount++;
		canvas_set_px(session->x, session->y, session->c);
		if (session->y <= 0) {
			session->y = px_height - 1;
		} else {
			session->y--;
		}
	} else if (fast_str_startswith("DOWN", line)) {
		px_pixelcount++;
		canvas_set_px(session->x, session->y, session->c);
		if (session->y >= px_height - 1) {
			session->y = 0;
		} else {
			session->y++;
		}
	} else if (fast_str_startswith("COLOR ", line)) {
		const char * ptr = line + 6;
		const char * endptr = ptr;
		errno = 0;

		// COLOR BB|RRGGBB|RRGGBBAA
		uint32_t c = fast_strtoul16((ptr = endptr), &endptr);
		if (endptr == ptr) {
			net_err(client,
					"Third parameter missing or invalid (should be hex color)");
			return;
		}

		if (endptr - ptr == 6) {
			// RGB -> RGBA (most common)
			c = (c << 8) + 0xff;
		} else if (endptr - ptr == 8) {
			// done
		} else if (endptr - ptr == 2) {
			// WW -> RGBA
			c = (c << 24) + (c << 16) + (c << 8) + 0xff;
		} else {
			net_err(client,
					"Color hex code must be 2, 6 or 8 characters long (WW, RGB or RGBA)");
			return;
		}

		session->c = c;
	} else if (fast_str_startswith("INFO", line)) {
		char str[64];
		if ((session->c & 0xff) == 0xff) {
			sprintf(str, "(%u, %u, %06x)", session->x, session->y, session->c >> 8);
		} else {
			sprintf(str, "(%u, %u, %08x)", session->x, session->y, session->c);
		}
		net_send(client, str);
	} else if (fast_str_startswith("SIZE", line)) {
		char str[64];
		snprintf(str, 64, "SIZE %d %d", px_width, px_height);
		net_send(client, str);
	} else if (fast_str_startswith("STATS", line)) {
		char str[128];
		snprintf(str, 128, "STATS px:%u conn:%u", px_pixelcount,
				px_clientcount);
		net_send(client, str);
	} else if (fast_str_startswith("HELP", line)) {
		net_send(client, HELP_MESSAGE);
	} else {
		net_err(client, "Unknown command");
	}
}

void px_on_key(int key, int scancode, int mods) {

	printf("Key pressed: key:%d scancode:%d mods:%d\n", key, scancode, mods);

	if (key == 300) { // F11
		int display = canvas_get_display();
		if (display < 0)
			canvas_fullscreen(0);
		else
			canvas_fullscreen(-1);
	} else if (key == 301) { // F12
		canvas_fullscreen(canvas_get_display() + 1);
	} else if (key == 67) { // c
		canvas_fill(0x00000088);
	} else if (key == 81 || key == 256) { // q or ESC
		canvas_close();
	}
}

void px_on_resize() {
	canvas_get_size(&px_width, &px_height);
}

void px_on_window_close() {
	printf("Window closed\n");
	net_stop();
}

int main(int argc, char **argv) {
	config_init();
	px_width = CONFIG_SCREEN_WIDTH;
	px_height = CONFIG_SCREEN_HEIGHT;

	rand_autoseed();

	canvas_setcb_key(&px_on_key);
	canvas_setcb_resize(&px_on_resize);

	canvas_start(CONFIG_TEXTURE_SIZE, &px_on_window_close);

	net_start(&px_on_connect, &px_on_read, &px_on_close);
	return 0;
}

