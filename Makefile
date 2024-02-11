demo:
	g++ main.cpp IniFile.cpp -I *.h --std=c++20 -o demo
run:
	g++ main.cpp IniFile.cpp -I *.h --std=c++20 -o demo&&./demo
clean:
	rm demo
