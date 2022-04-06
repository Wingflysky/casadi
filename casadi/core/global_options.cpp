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


#include "global_options.hpp"
#include "exception.hpp"

namespace casadi {

  bool GlobalOptions::simplification_on_the_fly = true;
  bool GlobalOptions::hierarchical_sparsity = true;

  std::string GlobalOptions::casadipath;
  std::string GlobalOptions::casadi_include_path;

  casadi_int GlobalOptions::max_num_dir = 64;

  // By default, use zero-based indexing
  casadi_int GlobalOptions::start_index = 0;



#ifdef _WIN32
  std::string GlobalOptions::default_system_prefix = "";
  std::string GlobalOptions::default_system_suffix = "";
  std::string GlobalOptions::default_compiler = "cl.exe";
  std::string GlobalOptions::default_linker = "link.exe";
  std::string GlobalOptions::default_compiler_setup = "/c";
  std::string GlobalOptions::default_linker_setup = "/DLL";
  std::string GlobalOptions::default_compiler_output_flag = "/Fo";
  std::string GlobalOptions::default_linker_output_flag = "/out:";
  std::vector<std::string> GlobalOptions::default_compiler_extra_suffixes = {".exp", ".lib"};
#else
  std::string GlobalOptions::default_system_prefix = "";
  std::string GlobalOptions::default_system_suffix = "";
  std::string GlobalOptions::default_compiler = "gcc";
  std::string GlobalOptions::default_linker = "gcc";
  std::string GlobalOptions::default_compiler_setup = "-fPIC -c";
  std::string GlobalOptions::default_linker_setup = "-shared";
  std::string GlobalOptions::default_compiler_output_flag = "-o ";
  std::string GlobalOptions::default_linker_output_flag = "-o ";
  std::vector<std::string> GlobalOptions::default_compiler_extra_suffixes = {};
#endif

} // namespace casadi
