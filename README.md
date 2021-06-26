# Pixelflut streaming

This is a handy little wrapper for hosting
[pixelflut](https://github.com/defnull/pixelflut), specifically pixelnuke,
along with some relevant documentation.

## Running

Despite the fact there's a `docker-compose.yaml` file *don't* run it directly -
bad things will happen, and nothing will work! Instead, use the `./composer`
utility script as documented below.

Before running either of the below, make a copy of `example.env` and modify the
environment variables as desired.

### Local

The simplest setup involves an entirely local RTMP server, which creates a
simple live stream. This is the most lightweight setup, involving the least
amount of fiddling around, but also probably the least reliable (unless you're
lucky enough to have your own CDN).

To run with a local NGINX RTMP server:

    $ ./composer local up

### Streaming service

To get better reliability and a better audience, you can also easily broadcast
to Twitch/YouTube/etc.

To run with a remote RTMP server:

    $ ./composer external up

Make sure to consult the relevant documentation for your livestreaming platform
of choice to get the exact values of `RTMP_URL` (the RTMP address to use) and
`STREAM_URL` (where viewers can go to find the stream).

