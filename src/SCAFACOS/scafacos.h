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

#ifdef KSPACE_CLASS
// clang-format off
KSpaceStyle(scafacos,Scafacos);
// clang-format on
#else

#ifndef LMP_SCAFACOS_H
#define LMP_SCAFACOS_H

#include "kspace.h"
//#include "fcs.h"

namespace LAMMPS_NS {

class Scafacos : public KSpace {
 public:
  Scafacos(class LAMMPS *);
  ~Scafacos() override;
  void init() override;
  void setup() override {}
  void settings(int, char **) override;
  void compute(int, int) override;
  int modify_param(int, char **) override;
  double memory_usage() override;

 private:
  int me;

  char *method;
  double tolerance;
  double *xpbc, *epot, **efield;
  int tolerance_type;
  int initialized, maxatom;

  int fmm_tuning_flag;

  void *fcs;    // ScaFaCoS handle

  // simulation state: box, natoms
  // so ScaFaCoS can detect if changes, e.g. for NPT

  double old_box_x[3], old_box_y[3], old_box_z[3];
  double old_origin[3];
  int old_periodicity[3];
  int old_natoms;

  double virial_int[9];

  void check_result(void *);
  void setup_handle();
  bool box_has_changed();
};

}    // namespace LAMMPS_NS

#endif
#endif
