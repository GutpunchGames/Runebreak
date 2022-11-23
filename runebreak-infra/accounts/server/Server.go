package server

import (
	"context"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/services/protos/accounts"
	"github.com/hashicorp/go-hclog"
)

type AccountsServer struct {
	Logger hclog.Logger
	accounts.UnimplementedAccountsServer
}

func NewServer(l hclog.Logger) *AccountsServer {
	return &AccountsServer{Logger: l, UnimplementedAccountsServer: accounts.UnimplementedAccountsServer{}}
}

func (server *AccountsServer) DoThing() {
	server.Logger.Info("did a thing")
}

func (server AccountsServer) GetExample(ctx context.Context, req *accounts.ExampleRequest) (*accounts.ExampleResponse, error) {
	server.Logger.Info("Handle GetRate", "base", req.ParamOne)
	return &accounts.ExampleResponse{Rate: 0.5}, nil
}