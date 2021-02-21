#!/bin/bash

set -e

if [ -z "$SCREEN_WIDTH" ]; then
    SCREEN_WIDTH=800
fi
if [ -z "$SCREEN_HEIGHT" ]; then
    SCREEN_HEIGHT=600
fi
export SCREEN_WIDTH SCREEN_HEIGHT

xvfb-run -n 99 --server-args="-screen 0 ${SCREEN_WIDTH}x${SCREEN_HEIGHT}x24" /runner.sh

