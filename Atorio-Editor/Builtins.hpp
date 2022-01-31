#ifndef ATORIO_BUILTINS
#define ATORIO_BUILTINS

#include <stdint.h>

extern "C" {

	uint32_t i420_rgb(int, int, int);

	void bi_cpuid(int, int, void*);

	int bi_ffs(int);
	int bi_ffsu(unsigned int);
	int bi_clz(int);
	int bi_clzu(unsigned int);
	int bi_ctz(int);
	int bi_ctzu(unsigned int);
	int bi_clrsb(int);
	int bi_clrsbu(unsigned int);
	int bi_popcount(int);
	int bi_popcountu(unsigned int);
	int bi_parity(int);
	int bi_parityu(unsigned int);

	int bi_ffsl(long);
	int bi_ffsul(unsigned long);
	int bi_clzl(unsigned long);
	int bi_clzul(unsigned long);
	int bi_ctzl(long);
	int bi_ctzul(unsigned long);
	int bi_clrsbl(long);
	int bi_clrsbul(unsigned long);
	int bi_popcountl(long);
	int bi_popcountul(unsigned long);
	int bi_parityl(long);
	int bi_parityul(unsigned long);

	int bi_ffsll(long long);
	int bi_ffsull(unsigned long long);
	int bi_clzll(unsigned long long);
	int bi_clzull(unsigned long long);
	int bi_ctzll(long long);
	int bi_ctzull(unsigned long long);
	int bi_clrsbll(long long);
	int bi_clrsbull(unsigned long long);
	int bi_popcountll(long long);
	int bi_popcountull(unsigned long long);
	int bi_parityll(long long);
	int bi_parityull(unsigned long long);
}

#endif
