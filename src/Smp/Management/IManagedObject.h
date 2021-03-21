//
// Title:
//      IManagedObject.h
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
//      This file defines the IManagedObject interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_MANAGEMENT_IMANAGEDOBJECT_H
#define SMP_MANAGEMENT_IMANAGEDOBJECT_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IObject.h"
#include "Smp/Exceptions.h"

// ----------------------------------------------------------------------------
// --------------------------- IManagedObject interface -----------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// SMP managed interfaces.
    /// Managed interfaces allow full access to all functionality of components.
    /// For composition and aggregation, they extend the existing
    /// interfaces by methods to add new components respective references.
    /// For entry points, event sources and event sinks, the managed interfaces
    /// provide access to the elements by name.
    /// For fields, access by name is provided by an extended interface allowing
    /// to read and write field values.
    /// @remarks Typically, these interfaces are called by a Loader or Model
    ///          Manager component to push configuration information into the 
    ///          models, which has been read from an SMDL Assembly file.
    namespace Management 
    {
        /// Managed object.
        /// A managed object additionally allows assigning name and description.
        class IManagedObject : public virtual IObject
        {
        public:
            /// Defines the name of the managed object ("property setter").
            /// Management components may use this to assign names to objects.
            /// @param   name Name of object.
            /// @remarks Names 
            ///          - must be unique within their context,
            ///          - must not be empty, 
            ///          - must not exceed 32 characters in size,
            ///          - must start with a letter, and
            ///          - must only contain letters, digits, the underscore ("_")
            ///            and brackets ("[" and "]").
            virtual void SetName(String8 name) throw (
                Smp::InvalidObjectName) = 0;

            /// Defines the description of the managed object ("property setter").
            /// Management components may use this to set object descriptions.
            /// @param   description Description of object.
            virtual void SetDescription(String8 description) = 0;
        };
    }
}

#endif // SMP_MANAGEMENT_IMANAGEDOBJECT_H

/***********
 * History *
 ***********/

//$Log: IManagedObject.h,v $
//Revision 1.2  2006/09/27 11:44:22  nin
//SMP2 v1.2
// 

