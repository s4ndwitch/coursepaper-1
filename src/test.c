#include <stdlib.h>

#include "list.h"


int main() {
    struct list *a = createList();
    free(a);
    return 0;
}