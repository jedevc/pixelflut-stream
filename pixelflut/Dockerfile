FROM ubuntu:20.10

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
COPY pixelnuke/ /pixelflut
WORKDIR /pixelflut
RUN make CC=clang-11 LDFLAGS=-fuse-ld=lld

# Copy helper scripts
COPY ./entrypoint.sh /entrypoint.sh
COPY ./runner.sh /runner.sh

CMD wait-for-it stream:1935 -- /entrypoint.sh

