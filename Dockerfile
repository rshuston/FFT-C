FROM debian:bookworm
USER root
RUN apt update
RUN apt install -y \
  sudo \
  pkg-config \
  vim \
  make \
  gcc \
  check \
  valgrind

RUN useradd -m frodo && echo "frodo:baggins" | chpasswd && usermod -aG sudo frodo

USER frodo
WORKDIR /home/frodo
CMD /bin/bash
