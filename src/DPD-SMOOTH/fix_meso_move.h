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

#ifdef FIX_CLASS
// clang-format off
FixStyle(meso/move,FixMesoMove);
// clang-format on
#else

#ifndef LMP_FIX_MESO_MOVE_H
#define LMP_FIX_MESO_MOVE_H

#include "fix.h"

namespace LAMMPS_NS {

class FixMesoMove : public Fix {
 public:
  FixMesoMove(class LAMMPS *, int, char **);
  ~FixMesoMove() override;
  int setmask() override;
  void init() override;
  void setup_pre_force(int) override;
  void initial_integrate(int) override;
  void final_integrate() override;

  double memory_usage() override;
  void write_restart(FILE *) override;
  void restart(char *) override;
  void grow_arrays(int) override;
  void copy_arrays(int, int, int) override;
  void set_arrays(int) override;
  int pack_exchange(int, double *) override;
  int unpack_exchange(int, double *) override;
  int pack_restart(int, double *) override;
  void unpack_restart(int, int) override;
  int maxsize_restart() override;
  int size_restart(int) override;

  void reset_dt() override;

 private:
  char *xvarstr, *yvarstr, *zvarstr, *vxvarstr, *vyvarstr, *vzvarstr;
  int mstyle;
  int vxflag, vyflag, vzflag, axflag, ayflag, azflag;
  double vx, vy, vz, ax, ay, az;
  double period, omega_rotate;
  double point[3], axis[3], runit[3];
  double dt, dtv, dtf;
  int xvar, yvar, zvar, vxvar, vyvar, vzvar;
  int xvarstyle, yvarstyle, zvarstyle, vxvarstyle, vyvarstyle, vzvarstyle;
  int time_origin;

  double **xoriginal;    // original coords of atoms
  int displaceflag, velocityflag;
  int maxatom;
  double **displace, **velocity;
};

}    // namespace LAMMPS_NS

#endif
#endif
