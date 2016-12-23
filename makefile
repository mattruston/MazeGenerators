build: 
	g++ RunMaze.cpp -o RunMaze

run: build
	./RunMaze

clean:
	rm -f RunMaze