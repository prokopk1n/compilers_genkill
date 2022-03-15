all: du
du: du.cpp
	g++ du.cpp -L./lib -lqbe -I ./include -D DEBUG -o du
test: du
	bash run.sh
clean:
	rm -rf du
	rm -R outputs
run: du.cpp
	g++ du.cpp -L./lib -lqbe -I ./include -o du
	./du