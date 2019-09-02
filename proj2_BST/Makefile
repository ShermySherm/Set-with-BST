project=ProjectStackBST

objs = main.o

CC=g++
CPPFLAGS := $(CPPFLAGS) -std=c++11 -Wall -g

output_file = $(project)

.PHONY: all
all: $(output_file)

$(output_file): BinarySearchTree.h Set.h main.cpp
	sed -i "s/^#define UNIT_TEST/\/\/#define UNIT_TEST/g" ./BinarySearchTree.h 2>/dev/null | true;
	sed -i "" "s/^#define UNIT_TEST/\/\/#define UNIT_TEST/g" ./BinarySearchTree.h 2>/dev/null | true;
	sed -i "s/^#define UNIT_TEST/\/\/#define UNIT_TEST/g" ./Set.h 2>/dev/null | true;
	sed -i "" "s/^#define UNIT_TEST/\/\/#define UNIT_TEST/g" ./Set.h 2>/dev/null | true;

	$(CC) $(CPPFLAGS) main.cpp -o $(project)

.PHONY: test
test:
	sed -i "s/\/\/#define UNIT_TEST/#define UNIT_TEST/g" ./BinarySearchTree.h | true; \
	sed -i "" "s/\/\/#define UNIT_TEST/#define UNIT_TEST/g" ./BinarySearchTree.h 2>/dev/null | true;\
	sed -i "s/\/\/#define UNIT_TEST/#define UNIT_TEST/g" ./Set.h 2>/dev/null | true;\
	sed -i "" "s/\/\/#define UNIT_TEST/#define UNIT_TEST/g" ./Set.h 2>/dev/null | true;\
	cp -f Set.h BinarySearchTree.h Exceptions.h tests/src; \
	cd ./tests; \
	cmake CMakeLists.txt; \
	make && ./RunBSTProjectTests; \
	cd .. ; \

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.gch
	rm -f $(project)

	cd ./tests; \
	./cmake_clean; \
	cd .. ; \
