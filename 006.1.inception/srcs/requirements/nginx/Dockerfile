FROM debian:bullseye

RUN apt-get update && apt-get install -y nginx openssl

EXPOSE 443

COPY ./conf/default /etc/nginx/sites-enabled/

COPY ./tools/nxstart.sh /

RUN chmod +x /nxstart.sh

ENTRYPOINT [ "/nxstart.sh" ]

CMD [ "nginx", "-g", "daemon off;" ]