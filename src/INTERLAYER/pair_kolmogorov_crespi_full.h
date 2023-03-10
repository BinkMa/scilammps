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
PairStyle(kolmogorov/crespi/full,PairKolmogorovCrespiFull);
// clang-format on
#else

#ifndef LMP_PAIR_KOLMOGOROV_CRESPI_FULL_H
#define LMP_PAIR_KOLMOGOROV_CRESPI_FULL_H

#include "pair.h"

namespace LAMMPS_NS {

class PairKolmogorovCrespiFull : public Pair {
 public:
  PairKolmogorovCrespiFull(class LAMMPS *);
  ~PairKolmogorovCrespiFull() override;

  void compute(int, int) override;
  void settings(int, char **) override;
  void coeff(int, char **) override;
  double init_one(int, int) override;
  void init_style() override;
  void KC_neigh();
  void calc_normal();
  void calc_FRep(int, int);
  void calc_FvdW(int, int);
  double single(int, int, int, int, double, double, double, double &) override;

  static constexpr int NPARAMS_PER_LINE = 12;

 protected:
  int maxlocal;           // size of numneigh, firstneigh arrays
  int pgsize;             // size of neighbor page
  int oneatom;            // max # of neighbors for one atom
  MyPage<int> *ipage;     // neighbor list pages
  int *KC_numneigh;       // # of pair neighbors for each atom
  int **KC_firstneigh;    // ptr to 1st neighbor of each atom
  int tap_flag;           // flag to turn on/off taper function

  struct Param {
    double z0, C0, C2, C4, C, delta, lambda, A, S;
    double delta2inv, z06, rcut;
    int ielement, jelement;
  };
  Param *params;    // parameter set for I-J interactions
  int nmax;         // max # of atoms

  double cut_global;
  double cut_normal;
  double **cutKCsq;
  double **offset;
  double **normal;
  double ***dnormdri;
  double ****dnormal;

  void read_file(char *);
  void allocate();
};

}    // namespace LAMMPS_NS

#endif
#endif
