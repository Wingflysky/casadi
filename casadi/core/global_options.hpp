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


#ifndef CASADI_GLOBAL_OPTIONS_HPP
#define CASADI_GLOBAL_OPTIONS_HPP

#include <fstream>
#include <iostream>

#include "casadi/core/casadi_common.hpp"
#include <casadi/core/casadi_export.h>

namespace casadi {

  /**
  * \brief Collects global CasADi options
  *
  *
  * Note to developers:  \n
  *  - use sparingly. Global options are - in general - a rather bad idea \n
  *  - this class must never be instantiated. Access its static members directly \n
  *
  *  \author Joris Gillis
  *  \date 2012
  */
  class CASADI_EXPORT GlobalOptions {
    private:
      /// No instances are allowed
      GlobalOptions();
    public:

#ifndef SWIG
      /** \brief Indicates whether simplifications should be made on the fly.
      * e.g.   cos(-x) -> cos(x)
      * Default: true
      */
      static bool simplification_on_the_fly;

      static std::string casadipath;

      static std::string casadi_include_path;

      static bool hierarchical_sparsity;

      static casadi_int max_num_dir;

      static casadi_int start_index;

      static std::string default_compiler;

      static std::string default_linker;

      static std::string default_compiler_setup;

      static std::string default_linker_setup;

      static std::string default_compiler_output_flag;

      static std::string default_linker_output_flag;

      static std::vector<std::string> default_compiler_extra_suffixes;

      static std::string default_system_prefix;

      static std::string default_system_suffix;

#endif //SWIG
      // Setter and getter for simplification_on_the_fly
      static void setSimplificationOnTheFly(bool flag) { simplification_on_the_fly = flag; }
      static bool getSimplificationOnTheFly() { return simplification_on_the_fly; }

      // Setter and getter for hierarchical_sparsity
      static void setHierarchicalSparsity(bool flag) { hierarchical_sparsity = flag; }
      static bool getHierarchicalSparsity() { return hierarchical_sparsity; }

      static void setCasadiPath(const std::string & path) { casadipath = path; }
      static std::string getCasadiPath() { return casadipath; }

      static void setCasadiIncludePath(const std::string & path) { casadi_include_path = path; }
      static std::string getCasadiIncludePath() { return casadi_include_path; }

      static void setMaxNumDir(casadi_int ndir) { max_num_dir=ndir; }
      static casadi_int getMaxNumDir() { return max_num_dir; }

      static void setDefaultCompiler(const std::string& s) { default_compiler = s; }
      static std::string getDefaultCompiler() { return default_compiler; }

      static void setDefaultLinker(const std::string& s) { default_linker = s; }
      static std::string getDefaultLinker() { return default_linker; }

      static void setDefaultCompilerSetup(const std::string& s) { default_compiler_setup = s; }
      static std::string getDefaultCompilerSetup() { return default_compiler_setup; }

      static void setDefaultLinkerSetup(const std::string& s) { default_linker_setup = s; }
      static std::string getDefaultLinkerSetup() { return default_linker_setup; }

      static void setDefaultCompilerOutputFlag(const std::string& s) { default_compiler_output_flag = s; }
      static std::string getDefaultCompilerOutputFlag() { return default_compiler_output_flag; }

      static void setDefaultLinkerOutputFlag(const std::string& s) { default_linker_output_flag = s; }
      static std::string getDefaultLinkerOutputFlag() { return default_linker_output_flag; }

      static void setDefaultCompilerExtraSuffixes(const std::vector<std::string>& s) { default_compiler_extra_suffixes = s; }
      static std::vector<std::string> getDefaultCompilerExtraSuffixes() { return default_compiler_extra_suffixes; }

      static void setDefaultSystemPrefix(const std::string& s) { default_system_prefix = s; }
      static std::string getDefaultSystemPrefix() { return default_system_prefix; }

      static void setDefaultSystemSuffix(const std::string& s) { default_system_suffix = s; }
      static std::string getDefaultSystemSuffix() { return default_system_suffix; }

  };

} // namespace casadi

#endif // CASADI_GLOBAL_OPTIONS_HPP
