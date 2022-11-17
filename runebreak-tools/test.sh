#!/bin/bash
# todo: ensure working directory is root of project
pushd .
cd runebreak-infra
go run services/gateway/main.go 9090 & go run services/accounts/main.go 9091 && fg
popd