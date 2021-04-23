#!/bin/bash

set -e

INRES="${SCREEN_WIDTH}x${SCREEN_HEIGHT}"
OUTRES="${SCREEN_WIDTH}x${SCREEN_HEIGHT}"
FPS="30"

unclutter -idle 0 &
/pixelnuke &
ffmpeg \
    -f lavfi -i anullsrc \
    -f x11grab -video_size $INRES -s $INRES -r $FPS -i $DISPLAY \
    -f flv \
    -s $OUTRES \
    -g $FPS \
    -keyint_min $FPS \
    -acodec aac -ar 44100 -b:a 128k \
    -vcodec libx264 \
    -vprofile baseline \
    -pix_fmt yuv420p \
    -preset ultrafast -tune zerolatency \
    -strict experimental \
    -threads 0 \
    "$RTMP"

