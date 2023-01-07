package gatewaydispatcher

import (
	"context"
	"time"

	gatewayPbs "github.com/GutpunchGames/Runebreak/runebreak-infra/protos/gateway"
	"github.com/hashicorp/go-hclog"
	"google.golang.org/grpc"
)

type GatewayDispatcher struct {
	logger hclog.Logger
}

func NewDispatcher(logger hclog.Logger) GatewayDispatcher {
	return GatewayDispatcher{
		logger: logger,
	}
}

func (dispatcher GatewayDispatcher) DispatchBulk(
	userIds []string,
	messageType gatewayPbs.Type,
	payload []byte,
) error {
	conn, err := grpc.Dial("gateway:9091", grpc.WithInsecure())
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	gatewayClient := gatewayPbs.NewGatewayClient(conn)
	req := gatewayPbs.DispatchMessageRequest{}
	req.Recipients = userIds

	req.Message = &gatewayPbs.Message{}
	req.Message.Payload = payload
	req.Message.Type = messageType

	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	_, err = gatewayClient.DispatchWSMessage(ctx, &req)
	if err != nil {
		dispatcher.logger.Info("dispatcher error", err)
	} 

	return err
}