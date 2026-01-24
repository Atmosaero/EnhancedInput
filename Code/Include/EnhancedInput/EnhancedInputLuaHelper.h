/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/RTTI/RTTI.h>
#include <AzCore/std/string/string.h>
#include <EnhancedInput/InputMappingContext.h>
#include <EnhancedInput/InputTrigger.h>
#include <EnhancedInput/InputTypes.h>
#include <AzFramework/Input/Channels/InputChannelId.h>
#include <AzCore/std/smart_ptr/shared_ptr.h>
#include <EnhancedInput/EnhancedInputBus.h>

namespace EnhancedInput
{
    class EnhancedInputLuaHelper
    {
    public:
        AZ_TYPE_INFO(EnhancedInputLuaHelper, "{DCDEF012-3456-789A-BCDE-F01234567890}");
        AZ_CLASS_ALLOCATOR(EnhancedInputLuaHelper, AZ::SystemAllocator);

        static InputMappingContextPtr CreateContext(const AZStd::string& name);

        static void RegisterAction(const AZStd::string& actionName, const AZStd::string& valueType);
        static void UnregisterAction(const AZStd::string& actionName);

        static void BindKey(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, const AZStd::string& triggerType = "pressed");
        static void BindAxis(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, float scaleX, float scaleY, float scaleZ);
        
        // Type-specific axis binding
        static void BindAxis1D(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, float scale);
        static void BindAxis2D(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, const AZ::Vector2& scale);
        static void BindAxis3D(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& keyName, const AZ::Vector3& scale);

        static void AddContext(InputMappingContextPtr context, int priority);
        static void RemoveContext(const AZStd::string& contextName);
        static void ClearAllContexts();

        static float GetActionValue(const AZStd::string& actionName);
        static float GetActionValueX(const AZStd::string& actionName);
        static float GetActionValueY(const AZStd::string& actionName);
        static float GetActionValueZ(const AZStd::string& actionName);
        static bool IsActionTriggered(const AZStd::string& actionName);

        static void AddModifierDeadZone(InputMappingContextPtr context, const AZStd::string& actionName, float lowerThreshold, float upperThreshold, const AZStd::string& type);
        static void AddModifierNegate(InputMappingContextPtr context, const AZStd::string& actionName, bool negateX, bool negateY, bool negateZ);
        // Vector-based modifier methods (more convenient)
        static void AddModifierScaleVector(InputMappingContextPtr context, const AZStd::string& actionName, const AZ::Vector3& scale);
        static void AddModifierDeadZoneVector(InputMappingContextPtr context, const AZStd::string& actionName, const AZ::Vector3& lowerThreshold, const AZ::Vector3& upperThreshold, const AZStd::string& type);
        static void AddModifierSwizzle(InputMappingContextPtr context, const AZStd::string& actionName, const AZStd::string& order);
        static void AddModifierClamp(InputMappingContextPtr context, const AZStd::string& actionName, float minValue, float maxValue);
        static void AddModifierNormalize(InputMappingContextPtr context, const AZStd::string& actionName);

        static void Reflect(AZ::ReflectContext* context);

    private:
        static AzFramework::InputChannelId GetInputChannelIdFromName(const AZStd::string& keyName);
        static InputTriggerPtr CreateTriggerFromName(const AZStd::string& triggerType);
    };

} // namespace EnhancedInput
