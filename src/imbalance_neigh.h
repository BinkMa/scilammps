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

#ifndef LMP_IMBALANCE_NEIGH_H
#define LMP_IMBALANCE_NEIGH_H

#include "imbalance.h"

namespace LAMMPS_NS {

class ImbalanceNeigh : public Imbalance {
 public:
  ImbalanceNeigh(class LAMMPS *);

 public:
  // parse options, return number of arguments consumed
  int options(int, char **) override;
  // compute and apply weight factors to local atom array
  void compute(double *) override;
  // print information about the state of this imbalance compute
  std::string info() override;

 private:
  double factor;    // weight factor for neighbor imbalance
  int did_warn;     // 1 if warned about no suitable neighbor list
};

}    // namespace LAMMPS_NS

#endif
