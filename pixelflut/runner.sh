#!/bin/bash

set -e

INRES="${SCREEN_WIDTH}x${SCREEN_HEIGHT}"
OUTRES="${SCREEN_WIDTH}x${SCREEN_HEIGHT}"
FPS="30"

unclutter -idle 0 &
/pixelnuke &
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

