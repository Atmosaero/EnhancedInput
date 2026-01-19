/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "EnhancedInputModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <EnhancedInput/EnhancedInputTypeIds.h>

#include <Clients/EnhancedInputSystemComponent.h>
#include <EnhancedInput/PlayerInputComponent.h>

namespace EnhancedInput
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(EnhancedInputModuleInterface,
        "EnhancedInputModuleInterface", EnhancedInputModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(EnhancedInputModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(EnhancedInputModuleInterface, AZ::SystemAllocator);

    EnhancedInputModuleInterface::EnhancedInputModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            EnhancedInputSystemComponent::CreateDescriptor(),
            PlayerInputComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList EnhancedInputModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<EnhancedInputSystemComponent>(),
        };
    }
} // namespace EnhancedInput
