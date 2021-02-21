Pixelflut: Multiplayer canvas
=============================

*This code is based on the [upstream pixelflut](https://github.com/defnull/pixelflut)
with a few additional quality-of-life patches.*

What happens if you give a bunch of hackers the ability to change pixel colors
on a projector screen? See yourself :)

Pixelflut is a very simple (and inefficient) ASCII based network protocol to
draw pixels on a screen.  You can write a basic client in a single line of
shell code if you want, but you only get to change a single pixel at a time.
If you want to get rectangles, lines, text or images on the screen you have to
implement that functionality yourself. That is part of the game.

Pixelflut Protocol
------------------

Pixelflut defines four main commands that are always supported to get you
started:

* `HELP`: Returns a short introductional help text.
* `SIZE`: Returns the size of the visible canvas in pixel as `SIZE <w> <h>`.
* `PX <x> <y>` Return the current color of a pixel as `PX <x> <y> <rrggbb>`.
* `PX <x> <y> <rrggbb(aa)>`: Draw a single pixel at position (x, y) with the specified hex color code.
  If the color code contains an alpha channel value, it is blended with the current color of the pixel.

You can send multiple commands over the same connection by terminating each
command with a single newline character (`\n`).

Example:

    $ echo "SIZE" | netcat pixelflut.example.com 1337
    SIZE 800 600
    $ echo "PX 23 42 ff8000" | netcat pixelflut.example.com 1337
    $ echo "PX 32 42" | netcat pixelflut.example.com 1337
    PX 23 42 ff8000

Implementations MAY support additional commands or have less strict parsing
rules (e.g. allow `\r\n` or any whitespace between parameters) but they MUST
support the commands above. 

Pixelnuke
----------------------

Server written in C, based on libevent2, OpenGL, GLFW and pthreads. It won't
get any faster than this. Perfect for fast networks and large groups.

    sudo apt-get install build-essential libevent-dev libglew-dev libglfw3-dev
    make
    ./pixelnuke

Keyboard controls:

* `F11`: Toggle between fullscreen and windowed mode
* `F12`: Switch between multiple monitors in fullscreen mode
* `c`: Clear the screen (50% black, hit multiple times)
* `q` or `ESC`: Quit

Additional Commands:

* `STATS` Return statistics as `STATS <name>:<value> ...`
* `px:<uint>` Number of pixels drawn so far. Will overflow eventually.
* `conn:<uint>` Number of currently connected clients.

