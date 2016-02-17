/* Author: Dustin Sallings.
   Original copy: https://gist.github.com/dustin/1189242 */

#include <string>
#include <iostream>
#include <algorithm>

#include <cstdlib>

#include "bloom_filter.hpp"

using namespace std;

string words("abcdefghijklmnopqrstuvwxyz"
             "0123456789");

const int report_every(100000);
const int max_permutations(1000);

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Need to tell me how many you want." << endl;
        exit(64); // EX_USAGE
    }

    srand(718472382); // Now with determinism.

    int todo(atoi(argv[1]));
    bloom_filter filter(todo, 0.0001, time(NULL));

    int dups(0);
    int since(0);
    for (int done = 0; done < todo;) {
        int length = (rand() % 6) + 6;
        random_shuffle(words.begin(), words.end());
        string word(words.substr(0, length));

        int permutations = rand() % max_permutations;
        for (int j = 0; j < permutations && done < todo; ++j) {
            if (!next_permutation(word.begin(), word.end())) {
                break;
            }

            if (filter.contains(word)) {
                ++dups;
            } else {
                ++done;
                filter.insert(word);
                cout << word << "\n";
            }

            if (done % report_every == 0 && dups > 0) {
                cerr << dups << " dups in the last " << since << endl;
                dups = 0;
                since = 0;
            }
            ++since;
        }
    }

    return 0;
}
