/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://www.lammps.org/, Sandia National Laboratories
   LAMMPS development team: developers@lammps.org

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing author: Axel Kohlmeyer (Temple U)
------------------------------------------------------------------------- */

#ifdef PAIR_CLASS
// clang-format off
PairStyle(tersoff/omp,PairTersoffOMP);
// clang-format on
#else

#ifndef LMP_PAIR_TERSOFF_OMP_H
#define LMP_PAIR_TERSOFF_OMP_H

#include "pair_tersoff.h"
#include "thr_omp.h"

namespace LAMMPS_NS {

class PairTersoffOMP : public PairTersoff, public ThrOMP {

 public:
  PairTersoffOMP(class LAMMPS *);

  void compute(int, int) override;
  double memory_usage() override;

 private:
  template <int SHIFT_FLAG, int EVFLAG, int EFLAG, int VFLAG_ATOM>
  void eval(int ifrom, int ito, ThrData *const thr);
};

}    // namespace LAMMPS_NS

#endif
#endif
