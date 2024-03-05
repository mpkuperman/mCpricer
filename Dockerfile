FROM ubuntu:22.04

RUN DEBIAN_FRONTEND=noninteractive \
apt update \
&& apt -y install vim \
&& apt -y install make \
&& apt -y install build-essential \
&& apt -y install clang \
&& apt -y install gcc

COPY /mCpricer usr/src/mCpricer
WORKDIR /usr/src/mCpricer

RUN make debug \
&& ./main
