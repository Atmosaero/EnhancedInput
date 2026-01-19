/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Serialization/SerializeContext.h>
#include "EnhancedInputEditorSystemComponent.h"

#include <EnhancedInput/EnhancedInputTypeIds.h>

namespace EnhancedInput
{
    AZ_COMPONENT_IMPL(EnhancedInputEditorSystemComponent, "EnhancedInputEditorSystemComponent",
        EnhancedInputEditorSystemComponentTypeId, BaseSystemComponent);

    void EnhancedInputEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<EnhancedInputEditorSystemComponent, EnhancedInputSystemComponent>()
                ->Version(0);
        }
    }

    EnhancedInputEditorSystemComponent::EnhancedInputEditorSystemComponent() = default;

    EnhancedInputEditorSystemComponent::~EnhancedInputEditorSystemComponent() = default;

    void EnhancedInputEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("EnhancedInputEditorService"));
    }

    void EnhancedInputEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("EnhancedInputEditorService"));
    }

    void EnhancedInputEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void EnhancedInputEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void EnhancedInputEditorSystemComponent::Activate()
    {
        EnhancedInputSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void EnhancedInputEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        EnhancedInputSystemComponent::Deactivate();
    }

} // namespace EnhancedInput
