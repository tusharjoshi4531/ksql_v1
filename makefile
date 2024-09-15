build:
	g++ src/main.cpp \
	src/storage/data_config.cpp \
	src/storage/bytes_writer.cpp \
	src/storage/bytes_reader.cpp \
	src/storage/bytes_parser.cpp \
	src/data/data_type.cpp \
	src/data/integer.cpp \
	src/data/double.cpp \
	src/data/chars.cpp \
	src/data/data_type_factory.cpp \
	src/db/document_factory.cpp \
	src/db/document.cpp \
	src/db/page.cpp \
	src/db/strict_document.cpp \
	src/test/storage/double_test.cpp \
	src/test/storage/string_test.cpp \
	src/test/db/document_test.cpp \
	src/test/db/page_test.cpp \
	-o main.out

run:
	./main.out

start: build run