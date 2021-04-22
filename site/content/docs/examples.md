---
weight: 20
---

# Examples

## A single pixel

As simple as you can get! Definitely start here, just to make everything's
working.

This should color a single pixel at `(100, 100)` pure red - it'll be difficult
to spot, especially if everyone else is running the same example - make sure to
mix up the co-ordinates and colours to experiment!

{{< tabs "square" >}}
{{< tab "Python" >}}
```python3
# pixel.py
if __name__ == "__main__":
    x = 100
    y = 100
    color = "ff0000"
    print(f"PX {x} {y} {color}")
```

To draw the square, run the program and pipe it into netcat:

    $ python3 pixel.py | nc pixelflut.jedevc.com 1337
{{< /tab >}}
{{< /tabs >}}

Note how we interact with the server - whatever language we use, we can just
print out to the console, and then use netcat (available as `nc`, `netcat` and
`ncat` with slightly different behaviours). This means that rendering is
simple, and easy, and makes our pipeline composable in case we want to do some
funky stuff later on.

## Square

This should render a single square of size 100 by 100 at the co-ordinates `(50, 50)`.

{{< tabs "square" >}}
{{< tab "Python" >}}
```python3
# square.py
if __name__ == "__main__":
    x = 50
    y = 50
    for i in range(100):
        for j in range(100):
            print(f"PX {x + i} {y + j} ff0000")
```

To draw the square, run the program and pipe it into netcat:

    $ python3 square.py | nc pixelflut.jedevc.com 1337
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

```python3
# image.py
import sys
from PIL import Image

def paste_image(im, x, y):
    for i in range(im.width):
        for j in range(im.height):
            try:
                r, g, b, a = im.getpixel((i, j))
                if a == 0:
                    # don't waste time rendering fully transparent pixels
                    continue
                color = f"{r:02x}{g:02x}{b:02x}{a:02x}"
            except ValueError:
                r, g, b = im.getpixel((i, j))
                color = f"{r:02x}{g:02x}{b:02x}"
            print(f'PX {x + i} {y + j} {color}')

if __name__ == "__main__":
    image = Image.open(sys.argv[1])
    paste_image(image, 0, 0)
```

To draw the image, run the program with an image file and pipe it into netcat:

    $ python3 image.py image.png | nc pixelflut.jedevc.com 1337
{{< /tab >}}
{{< /tabs >}}

## Clock

Rendering text is kind of useful, and so is rendering something over and over
again. This example combines both of them!

{{< tabs "clock" >}}
{{< tab "Python" >}}
```python3
# clock.py
import time
from PIL import Image, ImageDraw

from image import paste_image

BORDER = 10

def paste_text(text):
    im = Image.new("RGBA", (800, 600))
    draw = ImageDraw.Draw(im)
    draw.text((BORDER, BORDER), text, fill="black")

    bounds = im.getbbox()
    bounds = [
        bounds[0] - BORDER,
        bounds[1] - BORDER,
        bounds[2] + BORDER,
        bounds[3] + BORDER
    ]
    bgim = Image.new("RGBA", (800, 600))
    draw = ImageDraw.Draw(bgim)
    draw.rectangle(bounds, fill="white")
    bgim.paste(im, mask=im)

    # defined in image.py in an above example
    paste_image(bgim, 0, 0)

if __name__ == "__main__":
    while True:
        text = time.strftime("%H:%M:%S")
        paste_text(text)

        # time delay!
        time.sleep(1)
```

To continuously render the clock in the top-left corner of the screen, run the
program and pipe it into netcat:

    $ python3 clock.py | nc pixelflut.jedevc.com 1337
{{< /tab >}}
{{< /tabs >}}

## Worm

We can illustrate the progress of a [Random Walk](https://en.wikipedia.org/wiki/Random_walk)
by rendering the tail as well, drawing a worm that makes it way randomly through the canvas!

{{< tabs "worm" >}}
{{< tab "Python" >}}
```python3
# worm.py
import colorsys
import random
import time

# partition the available space into unit squares
PXWIDTH, PXHEIGHT = 800, 600
SQUARE = 20
WIDTH, HEIGHT = PXWIDTH // SQUARE, PXHEIGHT // SQUARE

TAIL_MAX = 5

def rect(x, y, width, height, color):
    for i in range(width):
        for j in range(height):
            print(f"PX {x + i} {y + j} {color}")

if __name__ == "__main__":
    # get a starting position
    x = random.randint(0, WIDTH - 1)
    y = random.randint(0, HEIGHT - 1)

    h, s, v = 0.0, 0.8, 0.9
    hdiff = 1 / 100

    tail = []

    while True:
        # change the worm's color
        h += hdiff

        # move the worm
        if random.choice([True, False]):
            x += random.choice([-1, 1])
            x = x % WIDTH
        else:
            y += random.choice([-1, 1])
            y = y % HEIGHT
        tail.append((x, y))
        while len(tail) > TAIL_MAX:
            tail.pop(0)

        # draw the worm
        drawn = set()
        for i, (tx, ty) in enumerate(tail):
            # make sure we don't redraw parts of the tail
            if (tx, ty) in drawn:
                continue
            drawn.add((tx, ty))

            color = colorsys.hsv_to_rgb(h, s, 0.7 + i / TAIL_MAX * 0.3)
            color = [int(c * 255) for c in color]
            color = f"{color[0]:02x}{color[1]:02x}{color[2]:02x}"

            rect(tx * SQUARE, ty * SQUARE, SQUARE, SQUARE, color)

        # time delay!
        time.sleep(0.1)
```

To continuously render the worm and have it crawl across the screen, run the
program and pipe it into netcat:

    $ python3 worm.py | nc pixelflut.jedevc.com 1337
{{< /tab >}}
{{< /tabs >}}
