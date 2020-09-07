FROM ubuntu

RUN apt-get update && apt-get install -y g++ make
RUN apt-get install -y libcpprest-dev libcurl4-gnutls-dev

EXPOSE 80

WORKDIR /cpp-rest-api
