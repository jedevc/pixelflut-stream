FROM nginx

RUN apt-get update && \
    apt-get upgrade -y
RUN apt-get install -y nginx-full libnginx-mod-rtmp

COPY nginx.conf /etc/nginx/nginx.conf

