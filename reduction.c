#include "reduction.h"

void fastReduction(BIGNUM* r, const BIGNUM* a, const BIGNUM* P)
{
	BIGNUM s1 = { {a->d[0], a->d[1], a->d[2], a->d[3], a->d[4], a->d[5], a->d[6], a->d[7]}, 8, 0 };
	BIGNUM s2 = { {0, 0, 0, a->d[11], a->d[12], a->d[13], a->d[14], a->d[15]}, 8, 0 };
	BIGNUM s3 = { {0, 0, 0, a->d[12], a->d[13], a->d[14], a->d[15], 0}, 8, 0 };
	BIGNUM s4 = { {a->d[8], a->d[9], a->d[10],0, 0, 0, a->d[14], a->d[15]}, 8, 0 };
	BIGNUM s5 = { {a->d[9], a->d[10], a->d[11], a->d[13], a->d[14], a->d[15], a->d[13], a->d[8]}, 8, 0 };
	BIGNUM s6 = { {a->d[11], a->d[12], a->d[13], 0, 0, 0, a->d[8], a->d[10]}, 8, 0 };
	BIGNUM s7 = { {a->d[12], a->d[13], a->d[14], a->d[15], 0, 0, a->d[9], a->d[11]}, 8, 0 };
	BIGNUM s8 = { {a->d[13], a->d[14], a->d[15], a->d[8], a->d[9], a->d[10], 0, a->d[12]}, 8, 0 };
	BIGNUM s9 = { {a->d[14], a->d[15], 0, a->d[9], a->d[10], a->d[11], 0, a->d[13]}, 8, 0 };

	BIGNUM sum = { {0, }, 0, 0 };

	PF_addition(&sum, P, &s1, &s2);
	PF_addition(&sum, P, &sum, &s2);
	PF_addition(&sum, P, &sum, &s3);
	PF_addition(&sum, P, &sum, &s3);
	PF_addition(&sum, P, &sum, &s4);
	PF_addition(&sum, P, &sum, &s5);
	
	PF_substraction(&sum, P, &sum, &s6);
	PF_substraction(&sum, P, &sum, &s7);
	PF_substraction(&sum, P, &sum, &s8);
	PF_substraction(&sum, P, &sum, &s9);

	//�����
	for (int i = 0; i < sum.top; i++)
	{
		r->d[i] = sum.d[i];
	}
	r->top = sum.top;
}