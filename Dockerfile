FROM debian:stretch

RUN apt-get update && apt-get install -y libtesseract-dev libleptonica-dev cmake build-essential 

WORKDIR /project