// clang-format off
/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   LAMMPS development team: developers@lammps.org

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef INTEGRATE_CLASS
// clang-format off
IntegrateStyle(verlet/lrt/intel,VerletLRTIntel);
// clang-format on
#else

#ifndef LMP_VERLET_LRT_INTEL_H
#define LMP_VERLET_LRT_INTEL_H

#include "pppm_intel.h"
#include "verlet.h"

#ifdef LMP_INTEL_USELRT
#if defined(LMP_INTEL_LRT11) || defined(__APPLE__)
#if __cplusplus > 199711L
#define _LMP_INTEL_LRT_11
#include <thread>
#else
#undef LMP_INTEL_USELRT
#ifdef LMP_INTEL_LRT11
#error C++11 support required for LMP_INTEL_LRT11 define
#endif
#endif
#else
#define _LMP_INTEL_LRT_PTHREAD
#include <pthread.h>
#endif
#endif

namespace LAMMPS_NS {

class VerletLRTIntel : public Verlet {
 public:
  VerletLRTIntel(class LAMMPS *, int, char **);
  ~VerletLRTIntel() override;
  void init() override;
  void setup(int flag) override;
  void run(int) override;

 protected:
  PPPMIntel *_intel_kspace;

#if defined(_LMP_INTEL_LRT_PTHREAD)
  static void *k_launch_loop(void *context);
  pthread_t _kspace_thread;
  pthread_attr_t _kspace_attr;
  pthread_mutex_t _kmutex;
  pthread_cond_t _kcond;
  int _kspace_ready, _kspace_done, _krun_n;
#endif
};

}    // namespace LAMMPS_NS

#endif
#endif
