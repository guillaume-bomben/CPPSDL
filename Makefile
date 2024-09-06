all:
	cmake -G "MinGW Makefiles" -B build
	cmake --build build

clean:
	rm -rf build

run:
	./build/bin/main