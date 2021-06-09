all: build run

clean:
	rm -rf build

build: clean
	mkdir build
	cd build && cmake .. && make

run:
	./build/WanderingClouds
