FROM ubuntu:20.10

# Install dependencies
RUN apt-get -y update && \
    apt-get -y upgrade
RUN DEBIAN_FRONTEND=noninteractive apt-get -y install \
    build-essential \
    clang-11 lld-11 \
    libevent-dev \
    libglew-dev \
    libglfw3-dev

# Build pixel nuke
COPY pixelnuke/ /pixelflut
WORKDIR /pixelflut
RUN make CC=clang-11 LDFLAGS=-fuse-ld=lld


FROM ubuntu:20.10

# Install dependencies
RUN apt-get -y update && \
    apt-get -y upgrade
RUN DEBIAN_FRONTEND=noninteractive apt-get -y install \
    libevent-2.1-7 libevent-pthreads-2.1-7 libglew2.1 libglfw3 \
    xvfb unclutter \
    ffmpeg \
    wait-for-it

# Copy files
COPY --from=0 /pixelflut/pixelnuke /pixelnuke
COPY ./entrypoint.sh /entrypoint.sh
COPY ./runner.sh /runner.sh

EXPOSE 1337

CMD wait-for-it stream:1935 -- /entrypoint.sh

