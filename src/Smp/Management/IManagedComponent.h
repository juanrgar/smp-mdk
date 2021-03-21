//
// Title:
//      IManagedComponent.h
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
//      This file defines the IManagedComponent interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_MANAGEMENT_IMANAGEDCOMPONENT_H
#define SMP_MANAGEMENT_IMANAGEDCOMPONENT_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"
#include "Smp/Management/IManagedObject.h"

// ----------------------------------------------------------------------------
// --------------------------- IManagedComponent interface --------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Management 
    {
        /// Managed component.
        /// A managed component additionally allows assigning the parent.
        class IManagedComponent :
            public virtual IManagedObject,
            public virtual IComponent
        {
        public:
            /// Defines the parent component ("property setter").
            /// Components link to their parent to allow traversing the
            /// tree of components in any direction.
            /// @param   parent Parent of component.
            /// @remarks Components that are part of a composition 
            ///          point to their parent via this property.
            ///          The parent is null for root components.
            virtual void SetParent(IComposite* parent) = 0;
        };
    }
}

#endif // SMP_MANAGEMENT_IMANAGEDCOMPONENT_H

/***********
 * History *
 ***********/

//$Log: IManagedComponent.h,v $
//Revision 1.2  2006/09/27 11:44:22  nin
//SMP2 v1.2
// 

