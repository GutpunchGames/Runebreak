FROM golang

# generic config
RUN apt-get update -y
RUN apt-get upgrade -y

# todo: don't commit secret keys lol
RUN git config --global url."https://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:@github.com/".insteadOf "https://github.com/"

# mariadb
RUN apt-get install -y mariadb-server

# now we're podracing
WORKDIR /accounts
COPY . .
RUN chmod 777 ./cmd.sh
CMD ["./cmd.sh"]