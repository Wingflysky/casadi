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


#ifndef CASADI_SHARED_OBJECT_INTERNAL_HPP
#define CASADI_SHARED_OBJECT_INTERNAL_HPP

#include "shared_object.hpp"

namespace casadi {

  /// \cond INTERNAL
  /// Internal class for the reference counting framework, see comments on the public class.
  class CASADI_EXPORT SharedObjectInternal {
    friend class SharedObject;
    friend class Memory;
  public:

    /// Default constructor
    SharedObjectInternal();

    /// Copy constructor
    SharedObjectInternal(const SharedObjectInternal& node);

    /// Assignment operator
    SharedObjectInternal& operator=(const SharedObjectInternal& node);

    /// Destructor
    virtual ~SharedObjectInternal() = 0;

    /// Get the reference count
    int getCount() const;

    /// Print a representation of the object
    virtual void repr(std::ostream &stream) const;

    /// Print a description of the object
    virtual void print(std::ostream &stream) const;

    /** \brief Get a weak reference to the object */
    WeakRef* weak();

  protected:
    /** Called in the constructor of singletons to avoid that the counter reaches zero */
    void initSingleton() {
      casadi_assert(count==0);
      count++;
    }

    /** Called in the destructor of singletons */
    void destroySingleton() {
      count--;
    }

    /// Get a shared object from the current internal object
    template<class B>
    B shared_from_this();

    /// Get a shared object from the current internal object
    template<class B>
    const B shared_from_this() const;

  private:
    /// Number of references pointing to the object
    unsigned int count;

    /// Weak pointer (non-owning) object for the object
    WeakRef* weak_ref_;
  };

  /// Template function implementations
  template<class B>
  B SharedObjectInternal::shared_from_this() {
    casadi_assert(B::test_cast(this));
    B ret;
    ret.assignNode(this);
    return ret;
  }

  template<class B>
  const B SharedObjectInternal::shared_from_this() const {
    casadi_assert(B::test_cast(this));
    B ret;
    ret.assignNode(const_cast<SharedObjectInternal*>(this));
    return ret;
  }

  class CASADI_EXPORT WeakRefInternal : public SharedObjectInternal {
  public:
    // Constructor
    WeakRefInternal(SharedObjectInternal* raw);

    // Destructor
    ~WeakRefInternal();

    // Raw pointer to the cached object
    SharedObjectInternal* raw_;
  };
  /// \endcond


} // namespace casadi


#endif // CASADI_SHARED_OBJECT_INTERNAL_HPP
