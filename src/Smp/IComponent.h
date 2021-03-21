//
// Title:
//      IComponent.h
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
//      This file defines the IComponent interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_ICOMPONENT_H
#define SMP_ICOMPONENT_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ---------------------------- IComponent interface --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    // Forward declaration because of circular references.
    class IComposite;

    /// Base interface for all components.
    /// All SMP components implement this interface.
    /// @remarks Services (IService) and models (IModel) are typical components 
    ///          in SMP, but the simulator (ISimulator) is a component as well.
    class IComponent : public virtual IObject
    {
    public:
        /// Returns the parent component of the component ("property getter").
        /// Components link to their parent to allow traversing the
        /// tree of components upwards to the root component, which is 
        /// typically the simulation environment (ISimulator).
        /// @return  Parent component of component, or null if component
        ///          has no parent.
        /// @remarks Components that are part of a composition
        ///          point to their parent via this property.
        ///          The parent is null for root components.
        ///          Typically, only the simulator itself is a root component,
        ///          so all other components should have a parent component.
        virtual IComposite* GetParent() const = 0;
    };
}

namespace Smp
{
    /// Collection of components.
    /// A component collection is an ordered collection of components,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings. 
    typedef std::vector<IComponent*> ComponentCollection;
}

#endif // SMP_ICOMPONENT_H

/***********
 * History *
 ***********/

//$Log: IComponent.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

