test:
	cc main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./a.out

clean:
	rm -rf ./a.out
