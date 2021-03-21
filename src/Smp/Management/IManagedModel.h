//
// Title:
//      IManagedModel.h
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
//      This file defines the IManagedModel interface.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef SMP_MANAGEMENT_IMANAGEDMODEL_H
#define SMP_MANAGEMENT_IMANAGEDMODEL_H

// ----------------------------------------------------------------------------
// --------------------------- Include Header Files ---------------------------
// ----------------------------------------------------------------------------

#include "Smp/IModel.h"
#include "Smp/Management/IManagedComponent.h"
#include <sstream>

// ----------------------------------------------------------------------------
// --------------------------- IManagedModel interface ------------------------
// ----------------------------------------------------------------------------

namespace Smp
{
    namespace Management 
    {
        static const Smp::String8 InvalidFieldNameTemplate  = "Invalid field name '%s'";
        static const Smp::String8 InvalidFieldValueTemplate = "Invalid value for field '%s'";
        static const Smp::String8 InvalidArrayValueTemplate = "Invalid value for array '%s'";

        /// Managed model.
        /// A managed model additionally allows getting and setting field values.
        class IManagedModel :
            public virtual IManagedComponent,
            public virtual IModel
        {
        public:
            /// Invalid field name.
            /// This exception is raised when an invalid field name is specified.
            class InvalidFieldName : public Smp::Exception
            {
            public:
                /// Fully qualified field name that is invalid.
                String8 fieldName;

                InvalidFieldName(
                    String8 _fieldName) throw() :
                Smp::Exception("InvalidFieldName"),
                    fieldName(_fieldName)
                {
                    description = new Char8[strlen(InvalidFieldNameTemplate) 
                        + strlen(fieldName)];

                    sprintf(description, InvalidFieldNameTemplate, 
                        fieldName);
                }
                ~InvalidFieldName() throw() {}
            };

            /// Invalid value for field.
            /// This exception is raised when trying to assign an illegal value to a
            /// field.
            class InvalidFieldValue : public Smp::Exception
            {
            public:
                /// Fully qualified field name the value was assigned to.
                String8 fieldName; 
                /// Value that was passed as new field value.
                const AnySimple invalidValue;

                InvalidFieldValue(
                    String8 _fieldName,
                    const AnySimple _invalidValue) throw() :
                Smp::Exception("InvalidFieldValue"),
                    fieldName(_fieldName),
                    invalidValue(_invalidValue)
                {
                    description = new Char8[strlen(InvalidFieldValueTemplate) 
                        + strlen(fieldName)];

                    sprintf(description, InvalidFieldValueTemplate, 
                        fieldName);
                }
                
                virtual ~InvalidFieldValue() throw ( )
                {
                }                
            };

            /// Invalid array size.
            /// This exception is raised when an invalid array size 
            /// is specified.
            class InvalidArraySize : public Smp::Exception
            {
            public:
                /// Name of field that has been accessed.
                String8 fieldName;
                /// Invalid array size.
                const Int64 givenSize;
                /// Real array size.
                const Int64 arraySize;

                InvalidArraySize(
                    String8 _fieldName,
                    const Int64 _givenSize,
                    const Int64 _arraySize) throw() :
                Smp::Exception("InvalidArraySize"),
                    fieldName(_fieldName),
                    givenSize(_givenSize),
                    arraySize(_arraySize)
                {
                    std::stringstream ss;
                    ss  << "Invalid size for array '"
                        << fieldName
                        << "': Expected "
                        << arraySize
                        << ", but found "
                        << givenSize;
                    
                    description = new Char8[ss.str().length()+1];
                    
                    strcpy(description, ss.str().c_str());
                }

                ~InvalidArraySize() throw() {}
            };

            /// Invalid value for field.
            /// This exception is raised when trying to assign an illegal value to a
            /// field.
            class InvalidArrayValue : public Smp::Exception
            {
            public:
                /// Fully qualified field name the value was assigned to.
                String8 fieldName; 
                /// Value that was passed as new field value.
                const AnySimpleArray invalidValue;

                InvalidArrayValue(
                    String8 _fieldName,
                    const AnySimpleArray _invalidValue) throw() :
                Smp::Exception("InvalidArrayValue"),
                    fieldName(_fieldName),
                    invalidValue(_invalidValue)
                {
                    description = new Char8[strlen(InvalidArrayValueTemplate) 
                        + strlen(fieldName)];

                    sprintf(description, InvalidArrayValueTemplate, 
                        fieldName);
                }

                ~InvalidArrayValue() throw() {}
            };

            /// Get the value of a field which is typed by a system type.
            /// @param   fullName Fully qualified field name.
            /// @return  Field value.
            /// @remarks This method can only be used to get values of simple
            ///          fields. For setting values of structured fields,
            ///          this method may be called multiply, e.g. specifying
            ///          "Position.x" to get the x component of a position.
            ///          For arrays of simple type, use GetArrayValue.
            virtual AnySimple GetFieldValue(String8 fullName) throw (
                Smp::Management::IManagedModel::InvalidFieldName) = 0;

            /// Set the value of a field which is typed by a system type.
            /// @param   fullName Fully qualified field name.
            /// @param   value Field value.
            /// @remarks This method can only be used to set values of simple
            ///          fields. For setting values of structured fields,
            ///          this method may be called multiply, e.g. specifying
            ///          "Position.x" to set the x component of a position.
            ///          For arrays of simple type, use SetArrayValue.
            virtual void SetFieldValue(String8 fullName, const AnySimple value) throw (
                Smp::Management::IManagedModel::InvalidFieldName, 
                Smp::Management::IManagedModel::InvalidFieldValue) = 0;

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
        };
    }
}

#endif // SMP_MANAGEMENT_IMANAGEDMODEL_H

/***********
 * History *
 ***********/

//$Log: IManagedModel.h,v $
//Revision 1.4  2006/12/21 16:03:31  nin
//Added missing destructor with throw statement to satisfy GCC.
//
//Revision 1.3  2006/11/20 13:58:59  nin
//Some message formatting reworked to be portable and without compile-time warnings.
//
//Revision 1.2  2006/09/27 11:44:22  nin
//SMP2 v1.2
// 

