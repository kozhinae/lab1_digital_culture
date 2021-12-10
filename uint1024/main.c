#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

const uint64_t limit = 4294967296;
struct uint1024_t {
    unsigned int num[32];
};

struct uint1024_t from_uint(unsigned int x) {
    struct uint1024_t temp;
    for (int i = 0; i < 32; i++) {
        temp.num[i] = 0;
    }
    temp.num[0] = x;
    return temp;
}

struct uint1024_t add_op(struct uint1024_t x, struct uint1024_t y) {
    struct uint1024_t ans = from_uint(0);
    int carry = 0;
    for (int i = 0; i < 32; i++) {
        uint64_t sum = ((uint64_t) x.num[i] + (uint64_t) y.num[i] + carry);
        carry = sum / limit;
        ans.num[i] = sum % limit;
    }
    return ans;
}

struct uint1024_t subtr_op(struct uint1024_t x, struct uint1024_t y) {
    int64_t diff = 0;
    int carry = 0;
    for (int i = 0; i < 32; i++) {
        diff = (x.num[i] - y.num[i] - carry);
        carry = 0;
        if (diff < 0) {
            diff += (int64_t) limit;
            carry = 1;
        }
        x.num[i] = diff;
    }
    return x;
}

struct uint1024_t mult_op(struct uint1024_t x, struct uint1024_t y) {
    struct uint1024_t ans = from_uint(0);
    for (int i = 0; i < 32; i++) {
        uint64_t carry = 0;
        struct uint1024_t temp = from_uint(0);
        for (int j = 0; j < 32; j++) {
            uint64_t balance = ((uint64_t) x.num[j] * (uint64_t) y.num[i] + carry);
            carry = balance / limit;
            temp.num[j] = balance % limit;
        }
        for (int j = 0; j < i; j++) {
            for (int k = 31; k > 0; k--) {
                temp.num[k] = temp.num[k - 1];
            }
            temp.num[0] = 0;
        }
        ans = add_op(ans, temp);
    }
    return ans;
}

void scanf_value(struct uint1024_t *x) {
    struct uint1024_t temp = from_uint(0);
    char str[400];
    scanf("%s", str);
    for (int i = 0; str[i] != '\0'; i++) {
        temp = mult_op(temp, from_uint(10));
        temp = add_op(temp, from_uint(str[i] - '0'));
    }
    for (int i = 0; i < 32; i++) {
        x->num[i] = temp.num[i];
    }
}

void str_add(char *x, char *y, char *res) {
    size_t max = 0;
    size_t len_x = strlen(x);
    size_t len_y = strlen(y);
    if (len_x > len_y) {
        max = len_x;
    } else {
        max = len_y;
    }
    int carry = 0;
    for (int i = 0; i < max; i++) {
        int x_i = i < len_x ? x[i] - '0' : 0;
        int y_i = i < len_y ? y[i] - '0' : 0;
        if (x_i + y_i + carry > 9) {
            res[i] = x_i + y_i + carry - 10 + '0';
            carry = 1;
        } else {
            res[i] = x_i + y_i + carry + '0';
            carry = 0;
        }
    }
    if (carry) {
        res[max] = '1';
        res[max + 1] = '\0';
    } else {
        res[max] = '\0';
    }
}

void printf_value(struct uint1024_t x) {
    char num[350];
    char pow2[350];
    char temp[350];
    num[0] = '0';
    num[1] = '\0';
    pow2[0] = '1';
    pow2[1] = '\0';
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            if ((x.num[i] >> j) & 1) {
                str_add(pow2, num, temp);
                strcpy(num, temp);
            }
            str_add(pow2, pow2, temp);
            strcpy(pow2, temp);
        }
    }
    for (int i = strlen(num) - 1; i >= 0; i--) {
        printf("%c", num[i]);
    }
}

int main() {
    struct uint1024_t num1 = from_uint(0);
    struct uint1024_t num2 = from_uint(0);
    scanf_value(&num1);
    scanf_value(&num2);
    printf_value(num1);
    printf("\n");
    printf_value(num2);
    printf("\n");
    printf_value(add_op(num1, num2));
    printf("\n");
    printf_value(subtr_op(num1, num2));
    printf("\n");
    printf_value(mult_op(num1, num2));
    return 0;
}