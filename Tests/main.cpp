#include "VertexBufferTests.h"

#include <cstdio>

int main() {
    TestCreateAndDeleteVertexBuffer();
    TestCreateAndDeleteAllVertexBuffer();
    TestCreateAndDeleteVertexBufferFromTheMiddle();
    printf("ALL TESTS COMPLETED SUCCESSFULLY\n");
    return 0;
}