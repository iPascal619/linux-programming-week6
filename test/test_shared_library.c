#include <assert.h>
#include "shared_library.h"

void test_read_names() {
    NameDatabase db;
    int count = read_names(&db, "data/names.txt");
    assert(count > 0);
}

void test_sort_names() {
    NameDatabase db;
    read_names(&db, "data/names.txt");
    int result = sort_names(&db);
    assert(result == 0);
    // Add assertions to check sorting
}

int main() {
    test_read_names();
    test_sort_names();
    printf("All shared library tests passed!\n");
    return 0;
}