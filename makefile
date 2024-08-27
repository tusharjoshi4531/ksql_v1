build:
	g++ src/main.cpp \
	src/storage/data_config.cpp \
	src/storage/bytes_writer.cpp \
	src/storage/bytes_reader.cpp \
	src/storage/bytes_parser.cpp \
	src/data/integer.cpp \
	src/data/double.cpp \
	src/data/chars.cpp \
	src/test/storage/double_test.cpp \
	src/test/storage/string_test.cpp \
	-o main.out

run:
	./main.out

start: build run