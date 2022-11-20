FROM golang
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y protobuf-compiler
WORKDIR /accounts
COPY . .
CMD ["go", "run", "main.go", "9090"]