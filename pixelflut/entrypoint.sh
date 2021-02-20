#!/bin/bash

set -e

INRES="800x600"
OUTRES="800x600"
FPS="30"

unclutter -idle 0 &
/pixelflut/pixelnuke &
ffmpeg \
    -f x11grab \
    -i $DISPLAY \
    -video_size $INRES \
    -s $INRES \
    -r $FPS \
    -f flv \
    -s $OUTRES \
    -vcodec libx264 \
    -keyint_min $FPS \
    -g $FPS \
    -vprofile baseline \
    -pix_fmt yuv420p \
    -preset ultrafast -tune zerolatency \
    -threads 0 \
    -strict experimental \
    rtmp://stream/show/stream

