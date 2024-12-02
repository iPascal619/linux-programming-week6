#ifndef SHARED_LIBRARY_H
#define SHARED_LIBRARY_H

#define MAX_NAMES 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char names[MAX_NAMES][MAX_NAME_LENGTH];
    int count;
} NameDatabase;

// Function prototypes with error handling
int read_names(NameDatabase* db, const char* filename);
int sort_names(NameDatabase* db);
int write_sorted_names(const NameDatabase* db, const char* output_filename);
int count_entries(const char* filename);

#endif