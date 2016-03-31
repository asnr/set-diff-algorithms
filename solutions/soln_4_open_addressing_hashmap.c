#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct Dict
{
    char **entries;
    uint32_t capacity;
    uint32_t size;
} Dict;

Dict init_dict(uint32_t capacity);
void add_to_dict(Dict*, char*);
uint32_t is_in(Dict, char*);  // 1 if in, 0 if not

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    uint64_t dict_size;
    if (argc > 2) {
        char *end;
        dict_size = strtol(argv[2], &end, 10);
    } else {
        dict_size = 200e6;
    }
    
    /***** Populate dictionary ******/

    Dict dict = init_dict(dict_size);

    uint32_t max_file_length = 1e9;
    // + 1 is for defensive terminating '\0' in case input doesn't end
    // with newline
    char *file_buf = (char *) calloc(max_file_length + 1, sizeof(char));
    char *end_of_file_buf = file_buf + max_file_length;
    
    char *start_of_line = file_buf;
    char *file_it = file_buf;
    uint32_t line_idx = 0;
    
    FILE *fp = fopen(filename, "r");
    char ch = getc(fp);
    while (ch != EOF) {
        if (file_it >= end_of_file_buf) {
            exit(1);
        }

        if (ch == '\n') {
            (*file_it) = '\0';
            
            // Finished reading line, add to dictionary
            add_to_dict(&dict, start_of_line);
            
            file_it++;
            start_of_line = file_it;
            line_idx++;
        } else {
            (*file_it) = ch;
            file_it++;
        }

        ch = getc(fp);
    }

    // Defensive null character at end of file buffer
    if (file_it > file_buf && *(file_it - 1) != '\0') {
        (*file_it) = '\0';
        file_it++;    
    }
    
    // end_of_file now points immediately after end of the buffer
    char *end_of_file = file_it;

    fclose(fp);

    printf("Read %d lines.\n", line_idx);


    /***** Check inputs against dictionary ******/
    printf("Printing what isn't in the dictionary...\n");
    start_of_line = file_buf;
    for (file_it = file_buf; file_it < end_of_file; file_it++) {
        if (*file_it == '\0') {
            if (!is_in(dict, start_of_line)) {
                printf("%s\n", start_of_line);
            }
            start_of_line = file_it + 1;
        }
    }

    if (!is_in(dict, "not in original usernames")) {
        printf("not in original usernames\n");
    }
    if (!is_in(dict, "also not in original usernames")) {
        printf("also not in original usernames\n");
    }
    if (!is_in(dict, "super also not")) {
        printf("super also not\n");
    }
    if (!is_in(dict, "super super not")) {
        printf("super super not\n");
    }

    return(0);
}

Dict init_dict(uint32_t capacity) {
    Dict ret;
    ret.capacity = capacity;
    ret.size = 0;
    ret.entries = (char**) calloc(capacity, sizeof(char*));
    return(ret);
}


uint32_t larsons_hash(char* str) {
    uint32_t hash = 0;
    while (*str) {
        hash = hash * 101 + (uint32_t) *str++;
    }
    return(hash);
}

// This method does *not* copy str; it is assumed that the memory str points
// to will not go out of scope/be overwritten.
void add_to_dict(Dict* dict, char* str) {
    if (dict->size == dict->capacity) {
        printf("Dictionary at capacity of %d entries, cannot add more entries.\n",
               dict->capacity);
        exit(1);
    }

    uint32_t hash = larsons_hash(str) % (dict->capacity);

    // Find the next available unused address
    char **end_of_dict = dict->entries + dict->capacity; 
    char **curr_entry = dict->entries + hash;
    while (*curr_entry != 0) {
        if (strcmp(str, *curr_entry) == 0) {
            // str is already in dictionary
            return;
        }

        curr_entry++;
        if (curr_entry >= end_of_dict) {
            curr_entry = dict->entries;
        }
    }

    dict->size++;
    (*curr_entry) = str;
}

uint32_t is_in(Dict dict, char* str) {
    uint32_t hash = larsons_hash(str) % (dict.capacity);

    char **end_of_dict = dict.entries + dict.capacity; 
    char **curr_entry = dict.entries + hash;
    while (*curr_entry != 0) {
        if (strcmp(str, *curr_entry) == 0) {
            return(1);
        }

        curr_entry++;
        if (curr_entry >= end_of_dict) {
            curr_entry = dict.entries;
        }
    }
    return(0);
}
