.PHONY: protos

ensure_protos_dir:
	mkdir -p "protos\gateway"

protos: ensure_protos_dir
	protoc -I protos/ protos/gateway.proto --go-grpc_out=protos/ --go_out=protos/