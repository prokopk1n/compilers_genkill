all: gk
gk: gk.cpp
	g++ gk.cpp -L./lib -lqbe -I ./include -D DEBUG -o gk
test: gk
	bash run.sh
clean:
	rm -rf gk
	rm -R outputs
run: gk.cpp
	g++ gk.cpp -L./lib -lqbe -I ./include -o gk
	./gk