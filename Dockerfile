FROM alpine:latest

RUN apk update && apk add --no-cache \
  build-base

COPY . /workspace
WORKDIR /workspace
