# FROM gcc:latest
# COPY . /usr/src/code
# WORKDIR /usr/src/code
# RUN g++ -o out.o main.cpp

FROM ubuntu:24.04
RUN apt-get update && apt-get install -y clang
COPY . /usr/src/code
WORKDIR /usr/src/code
RUN clang++ -o out.o main.cpp