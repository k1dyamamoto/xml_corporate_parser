SRC=xmlparser.cpp objects.cpp commands.cpp main.cpp

exec: $(SRC)
	g++ $(SRC) -o $@
clean:
	rm exec
