FROM golang
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y protobuf-compiler
RUN git config --global url."https://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:@github.com/".insteadOf "https://github.com/"
WORKDIR /accounts
COPY . .
CMD ["go", "run", "main.go", "9001"]