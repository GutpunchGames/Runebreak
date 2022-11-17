.PHONY: protos

ensure_protos_dir:
	if not exist "protos\gateway" mkdir "protos\gateway"

protos: ensure_protos_dir
	protoc -I protos/ protos/gateway.proto --go-grpc_out=protos/ --go_out=protos/