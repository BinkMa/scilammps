// clang-format off
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
PairStyle(eam/fs/intel,PairEAMFSIntel);
// clang-format on
#else

#ifndef LMP_PAIR_EAM_FS_INTEL_H
#define LMP_PAIR_EAM_FS_INTEL_H

#include "pair_eam_intel.h"

namespace LAMMPS_NS {

// need virtual public b/c of how eam/fs/opt inherits from it

class PairEAMFSIntel : virtual public PairEAMIntel {
 public:
  PairEAMFSIntel(class LAMMPS *);

  void coeff(int, char **) override;

 protected:
  void read_file(char *) override;
  void file2array() override;
};

}    // namespace LAMMPS_NS

#endif
#endif
