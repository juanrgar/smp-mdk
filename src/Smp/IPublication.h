//
// Title:
//      IPublication.h
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
//      This file defines the IPublication interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//
// Note:
//      This file defines the C++ specific publication of models.
//      This includes publication of fields, properties, and operations.
//      Further, publication defines hooks for implementing IManagedModel
//      and IDynamicInvocation, as these can make use of published data.

#ifndef SMP_IPUBLICATION_H
#define SMP_IPUBLICATION_H

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IRequest.h"
#include "Smp/Management/IManagedModel.h"
#include "Smp/Publication/ITypeRegistry.h"
#include "Smp/Publication/IPublishOperation.h"

// ----------------------------------------------------------------------------
// ---------------------------- AccessKind ------------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// The Access Kind of a property defines whether it has getter and setter.
    enum AccessKind
    {
        AK_ReadWrite,        ///< Read/Write access, i.e. getter and setter.
        AK_ReadOnly,         ///< Read  only access, i.e. only getter method.
        AK_WriteOnly         ///< Write only access, i.e. only setter method.
    };
}

namespace Smp
{
    namespace Publication
    {
        static const String8 InvalidFieldTypeTemplate   = "Invalid type used for field: '%s'";
        
        /// Invalid type of Field.
        /// This exception is raised when trying to use publish a field or an array 
        /// of type ST_String8. This simple type is allowed only in operations.
        /// @remarks For fields and arrays the user-defined string types are to be used.
        class InvalidFieldType : public Exception
        {
        public:
            /// Type that is not valid.
            Smp::SimpleTypeKind invalidType;
    
            /// Constructor for new exception.
            InvalidFieldType(Smp::SimpleTypeKind _invalidType) throw() :
                Exception("InvalidFieldType"),
                invalidType(_invalidType)
            {
                description = new Char8[
                    strlen(InvalidFieldTypeTemplate) +
                    strlen(TypeName[invalidType])];
    
                sprintf(description, InvalidFieldTypeTemplate, 
                    TypeName[invalidType]);
            }
            ~InvalidFieldType() throw() {}
        };
    }
}

