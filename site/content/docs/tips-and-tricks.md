---
weight: 30
---

# Tips and Tricks

## Fading in renders

Instead of rendering from top-to-bottom, or left-to-right, you can play with
the order that things are rendered in.

If you're just printing out using the pipe to netcat trick as in the
[Examples]({{< relref "/docs/examples" >}}), then we can just use the power of
the `shuf` command to get a nice fade-in!

For example, with the [square example]({{< relref "/docs/examples" >}}#square):

    $ python3 square.py | shuf | nc pixelflut.jedevc.com 1337

Note that this won't work with scripts that continuously render, since `shuf`
reads the whole input before outputing anything. If you want to fade in with
continuous rendering, then you need to randomize the order that you write
commands to the server in yourself.

## Capture an image from the stream

It can be fun to capture an image from the stream, and then to use that to
create even weirder renders.

You can use the all-powerful `ffmpeg` to do this, if you know the URL of the
stream file:

    $ ffmpeg -y -sseof -1 -i <stream-file> -vframes 1 capture.png

However, if you're using a video player like YouTube or Twitch, it's reasonable
likely you won't have access to that URL. You can extract it using a tool like
`youtube-dl`:

    $ youtube-dl -g 'https://www.youtube.com/watch?v=_Lz69TixAn0'

You can combine both of these to a powerful single line command:

    $ ffmpeg -y -sseof -1 -i "$(youtube-dl -g 'https://www.youtube.com/watch?v=_Lz69TixAn0' | head -n 1)" -vframes 1 capture.png

Though, I'm sure that there are better ways!

