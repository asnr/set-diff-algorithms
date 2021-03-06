Set difference algorithms
=========================

Several different hashmap-based set difference algorithms. The sets are composed of short strings.

This is inspired by an interview problem posed by Dustin Sallings a few years ago. The post URL is [http://dustin.sallings.org/2011/09/20/catching-up.html](http://dustin.sallings.org/2011/09/20/catching-up.html), see the section called "the programming challenge". I've quoted the relevant part below:

>The basic problem involves reading a file with a bunch (~1M) usernames into a structure in memory and providing a function to tell you whether a given user is in it.

>Candidates invariably want to build something like a trie, but often fall into this trap where they believe pointers don’t take up space (even arrays of pointers, apparently). I wanted to give it a go, so I did a plain C implementation that ended up being fewer lines of code than what we’d got from our candidates, used about 10% of the memory and ran many times faster.

>I sucked some other people’s time into this as well. If you’d like to offer a suggestion, here’s a tool that generates 100M usernames for you to try out. (finally got to use a bloom filter, yay! (and no, the answer doesn’t involve a bloom filter unless you want to do a times/space tradeoff thing)

>If you want to try it, note that my program is < 100 lines of plain C (no external libraries) and uses 1.26GB of RAM on my macbook for 100,000,000 usernames. It loads and indexes them in 84 seconds and spends another 31 seconds verifying it can find each of the 100,000,000 users within that list (+ 4 more that are known to not be there). Please do better than that.

Running solutions
-----------------

First argument is the filename of the usernames text file.

For the C solutions that implement hashmaps, the second argument is the number of entries in the hashmap.


Measuring performance
---------------------

```sh
$ /usr/bin/time -l $EXECUTABLE $ARGS
```

with instruments:

```sh
$ instruments -t "Time Profiler" -D $TRACE_OUTPUT_FILE $EXECUTEABLE usernames.txt 10000000
```
