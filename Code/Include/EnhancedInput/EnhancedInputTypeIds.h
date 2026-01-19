/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

namespace EnhancedInput
{
    // System Component TypeIds
    inline constexpr const char* EnhancedInputSystemComponentTypeId = "{6D41A1B7-068E-457D-A18A-FCA2D6B339C5}";
    inline constexpr const char* EnhancedInputEditorSystemComponentTypeId = "{8B7A971B-D759-4E97-B398-8BB8EA1A678D}";

    // Module derived classes TypeIds
    inline constexpr const char* EnhancedInputModuleInterfaceTypeId = "{23ED20D8-A6C0-4DCA-95FF-F0942AA2052E}";
    inline constexpr const char* EnhancedInputModuleTypeId = "{18915EE8-ABF7-481F-8C45-68CF7183D891}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* EnhancedInputEditorModuleTypeId = EnhancedInputModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* EnhancedInputRequestsTypeId = "{A4D7D254-ACA3-406B-AC8E-B717B8F16979}";
} // namespace EnhancedInput
