#!/bin/bash

service mariadb start
mysql --execute="CREATE DATABASE IF NOT EXISTS testdb"
mysql --execute="CREATE USER 'accountsservice'@'localhost' IDENTIFIED BY 'accountsservice_pw';"
mysql --execute="GRANT ALL PRIVILEGES ON *.* TO 'accountsservice'@'localhost' WITH GRANT OPTION;"

go run main.go 9090