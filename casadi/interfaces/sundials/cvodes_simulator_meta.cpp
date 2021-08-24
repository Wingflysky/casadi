/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


      #include "cvodes_simulator.hpp"
      #include <string>

      const std::string casadi::CvodesSimulator::meta_doc=
      "\n"
"Interface to CVodes from the Sundials suite.\n"
"\n"
"A call to evaluate will integrate to the end.\n"
"\n"
"You can retrieve the entire state trajectory as follows, after the\n"
"evaluate call: Call reset. Then call integrate(t_i) and getOuput for a\n"
"series of times t_i.\n"
"\n"
"Note: depending on the dimension and structure of your problem, you\n"
"may experience a dramatic speed-up by using a sparse linear solver:\n"
"\n"
"\n"
"\n"
"::\n"
"\n"
"     intg.setOption(\"linear_solver\",\"csparse\")\n"
"     intg.setOption(\"linear_solver_type\",\"user_defined\")\n"
"\n"
"\n"
"\n"
"\n"
">List of available options\n"
"\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"|       Id        |      Type       |     Default     |   Description   |\n"
"+=================+=================+=================+=================+\n"
"| abstol          | OT_DOUBLE         | 0.000           | Absolute        |\n"
"|                 |                 |                 | tolerence for   |\n"
"|                 |                 |                 | the IVP         |\n"
"|                 |                 |                 | solution        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| abstolB         | OT_DOUBLE         | GenericType()   | Absolute        |\n"
"|                 |                 |                 | tolerence for   |\n"
"|                 |                 |                 | the adjoint     |\n"
"|                 |                 |                 | sensitivity     |\n"
"|                 |                 |                 | solution        |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to abstol]      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| disable_interna | OT_BOOL      | false           | Disable CVodes  |\n"
"| l_warnings      |                 |                 | internal        |\n"
"|                 |                 |                 | warning         |\n"
"|                 |                 |                 | messages        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| exact_jacobian  | OT_BOOL      | true            | Use exact       |\n"
"|                 |                 |                 | Jacobian        |\n"
"|                 |                 |                 | information for |\n"
"|                 |                 |                 | the forward     |\n"
"|                 |                 |                 | integration     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| exact_jacobianB | OT_BOOL      | GenericType()   | Use exact       |\n"
"|                 |                 |                 | Jacobian        |\n"
"|                 |                 |                 | information for |\n"
"|                 |                 |                 | the backward    |\n"
"|                 |                 |                 | integration     |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to              |\n"
"|                 |                 |                 | exact_jacobian] |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| finite_differen | OT_BOOL      | false           | Use finite      |\n"
"| ce_fsens        |                 |                 | differences to  |\n"
"|                 |                 |                 | approximate the |\n"
"|                 |                 |                 | forward         |\n"
"|                 |                 |                 | sensitivity     |\n"
"|                 |                 |                 | equations (if   |\n"
"|                 |                 |                 | AD is not       |\n"
"|                 |                 |                 | available)      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| fsens_abstol    | OT_DOUBLE         | GenericType()   | Absolute        |\n"
"|                 |                 |                 | tolerence for   |\n"
"|                 |                 |                 | the forward     |\n"
"|                 |                 |                 | sensitivity     |\n"
"|                 |                 |                 | solution        |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to abstol]      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| fsens_all_at_on | OT_BOOL      | true            | Calculate all   |\n"
"| ce              |                 |                 | right hand      |\n"
"|                 |                 |                 | sides of the    |\n"
"|                 |                 |                 | sensitivity     |\n"
"|                 |                 |                 | equations at    |\n"
"|                 |                 |                 | once            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| fsens_err_con   | OT_BOOL      | true            | include the     |\n"
"|                 |                 |                 | forward         |\n"
"|                 |                 |                 | sensitivities   |\n"
"|                 |                 |                 | in all error    |\n"
"|                 |                 |                 | controls        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| fsens_reltol    | OT_DOUBLE         | GenericType()   | Relative        |\n"
"|                 |                 |                 | tolerence for   |\n"
"|                 |                 |                 | the forward     |\n"
"|                 |                 |                 | sensitivity     |\n"
"|                 |                 |                 | solution        |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to reltol]      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| fsens_scaling_f | OT_DOUBLEVECTOR   | GenericType()   | Scaling factor  |\n"
"| actors          |                 |                 | for the         |\n"
"|                 |                 |                 | components if   |\n"
"|                 |                 |                 | finite          |\n"
"|                 |                 |                 | differences is  |\n"
"|                 |                 |                 | used            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| fsens_sensitivi | OT_INTVECTO | GenericType()   | Specifies which |\n"
"| y_parameters    | R               |                 | components will |\n"
"|                 |                 |                 | be used when    |\n"
"|                 |                 |                 | estimating the  |\n"
"|                 |                 |                 | sensitivity     |\n"
"|                 |                 |                 | equations       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| interpolation_t | OT_STRING       | \"hermite\"       | Type of         |\n"
"| ype             |                 |                 | interpolation   |\n"
"|                 |                 |                 | for the adjoint |\n"
"|                 |                 |                 | sensitivities ( |\n"
"|                 |                 |                 | hermite|polynom |\n"
"|                 |                 |                 | ial)            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| iterative_solve | OT_STRING       | \"gmres\"         | (gmres|bcgstab| |\n"
"| r               |                 |                 | tfqmr)          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| iterative_solve | OT_STRING       | GenericType()   | (gmres|bcgstab| |\n"
"| rB              |                 |                 | tfqmr)          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_multiste | OT_STRING       | \"bdf\"           | Simulator      |\n"
"| p_method        |                 |                 | scheme          |\n"
"|                 |                 |                 | (bdf|adams)     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_solver   | OT_STRING       | GenericType()   | A custom linear |\n"
"|                 |                 |                 | solver creator  |\n"
"|                 |                 |                 | function        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_solverB  | OT_STRING       | GenericType()   | A custom linear |\n"
"|                 |                 |                 | solver creator  |\n"
"|                 |                 |                 | function for    |\n"
"|                 |                 |                 | backwards       |\n"
"|                 |                 |                 | integration     |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to              |\n"
"|                 |                 |                 | linear_solver]  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_solver_o | OT_DICT   | GenericType()   | Options to be   |\n"
"| ptions          |                 |                 | passed to the   |\n"
"|                 |                 |                 | linear solver   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_solver_o | OT_DICT   | GenericType()   | Options to be   |\n"
"| ptionsB         |                 |                 | passed to the   |\n"
"|                 |                 |                 | linear solver   |\n"
"|                 |                 |                 | for backwards   |\n"
"|                 |                 |                 | integration     |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to linear_solve |\n"
"|                 |                 |                 | r_options]      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_solver_t | OT_STRING       | \"dense\"         | (user_defined|d |\n"
"| ype             |                 |                 | ense|banded|ite |\n"
"|                 |                 |                 | rative)         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_solver_t | OT_STRING       | GenericType()   | (user_defined|d |\n"
"| ypeB            |                 |                 | ense|banded|ite |\n"
"|                 |                 |                 | rative)         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| lower_bandwidth | OT_INT      | GenericType()   | Lower band-     |\n"
"|                 |                 |                 | width of banded |\n"
"|                 |                 |                 | Jacobian        |\n"
"|                 |                 |                 | (estimations)   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| lower_bandwidth | OT_INT      | GenericType()   | lower band-     |\n"
"| B               |                 |                 | width of banded |\n"
"|                 |                 |                 | jacobians for   |\n"
"|                 |                 |                 | backward        |\n"
"|                 |                 |                 | integration     |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to lower_bandwi |\n"
"|                 |                 |                 | dth]            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_krylov      | OT_INT      | 10              | Maximum Krylov  |\n"
"|                 |                 |                 | subspace size   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_krylovB     | OT_INT      | GenericType()   | Maximum krylov  |\n"
"|                 |                 |                 | subspace size   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_multistep_o | OT_INT      | 5               |                 |\n"
"| rder            |                 |                 |                 |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_num_steps   | OT_INT      | 10000           | Maximum number  |\n"
"|                 |                 |                 | of simulator   |\n"
"|                 |                 |                 | steps           |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| nonlinear_solve | OT_STRING       | \"newton\"        | (newton|functio |\n"
"| r_iteration     |                 |                 | nal)            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| pretype         | OT_STRING       | \"none\"          | (none|left|righ |\n"
"|                 |                 |                 | t|both)         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| pretypeB        | OT_STRING       | GenericType()   | (none|left|righ |\n"
"|                 |                 |                 | t|both)         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| quad_err_con    | OT_BOOL      | false           | Should the      |\n"
"|                 |                 |                 | quadratures     |\n"
"|                 |                 |                 | affect the step |\n"
"|                 |                 |                 | size control    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| reltol          | OT_DOUBLE         | 0.000           | Relative        |\n"
"|                 |                 |                 | tolerence for   |\n"
"|                 |                 |                 | the IVP         |\n"
"|                 |                 |                 | solution        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| reltolB         | OT_DOUBLE         | GenericType()   | Relative        |\n"
"|                 |                 |                 | tolerence for   |\n"
"|                 |                 |                 | the adjoint     |\n"
"|                 |                 |                 | sensitivity     |\n"
"|                 |                 |                 | solution        |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to reltol]      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| sensitivity_met | OT_STRING       | \"simultaneous\"  | (simultaneous|s |\n"
"| hod             |                 |                 | taggered)       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| steps_per_check | OT_INT      | 20              | Number of steps |\n"
"| point           |                 |                 | between two     |\n"
"|                 |                 |                 | consecutive     |\n"
"|                 |                 |                 | checkpoints     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| stop_at_end     | OT_BOOL      | true            | Stop the        |\n"
"|                 |                 |                 | simulator at   |\n"
"|                 |                 |                 | the end of the  |\n"
"|                 |                 |                 | interval        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| upper_bandwidth | OT_INT      | GenericType()   | Upper band-     |\n"
"|                 |                 |                 | width of banded |\n"
"|                 |                 |                 | Jacobian        |\n"
"|                 |                 |                 | (estimations)   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| upper_bandwidth | OT_INT      | GenericType()   | Upper band-     |\n"
"| B               |                 |                 | width of banded |\n"
"|                 |                 |                 | jacobians for   |\n"
"|                 |                 |                 | backward        |\n"
"|                 |                 |                 | integration     |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to upper_bandwi |\n"
"|                 |                 |                 | dth]            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| use_preconditio | OT_BOOL      | false           | Precondition an |\n"
"| ner             |                 |                 | iterative       |\n"
"|                 |                 |                 | solver          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| use_preconditio | OT_BOOL      | GenericType()   | Precondition an |\n"
"| nerB            |                 |                 | iterative       |\n"
"|                 |                 |                 | solver for the  |\n"
"|                 |                 |                 | backwards       |\n"
"|                 |                 |                 | problem         |\n"
"|                 |                 |                 | [default: equal |\n"
"|                 |                 |                 | to use_precondi |\n"
"|                 |                 |                 | tioner]         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"\n"
"\n"
">List of available monitors\n"
"\n"
"+---------+\n"
"|   Id    |\n"
"+=========+\n"
"| djacB   |\n"
"+---------+\n"
"| psetupB |\n"
"+---------+\n"
"| res     |\n"
"+---------+\n"
"| resB    |\n"
"+---------+\n"
"| resQB   |\n"
"+---------+\n"
"| reset   |\n"
"+---------+\n"
"\n"
"\n"
">List of available stats\n"
"\n"
"+-------------+\n"
"|     Id      |\n"
"+=============+\n"
"| nlinsetups  |\n"
"+-------------+\n"
"| nlinsetupsB |\n"
"+-------------+\n"
"| nsteps      |\n"
"+-------------+\n"
"| nstepsB     |\n"
"+-------------+\n"
"\n"
"\n"
"\n"
"\n"
;