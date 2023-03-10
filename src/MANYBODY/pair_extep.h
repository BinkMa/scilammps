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
PairStyle(extep,PairExTeP);
// clang-format on
#else

#ifndef LMP_PAIR_EXTEP_H
#define LMP_PAIR_EXTEP_H

#include "pair.h"

#define MAXTYPES 8
#define NSPLINE 5

namespace LAMMPS_NS {

class PairExTeP : public Pair {
 public:
  PairExTeP(class LAMMPS *);
  ~PairExTeP() override;
  void compute(int, int) override;
  void settings(int, char **) override;
  void coeff(int, char **) override;
  void init_style() override;
  double init_one(int, int) override;

 protected:
  struct Param {
    double lam1, lam2, lam3;
    double c, d, h;
    double gamma, powerm;
    double powern, beta;
    double biga, bigb, bigd, bigr;
    double cut, cutsq;
    double c1, c2, c3, c4;
    int ielement, jelement, kelement;
    int powermint;
    double Z_i, Z_j;    // added for ExTePZBL
    double ZBLcut, ZBLexpscale;
    double c5, ca1, ca4;    // added for ExTePMOD
    double powern_del;
  };

  Param *params;    // parameter set for an I-J-K interaction
  double cutmax;    // max cutoff for all elements

  int maxlocal;           // size of numneigh, firstneigh arrays
  int maxpage;            // # of pages currently allocated
  int pgsize;             // size of neighbor page
  int oneatom;            // max # of neighbors for one atom
  MyPage<int> *ipage;     // neighbor list pages
  int *SR_numneigh;       // # of pair neighbors for each atom
  int **SR_firstneigh;    // ptr to 1st neighbor of each atom

  double *Nt, *Nd;    // sum of cutoff fns ( f_C ) with SR neighs

  void allocate();
  void spline_init();
  virtual void read_file(char *);
  void setup() override;
  virtual void repulsive(Param *, double, double &, int, double &);
  virtual double zeta(Param *, double, double, double *, double *);
  virtual void force_zeta(Param *, double, double, double &, double &, int, double &);
  void attractive(Param *, double, double, double, double *, double *, double *, double *,
                  double *);

  virtual double ters_fc(double, Param *);
  virtual double ters_fc_d(double, Param *);
  virtual double ters_fa(double, Param *);
  virtual double ters_fa_d(double, Param *);
  virtual double ters_bij(double, Param *);
  virtual double ters_bij_d(double, Param *);

  virtual void ters_zetaterm_d(double, double *, double, double *, double, double *, double *,
                               double *, Param *);
  void costheta_d(double *, double, double *, double, double *, double *, double *);

  // inlined functions for efficiency

  inline double ters_gijk(const double costheta, const Param *const param) const
  {
    const double ters_c = param->c * param->c;
    const double ters_d = param->d * param->d;
    const double hcth = param->h - costheta;

    return param->gamma * (1.0 + ters_c / ters_d - ters_c / (ters_d + hcth * hcth));
  }

  inline double ters_gijk_d(const double costheta, const Param *const param) const
  {
    const double ters_c = param->c * param->c;
    const double ters_d = param->d * param->d;
    const double hcth = param->h - costheta;
    const double numerator = -2.0 * ters_c * hcth;
    const double denominator = 1.0 / (ters_d + hcth * hcth);
    return param->gamma * numerator * denominator * denominator;
  }

  // splines parameters
  // F[Ni=0-1, 1-2, 2-3,
  //   Nj=...,
  struct TF_corr_param {
    double f_00, f_01, f_10, f_11, f_x_00, f_x_01, f_x_10, f_x_11, f_y_00, f_y_01, f_y_10, f_y_11;
  } F_corr_param[MAXTYPES][MAXTYPES][NSPLINE][NSPLINE];

  double F_corr_data[MAXTYPES][MAXTYPES][NSPLINE][NSPLINE][3];

  double F_corr(int, int, double, double, double *, double *);
  void SR_neigh();

  double envelop_function(double, double, double *);
};

}    // namespace LAMMPS_NS

#endif
#endif
