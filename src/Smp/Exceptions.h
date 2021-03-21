//
// Title:
//      Exceptions.h
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
//      This file defines some exceptions used throughout SMP2. This includes
//      the Exception base class as well as some derived exceptions.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_EXCEPTIONS_H
#define SMP_EXCEPTIONS_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include <exception>

#include <stdio.h>

#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ---------------------------- Exceptions ------------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    static const String8 InvalidObjectNameTemplate  = "Invalid object name '%s'";
    static const String8 DuplicateNameTemplate      = "Name '%s' is already used by another object";
    static const String8 InvalidAnyTypeTemplate     = "Invalid type found: Expected '%s', but found '%s'";
    static const String8 InvalidObjectTypeTemplate  = "Object '%s' is not of valid type.";
    static const String8 TypeName[] = {
        "None",        ///< no type, e.g. for void.
        "Char8",       ///<  8 bit character type.
        "Bool",        ///<  1 bit Bool type.
        "Int8",        ///<  8 bit   signed integer type.
        "UInt8",       ///<  8 bit unsigned integer type.
        "Int16",       ///< 16 bit   signed integer type.
        "UInt16",      ///< 16 bit unsigned integer type.
        "Int32",       ///< 32 bit   signed integer type.
        "UInt32",      ///< 32 bit unsigned integer type.
        "Int64",       ///< 64 bit   signed integer type.
        "UInt64",      ///< 64 bit unsigned integer type.
        "Float32",     ///< 32 bit single floating-point type.
        "Float64",     ///< 64 bit double floating-point type.
        "Duration",    ///< Duration in nanoseconds.
        "DateTime",    ///< Point in time in nanoseconds.
        "String8"      ///<  8 bit NULL terminated string type.
    };

    /// Base class for all SMP exceptions.
    /// This exception is the base class for all other SMP exceptions.
    /// It provides a Name and a Description.
    class Exception : public std::exception, public virtual IObject
    {
    private:
        /// Name of the exception that is returned by GetName.
        String8 exceptionName;

    protected:
        /// Description of the problem encountered.
        Char8* description;

        /// Protected constructor available to derived classes only.
        Exception(
            String8 _exceptionName) throw() :
        exceptionName(_exceptionName),
            description(NULL)
        {
        }

        /// Virtual destructor to release memory.
        virtual ~Exception() throw()
        {
            delete[] description;
        }

    public:
        /// Get name of exception class.
        /// Returns the name of the exception class.
        /// This name can be used e.g. for debugging purposes.
        /// @return  Name of the exception class.
        String8 GetName() const
        {
            return exceptionName;
        }

        /// Get description of exception.
        /// Returns a textual description of the exception.
        /// This description can be used e.g. for debugging purposes.
        /// @return  Textual description of the problem encountered.
        String8 GetDescription() const
        {
            return description;
        }
    };
}

namespace Smp
{
    /// Invalid object name.
    /// This exception is raised when trying to set an object's name to an
    /// invalid name. Names 
    ///          - must not be empty, 
    ///          - must not exceed 32 characters in size,
    ///          - must start with a letter, and
    ///          - must only contain letters, digits, the underscore ("_")
    ///            and brackets ("[" and "]").
    class InvalidObjectName : public Exception
    {
    public:
        /// Invalid object name passed to SetName().
        String8 objectName;

        /// Constructor for new exception.
        InvalidObjectName(
            String8 _objectName) :
        Exception("InvalidObjectName"),
            objectName(_objectName)
        {
            description = new Char8[strlen(InvalidObjectNameTemplate) 
                + strlen(objectName)];

            sprintf(description, InvalidObjectNameTemplate, 
                objectName);
        }
        ~InvalidObjectName() throw() {}
    };
}

namespace Smp
{
    /// Duplicate name.
    /// This exception is raised when trying to add an object to a collection 
    /// of objects which have to have unique names, but another object with 
    /// the same name does exist. This would lead to duplicate names.
    class DuplicateName : public Exception
    {
    public:
        /// Name that already exists in the collection.
        String8 name;

        /// Constructor for new exception.
        DuplicateName(
            String8 _name) throw() :
        Exception("DuplicateName"),
            name(_name)
        {
            description = new Char8[strlen(DuplicateNameTemplate) 
                + strlen(name)];

            sprintf(description, DuplicateNameTemplate, 
                name);
        }

        ~DuplicateName() throw() {}
    };
}

namespace Smp
{
    /// Invalid type of AnySimple.
    /// This exception is raised when trying to use an AnySimple of wrong type.
    /// @remarks This can happen when assigning a value to an AnySimple 
    ///          instance, but as well when e.g. registering an event sink
    ///          with an event source of another event argument type.
    class InvalidAnyType : public Exception
    {
    public:
        /// Type that is not valid.
        Smp::SimpleTypeKind invalidType;
        /// Type that was expected.
        Smp::SimpleTypeKind expectedType;

        /// Constructor for new exception.
        InvalidAnyType(
            Smp::SimpleTypeKind _invalidType,
            Smp::SimpleTypeKind _expectedType) throw() :
        Exception("InvalidAnyType"),
            invalidType(_invalidType),
            expectedType(_expectedType)
        {
            description = new Char8[strlen(InvalidAnyTypeTemplate) 
                    + strlen(TypeName[expectedType]) 
                    + strlen(TypeName[invalidType])];

            sprintf(description, InvalidAnyTypeTemplate, 
                TypeName[expectedType], 
                TypeName[invalidType]);
        }

        ~InvalidAnyType() throw() {}
    };
}

namespace Smp
{
    /// Invalid type of an Object.
    /// This exception is raised when trying to pass an object of wrong type.
    /// @remarks This can happen when adding a model to a container or 
    ///          reference which is semantically typed by a specific type
    ///          derived from IComponent.
    class InvalidObjectType : public Exception
    {
    public:
        /// Object that is not valid type.
        Smp::IObject* invalidObject;

        /// Constructor for new exception.
        /// @param _invalidObject Object with invalid type.
        InvalidObjectType(
            IObject* _invalidObject) :
        Exception("InvalidObjectType"),
            invalidObject(_invalidObject)
        {
            Smp::String8 objectName = "NULL";

            if (invalidObject)
            {
                objectName = invalidObject->GetName();
            }

            description = new Char8[strlen(InvalidObjectTypeTemplate) 
                + strlen(objectName)];

            sprintf(description, InvalidObjectTypeTemplate, 
                objectName);
        }

        ~InvalidObjectType() throw() {}
    };
}

#endif // SMP_EXCEPTIONS_H

/***********
 * History *
 ***********/

//$Log: Exceptions.h,v $
//Revision 1.4  2007/04/26 12:27:19  nin
//Exception.description was deallocated with delete instead of delete[].
//
//Revision 1.3  2007/04/25 16:10:58  nin
//SPR-294 String8 set as last item in array TypeName, to avoid mismatches with the SimpleTypeKind enum.
//
//Revision 1.2  2006/12/21 15:59:11  nin
//String8 added in TypeName array.
//
//Revision 1.1  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

