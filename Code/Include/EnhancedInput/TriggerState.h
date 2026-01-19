/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/RTTI/RTTI.h>

namespace EnhancedInput
{
    enum class TriggerState : AZ::u8
    {
        None,
        Started,
        Ongoing,
        Triggered,
        Completed,
        Canceled
    };

    enum class TriggerEvent : AZ::u8
    {
        None        = 0,
        Started     = 1 << 0,
        Ongoing     = 1 << 1,
        Triggered   = 1 << 2,
        Completed   = 1 << 3,
        Canceled    = 1 << 4
    };

    inline TriggerEvent operator|(TriggerEvent a, TriggerEvent b)
    {
        return static_cast<TriggerEvent>(static_cast<AZ::u8>(a) | static_cast<AZ::u8>(b));
    }

    inline TriggerEvent operator&(TriggerEvent a, TriggerEvent b)
    {
        return static_cast<TriggerEvent>(static_cast<AZ::u8>(a) & static_cast<AZ::u8>(b));
    }

    inline bool HasFlag(TriggerEvent flags, TriggerEvent flag)
    {
        return (static_cast<AZ::u8>(flags) & static_cast<AZ::u8>(flag)) != 0;
    }

} // namespace EnhancedInput