// ----------------------------------------------------------------------------
// ---------------------------- IPublication ----------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    /// Publication receiver.
    /// Provide functionality to allow publishing fields and operations.
    /// @remarks This interface is platform specific.
    class IPublication
    {
    public:
        /// Virtual destructor.
        /// This is needed to be able to destroy instances
        /// using the actual derived destructor.
        virtual ~IPublication() { }

        // ---------------------------------------------------------------------
        // Type registration mechanism
        // ---------------------------------------------------------------------

        /// Give access to the global type registry.
        /// @return Reference to global type registry.
        /// @remarks The type registry is typically a singleton, and must not
        ///          be null, to allow use of existing types, and registration 
        ///          of new types.
        virtual Publication::ITypeRegistry* GetTypeRegistry() const = 0;

        // ---------------------------------------------------------------------
        // Simple field publication mechanism
        // ---------------------------------------------------------------------
        /// Publish Char8 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            Char8* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish a Bool field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            Bool* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish Int8 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            Int8* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish Int16 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            Int16* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish Int32 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            Int32* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish Int64 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            Int64* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish UInt8 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            UInt8* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish UInt16 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            UInt16* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish UInt32 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            UInt32* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish UInt64 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            UInt64* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish Float32 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            Float32* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        /// Publish Float64 field.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            Float64* address,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) = 0;

        // ---------------------------------------------------------------------
        // Field publication mechanism
        // ---------------------------------------------------------------------
        /// Publish field of any type.
        /// @param name Field name.
        /// @param description Field description.
        /// @param address Field memory address.
        /// @param typeUuid Uuid of field type (determines the size).
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishField(
            String8 name,
            String8 description,
            void* address,
            const Smp::Uuid typeUuid,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false) 
        throw(Smp::Publication::NotRegistered, Smp::Publication::InvalidFieldType) = 0;

        /// Publish array of simple type.
        /// @param name Array name.
        /// @param description Array description.
        /// @param count Size of array.
        /// @param address Array field memory address.
        /// @param type Array item type.
        /// @param view Show field in model tree.
        /// @param state Include field in store/restore of simulation state.
        /// @param input True if field is an input field, false otherwise.
        /// @param output True if field is an output field, false otherwise.
        virtual void PublishArray(
            String8 name,
            String8 description,
            const Int64 count,
            void* address,
            const SimpleTypeKind type,
            const Bool view = true,
            const Bool state = true,
            const Bool input = false,
            const Bool output = false)
        throw(Smp::Publication::InvalidFieldType) = 0;

        /// Publish array of any type.
        /// @param name Array name.
        /// @param description Array description.
        virtual IPublication* PublishArray(
            String8 name,
            String8 description) = 0;

        /// Publish structure.
        /// @param name Structure name.
        /// @param description Structure description.
        virtual IPublication* PublishStructure(
            String8 name,
            String8 description) = 0;

        // ---------------------------------------------------------------------
        // Operation publication mechanism
        // ---------------------------------------------------------------------

        /// Publish an operation with complex return type.
        /// @param name Operation name.
        /// @param description Operation description.
        /// @param returnTypeUuid Uuid of return type of operation.
        /// @return  Reference to publish parameters against.
        /// @remarks The operation parameters may be published
        ///          against the returned IPublishOperation interface
        ///          after calling PublishOperation().
        virtual Publication::IPublishOperation* PublishOperation(
            String8 name,
            String8 description,
            const Smp::Uuid returnTypeUuid) throw (Smp::Publication::NotRegistered) = 0;

        // ---------------------------------------------------------------------
        // Property publication mechanism
        // ---------------------------------------------------------------------

        /// Publish a property.
        /// @param   name Property name.
        /// @param   description Property description.
        /// @param   typeUuid Uuid of type of Property.
        /// @param   accessKind Access kind of Property
        virtual void PublishProperty(
            String8 name,
            String8 description,
            const Smp::Uuid typeUuid,
            const AccessKind accessKind) throw (Smp::Publication::NotRegistered) = 0;

        // ---------------------------------------------------------------------
        // Managed Model method implementation
        // ---------------------------------------------------------------------

        /// Get the value of a field which is typed by a system type.
        /// @param   fullName Fully qualified field name.
        /// @return  Field value.
        /// @remarks This method can only be used to get values of simple
        ///          fields. For setting values of structured fields,
        ///          this method may be called multiply, e.g. specifying
        ///          "Position.x" to get the x component of a position.
        ///          For arrays of simple type, use GetArrayValue.
        virtual AnySimple GetFieldValue(String8 fullName) = 0;

        /// Set the value of a field which is typed by a system type.
        /// @param   fullName Fully qualified field name.
        /// @param   value Field value.
        /// @remarks This method can only be used to set values of simple
        ///          fields. For setting values of structured fields,
        ///          this method may be called multiply, e.g. specifying
        ///          "Position.x" to set the x component of a position.
        ///          For arrays of simple type, use SetArrayValue.
        virtual void SetFieldValue(String8 fullName, AnySimple value) = 0;

        /// Get the value of an array field which is typed by a system type.
        /// @param   fullName Fully qualified array field name.
        /// @param   values Array of field values.
        /// @param   length Length of array for safety checks.
        /// @remarks This method can only be used to get values of arrays of
        ///          simple type. These may be nested in a structure or array.
        virtual void GetArrayValue(
            String8 fullName,
            const AnySimpleArray values,
            const Int32 length) throw (
            Smp::Management::IManagedModel::InvalidFieldName, 
            Smp::Management::IManagedModel::InvalidArraySize) = 0;

        /// Set the value of an array field which is typed by a system type.
        /// @param   fullName Fully qualified array field name.
        /// @param   values Array of field values.
        /// @param   length Length of array for safety checks.
        /// @remarks This method can only be used to set values of arrays of
        ///          system type. For setting values of structured or array
        ///          fields, this method may be called multiply, e.g. by
        ///          specifying a field name "MyField.Position[2]"
        ///          in order to access an array item of a structure.
        virtual void SetArrayValue(
            String8 fullName, 
            const AnySimpleArray values, 
            const Int32 length) throw (
            Smp::Management::IManagedModel::InvalidFieldName, 
            Smp::Management::IManagedModel::InvalidArraySize, 
            Smp::Management::IManagedModel::InvalidArrayValue) = 0;

        // ---------------------------------------------------------------------
        // Dynamic Invocation method implementation
        // ---------------------------------------------------------------------
        /// Create request object.
        /// Returns a request object for the given operation
        /// that describes the parameters and the return value.
        /// @param   operationName Name of operation.
        /// @return  Request object for operation.
        /// @remarks Request object may be undefined if no operation with
        ///             given name could be found.
        virtual IRequest* CreateRequest(String8 operationName) = 0;

        /// Delete request object.
        /// Destroys a request object that has been created
        /// with the CreateRequest() method before.
        /// @param   request Request object to delete.
        /// @remarks The request object must not be used anymore after
        ///             DeleteRequest has been called for it.
        virtual void DeleteRequest(IRequest* request) = 0;
    };
}

#endif // SMP_IPUBLICATION_H

/***********
 * History *
 ***********/

//$Log: IPublication.h,v $
//Revision 1.4  2006/12/21 16:09:22  nin
//InvalidFieldType exception added.
//InvalidFieldType exception thrown by PublishField() and PublishArray().
//
//Revision 1.2  2006/09/27 11:43:48  nin
//SMP2 v1.2
// 

