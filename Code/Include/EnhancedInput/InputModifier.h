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

namespace EnhancedInput
{
    class InputModifier
    {
    public:
        AZ_TYPE_INFO(InputModifier, "{D0E1F2A3-B4C5-6789-ABCD-EF0123456789}");
        AZ_CLASS_ALLOCATOR(InputModifier, AZ::SystemAllocator);

        InputModifier() = default;
        virtual ~InputModifier() = default;

        virtual InputValue ModifyValue(const InputValue& value) const = 0;

        static void Reflect(AZ::ReflectContext* context);
    };

    class InputModifierDeadZone : public InputModifier
    {
    public:
        AZ_TYPE_INFO(InputModifierDeadZone, "{E1F2A3B4-C5D6-789A-BCDE-F01234567890}");
        AZ_CLASS_ALLOCATOR(InputModifierDeadZone, AZ::SystemAllocator);

        enum class DeadZoneType : AZ::u8
        {
            Axial,
            Radial
        };

        InputModifierDeadZone() = default;
        InputModifierDeadZone(float lowerThreshold, float upperThreshold, DeadZoneType type = DeadZoneType::Axial)
            : m_lowerThreshold(lowerThreshold)
            , m_upperThreshold(upperThreshold)
            , m_type(type)
        {
        }

        InputValue ModifyValue(const InputValue& value) const override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        float m_lowerThreshold = 0.2f;
        float m_upperThreshold = 1.0f;
        DeadZoneType m_type = DeadZoneType::Axial;
    };

    class InputModifierNegate : public InputModifier
    {
    public:
        AZ_TYPE_INFO(InputModifierNegate, "{F2A3B4C5-D6E7-89AB-CDEF-012345678901}");
        AZ_CLASS_ALLOCATOR(InputModifierNegate, AZ::SystemAllocator);

        InputModifierNegate() = default;
        InputModifierNegate(bool negateX, bool negateY, bool negateZ)
            : m_negateX(negateX)
            , m_negateY(negateY)
            , m_negateZ(negateZ)
        {
        }

        InputValue ModifyValue(const InputValue& value) const override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        bool m_negateX = true;
        bool m_negateY = true;
        bool m_negateZ = true;
    };

    class InputModifierScale : public InputModifier
    {
    public:
        AZ_TYPE_INFO(InputModifierScale, "{A3B4C5D6-E7F8-9ABC-DEF0-123456789012}");
        AZ_CLASS_ALLOCATOR(InputModifierScale, AZ::SystemAllocator);

        InputModifierScale() = default;
        explicit InputModifierScale(const AZ::Vector3& scale)
            : m_scale(scale)
        {
        }

        InputValue ModifyValue(const InputValue& value) const override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        AZ::Vector3 m_scale = AZ::Vector3::CreateOne();
    };

    class InputModifierSwizzle : public InputModifier
    {
    public:
        AZ_TYPE_INFO(InputModifierSwizzle, "{B4C5D6E7-F8A9-ABCD-EF01-234567890123}");
        AZ_CLASS_ALLOCATOR(InputModifierSwizzle, AZ::SystemAllocator);

        enum class SwizzleOrder : AZ::u8
        {
            XYZ,
            XZY,
            YXZ,
            YZX,
            ZXY,
            ZYX
        };

        InputModifierSwizzle() = default;
        explicit InputModifierSwizzle(SwizzleOrder order)
            : m_order(order)
        {
        }

        InputValue ModifyValue(const InputValue& value) const override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        SwizzleOrder m_order = SwizzleOrder::XYZ;
    };

    class InputModifierClamp : public InputModifier
    {
    public:
        AZ_TYPE_INFO(InputModifierClamp, "{C5D6E7F8-A9BA-BCDE-F012-345678901234}");
        AZ_CLASS_ALLOCATOR(InputModifierClamp, AZ::SystemAllocator);

        InputModifierClamp() = default;
        InputModifierClamp(float minValue, float maxValue)
            : m_min(minValue)
            , m_max(maxValue)
        {
        }

        InputValue ModifyValue(const InputValue& value) const override;

        static void Reflect(AZ::ReflectContext* context);

    private:
        float m_min = -1.0f;
        float m_max = 1.0f;
    };

    class InputModifierNormalize : public InputModifier
    {
    public:
        AZ_TYPE_INFO(InputModifierNormalize, "{D6E7F8A9-BACB-CDEF-0123-456789012345}");
        AZ_CLASS_ALLOCATOR(InputModifierNormalize, AZ::SystemAllocator);

        InputValue ModifyValue(const InputValue& value) const override;

        static void Reflect(AZ::ReflectContext* context);
    };

    using InputModifierPtr = AZStd::shared_ptr<InputModifier>;

} // namespace EnhancedInput
