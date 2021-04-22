---
weight: 10
---

# Stream

The stream is provided as an HLS file, which can be streamed by most modern
media players, for example, by [VLC](https://www.videolan.org/vlc/) or `ffplay`.

You can access the URL directly at `http://stream.pixelflut.jedevc.com/hls/stream.m3u8`.

To play it using VLC (recommended):

    $ vlc "http://stream.pixelflut.jedevc.com/hls/stream.m3u8"

To play it from the command line using ffplay:

    $ ffplay "http://stream.pixelflut.jedevc.com/hls/stream.m3u8"

You can also capture a single frame from the stream to `capture.png` easily using `ffmpeg`:

    $ ffmpeg -y -i "https://stream.pixelflut.jedevc.com/dash/stream.mpd" -vframes 1 capture.png

