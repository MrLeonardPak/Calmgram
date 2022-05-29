clean:
	rm -rf build && \
	clear

packages:
	sudo apt-get update -y && \
	sudo apt-get install build-essential && \
	sudo apt-get install -y cppcheck clang-tidy python3-pip libc6-dbg lcov libgtest-dev && \
	pip3 install cpplint && \
	sudo apt-get install valgrind

build:
	mkdir build && \
	cd build && \
	cmake -D TESTS=ON ../project  && \
	make

analysis: 
	./linters/run.sh

test:
	./build/tests/test_calc && \
	valgrind --tool=memcheck --leak-check=yes ./build/tests/test_calc

report:	
	lcov -t "build/tests/test_calc" -o coverage.info -c -d build/calculate_side_length