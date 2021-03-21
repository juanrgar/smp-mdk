//
// Title:
//      IRequest.h
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
//      This file defines the IRequest interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IREQUEST_H
#define SMP_IREQUEST_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exceptions.h"
#include "Smp/SimpleTypes.h"

// ----------------------------------------------------------------------------
// ---------------------------- IRequest interface ----------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    static const Smp::String8 InvalidParameterIndexTemplate = "Invalid parameter index %d for operation '%s'";
    static const Smp::String8 InvalidParameterValueTemplate = "Invalid value for parameter '%s'";
    static const Smp::String8 InvalidReturnValueTemplate    = "Invalid return value for operation '%s'";
    static const Smp::String8 VoidOperationTemplate         = "Operation '%s' is a void operation";

    /// Request for dynamic invocation.
    /// The request holds information which is passed between a client
    /// invoking an operation via the IDynamicInvocation interface
    /// and a component (model or service) being invoked.
    class IRequest
    {
    public:
        /// Virtual Destructor.
        virtual ~IRequest() { }

        /// Invalid parameter index.
        /// This exception is raised when using an invalid parameter index to
        /// set (SetParameterValue()) or get (GetParameterValue()) a parameter
        /// value of an operation in a request.
        class InvalidParameterIndex : public Smp::Exception
        {
        public:
            /// Name of operation.
            String8 operationName;
            /// Invalid parameter index used.
            const Int32 parameterIndex;

            InvalidParameterIndex(
                String8 _operationName,
                const Int32  _parameterIndex) throw() :
            Smp::Exception("InvalidParameterIndex"),
                operationName (_operationName),
                parameterIndex(_parameterIndex)
            {
                description = new Char8[strlen(InvalidParameterIndexTemplate) 
                    + 8
                    + strlen(operationName)];

                sprintf(description, InvalidParameterIndexTemplate, 
                    parameterIndex,
                    operationName);
            }

            ~InvalidParameterIndex() throw() {}
        };

        /// Invalid value for parameter.
        /// This exception is raised when trying to assign an illegal value to
        /// a parameter of an operation in a request using SetParameterValue().
        class InvalidParameterValue : public Smp::Exception
        {
        public:
            /// Name of parameter value was assigned to.
            String8 parameterName;
            /// Value that was passed as parameter.
            const AnySimple value;

            InvalidParameterValue(
                String8 _parameterName,
                const AnySimple _value) throw() :
            Smp::Exception("InvalidParameterValue"),
                parameterName (_parameterName),
                value(_value)
            {
                description = new Char8[strlen(InvalidParameterValueTemplate) 
                    + strlen(parameterName)];

                sprintf(description, InvalidParameterValueTemplate, 
                    parameterName);
            }
            
            virtual ~InvalidParameterValue() throw ( )
            {
            }
        };

        /// Invalid value for return value.
        /// This exception is raised when trying to assign an illegal return
        /// value of an operation in a request using SetReturnValue().
        class InvalidReturnValue : public Smp::Exception
        {
        public:
            /// Name of operation the return value was assigned to.
            String8 operationName;
            /// Value that was passed as return value.
            const AnySimple value;

            InvalidReturnValue(
                String8 _operationName,
                const AnySimple _value) throw() :
            Smp::Exception("InvalidReturnValue"),
                operationName (_operationName),
                value(_value)
            {
                description = new Char8[strlen(InvalidReturnValueTemplate) 
                    + strlen(operationName)];

                sprintf(description, InvalidReturnValueTemplate, 
                    operationName);
            }
            
            virtual ~InvalidReturnValue() throw ( )
            {
            }            
        };

        /// Operation is a void operation.
        /// This exception is raised when trying to read (GetReturnValue())
        /// or write (SetReturnValue()) the return value of a void operation.
        class VoidOperation : public Smp::Exception
        {
        public:
            /// Name of operation.
            String8 operationName;

            VoidOperation(
                String8 _operationName) throw() :
            Smp::Exception("VoidOperation"),
                operationName (_operationName)
            {
                description = new Char8[strlen(VoidOperationTemplate) 
                    + strlen(operationName)];

                sprintf(description, VoidOperationTemplate, 
                    operationName);
            }
            ~VoidOperation() throw() {}
        };

        /// Get operation name.
        /// Returns the name of the operation that this request is for.
        /// @remarks A request is typically created using the CreateRequest() 
        ///          method to dynamically call a specific method of a component
        ///          implementing the IDynamicInvocation interface.
        ///          This method returns the name passed to it, to allow finding
        ///          out which method is actually called on Invoke().
        virtual String8 GetOperationName() const = 0;

        /// Get parameter count.
        /// Returns the number of parameters stored in the request.
        /// @remarks Parameters are typically accessed by their 0-based index.
        ///          This index 
        ///          - must not be negative, 
        ///          - must be smaller than the parameter count.
        ///
        ///          Use the GetParameterIndex() method to access parameters by
        ///          name.
        virtual Int32 GetParameterCount() const = 0;

        /// Get index of a parameter.
        /// Query for a parameter index by parameter name.
        /// @param   parameterName Name of parameter.
        /// @return  Index of parameter with the given name (0-based), or 
        ///          -1 if no parameter with the given name could be found.
        /// @remarks An index of -1 indicates that no parameter with the
        ///          given name exists.
        virtual Int32 GetParameterIndex(String8 parameterName) const = 0;

        /// Set a parameter value.
        /// Assign a value to a parameter at a given position.
        /// @param   index Index of parameter (0-based).
        /// @param   value Value of parameter.
        virtual void SetParameterValue(
            const Int32 index, 
            const AnySimple value) throw (
            Smp::IRequest::InvalidParameterIndex, 
            Smp::IRequest::InvalidParameterValue,
            Smp::InvalidAnyType) = 0;

        /// Get a parameter value.
        /// Query a value of a parameter at a given position.
        /// @param   index Index of parameter (0-based).
        /// @return  Value of parameter with given index.
        virtual AnySimple GetParameterValue(const Int32 index) const throw (
            Smp::IRequest::InvalidParameterIndex) = 0;

        /// Set the return value.
        /// Assign the return value of the operation.
        /// @param   value Return value.
        virtual void SetReturnValue(const AnySimple value) throw (
            Smp::IRequest::InvalidReturnValue, 
            Smp::IRequest::VoidOperation,
            Smp::InvalidAnyType) = 0;

        /// Get the return value.
        /// Query the return value of the operation.
        /// @return  Return value of the operation.
        virtual AnySimple GetReturnValue() const throw (
            Smp::IRequest::VoidOperation) = 0;
    };
}

#endif // SMP_IREQUEST_H

/***********
 * History *
 ***********/

//$Log: IRequest.h,v $
//Revision 1.3  2006/12/21 16:01:49  nin
//Added missing destructors with throw statement to satisfy GCC.
//
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

