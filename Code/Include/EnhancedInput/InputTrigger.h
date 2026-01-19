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
#include <AzCore/std/smart_ptr/shared_ptr.h>
#include <EnhancedInput/InputValue.h>
#include <EnhancedInput/TriggerState.h>

namespace EnhancedInput
{
    class InputTrigger
    {
    public:
        AZ_TYPE_INFO(InputTrigger, "{C3D4E5F6-A7B8-9012-3456-789ABCDEF012}");
        AZ_CLASS_ALLOCATOR(InputTrigger, AZ::SystemAllocator);

        InputTrigger() = default;
        virtual ~InputTrigger() = default;

        virtual TriggerState UpdateState(const InputValue& value, float deltaTime) = 0;
        virtual void Reset() { m_state = TriggerState::None; }

        TriggerState GetState() const { return m_state; }

        static void Reflect(AZ::ReflectContext* context);

    protected:
        TriggerState m_state = TriggerState::None;
        float m_elapsedTime = 0.0f;
    };

    class InputTriggerPressed : public InputTrigger
    {
    public:
        AZ_TYPE_INFO(InputTriggerPressed, "{D4E5F6A7-B8C9-0123-4567-89ABCDEF0123}");
        AZ_CLASS_ALLOCATOR(InputTriggerPressed, AZ::SystemAllocator);

        TriggerState UpdateState(const InputValue& value, float deltaTime) override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        bool m_wasPressed = false;
    };

    class InputTriggerReleased : public InputTrigger
    {
    public:
        AZ_TYPE_INFO(InputTriggerReleased, "{E5F6A7B8-C9D0-1234-5678-9ABCDEF01234}");
        AZ_CLASS_ALLOCATOR(InputTriggerReleased, AZ::SystemAllocator);

        TriggerState UpdateState(const InputValue& value, float deltaTime) override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        bool m_wasPressed = false;
    };

    class InputTriggerDown : public InputTrigger
    {
    public:
        AZ_TYPE_INFO(InputTriggerDown, "{F6A7B8C9-D0E1-2345-6789-ABCDEF012345}");
        AZ_CLASS_ALLOCATOR(InputTriggerDown, AZ::SystemAllocator);

        TriggerState UpdateState(const InputValue& value, float deltaTime) override;

        static void Reflect(AZ::ReflectContext* context);
    };

    class InputTriggerHold : public InputTrigger
    {
    public:
        AZ_TYPE_INFO(InputTriggerHold, "{A7B8C9D0-E1F2-3456-789A-BCDEF0123456}");
        AZ_CLASS_ALLOCATOR(InputTriggerHold, AZ::SystemAllocator);

        InputTriggerHold() = default;
        explicit InputTriggerHold(float holdTime, bool triggerOnce = false)
            : m_holdTime(holdTime)
            , m_triggerOnce(triggerOnce)
        {
        }

        TriggerState UpdateState(const InputValue& value, float deltaTime) override;
        void Reset() override;

        float GetHoldTime() const { return m_holdTime; }
        void SetHoldTime(float time) { m_holdTime = time; }

        static void Reflect(AZ::ReflectContext* context);

    private:
        float m_holdTime = 0.5f;
        bool m_triggerOnce = false;
        bool m_hasTriggered = false;
    };

    class InputTriggerTap : public InputTrigger
    {
    public:
        AZ_TYPE_INFO(InputTriggerTap, "{B8C9D0E1-F2A3-4567-89AB-CDEF01234567}");
        AZ_CLASS_ALLOCATOR(InputTriggerTap, AZ::SystemAllocator);

        InputTriggerTap() = default;
        explicit InputTriggerTap(float maxTapTime)
            : m_maxTapTime(maxTapTime)
        {
        }

        TriggerState UpdateState(const InputValue& value, float deltaTime) override;
        void Reset() override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        float m_maxTapTime = 0.2f;
        bool m_wasPressed = false;
    };

    class InputTriggerPulse : public InputTrigger
    {
    public:
        AZ_TYPE_INFO(InputTriggerPulse, "{C9D0E1F2-A3B4-5678-9ABC-DEF012345678}");
        AZ_CLASS_ALLOCATOR(InputTriggerPulse, AZ::SystemAllocator);

        InputTriggerPulse() = default;
        explicit InputTriggerPulse(float interval, bool triggerOnStart = true)
            : m_interval(interval)
            , m_triggerOnStart(triggerOnStart)
        {
        }

        TriggerState UpdateState(const InputValue& value, float deltaTime) override;
        void Reset() override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        float m_interval = 0.1f;
        bool m_triggerOnStart = true;
        float m_timeSinceLastTrigger = 0.0f;
        bool m_isFirstTrigger = true;
    };

    using InputTriggerPtr = AZStd::shared_ptr<InputTrigger>;

} // namespace EnhancedInput
