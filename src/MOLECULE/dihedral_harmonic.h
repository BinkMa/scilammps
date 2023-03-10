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

#ifdef DIHEDRAL_CLASS
// clang-format off
DihedralStyle(harmonic,DihedralHarmonic);
// clang-format on
#else

#ifndef LMP_DIHEDRAL_HARMONIC_H
#define LMP_DIHEDRAL_HARMONIC_H

#include "dihedral.h"

namespace LAMMPS_NS {

class DihedralHarmonic : public Dihedral {
 public:
  DihedralHarmonic(class LAMMPS *);
  ~DihedralHarmonic() override;
  void compute(int, int) override;
  void coeff(int, char **) override;
  void write_restart(FILE *) override;
  void read_restart(FILE *) override;
  void write_data(FILE *) override;

 protected:
  double *k, *cos_shift, *sin_shift;
  int *sign, *multiplicity;

  virtual void allocate();
};

}    // namespace LAMMPS_NS

#endif
#endif
