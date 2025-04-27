FROM ubuntu:latest
RUN apt-get update && apt-get -y install build-essential
RUN apt-get update && apt-get install -y iproute2
COPY  . /workspace
WORKDIR /workspace
RUN ip addr
CMD ["ip", "addr"]
