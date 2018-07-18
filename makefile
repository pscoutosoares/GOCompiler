CC = go build
FLAGS = -i

all: exemplo1.go
	$(CC) -o exemplo $(FLAGS)
