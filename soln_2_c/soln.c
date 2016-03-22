#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct DictEntry
{
    struct DictEntry *next;
    char *val;  // NUL when Dict Entry is empty
} DictEntry;

typedef struct Dict
{
    DictEntry *entries;
    uint32_t capacity;
} Dict;

Dict init_dict(uint32_t capacity);
void add_to_dict(Dict*, char*);
uint32_t is_in(Dict, char*);  // 1 if in, 0 if not

int main(int argc, char *argv[])
{
    char *filename = argv[1];

    Dict dict = init_dict(2e6);

    printf("filename = %s\n", filename);

    uint32_t max_file_length = 1e9;
    char *file_buf = (char *) calloc(max_file_length + 1, sizeof(char));
    char *end_of_file_buf = file_buf + max_file_length + 1;
    // uint32_t max_line_length = 511;
    // char line_buf[max_line_length + 1];

    char *start_of_line = file_buf;
    char *file_it = file_buf;
    uint32_t line_idx = 0;
    // uint32_t char_idx = 0;
    // uint32_t col_idx = 0;

    FILE *fp = fopen(filename, "r");
    char ch = getc(fp);
    // This assumes last character is a newline '\n'
    while (ch != EOF) {

        if (file_it >= end_of_file_buf) {
            exit(1);
        }

        if (ch == '\n') {
            (*file_it) = '\0';
            
            // line_buf complete! Copy buffer, then add to dictionary
            // uint32_t length = col_idx + 1;
            // char *new_buff = calloc(length, sizeof(char));
            // memcpy(new_buff, line_buf, length);
            add_to_dict(&dict, start_of_line);
            
            if (line_idx < 10) {
                printf("%s\n", start_of_line);
            }

            file_it++;
            start_of_line = file_it;
            line_idx++;
            // file_idx++;            
            // col_idx = 0;
        } else {
            // if (col_idx >= max_line_length) {
            //     exit(1);
            // }            
            (*file_it) = ch;
            file_it++;
            // col_idx++;
        }

        ch = getc(fp);
    }

    printf("Read %d lines.\n", line_idx);

    fclose(fp);
    return(0);
}

Dict init_dict(uint32_t capacity) {
    Dict ret;
    ret.capacity = capacity;
    ret.entries = (DictEntry*) calloc(capacity, sizeof(DictEntry));
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
    
    uint32_t hash = larsons_hash(str) % (dict->capacity);

    DictEntry *curr_entry = dict->entries + hash;
    while (curr_entry->val != 0) {
        if (strcmp(str, curr_entry->val) == 0) {
            // str is already in dictionary
            return;
        }
        curr_entry = curr_entry->next;
    }

    curr_entry->val = str;
    curr_entry->next = (DictEntry*) calloc(1, sizeof(DictEntry));
}

uint32_t is_in(Dict dict, char* str) {
    uint32_t hash = larsons_hash(str) % (dict.capacity);

    DictEntry *curr_entry = dict.entries + hash;
    while (curr_entry->val != 0) {
        if (strcmp(str, curr_entry->val) == 0) {
            // str is already in dictionary
            return(1);
        }
        curr_entry = curr_entry->next;
    }
    return(0);
}
