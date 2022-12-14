package server

import (
	"context"
	"database/sql"
	"errors"
	"fmt"
	"strconv"
	"time"

	"github.com/GutpunchGames/Runebreak/runebreak-infra/protos/accounts"
	"github.com/hashicorp/go-hclog"
)

type AccountsServer struct {
	Logger hclog.Logger
	accounts.UnimplementedAccountsServer
}

func NewServer(l hclog.Logger) *AccountsServer {
	return &AccountsServer{Logger: l, UnimplementedAccountsServer: accounts.UnimplementedAccountsServer{}}
}

func (server AccountsServer) Register(ctx context.Context, req *accounts.UserAuthenticationRequest) (*accounts.UserAuthenticationResponse, error) {
	server.Logger.Info("Handle Register", "username", req.Username, "pw", req.Password)
	userId, err := server.createUser(req.Username, req.Password)
	if err == nil {
		return &accounts.UserAuthenticationResponse{UserId: strconv.FormatInt(*userId, 10), Username: req.Username}, nil
	} else {
		return nil, err
	}
}

func (server AccountsServer) createUser(username string, password string) (*int64, error) {
	fmt.Printf("attempting to interface with db\n")
	db, err := sql.Open("mysql", "accountsservice:accountsservice_pw@tcp(localhost:3306)/accounts")
    defer db.Close()

	if err != nil {
		fmt.Printf("bad stuff happened 1: %s\n", err)
		return nil, err
	}

	doesUserExist, err := server.doesUserExist(username)
	if err != nil {
		fmt.Printf("bad stuff happened 2: %s\n", err)
		return nil, err
	}

	if (doesUserExist != nil && *doesUserExist) {
		server.Logger.Error("User with username already exists.", "username", username)
		return nil, errors.New(fmt.Sprintf("User with username %s already exists.", username))
	}

	query := "INSERT INTO accounts(user_name, authentication_code) VALUES (?, ?)"
	ctx, cancelfunc := context.WithTimeout(context.Background(), 5 * time.Second)
    defer cancelfunc()

    stmt, err := db.PrepareContext(ctx, query)
    if err != nil {
		server.Logger.Error("Error when preparing SQL statement", "error", err)
		return nil, err
    }
    defer stmt.Close()

	res, err := stmt.ExecContext(ctx, username, password)  
	if err != nil {  
		server.Logger.Error("Error when inserting row into accounts table", "error", err)
		return nil, err
	}
	rows, err := res.RowsAffected()  
	if err != nil {  
		server.Logger.Error("Error when finding rows affected", "error", err)
		return nil, err
	}
	server.Logger.Info(fmt.Sprintf("%d users created", rows))

    var newUserId int64
    query = "SELECT LAST_INSERT_ID()"
    err = db.QueryRow(query).Scan(&newUserId)

	if (err != nil) {
		server.Logger.Error("Error accessing new user", "error", err)
		return nil, err
	}

	return &newUserId, nil
}

func (server AccountsServer) doesUserExist(username string) (*bool, error) {
	fmt.Printf("attempting to interface with db\n")
	db, err := sql.Open("mysql", "accountsservice:accountsservice_pw@tcp(localhost:3306)/accounts")
    defer db.Close()

	if err != nil {
		fmt.Printf("bad stuff happened 1: %s\n", err)
		return nil, err
	}

	innerQuery := fmt.Sprintf("SELECT user_id FROM accounts WHERE user_name LIKE '%s'", username)
	return server.doesRowExist(db, innerQuery)
}

func (server AccountsServer) doesRowExist(db *sql.DB, innerQuery string) (*bool, error) {
    var exists bool
    query := fmt.Sprintf("SELECT exists (%s)", innerQuery)
    err := db.QueryRow(query).Scan(&exists)
    if err != nil && err != sql.ErrNoRows {
		server.Logger.Error("error checking if row exists", "innerQuery", innerQuery, "error", err)
		return nil, err
    }
    return &exists, nil
}