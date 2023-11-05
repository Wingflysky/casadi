//
//    MIT No Attribution
//
//    Copyright (C) 2010-2023 Joel Andersson, Joris Gillis, Moritz Diehl, KU Leuven.
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy of this
//    software and associated documentation files (the "Software"), to deal in the Software
//    without restriction, including without limitation the rights to use, copy, modify,
//    merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
//    permit persons to whom the Software is furnished to do so.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

// SYMBOL "copy"
template<typename T1>
void casadi_copy(const T1* x, casadi_int n, T1* y) {
  casadi_int i;
  if (y) {
    if (x) {
#if defined(CASADI_WITH_CBLAS_DOUBLE)
      cblas_dcopy(n, x, 1, y, 1);
#elif defined(CASADI_WITH_CBLAS_SINGLE)
      cblas_scopy(n, x, 1, y, 1);
#else
      for (i=0; i<n; ++i) *y++ = *x++;
#endif
    } else {
      for (i=0; i<n; ++i) *y++ = 0.;
    }
  }
}
