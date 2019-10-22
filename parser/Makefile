.PHONY= parse_test

parse_test:parser.o common.o
	gcc -Wall -o parser parser.o common.o -DTEST -std=c99
parser.o: parser.c parser.h common.h
	gcc -Wall -c parser.c common.c -DTEST -std=c99
clean:
	rm -f parser.o common.o parser
