#define _CRT_SECURE_NO_WARNINGS
#include "test.h"
#include "cpucycles.h"

void ADDSUB()
{
	FILE* fp0 = NULL;
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	FILE* fp3 = NULL;
	FILE* fp4 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t P256[8] = { 0 };
	uint32_t opA[8] = { 0 };
	uint32_t opB[8] = { 0 };
	uint32_t opC[8] = { 0 };

	BIGNUM A = { {0,}, 0};
	BIGNUM B = { {0,}, 0 };
	BIGNUM C = { {0,}, 0 };
	BIGNUM P = { {0,}, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long ADDcc = 0, SUBcc = 0;
	int count = 0;

	fp0 = fileOpen("P256값.txt", "r");
	fp1 = fileOpen("TV_opA_add.txt", "r");
	fp2 = fileOpen("TV_opB_add.txt", "r");
	fp3 = fileOpen("TV_PF_add.txt", "w");
	fp4 = fileOpen("TV_PF_sub.txt", "w");

	//p256값 저장
	fscanf(fp0, "%s", input_str);
	len = strlen(input_str) / (sizeof(int) * 2);
	str2hex(input_str, P256, len);
	initBignum(P256, len, &P);

	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		count++;
		//opA값 저장
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//opB값 저장
		fscanf(fp2, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opB, len);
		initBignum(opB, len, &B);

		//소수체 덧셈연산
		initBignum(opC, len, &C);
		start = cpucycles();
		PF_addition(&C, &P, &A, &B);
		end = cpucycles();
		ADDcc += (end - start);

		//결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", C.d[i]);
		}
		fprintf(fp3, "\n\n");

		//소수체 뺄셈연산
		initBignum(opC, len, &C);
		start = cpucycles();
		PF_substraction(&C, &P, &A, &B);
		end = cpucycles();
		SUBcc += (end - start);

		//결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", C.d[i]);
		}
		fprintf(fp4, "\n\n");
	}
	printf("ADDcc = %d\n", ADDcc / count);
	printf("SUBcc = %d\n", SUBcc / count);

	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}

void MUL()
{
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;
	FILE* fp5;

	unsigned char input_str[1000] = { 0 };
	uint32_t opA[8] = { 0 };
	uint32_t opB[8] = { 0 };
	uint32_t opC[16] = { 0 };

	BIGNUM A = { {0,}, 0 };
	BIGNUM B = { {0,}, 0 };
	BIGNUM C = { {0,}, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long OScc = 0, PScc = 0;
	int count = 0;

	fp1 = fileOpen("TV_opA.txt", "r");
	fp2 = fileOpen("TV_opB.txt", "r");
	fp3 = fileOpen("TV_PF_OS.txt", "w");
	fp4 = fileOpen("TV_PF_PS.txt", "w");
	fp5 = fileOpen("TV_PF_sqr.txt", "w");

	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		count++;
		//opA값 저장
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//opB값 저장
		fscanf(fp2, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opB, len);
		initBignum(opB, len, &B);

		//OS 곱셈연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		OperandScanning(&C, &A, &B);
		end = cpucycles();
		OScc += (end - start);

		//결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", C.d[i]);
		}
		fprintf(fp3, "\n\n");

		//PS 곱셈연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		ProductScanning(&C, &A, &B);
		end = cpucycles();
		PScc += (end - start);

		//결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", C.d[i]);
		}
		fprintf(fp4, "\n\n");

		//제곱연산
		initBignum(opC, A.top + B.top, &C);
		Squaring(&C, &A);

		//결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp5, "%08X", C.d[i]);
		}
		fprintf(fp5, "\n\n");
	}
	printf("OScc = %d\n", OScc / count);
	printf("PScc = %d\n", PScc / count);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
}