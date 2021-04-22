---
weight: 20
---

# API

The pixelflut server is accessed over a TCP socket.

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
    PX x y: Get color at position (x,y)
    PX x y rrggbb(aa): Draw a pixel (with optional alpha channel)
    SIZE: Get canvas size
    STATS: Return statistics

## Painting

To paint a single pixel, use the `PX` command.

{{< hint info >}}
`PX <x-coordinate> <y-coordinate> <hex-color>`

Colors a single pixel at the provided co-ordinates.
{{< /hint >}}

For example,

    $ nc stream.pixelflut.jedevc.com 1337
    PX 100 200 ff0000

This paints a single pure red pixel at `(100, 200)`.

You can also paint pixels with transparency:

    $ nc stream.pixelflut.jedevc.com 1337
    PX 100 200 ff0000a0

This paints a single slightly-transparent red pixel at the same co-ordinates as
above.

## Statistics

You can also get data about the shared canvas which you can use to get
information to inform your painting decisions automatically!

{{< hint info >}}
`PX <x-coordinate> <y-coordinate>`

Get the color of a single pixel at the provided co-ordinates.
{{< /hint >}}

For example,

    $ nc stream.pixelflut.jedevc.com 1337
    PX 100 100
    PX 100 100 FF0000

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

