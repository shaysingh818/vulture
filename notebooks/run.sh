
sudo rm vulture.db
touch vulture.db
sqlite3 vulture.db ".read sqlscripts/create_tables.sql"
sqlite3 vulture.db ".read sqlscripts/insert.sql"

g++ main.cpp controllers.cpp db.cpp -lsqlite3
./a.out
