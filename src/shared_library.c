#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared_library.h"

int read_names(NameDatabase* db, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }

    db->count = 0;
    while (db->count < MAX_NAMES && 
           fscanf(file, "%s", db->names[db->count]) == 1) {
        db->count++;
    }

    fclose(file);
    return db->count;
}

int sort_names(NameDatabase* db) {
    if (db->count <= 0) {
        fprintf(stderr, "Error: No names to sort\n");
        return -1;
    }

    for (int i = 0; i < db->count - 1; i++) {
        for (int j = 0; j < db->count - i - 1; j++) {
            if (strcmp(db->names[j], db->names[j+1]) > 0) {
                char temp[MAX_NAME_LENGTH];
                strcpy(temp, db->names[j]);
                strcpy(db->names[j], db->names[j+1]);
                strcpy(db->names[j+1], temp);
            }
        }
    }
    return 0;
}

int write_sorted_names(const NameDatabase* db, const char* output_filename) {
    FILE* file = fopen(output_filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot write to file %s\n", output_filename);
        return -1;
    }

    for (int i = 0; i < db->count; i++) {
        fprintf(file, "%s\n", db->names[i]);
    }

    fclose(file);
    return 0;
}

int count_entries(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return -1;
    }

    int count = 0;
    char buffer[MAX_NAME_LENGTH];
    while (fscanf(file, "%s", buffer) == 1) {
        count++;
    }

    fclose(file);
    return count;
}