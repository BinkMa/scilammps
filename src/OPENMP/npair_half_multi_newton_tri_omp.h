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
NPairStyle(half/multi/newton/tri/omp,
           NPairHalfMultiNewtonTriOmp,
           NP_HALF | NP_MULTI | NP_NEWTON | NP_TRI | NP_OMP);
// clang-format on
#else

#ifndef LMP_NPAIR_HALF_MULTI_NEWTON_TRI_OMP_H
#define LMP_NPAIR_HALF_MULTI_NEWTON_TRI_OMP_H

#include "npair.h"

namespace LAMMPS_NS {

class NPairHalfMultiNewtonTriOmp : public NPair {
 public:
  NPairHalfMultiNewtonTriOmp(class LAMMPS *);
  void build(class NeighList *) override;
};

}    // namespace LAMMPS_NS

#endif
#endif
