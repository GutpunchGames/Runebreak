#!/bin/bash

service mariadb start
mysql --execute="CREATE DATABASE IF NOT EXISTS accounts"
mysql accounts < init-db.sql

go run main.go 9090