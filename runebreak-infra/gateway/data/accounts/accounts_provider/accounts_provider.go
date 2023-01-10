package accounts_provider

import "log"

type AccountRecord struct {
	UserId   string
	Username string
}

type AccountsProvider interface {
	GetAccount(userId string) (*AccountRecord, error)
	GetAccounts(userIds []string) ([]*AccountRecord, error)
}

func NewAccountsProvider(logger *log.Logger) AccountsProvider {
	return newLiveAccountsProvider(logger)
}
