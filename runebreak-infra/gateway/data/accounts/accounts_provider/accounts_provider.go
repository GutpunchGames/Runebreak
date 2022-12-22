package accounts_provider

import "log"

type AccountRecord struct {
	userId   string
	username string
}

type AccountsProvider interface {
	GetAccount(userId string) (*AccountRecord, error)
}

func NewAccountsProvider(logger *log.Logger) AccountsProvider {
	return newLiveAccountsProvider(logger)
}
