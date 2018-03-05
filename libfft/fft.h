#ifndef _fft_h_
#define _fft_h_


#ifdef __cplusplus
extern "C" {
#endif


#include "complex.h"


void fft_f(complex_f data[], unsigned log2_N);

void fft_copy_shuffle_f(complex_f src[], complex_f dst[], unsigned log2_N);
void fft_shuffle_f(complex_f data[], unsigned log2_N);
void fft_evaluate_f(complex_f data[], unsigned log2_N);


#ifdef __cplusplus
}
#endif


#endif
