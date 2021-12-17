#ifndef RAMBO_H
#define RAMBO_H 1

#include "mgOnGpuConfig.h"
#include "mgOnGpuTypes.h"
//#include "mgOnGpuVectors.h"

//--------------------------------------------------------------------------

// Simplified rambo version for 2 to N (with N>=2) processes with massless particles
#ifdef __CUDACC__
namespace grambo2toNm0
#else
namespace rambo2toNm0
#endif
{

  using mgOnGpu::np4;
  using mgOnGpu::npari;
  using mgOnGpu::nparf;
  using mgOnGpu::npar;

  //--------------------------------------------------------------------------

  // Fill in the momenta of the initial particles
  // [NB: the output buffer includes both initial and final momenta, but only initial momenta are filled in]
  __global__
  void getMomentaInitial( const fptype energy,   // input: energy
                          fptype momenta1d[]     // output: momenta as AOSOA[npagM][npar][4][neppM]
#ifndef __CUDACC__
                          , const int nevt       // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
#endif
                          );

  //--------------------------------------------------------------------------

  // Fill in the momenta of the final particles using the RAMBO algorithm
  // [NB: the output buffer includes both initial and final momenta, but only initial momenta are filled in]
  __global__
  void getMomentaFinal( const fptype energy,      // input: energy
                        const fptype rnarray1d[], // input: random numbers in [0,1] as AOSOA[npagR][nparf][4][neppR]
                        fptype momenta1d[],       // output: momenta as AOSOA[npagM][npar][4][neppM]
                        fptype wgts[]             // output: weights[nevt]
#ifndef __CUDACC__
                        , const int nevt          // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
#endif
                        );

  //--------------------------------------------------------------------------

}

#endif // RAMBO_H 1
