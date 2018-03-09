#ifndef _fft_h_
#define _fft_h_


#ifdef __cplusplus
extern "C" {
#endif


#include "complex.h"


/* In-place FFT */
void ffti_f(complex_f data[], unsigned log2_N);
void ffti_copy_shuffle_f(complex_f src[], complex_f dst[], unsigned log2_N);
void ffti_shuffle_f(complex_f data[], unsigned log2_N);
void ffti_evaluate_f(complex_f data[], unsigned log2_N);

/* Recursive FFT */
void fftr_f(complex_f data[], unsigned log2_N);


#ifdef __cplusplus
}
#endif


#endif
