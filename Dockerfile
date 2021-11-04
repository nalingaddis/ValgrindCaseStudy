FROM ubuntu:latest

# install gcc compiler
RUN apt update
RUN apt install build-essential -y
RUN apt install manpages-dev -y



ENTRYPOINT [ "bash" ]

## To Run In Bash
#(1) docker build -t valgrind .
#(2) docker run -it --mount type=bind,src="$(pwd)",target=/home valgrind