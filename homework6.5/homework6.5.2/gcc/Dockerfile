FROM gcc:latest
COPY . /usr/src/code
WORKDIR /usr/src/code
RUN apt-get update && apt-get install -y cmake
RUN cmake CMakeLists.txt
RUN make