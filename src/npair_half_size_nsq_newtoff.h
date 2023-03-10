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

#ifdef NPAIR_CLASS
// clang-format off
NPairStyle(half/size/nsq/newtoff,
           NPairHalfSizeNsqNewtoff,
           NP_HALF | NP_SIZE | NP_NSQ | NP_NEWTOFF | NP_ORTHO | NP_TRI);
// clang-format on
#else

#ifndef LMP_NPAIR_HALF_SIZE_NSQ_NEWTOFF_H
#define LMP_NPAIR_HALF_SIZE_NSQ_NEWTOFF_H

#include "npair.h"

namespace LAMMPS_NS {

class NPairHalfSizeNsqNewtoff : public NPair {
 public:
  NPairHalfSizeNsqNewtoff(class LAMMPS *);
  void build(class NeighList *) override;
};

}    // namespace LAMMPS_NS

#endif
#endif
