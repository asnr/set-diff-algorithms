CFLAGS=--std=c99 -O6 -funroll-loops
CXXFLAGS=-O6

TODO=5000000

usernames.txt: gen_usernames
	./gen_usernames $(TODO) > usernames.txt.tmp
	mv usernames.txt.tmp usernames.txt

gen_usernames: gen_usernames.o
	$(CXX) -o $@ gen_usernames.o

soln_2: soln_2_c/soln.c
	gcc -O3 -Wall $< -o $@