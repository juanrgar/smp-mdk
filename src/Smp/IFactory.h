//
// Title:
//      IFactory.h
//
// Project:
//      Simulation Model Portability (SMP) Standard 2.0
//      C++ Mapping
//      Version 1.2 from October 28th, 2005
//
// Origin:
//      Simulation Model Portability (SMP) Configuration Control Board (CCB)
//
// Purpose:
//      This file defines the IFactory interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IFACTORY_H
#define SMP_IFACTORY_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/IComponent.h"

// ---------------------------------------------------------------------------
// --------------------------- IFactory interface ---------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    /// This interface is implemented by all component factories.
    class IFactory : public virtual IObject
    {
    public:
        /// Get specification identifier of factory.
        /// @return  Identifier of component specification.
        virtual Uuid GetSpecification() const = 0;

        /// Get implementation identifier of factory.
        /// @return  Identifier of component implementation.
        virtual Uuid GetImplementation() const = 0;

        /// Create a new instance.
        /// This method creates a new component instance.
        virtual IComponent* CreateInstance() = 0;

        /// Delete an existing instance.
        /// This method deletes an existing component instance that has been 
        /// created using CreateInstance() earlier.
        /// @param instance Instance to delete.
        virtual void DeleteInstance(IComponent* instance) = 0;
    };
}

namespace Smp
{
    /// Collection of factories.
    /// A factory collection is an ordered collection of factories,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings. 
    typedef std::vector<IFactory*> FactoryCollection;
}

#endif  // SMP_IFACTORY_H

/***********
 * History *
 ***********/

//$Log: IFactory.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

