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

#ifndef LMP_FIX_NH_SPHERE_H
#define LMP_FIX_NH_SPHERE_H

#include "fix_nh.h"

namespace LAMMPS_NS {

class FixNHSphere : public FixNH {
 public:
  FixNHSphere(class LAMMPS *, int, char **);

  void init() override;

 protected:
  double inertia;

  void nve_v() override;
  void nve_x() override;
  void nh_v_temp() override;
};

}    // namespace LAMMPS_NS

#endif
