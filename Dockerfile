FROM ubuntu:22.04

RUN DEBIAN_FRONTEND=noninteractive \
apt update \
&& apt -y install vim \
&& apt -y install make \
&& apt -y install build-essential \
&& apt -y install clang \
&& apt -y install gcc

WORKDIR /mCpricer

RUN make debug \
&& ./main
