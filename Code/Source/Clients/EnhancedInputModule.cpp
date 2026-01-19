/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <EnhancedInput/EnhancedInputTypeIds.h>
#include <EnhancedInputModuleInterface.h>
#include "EnhancedInputSystemComponent.h"

namespace EnhancedInput
{
    class EnhancedInputModule
        : public EnhancedInputModuleInterface
    {
    public:
        AZ_RTTI(EnhancedInputModule, EnhancedInputModuleTypeId, EnhancedInputModuleInterface);
        AZ_CLASS_ALLOCATOR(EnhancedInputModule, AZ::SystemAllocator);
    };
}// namespace EnhancedInput

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), EnhancedInput::EnhancedInputModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_EnhancedInput, EnhancedInput::EnhancedInputModule)
#endif
