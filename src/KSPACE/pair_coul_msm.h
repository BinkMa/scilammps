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

#ifdef PAIR_CLASS
// clang-format off
PairStyle(coul/msm,PairCoulMSM);
// clang-format on
#else

#ifndef LMP_PAIR_COUL_MSM_H
#define LMP_PAIR_COUL_MSM_H

#include "pair_coul_long.h"

namespace LAMMPS_NS {

class PairCoulMSM : public PairCoulLong {
 public:
  PairCoulMSM(class LAMMPS *);

  void compute(int, int) override;
  double single(int, int, int, int, double, double, double, double &) override;
  void *extract(const char *, int &) override;
};

}    // namespace LAMMPS_NS

#endif
#endif
