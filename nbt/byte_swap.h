void SwapBytes(void *pv, size_t n){
	char *p = pv;
	size_t lo, hi;
	for(lo=0, hi=n-1; hi>lo; lo++, hi--){
		char tmp=p[lo];
		p[lo] = p[hi];
		p[hi] = tmp;
	}
}
#define SWAP(x) SwapBytes(&x, sizeof(x));
