FROM golang
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y protobuf-compiler
WORKDIR /gateway
COPY . .
CMD ["go", "run", "main.go", "9090"]
EXPOSE 9090