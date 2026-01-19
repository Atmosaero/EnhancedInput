/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <EnhancedInput/InputMappingContext.h>
#include <AzCore/Serialization/EditContext.h>

namespace EnhancedInput
{
    void InputActionBinding::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputActionBinding>()
                ->Version(1)
                ->Field("ActionName", &InputActionBinding::m_actionName)
                ->Field("InputChannelId", &InputActionBinding::m_inputChannelId)
                ->Field("Modifiers", &InputActionBinding::m_modifiers)
                ->Field("Triggers", &InputActionBinding::m_triggers);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputActionBinding>("Input Action Binding", "Maps an input channel to an action")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputActionBinding::m_actionName, "Action Name", "Name of the action to trigger")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputActionBinding::m_inputChannelId, "Input Channel", "The input channel to bind")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputActionBinding::m_modifiers, "Modifiers", "Value modifiers applied in order")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputActionBinding::m_triggers, "Triggers", "Trigger conditions");
            }
        }
    }

    void InputMappingContext::AddBinding(const InputActionBinding& binding)
    {
        m_bindings.push_back(binding);
    }

    void InputMappingContext::RemoveBinding(const AZStd::string& actionName, const AzFramework::InputChannelId& channelId)
    {
        m_bindings.erase(
            AZStd::remove_if(m_bindings.begin(), m_bindings.end(),
                [&](const InputActionBinding& binding)
                {
                    return binding.m_actionName == actionName && binding.m_inputChannelId == channelId;
                }),
            m_bindings.end());
    }

    void InputMappingContext::ClearBindings()
    {
        m_bindings.clear();
    }

    AZStd::vector<const InputActionBinding*> InputMappingContext::GetBindingsForChannel(const AzFramework::InputChannelId& channelId) const
    {
        AZStd::vector<const InputActionBinding*> result;
        for (const auto& binding : m_bindings)
        {
            if (binding.m_inputChannelId == channelId)
            {
                result.push_back(&binding);
            }
        }
        return result;
    }

    AZStd::vector<const InputActionBinding*> InputMappingContext::GetBindingsForAction(const AZStd::string& actionName) const
    {
        AZStd::vector<const InputActionBinding*> result;
        for (const auto& binding : m_bindings)
        {
            if (binding.m_actionName == actionName)
            {
                result.push_back(&binding);
            }
        }
        return result;
    }

    void InputMappingContext::Reflect(AZ::ReflectContext* context)
    {
        InputActionBinding::Reflect(context);

        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<InputMappingContext>()
                ->Version(1)
                ->Field("Name", &InputMappingContext::m_name)
                ->Field("Bindings", &InputMappingContext::m_bindings);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<InputMappingContext>("Input Mapping Context", "A collection of input bindings that can be enabled/disabled together")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputMappingContext::m_name, "Name", "Context name")
                    ->DataElement(AZ::Edit::UIHandlers::Default, &InputMappingContext::m_bindings, "Bindings", "Input bindings in this context");
            }
        }
    }

} // namespace EnhancedInput
