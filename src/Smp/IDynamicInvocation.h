//
// Title:
//      IDynamicInvocation.h
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
//      This file defines the IDynamicInvocation interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_IDYNAMICINVOCATION_H
#define SMP_IDYNAMICINVOCATION_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"
#include "Smp/IRequest.h"

// ----------------------------------------------------------------------------
// ---------------------------- IDynamicInvocation interface ------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    static const Smp::String8 InvalidOperationNameTemplate  = "Invalid operation name '%s'";
    static const Smp::String8 InvalidParameterCountTemplate = "Invalid parameter count of operation '%s': Expected '%d', but found '%d'";
    static const Smp::String8 InvalidParameterTypeTemplate  = "Invalid parameter '%s' of operation '%s': Expected '%s', but found '%s'";

    /// Dynamic invocation.
    /// A component may implement this interface in order to allow
    /// dynamic invocation of its operations.
    /// @remarks This is an optional interface. It needs to be implemented
    ///          only for components supporting dynamic invocation.
    ///          Dynamic invocation is typically used for scripting.
    ///          In its current implementation, dynamic invocation is limited
    ///          to operations using only simple types.
    class IDynamicInvocation : public virtual IComponent
    {
    public:
        /// Invalid operation name.
        /// This exception is raised by the Invoke() method when trying to
        /// invoke a method that does not exist, or that does not support dynamic
        /// invocation.
        /// @remarks The name of the operation 
        ///          can be extracted from the request using the method 
        ///          GetOperationName().
        class InvalidOperationName : public Smp::Exception
        {
        public:
            /// Operation name of request passed to the Invoke() method.
            String8 operationName;

            InvalidOperationName(
                String8 _operationName) throw() :
            Smp::Exception("InvalidOperationName"),
                operationName (_operationName)
            {
                description = new Char8[strlen(InvalidOperationNameTemplate) 
                    + strlen(operationName)];

                sprintf(description, InvalidOperationNameTemplate, 
                    operationName);
            }
            ~InvalidOperationName() throw() {}
        };

        /// Invalid parameter count.
        /// This exception is raised by the Invoke() method when trying to
        /// invoke a method with a wrong number of parameters.
        /// @remarks The wrong number of parameters 
        ///          can be extracted from the request using the method 
        ///          GetParameterCount().
        class InvalidParameterCount : public Smp::Exception
        {
        public:
            /// Operation name of request passed to the Invoke() method.
            String8 operationName;
            /// Correct number of parameters of operation.
            const Int32 operationParameters;
            /// Wrong number of parameters of operation.
            const Int32 requestParameters;

            InvalidParameterCount(
                String8 _operationName,
                const Int32 _operationParameters,
                const Int32 _requestParameters) throw() :
            Smp::Exception("InvalidParameterCount"),
                operationName (_operationName),
                operationParameters(_operationParameters),
                requestParameters(_requestParameters)
            {
                description = new Char8[strlen(InvalidParameterCountTemplate) 
                    + strlen(operationName) 
                    + 8
                    + 8];

                sprintf(description, InvalidParameterCountTemplate, 
                    operationName, 
                    operationParameters, 
                    requestParameters);
            }
            ~InvalidParameterCount() throw() {}

        };

        /// Invalid parameter type.
        /// This exception is raised by the Invoke() method when trying to
        /// invoke a method passing a parameter of wrong type.
        /// @remarks The index of parameter of wrong type 
        ///          can be extracted from the request using the method 
        ///          GetParameterIndex().
        class InvalidParameterType : public Smp::Exception
        {
        public:
            /// Operation name of request passed to the Invoke() method.
            String8 operationName;
            /// Name of parameter of wrong type.
            String8 parameterName;
            /// Type that is not valid.
            Smp::SimpleTypeKind invalidType;
            /// Type that was expected.
            Smp::SimpleTypeKind expectedType;

            InvalidParameterType(
                String8 _operationName,
                String8 _parameterName,
                Smp::SimpleTypeKind _invalidType,
                Smp::SimpleTypeKind _expectedType) throw() :
            Smp::Exception("InvalidParameterType"),
                operationName(_operationName),
                parameterName(_parameterName),
                invalidType(_invalidType),
                expectedType(_expectedType)
            {
                description = new Char8[strlen(InvalidParameterTypeTemplate) 
                    + strlen(parameterName) 
                    + strlen(operationName) 
                    + strlen(TypeName[expectedType]) 
                    + strlen(TypeName[invalidType])];

                sprintf(description, InvalidParameterTypeTemplate, 
                    parameterName, 
                    operationName, 
                    TypeName[expectedType], 
                    TypeName[invalidType]);
            }
            ~InvalidParameterType() throw() {}

        };

        /// Create request.
        /// Returns a request for the given operation
        /// that describes the parameters and the return value.
        /// @param   operationName Name of operation.
        /// @return  Request object for operation with given name,
        ///               or null if no operation with given name exists.
        /// @remarks The returned request may be null if no 
        ///          operation with given name could be found, or if the 
        ///          method of this name does not support dynamic invocation.
        ///          In its current implementation, dynamic invocation is limited
        ///          to operations using only simple types.
        virtual IRequest* CreateRequest(String8 operationName) = 0;

        /// Dynamic invocation of operation.
        /// Dynamically invokes an operation using a request
        /// that has been created by CreateRequest() and filled
        /// with parameter values by the caller.
        /// @param   request Request object.
        /// @remarks On successful invocation, the return value of the
        ///          operation can be retrieved via GetReturnValue().
        virtual void Invoke(IRequest* request) throw (
            Smp::IDynamicInvocation::InvalidOperationName, 
            Smp::IDynamicInvocation::InvalidParameterCount, 
            Smp::IDynamicInvocation::InvalidParameterType) = 0;

        /// Delete request.
        /// Destroys a request that has been created
        /// with the CreateRequest() method before.
        /// @param   request Request object to delete.
        /// @remarks The request must not be used anymore after
        ///          DeleteRequest() has been called for it.
        virtual void DeleteRequest(IRequest* request) = 0;
    };
}

#endif // SMP_IDYNAMICINVOCATION_H

/***********
 * History *
 ***********/

//$Log: IDynamicInvocation.h,v $
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

