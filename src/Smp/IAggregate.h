//
// Title:
//      IAggregate.h
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
//      This file defines the IAggregate interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IAGGREGATE_H
#define SMP_IAGGREGATE_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IReference.h"

// ----------------------------------------------------------------------------
// ---------------------------- IAggregate interface --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Aggregate component.
    /// A component with references to other components implements this interface.
    /// Referenced components are held in named references.
    /// @remarks Together with the IReference interface, this interface 
    ///          represents the aggregation mechanism (Reference) of the SMP 
    ///          Metamodel (SMDL).
    ///          In UML 2.0, this maps to an aggregate required interface.
    class IAggregate : public virtual IComponent
    {
    public:
        /// Get all references.
        /// Query for the collection of all references of the component.
        /// @return  Collection of references.
        /// @remarks The collection may be empty if no references exist.
        virtual const ReferenceCollection* GetReferences() const = 0;

        /// Get a reference by name.
        /// Query for a reference of this component by its name.
        /// @param   name Reference name.
        /// @return  Reference with the given name, or null if no
        ///          reference with the given name could be found.
        /// @remarks The returned reference may be null if no
        ///          reference with the given name could be found.
        virtual IReference* GetReference(String8 name) const = 0;
    };
}

#endif // SMP_IAGGREGATE_H

/***********
 * History *
 ***********/

//$Log: IAggregate.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

