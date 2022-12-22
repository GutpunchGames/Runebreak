-- we create the db in cmd.sh, so no need to do so here.

CREATE USER 'accountsservice'@'localhost' IDENTIFIED BY 'accountsservice_pw';
GRANT ALL PRIVILEGES ON *.* TO 'accountsservice'@'localhost' WITH GRANT OPTION;
CREATE TABLE accounts (
    user_id int NOT NULL AUTO_INCREMENT,
    user_name varchar(32) NOT NULL,
    PRIMARY KEY (user_id)
)
