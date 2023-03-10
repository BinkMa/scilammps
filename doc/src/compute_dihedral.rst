.. index:: compute dihedral

compute dihedral command
========================

Syntax
""""""

.. code-block:: LAMMPS

   compute ID group-ID dihedral

* ID, group-ID are documented in :doc:`compute <compute>` command
* dihedral = style name of this compute command

Examples
""""""""

.. code-block:: LAMMPS

   compute 1 all dihedral

Description
"""""""""""

Define a computation that extracts the dihedral energy calculated by
each of the dihedral sub-styles used in the :doc:`dihedral_style hybrid <dihedral_hybrid>` command.  These values are made
accessible for output or further processing by other commands.  The
group specified for this command is ignored.

This compute is useful when using :doc:`dihedral_style hybrid <dihedral_hybrid>` if you want to know the portion of the
total energy contributed by one or more of the hybrid sub-styles.

Output info
"""""""""""

This compute calculates a global vector of length :math:`N`, where :math:`N`
is the number of sub_styles defined by the
:doc:`dihedral_style hybrid <dihedral_style>` command, which can be accessed by
the indices 1 through :math:`N`.  These values can be used by any command that
uses global scalar or vector values from a compute as input.  See the
:doc:`Howto output <Howto_output>` page for an overview of LAMMPS output
options.

The vector values are "extensive" and will be in energy
:doc:`units <units>`.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`compute pe <compute_pe>`, :doc:`compute pair <compute_pair>`

Default
"""""""

none
