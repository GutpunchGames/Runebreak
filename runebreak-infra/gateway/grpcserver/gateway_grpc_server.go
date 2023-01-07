package gatewaygrpcserver

import (
	"context"
	"errors"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/gateway/connections"
	gatewayPbs "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/gateway"
	"github.com/hashicorp/go-hclog"
)

type GatewayGRPCServer struct {
	Logger hclog.Logger
	connectionManager *connections.ConnectionManager
	gatewayPbs.UnimplementedGatewayServer
}

func NewServer(l hclog.Logger, connectionManager *connections.ConnectionManager) *GatewayGRPCServer {
	return &GatewayGRPCServer{
		Logger: l,
		connectionManager: connectionManager,
		UnimplementedGatewayServer: gatewayPbs.UnimplementedGatewayServer{},
	}
}

func (server GatewayGRPCServer) Create(ctx context.Context, req *gatewayPbs.DispatchMessageRequest) (*gatewayPbs.DispatchMessageResponse, error) {
	return nil, errors.New("unimplemented")
}
