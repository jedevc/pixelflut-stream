FROM ubuntu:latest

# Install dependencies
RUN apt-get -y update && \
    apt-get -y upgrade
RUN DEBIAN_FRONTEND=noninteractive apt-get -y install \
    build-essential \
    libevent-dev \
    libglew-dev \
    libglfw3-dev \
    xvfb \
    ffmpeg \
    xdotool \
    unclutter \
    clang-11 lld-11 \
    wait-for-it

# Build pixel nuke
COPY pixelflut/pixelnuke /pixelflut
WORKDIR /pixelflut
RUN sed -i -e "s/px_width = 1024/px_width = 1920/" -e "s/px_height = 1024/px_height = 1080/" -e "s/1024/1920/g" pixelnuke.c && \
    sed -i -e 's/glfwCreateWindow(800, 600, "Pixelflut", NULL, NULL);/glfwCreateWindow(1920, 1080, "Pixelflut", NULL, NULL);/' -e "s/1024/1920/g" canvas.c;
RUN make CC=clang-11 LD=lld-11

EXPOSE 1337
COPY ./entrypoint.sh /entrypoint.sh
CMD wait-for-it stream:1935 -- xvfb-run -n 99 --server-args="-screen 0 1920x1080x24" /entrypoint.sh

