---
weight: 20
---

# Examples

## A single pixel

As simple as you can get! Definitely start here, just to make everything's
working.

This should color a single pixel somewhere on the canvas pure red - it'll be
difficult to spot, especially if everyone else is running the same example -
make sure to mix up the colours to experiment!

{{< tabs "pixel" >}}
{{< tab "Python" >}}
```python
# pixel.py
import socket

if __name__ == "__main__":
    SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    SOCKET.connect(('pixelflut.jedevc.com', 1337))
    SOCKET = SOCKET.makefile('rw')

    color = "ff0000"
    print(f"COLOR {color}", file=SOCKET)
    print("RIGHT", file=SOCKET)

    SOCKET.close()
```

To draw the square, just run the program:

    $ python3 pixel.py
{{< /tab >}}
{{< /tabs >}}

Before continuing, make sure this works! If you have problems, try removing the
`file=SOCKET` part to print to stdout so it's easier to see what's going on and
what commands are being sent.

{{< hint info >}}
Alternatively, instead of connecting using your language's TCP socket
connection primitives, and you're on Linux you can take the simpler option of
just directly printing out your commands directly to the console.

Then, you can run it like so, using a pipe:

    $ python3 pixel.py | nc pixelflut.jedevc.com 1337

If you're on Linux, you should definitely give this technique a go - it's much
more flexible, and also works for whatever programming language you want to
use, without needing to learn their socket APIs!
{{< /hint >}}

## Square

This should render a single square of size 100 by 100.

{{< tabs "square" >}}
{{< tab "Python" >}}
```python
# square.py
import socket

WIDTH = 100
HEIGHT = 100

if __name__ == "__main__":
    SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    SOCKET.connect(('pixelflut.jedevc.com', 1337))
    SOCKET = SOCKET.makefile('rw')

    for i in range(HEIGHT):
        for j in range(WIDTH):
            if j == WIDTH - 1:
                print("DOWN", file=SOCKET)
            elif i % 2 == 0:
                print("RIGHT", file=SOCKET)
            else:
                print("LEFT", file=SOCKET)

    SOCKET.close()
```

To draw the square, run the program:

    $ python3 square.py
{{< /tab >}}
{{< /tabs >}}

## Images

You probably want to be able to paste images into the canvas. To do this, it's
best to integrate into your language of choice's image library. Not only will
they manage the loading and reading of image files for you, but they'll also
probably provide a lot of useful utilities!

{{< tabs "images" >}}
{{< tab "Python" >}}
To load and render images you can use the Python [Pillow](https://pillow.readthedocs.io/en/stable/)
library.

```python
# image.py
import socket
import sys

from PIL import Image

def paste_image(im):
    for i in range(im.height):
        for j in range(im.width):
            at_end = j == im.width - 1
            if i % 2 == 1:
                j = im.width - j - 1

            try:
                r, g, b, a = im.getpixel((j, i))
                color = f"{r:02x}{g:02x}{b:02x}{a:02x}"
            except ValueError:
                r, g, b = im.getpixel((j, i))
                color = f"{r:02x}{g:02x}{b:02x}"
            print(f'COLOR {color}', file=SOCKET)

            if at_end:
                print("DOWN", file=SOCKET)
            elif i % 2 == 0:
                print("RIGHT", file=SOCKET)
            else:
                print("LEFT", file=SOCKET)

if __name__ == "__main__":
    SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    SOCKET.connect(('pixelflut.jedevc.com', 1337))
    SOCKET = SOCKET.makefile('rw')

    image = Image.open(sys.argv[1])
    paste_image(image)

    SOCKET.close()
```

To draw the image, run the program with an image file:

    $ python3 image.py image.png
{{< /tab >}}
{{< /tabs >}}

## Clock

Rendering text is kind of useful, and so is rendering something over and over
again. This example combines both of them!

As useful helpers, we need to get the size of the canvas, and also be able to
reposition ourselves to the top-left corner of the screen.

{{< tabs "clock" >}}
{{< tab "Python" >}}
```python
# clock.py
import socket
import time
from PIL import Image, ImageDraw

BORDER = 10

def paste_text(text):
    im = Image.new("RGBA", (WIDTH, HEIGHT))
    draw = ImageDraw.Draw(im)
    draw.text((BORDER, BORDER), text, fill="black")

    bounds = im.getbbox()
    bounds = [
        bounds[0] - BORDER,
        bounds[1] - BORDER,
        bounds[2] + BORDER,
        bounds[3] + BORDER
    ]
    im = im.crop(bounds)

    bgim = Image.new("RGBA", im.size, "white")
    bgim.paste(im, mask=im)

    # defined above in image.py
    paste_image(bgim)

def goto(tx, ty):
    print("INFO", file=SOCKET, flush=True)
    line = SOCKET.readline().strip(" \n()")
    x, y, _ = line.split(", ")
    x, y = int(x), int(y)

    while x < tx:
        print("RIGHT", file=SOCKET)
        x += 1
    while x > tx:
        print("LEFT", file=SOCKET)
        x -= 1
    while y < ty:
        print("DOWN", file=SOCKET)
        y += 1
    while y > ty:
        print("UP", file=SOCKET)
        y -= 1

if __name__ == "__main__":
    SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    SOCKET.connect(('pixelflut.jedevc.com', 1337))
    SOCKET = SOCKET.makefile('rw')

    print("SIZE", file=SOCKET, flush=True)
    WIDTH, HEIGHT = [int(s) for s in SOCKET.readline().split()[1:]]

    while True:
        goto(0, 0)
        text = time.strftime("%H:%M:%S")
        paste_text(text)

        # time delay!
        time.sleep(0.5)

    SOCKET.close()
```

To continuously render the clock in the top-left corner of the screen, run the
program:

    $ python3 clock.py
{{< /tab >}}
{{< /tabs >}}

