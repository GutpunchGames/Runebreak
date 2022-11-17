.PHONY: protos

ensure_protos_dir:
	if not exist "generated" mkdir "generated"

protos:
	protoc -I . accounts.proto --go-grpc_out=. --go_out=.