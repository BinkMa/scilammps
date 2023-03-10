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

/* ----------------------------------------------------------------------
   Contributing author: Mike Brown (ORNL)
------------------------------------------------------------------------- */

#ifndef LMP_GPU_EXTRA_H
#define LMP_GPU_EXTRA_H

#include "error.h"
#include "modify.h"

// ---------------------- OPENMP PREPROCESSOR STUFF ------------------
#if defined(_OPENMP)
#if !defined(LAL_USE_OMP)
#define LAL_USE_OMP 1
#endif

#if !defined(LAL_USE_OMP_SIMD)
#if (_OPENMP >= 201307)
#define LAL_USE_OMP_SIMD 1
#else
#define LAL_USE_OMP_SIMD 0
#endif
#endif
#else
#if !defined(LAL_USE_OMP)
#define LAL_USE_OMP 0
#endif

#if !defined(LAL_USE_OMP_SIMD)
#define LAL_USE_OMP_SIMD 0
#endif
#endif

namespace GPU_EXTRA {

inline void check_flag(int error_flag, LAMMPS_NS::Error *error, MPI_Comm &world)
{
  int all_success;
  MPI_Allreduce(&error_flag, &all_success, 1, MPI_INT, MPI_MIN, world);
  if (all_success != 0) {
    if (all_success == -1)
      error->all(FLERR, "The package gpu command is required for gpu styles");
    else if (all_success == -2)
      error->all(FLERR, "Could not find/initialize a specified accelerator device");
    else if (all_success == -3)
      error->all(FLERR, "Insufficient memory on accelerator");
    else if (all_success == -4)
      error->all(FLERR, "GPU library not compiled for this accelerator");
    else if (all_success == -5)
      error->all(FLERR, "Double precision is not supported on this accelerator");
    else if (all_success == -6)
      error->all(FLERR, "Unable to initialize accelerator for use");
    else if (all_success == -7)
      error->all(FLERR, "Accelerator sharing is not currently supported on system");
    else if (all_success == -8)
      error->all(FLERR, "GPU particle split must be set to 1 for this pair style.");
    else if (all_success == -9)
      error->all(FLERR, "CPU neighbor lists must be used for ellipsoid/sphere mix.");
    else if (all_success == -10)
      error->all(FLERR, "Invalid threads_per_atom specified.");
    else if (all_success == -11)
      error->all(FLERR, "Invalid custom OpenCL parameter string.");
    else if (all_success == -12)
      error->all(FLERR, "Invalid OpenCL platform ID.");
    else if (all_success == -13)
      error->all(FLERR, "Invalid device configuration.");
    else if (all_success == -15)
      error->all(FLERR,
                 "PPPM was compiled for double precision floating point "
                 "but GPU device supports single precision only.");
    else if (all_success == -16)
      error->all(FLERR,
                 "GPU library was compiled for double or mixed precision "
                 "floating point but GPU device supports single precision only.");
    else
      error->all(FLERR, "Unknown error in GPU library");
  }
}

inline void gpu_ready(LAMMPS_NS::Modify *modify, LAMMPS_NS::Error *error)
{
  int ifix = modify->find_fix("package_gpu");
  if (ifix < 0) error->all(FLERR, "The package gpu command is required for gpu styles");
}
}    // namespace GPU_EXTRA

#endif
