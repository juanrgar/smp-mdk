//
// Title:
//      IObject.h
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
//      This file defines the IObject interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IOBJECT_H
#define SMP_IOBJECT_H

// ---------------------------------------------------------------------------
// --------------------------- Include Header Files --------------------------
// ---------------------------------------------------------------------------

#include "Smp/SimpleTypes.h"

// ---------------------------------------------------------------------------
// --------------------------- IObject interface -----------------------------
// ---------------------------------------------------------------------------

namespace Smp
{
    /// Base interface for all objects.
    /// This is the base interface for all other SMP interfaces.
    /// While most interfaces derive from IComponent, which itself is derived
    /// from IObject, some objects (including IEntryPoint, IEventSink, and
    /// IEventSource) are directly derived from IObject.
    /// @remarks The two methods of this interface ensure that all SMP objects
    ///          can be shown with a name, and with an optional description.
    class IObject
    {
    public:
        /// Standard destructor.
        /// This is needed to be able to destroy objects
        /// using the actual derived object's destructor.
        virtual ~IObject() { }

        /// Returns the name of the object ("property getter").
        /// Applications may display the name as user readable object
        /// identification.
        /// @return  Name of object.
        /// @remarks Names 
        ///          - must be unique within their context,
        ///          - must not be empty, 
        ///          - must not exceed 32 characters in size,
        ///          - must start with a letter, and
        ///          - must only contain letters, digits, the underscore ("_")
        ///            and brackets ("[" and "]").
        virtual String8 GetName() const = 0;

        /// Returns the description of the object ("property getter").
        /// Applications may display the description as additional
        /// information on the object.
        /// @return  Description of object.
        /// @remarks Descriptions are optional and may be empty.
        virtual String8 GetDescription() const = 0;
    };
}

#endif // SMP_IOBJECT_H

/***********
 * History *
 ***********/

//$Log: IObject.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

