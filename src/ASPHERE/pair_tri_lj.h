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
PairStyle(tri/lj,PairTriLJ);
// clang-format on
#else

#ifndef LMP_PAIR_TRI_LJ_H
#define LMP_PAIR_TRI_LJ_H

#include "pair.h"

namespace LAMMPS_NS {

class PairTriLJ : public Pair {
 public:
  PairTriLJ(class LAMMPS *);
  ~PairTriLJ() override;
  void compute(int, int) override;
  void settings(int, char **) override;
  void coeff(int, char **) override;
  void init_style() override;
  double init_one(int, int) override;

 protected:
  double cut_global;
  double **cut;
  double **epsilon, **sigma;
  double **lj1, **lj2, **lj3, **lj4;
  class AtomVecTri *avec;

  struct Discrete {
    double dx, dy, dz;
    double sigma;
  };
  Discrete *discrete;    // list of all discretes for all lines
  int ndiscrete;         // number of discretes in list
  int dmax;              // allocated size of discrete list
  int *dnum;             // number of discretes per line, 0 if uninit
  int *dfirst;           // index of first discrete per each line
  int nmax;              // allocated size of dnum,dfirst vectors

  void allocate();
  void discretize(int, double, double *, double *, double *);
};

}    // namespace LAMMPS_NS

#endif
#endif
