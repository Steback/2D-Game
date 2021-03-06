////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_ASSIGNABLEFROMTYPE_H__
#define __CORE_ASSIGNABLEFROMTYPE_H__


#include <NsCore/Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{

class Type;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metadata used to specify an assignable type
////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_CORE_KERNEL_API AssignableFromType: public TypeMetaData
{
    AssignableFromType(const Type* type_);

    const Type* type;

    NS_DECLARE_REFLECTION(AssignableFromType, TypeMetaData)
};

}

#endif
