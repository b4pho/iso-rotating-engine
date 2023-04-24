#include <stdio.h>
#include "math/quaternion.h"

int main(int n, char** args) {

    Quaternion q = quat_create(1, 2, 3, 4);
    Quaternion p = quat_coniugate(q);
    Quaternion qp = quat_multiply(q, p);
    quat_print(q);
    quat_print(p);
    quat_print(qp);
    if (qp -> a == 30.0) {
        printf("SUCCESS\n");
    } else {
        printf("UNEXPECTED RESULT\n");
    }
    quat_destroy(q);
    quat_destroy(p);
    quat_destroy(qp);
    return 0;
}
