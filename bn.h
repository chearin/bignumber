#pragma once
#include <stdio.h>
#include <stdint.h>

typedef struct bignum_st {
    uint32_t d[9]; //d[top]은 1이면 carry, -1(0xffffffff)이면 borrow
    int top; //실제 사용중인 d 배열의 크기
}BIGNUM;

void initBignum(const uint32_t* num, const size_t inlen, BIGNUM* BN);
uint32_t compare(const BIGNUM* a, const BIGNUM* b);

void BignumberAdd(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
void BignumberSub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);

void PF_addition(BIGNUM* c, const BIGNUM* P, const BIGNUM* a, const BIGNUM* b);
void PF_substraction(BIGNUM* c, const BIGNUM* P, const BIGNUM* a, const BIGNUM* b);