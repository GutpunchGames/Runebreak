FROM golang

# generic config
RUN apt-get update -y
RUN apt-get upgrade -y

# todo: don't commit secret keys lol
RUN git config --global url."https://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:@github.com/".insteadOf "https://github.com/"

# now we're podracing
WORKDIR /lobbies
COPY . .
RUN go mod tidy
CMD ["go", "run", "main.go", "9090"]