package accounts_provider

import (
	"context"
	"log"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/accounts"
	"google.golang.org/grpc"
)

type liveAccountsProvider struct {
	logger *log.Logger
}

func newLiveAccountsProvider(logger *log.Logger) liveAccountsProvider {
	return liveAccountsProvider{logger: logger}
}

func (provider liveAccountsProvider) GetAccount(userId string) (*AccountRecord, error) {
	account, err := provider.rpcGetAccount(userId)
	if err != nil {
		return nil, err
	}

	return &AccountRecord{userId: account.UserId, username: account.Username}, nil
}

func (provider liveAccountsProvider) rpcGetAccount(userId string) (*accounts.GetAccountResponse, error) {
	conn, err := grpc.Dial("accounts:9090", grpc.WithInsecure())
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	accountsClient := accounts.NewAccountsClient(conn)
	req := accounts.GetAccountRequest{UserId: userId}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	resp, err := accountsClient.GetAccount(ctx, &req)
	if err == nil {
		provider.logger.Printf("got response: %s\n", resp)
		return resp, nil
	} else {
		provider.logger.Printf("got error: %s\n", err)
		return nil, err
	}
}