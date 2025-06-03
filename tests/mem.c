#include "mem.h"
#include "alloc.h"
#include "macros.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#define	L1_TEST 10
#define	L2_TEST 500
#define	L3_TEST 5000
#define	L4_TEST 50000
#define	L5_TEST 500000

void	memcpy_tests()
{
	{
		LV_DEFER char *a = lv_alloc(L1_TEST);
		LV_DEFER char *b = lv_alloc(L1_TEST);

		memset(a, 'a', L1_TEST);
		lv_memcpy(b, a, L1_TEST);
		assert(memcmp(a, b, L1_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(L2_TEST);
		LV_DEFER char *b = lv_alloc(L2_TEST);

		memset(a, 'a', L2_TEST);
		lv_memcpy(b, a, L2_TEST);
		assert(memcmp(a, b, L2_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(L3_TEST);
		LV_DEFER char *b = lv_alloc(L3_TEST);

		memset(a, 'a', L3_TEST);
		lv_memcpy(b, a, L3_TEST);
		assert(memcmp(a, b, L3_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(L4_TEST);
		LV_DEFER char *b = lv_alloc(L4_TEST);

		memset(a, 'a', L4_TEST);
		lv_memcpy(b, a, L4_TEST);
		assert(memcmp(a, b, L4_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(L5_TEST);
		LV_DEFER char *b = lv_alloc(L5_TEST);

		memset(a, 'a', L5_TEST);
		lv_memcpy(b, a, L5_TEST);
		assert(memcmp(a, b, L5_TEST) == 0);
	}

	LV_DEFER char *a = lv_alloc(L5_TEST);
	LV_DEFER char *b = lv_alloc(L5_TEST);

	assert(lv_memcpy(NULL, b, 1) == NULL);
	assert(lv_memcpy(b, NULL, 1) == NULL);
	assert(lv_memcpy(b, b, 1) == NULL);
}

void	memmove_tests()
{
	{
		LV_DEFER char *a = lv_alloc(L1_TEST);
		LV_DEFER char *b = lv_alloc(L1_TEST);

		memset(a, 'a', L1_TEST);
		lv_memmove(b, a, L1_TEST);
		assert(memcmp(a, b, L1_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(L2_TEST);
		LV_DEFER char *b = lv_alloc(L2_TEST);

		memset(a, 'a', L2_TEST);
		lv_memmove(b, a, L2_TEST);
		assert(memcmp(a, b, L2_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(L3_TEST);
		LV_DEFER char *b = lv_alloc(L3_TEST);

		memset(a, 'a', L3_TEST);
		lv_memmove(b, a, L3_TEST);
		assert(memcmp(a, b, L3_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(L4_TEST);
		LV_DEFER char *b = lv_alloc(L4_TEST);

		memset(a, 'a', L4_TEST);
		lv_memmove(b, a, L4_TEST);
		assert(memcmp(a, b, L4_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(L5_TEST);
		LV_DEFER char *b = lv_alloc(L5_TEST);

		memset(a, 'a', L5_TEST);
		lv_memmove(b, a, L5_TEST);
		assert(memcmp(a, b, L5_TEST) == 0);
	}

	{
		LV_DEFER char *a = lv_alloc(6);

		a[0] = '1';
		a[1] = '2';
		a[2] = '3';
		a[3] = '4';
		a[4] = '5';
		a[5] = '\0';

		lv_memmove(a + 1, a, 2);

		assert(a[0] == '1');
		assert(a[1] == '1');
		assert(a[2] == '2');
		assert(a[3] == '4');
		assert(a[4] == '5');
	}

	{
		LV_DEFER char *a = lv_alloc(6);

		a[0] = '1';
		a[1] = '2';
		a[2] = '3';
		a[3] = '4';
		a[4] = '5';
		a[5] = '\0';

		lv_memmove(a, a + 1, 2);

		assert(a[0] == '2');
		assert(a[1] == '3');
		assert(a[2] == '3');
		assert(a[3] == '4');
		assert(a[4] == '5');
	}

	LV_DEFER char *b = lv_alloc(L5_TEST);

	assert(lv_memmove(NULL, b, 1) == NULL);
	assert(lv_memmove(b, NULL, 1) == NULL);
	assert(lv_memmove(b, b, 1) == NULL);
}

void	memffb_tests() {
	{
		LV_DEFER char *buf = lv_alloc(L1_TEST);
		memset(buf, 'x', L1_TEST);
		buf[0] = 'z';
		void *res = lv_memffb(buf, 'z', L1_TEST);
		assert(res == buf);
	}

	{
		LV_DEFER char *buf = lv_alloc(L1_TEST);
		memset(buf, 'x', L1_TEST);
		buf[L1_TEST - 1] = 'y';
		void *res = lv_memffb(buf, 'y', L1_TEST);
		assert(res == buf + L1_TEST - 1);
	}

	{
		LV_DEFER char *buf = lv_alloc(L1_TEST);
		memset(buf, 'x', L1_TEST);
		buf[5] = 'm';
		void *res = lv_memffb(buf, 'm', L1_TEST);
		assert(res == buf + 5);
	}

	{
		LV_DEFER char *buf = lv_alloc(L1_TEST);
		memset(buf, 'x', L1_TEST);
		void *res = lv_memffb(buf, 'z', L1_TEST);
		assert(res == NULL);
	}

	{
		LV_DEFER char *buf = lv_alloc(L3_TEST);
		memset(buf, 'x', L3_TEST);
		buf[1234] = '!';
		void *res = lv_memffb(buf, '!', L3_TEST);
		assert(res == buf + 1234);
	}

	{
		LV_DEFER char *buf = lv_alloc(L1_TEST);
		memset(buf, 'x', L1_TEST);
		void *res = lv_memffb(buf, 'x', 0);
		assert(res == NULL);
	}

	{
		LV_DEFER char *base = lv_alloc(L2_TEST + 1);
		char *buf = base + 1;
		memset(buf, 'x', L2_TEST);
		buf[250] = 'q';
		void *res = lv_memffb(buf, 'q', L2_TEST);
		assert(res == buf + 250);
	}

	{
		void *res = lv_memffb(NULL, 'x', 0);
		assert(res == NULL);
	}
}

void memswap_tests()
{
	{
		LV_DEFER char *a = lv_alloc(L1_TEST);
		LV_DEFER char *b = lv_alloc(L1_TEST);

		memset(a, 'a', L1_TEST);
		memset(b, 'b', L1_TEST);
		lv_memswap(a, b, L1_TEST);
		for (int i = 0; i < L1_TEST; i++) {
			assert(a[i] == 'b');
			assert(b[i] == 'a');
		}
	}

	{
		LV_DEFER char *a = lv_alloc(L2_TEST);
		LV_DEFER char *b = lv_alloc(L2_TEST);

		memset(a, 'c', L2_TEST);
		memset(b, 'd', L2_TEST);
		lv_memswap(a, b, L2_TEST);
		for (int i = 0; i < L2_TEST; i++) {
			assert(a[i] == 'd');
			assert(b[i] == 'c');
		}
	}

	{
		LV_DEFER char *a = lv_alloc(L3_TEST);
		LV_DEFER char *b = lv_alloc(L3_TEST);

		memset(a, 'x', L3_TEST);
		memset(b, 'y', L3_TEST);
		lv_memswap(a, b, L3_TEST);
		for (int i = 0; i < L3_TEST; i++) {
			assert(a[i] == 'y');
			assert(b[i] == 'x');
		}
	}

	{
		LV_DEFER char *a = lv_alloc(L4_TEST);
		LV_DEFER char *b = lv_alloc(L4_TEST);

		memset(a, 0x11, L4_TEST);
		memset(b, 0x22, L4_TEST);
		lv_memswap(a, b, L4_TEST);
		for (int i = 0; i < L4_TEST; i++) {
			assert(a[i] == 0x22);
			assert(b[i] == 0x11);
		}
	}

	{
		LV_DEFER char *a = lv_alloc(L5_TEST);
		LV_DEFER char *b = lv_alloc(L5_TEST);

		memset(a, 0xA5, L5_TEST);
		memset(b, 0x5A, L5_TEST);
		lv_memswap(a, b, L5_TEST);
		for (int i = 0; i < L5_TEST; i++) {
			assert((unsigned char)a[i] == 0x5A);
			assert((unsigned char)b[i] == 0xA5);
		}
	}

	{
		LV_DEFER char *a = lv_alloc(L1_TEST);

		for (int i = 0; i < L1_TEST; i++)
			a[i] = i;
		lv_memswap(a, a, L1_TEST);
		for (int i = 0; i < L1_TEST; i++)
			assert(a[i] == i);
	}
}

void	memset_tests()
{
	{
		LV_DEFER char *buf1 = lv_alloc(L1_TEST);
		LV_DEFER char *buf2 = lv_alloc(L1_TEST);
		lv_memset(buf1, 'x', L1_TEST);
		memset(buf2, 'x', L1_TEST);
		assert(!memcmp(buf1, buf2, L1_TEST));
	}
	{
		LV_DEFER char *buf1 = lv_alloc(L2_TEST);
		LV_DEFER char *buf2 = lv_alloc(L2_TEST);
		lv_memset(buf1, 'x', L2_TEST);
		memset(buf2, 'x', L2_TEST);
		assert(!memcmp(buf1, buf2, L2_TEST));
	}
	{
		LV_DEFER char *buf1 = lv_alloc(L3_TEST);
		LV_DEFER char *buf2 = lv_alloc(L3_TEST);
		lv_memset(buf1, 'x', L3_TEST);
		memset(buf2, 'x', L3_TEST);
		assert(!memcmp(buf1, buf2, L3_TEST));
	}
	{
		LV_DEFER char *buf1 = lv_alloc(L4_TEST);
		LV_DEFER char *buf2 = lv_alloc(L4_TEST);
		lv_memset(buf1, 'x', L4_TEST);
		memset(buf2, 'x', L4_TEST);
		assert(!memcmp(buf1, buf2, L4_TEST));
	}
	{
		LV_DEFER char *buf1 = lv_alloc(L5_TEST);
		LV_DEFER char *buf2 = lv_alloc(L5_TEST);
		lv_memset(buf1, 'x', L5_TEST);
		memset(buf2, 'x', L5_TEST);
		assert(!memcmp(buf1, buf2, L5_TEST));
	}

	LV_DEFER char *buf1 = lv_alloc(L1_TEST);

	assert(lv_memset(NULL, 'x', 1) == NULL);
	assert(lv_memset(buf1, 0, 0) == buf1);
}

int main()
{
	memcpy_tests();
	memmove_tests();
	memffb_tests();
	memswap_tests();
	memset_tests();
	printf("[TESTER] All mem test passed\n");
	return (0);
}
