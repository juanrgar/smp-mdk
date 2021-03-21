//
// Title:
//      IReference.h
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
//      This file defines the IReference interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IREFERENCE_H
#define SMP_IREFERENCE_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"

// ----------------------------------------------------------------------------
// ---------------------------- IReference interface --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Reference to components.
    /// A reference allows to query for the referenced components.
    /// @remarks Together with the IAggregate interface, this interface 
    ///          represents the aggregation mechanism (Reference) of the SMP 
    ///          Metamodel (SMDL).
    class IReference : public virtual IObject
    {
    public:
        /// Get all referenced components.
        /// Query for the collection of all referenced components.
        /// @return Collection of referenced components.
        /// @remarks The collection may be empty if no components exist
        ///          in the reference.
        virtual const ComponentCollection* GetComponents() const = 0;

        /// Get a referenced component by name.
        /// Query for a referenced component by its name.
        /// @param   name Component name.
        /// @return  Referenced component with the given name, or null if no 
        ///          referenced component with the given name could be found.
        /// @remarks The returned component may be null if no
        ///          component with the given name could be found.
        ///          If more than one component with the given name exists, 
        ///          it is undefined which one is returned with this method.
        virtual IComponent* GetComponent(String8 name) const = 0;
    };
}

namespace Smp
{
    /// Collection of references.
    /// A reference collection is an ordered collection of references,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings. 
    typedef std::vector<IReference*> ReferenceCollection;
}

#endif // SMP_IREFERENCE_H

/***********
 * History *
 ***********/

//$Log: IReference.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

