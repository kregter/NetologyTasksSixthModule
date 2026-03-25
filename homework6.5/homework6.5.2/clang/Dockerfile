FROM ubuntu:24.04
RUN apt-get update && apt-get install -y clang
COPY . /usr/src/code
WORKDIR /usr/src/code
RUN apt-get update && apt-get install -y cmake
RUN cmake CMakeLists.txt
RUN make