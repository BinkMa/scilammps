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
PairStyle(coul/dsf/gpu,PairCoulDSFGPU);
// clang-format on
#else

#ifndef LMP_PAIR_COUL_DSF_GPU_H
#define LMP_PAIR_COUL_DSF_GPU_H

#include "pair_coul_dsf.h"

namespace LAMMPS_NS {

class PairCoulDSFGPU : public PairCoulDSF {
 public:
  PairCoulDSFGPU(LAMMPS *lmp);
  ~PairCoulDSFGPU() override;
  void cpu_compute(int, int, int, int, int *, int *, int **);
  void compute(int, int) override;
  void init_style() override;
  double memory_usage() override;

  enum { GPU_FORCE, GPU_NEIGH, GPU_HYB_NEIGH };

 private:
  int gpu_mode;
  double cpu_time;
};

}    // namespace LAMMPS_NS
#endif
#endif
