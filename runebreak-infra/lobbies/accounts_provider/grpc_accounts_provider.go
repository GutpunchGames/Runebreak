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
	resp, err := provider.rpcGetAccount(userId)
	if err != nil {
		return nil, err
	}

	return &AccountRecord{UserId: resp.Account.UserId, Username: resp.Account.Username}, nil
}

func (provider liveAccountsProvider) GetAccounts(userIds []string) ([]*AccountRecord, error) {
	resp, err := provider.rpcGetAccounts(userIds)
	if err != nil {
		return nil, err
	}

	accRecords := make([]*AccountRecord, 0)
	for _, user := range resp.Accounts {
		accRecords = append(accRecords, &AccountRecord{UserId: user.UserId, Username: user.Username})
	}
	return accRecords, nil
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
		return resp, nil
	} else {
		provider.logger.Printf("got error: %s\n", err)
		return nil, err
	}
}

func (provider liveAccountsProvider) rpcGetAccounts(userId []string) (*accounts.GetAccountsResponse, error) {
	conn, err := grpc.Dial("accounts:9090", grpc.WithInsecure())
	if err != nil {
		panic(err)
	}
	defer conn.Close()

	accountsClient := accounts.NewAccountsClient(conn)
	req := accounts.GetAccountsRequest{UserId: userId}
	ctx, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	resp, err := accountsClient.GetAccounts(ctx, &req)
	if err == nil {
		return resp, nil
	} else {
		provider.logger.Printf("got error: %s\n", err)
		return nil, err
	}
}