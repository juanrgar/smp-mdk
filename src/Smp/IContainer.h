//
// Title:
//      IContainer.h
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
//      This file defines the IContainer interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_ICONTAINER_H
#define SMP_ICONTAINER_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"

// ----------------------------------------------------------------------------
// ---------------------------- IContainer interface --------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Container of components.
    /// A container allows to query for its contained components.
    /// @remarks Together with the IComposite interface, this interface 
    ///          represents the composition mechanism (Container) of the SMP 
    ///          Metamodel (SMDL).
    class IContainer : public virtual IObject
    {
    public:
        /// Get all contained components.
        /// Query for the collection of all contained components.
        /// @return Collection of contained component.
        /// @remarks The collection may be empty if no components exist
        ///          in the container.
        virtual const ComponentCollection* GetComponents() const = 0;

        /// Get a contained component by name.
        /// Query for a contained component by its name.
        /// @param   name Child name.
        /// @return  Child component, or undefined if no component
        ///             with the given name is contained.
        /// @remarks The returned component may be undefined if no
        ///          component with the given name could be found.
        virtual IComponent* GetComponent(String8 name) const = 0;
    };
}

namespace Smp
{
    /// Collection of containers.
    /// A container collection is an ordered collection of containers,
    /// which allows iterating all members.
    /// @remarks This type is platform specific.
    ///          For details see the SMP Platform Mappings. 
    typedef std::vector<IContainer*> ContainerCollection;
}

#endif // SMP_ICONTAINER_H

/***********
 * History *
 ***********/

//$Log: IContainer.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

