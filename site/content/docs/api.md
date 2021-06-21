---
weight: 10
---

# API

The pixelsnake server is accessed over a TCP socket.

Using the linux command lines:

    $ nc stream.pixelflut.jedevc.com 1337

This opens a tcp connection to the server - you can type a command, then press
enter to execute it. To close the connection, press CTRL-D or CTRL-C.

## Help

To get help from the server, you can use the `HELP` command.

{{< hint info >}}
`HELP`

Prints out generic help information for the server
{{< /hint >}}

For example,

    $ nc stream.pixelflut.jedevc.com 1337
    HELP
    LEFT/RIGHT: Move snake horizontally
    UP/DOWN: Move snake vertically
    COLOR rrggbb(aa): Set snake color (with optional alpha channel)
    RESET: Randomly re-position and re-color snake
    SIZE: Get canvas size
    STATS: Return statistics

## Moving

To move, use the directional commands: `LEFT`, `RIGHT`, `UP` and `DOWN`.

{{< hint info >}}
`LEFT` / `RIGHT` / `UP` / `DOWN`

Colors a single pixel at the location *just* left.
{{< /hint >}}

For example,

    $ nc stream.pixelflut.jedevc.com 1337
    RIGHT
    DOWN
    LEFT
    UP

This paints a small square with the upper left corner at the randomly selected
start position.

## Coloring

By default, the snake's color is randomly selected; however, you can change
this yourself.

{{< hint info >}}
`COLOR <hex-color>`

Changes the snake's color.
{{< /hint >}}

For example, to change the snake color to pure red for all future movement:

    $ nc stream.pixelflut.jedevc.com 1337
    COLOR ff0000

You can also use colors with transparency:

    $ nc stream.pixelflut.jedevc.com 1337
    COLOR ff0000a0

## Reset

To abandon your old snake and create a new one, you can use the `RESET`
command, avoiding needing to disconnect and reconnect to the server.

{{< hint info >}}
`RESET`

Randomly reset the snake's position and color.
{{< /hint >}}

## Statistics

You can also get data about the shared canvas which you can use to get
information to inform your painting decisions automatically!

{{< hint info >}}
`INFO`

Get the state of the current snake, as a 3-tuple `(<x-position>, <y-position>, <color>)`.
{{< /hint >}}

For example,

    $ nc stream.pixelflut.jedevc.com 1337
    INFO
    (238, 618, 8C85D3FF)

{{< hint info >}}
`SIZE`

Get the size of the canvas.
{{< /hint >}}

For example,

    $ nc stream.pixelflut.jedevc.com 1337
    SIZE
    SIZE 800 600

{{< hint info >}}
`STATS`

Get generic statistics about the current state of the canvas.
{{< /hint >}}

For example:

    $ nc stream.pixelflut.jedevc.com 1337
    STATS
    STATS px:103 conn:2

This tells us that 103 pixels have been painted on the canvas, and that 2 TCP
connections are currently open to the server.

