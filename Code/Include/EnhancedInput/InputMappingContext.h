/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/RTTI/RTTI.h>
#include <AzCore/Memory/Memory.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/std/containers/unordered_map.h>
#include <AzCore/std/string/string.h>
#include <AzCore/std/smart_ptr/shared_ptr.h>
#include <AzFramework/Input/Channels/InputChannelId.h>
#include <EnhancedInput/InputAction.h>
#include <EnhancedInput/InputTrigger.h>
#include <EnhancedInput/InputModifier.h>

namespace EnhancedInput
{
    struct InputActionBinding
    {
        AZ_TYPE_INFO(InputActionBinding, "{E7F8A9BA-CBDC-DEF0-1234-567890123456}");
        AZ_CLASS_ALLOCATOR(InputActionBinding, AZ::SystemAllocator);

        AZStd::string m_actionName;
        AzFramework::InputChannelId m_inputChannelId;
        AZStd::vector<InputModifierPtr> m_modifiers;
        AZStd::vector<InputTriggerPtr> m_triggers;

        static void Reflect(AZ::ReflectContext* context);
    };

    class InputMappingContext
    {
    public:
        AZ_TYPE_INFO(InputMappingContext, "{F8A9BACB-DCDE-EF01-2345-678901234567}");
        AZ_CLASS_ALLOCATOR(InputMappingContext, AZ::SystemAllocator);

        InputMappingContext() = default;
        explicit InputMappingContext(const AZStd::string& name)
            : m_name(name)
        {
        }

        const AZStd::string& GetName() const { return m_name; }
        void SetName(const AZStd::string& name) { m_name = name; }

        void AddBinding(const InputActionBinding& binding);
        void RemoveBinding(const AZStd::string& actionName, const AzFramework::InputChannelId& channelId);
        void ClearBindings();

        const AZStd::vector<InputActionBinding>& GetBindings() const { return m_bindings; }
        AZStd::vector<InputActionBinding>& GetBindings() { return m_bindings; }

        AZStd::vector<const InputActionBinding*> GetBindingsForChannel(const AzFramework::InputChannelId& channelId) const;
        AZStd::vector<const InputActionBinding*> GetBindingsForAction(const AZStd::string& actionName) const;

        static void Reflect(AZ::ReflectContext* context);

    private:
        AZStd::string m_name;
        AZStd::vector<InputActionBinding> m_bindings;
    };

    struct ActiveMappingContext
    {
        AZStd::shared_ptr<InputMappingContext> m_context;
        int m_priority = 0;

        bool operator<(const ActiveMappingContext& other) const
        {
            return m_priority > other.m_priority;
        }
    };

    using InputMappingContextPtr = AZStd::shared_ptr<InputMappingContext>;

} // namespace EnhancedInput
