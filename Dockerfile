FROM ubuntu:latest

RUN apt update

# gcc compiler
RUN apt install build-essential -y

# man pages
RUN apt install manpages-dev -y

# valgrind
RUN DEBIAN_FRONTEND=noninteractive apt install g++ valgrind -y
RUN apt install automake -y

WORKDIR /home

ENTRYPOINT [ "bash" ]

## To Run In Bash
#(1) docker build -t valgrind .
#(2) docker run -it --mount type=bind,src="$(pwd)",target=/home valgrind