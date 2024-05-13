#!/bin/bash

service mariadb start

sleep 3

mariadb -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE_NAME;"
mariadb -e "CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';"
mariadb -e "GRANT ALL PRIVILEGES ON $MYSQL_DATABASE_NAME.* TO '$MYSQL_USER'@'%';"
mariadb -e "FLUSH PRIVILEGES;"
mariadb -e "SHUTDOWN;"

exec "$@"