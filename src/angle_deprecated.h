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

#ifdef ANGLE_CLASS
// clang-format off
AngleStyle(DEPRECATED,AngleDeprecated);
// clang-format on
#else

#ifndef LMP_ANGLE_DEPRECATED_H
#define LMP_ANGLE_DEPRECATED_H

#include "angle.h"

namespace LAMMPS_NS {

class AngleDeprecated : public Angle {
 public:
  AngleDeprecated(class LAMMPS *lmp) : Angle(lmp) {}

  void compute(int, int) override {}
  void settings(int, char **) override;
  void coeff(int, char **) override {}
  double equilibrium_angle(int) override { return 0.0; }
  void write_restart(FILE *) override {}
  void read_restart(FILE *) override {}
  double single(int, int, int, int) override { return 0.0; }
};

}    // namespace LAMMPS_NS

#endif
#endif
