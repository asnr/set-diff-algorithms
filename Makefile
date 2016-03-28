CFLAGS=--std=c99 -O6 -funroll-loops
CXXFLAGS=-O6

TODO=5000000

usernames.txt: gen_usernames
	./gen_usernames $(TODO) > usernames.txt.tmp
	mv usernames.txt.tmp usernames.txt

gen_usernames: gen_usernames.o
	$(CXX) -o $@ gen_usernames.o

soln_3_chaining_hashmap: solutions/soln_3_chaining_hashmap.c
	gcc -O3 -Wall $< -o $@

soln_4_open_addressing_hashmap: solutions/soln_4_open_addressing_hashmap.c
	gcc -O3 -Wall $< -o $@
