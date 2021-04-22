FROM ubuntu:20.04

ARG HUGO_VERSION=0.82.1

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y curl

RUN curl -L https://github.com/gohugoio/hugo/releases/download/v${HUGO_VERSION}/hugo_extended_${HUGO_VERSION}_Linux-64bit.tar.gz \
    | tar xvz -C /usr/local/bin hugo 

WORKDIR /site
COPY . ./
RUN hugo && ls -lh


FROM nginx
COPY --from=0 /site/public/ /usr/share/nginx/html

