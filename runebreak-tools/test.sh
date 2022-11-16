#!/bin/bash
# todo: ensure working directory is root of project
pushd .
cd runebreak-infra
go run services/gateway/main/main.go 9090
popd