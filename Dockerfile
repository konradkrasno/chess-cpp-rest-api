FROM ubuntu

RUN apt-get update && apt-get install -y g++ make
RUN apt-get install -y -8 -60 libcpprest-dev

EXPOSE 80

WORKDIR /cpp-rest-api
