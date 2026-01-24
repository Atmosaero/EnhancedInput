#pragma once

#include <AzCore/RTTI/BehaviorContext.h>
#include <EnhancedInput/EnhancedInputBus.h>

namespace EnhancedInput
{
    struct EnhancedInputNotificationBusHandler final
        : public EnhancedInputNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
        AZ_EBUS_BEHAVIOR_BINDER(
            EnhancedInputNotificationBusHandler,
            "{CBDCDEF0-1234-5678-9ABC-DEF012345678}",
            AZ::SystemAllocator,
            OnActionTriggered,
            OnActionStarted,
            OnActionOngoing,
            OnActionCompleted,
            OnActionCanceled);

        void OnActionTriggered(const InputActionInstance& instance) override
        {
            Call(FN_OnActionTriggered, instance);
        }

        void OnActionStarted(const InputActionInstance& instance) override
        {
            Call(FN_OnActionStarted, instance);
        }

        void OnActionOngoing(const InputActionInstance& instance) override
        {
            Call(FN_OnActionOngoing, instance);
        }

        void OnActionCompleted(const InputActionInstance& instance) override
        {
            Call(FN_OnActionCompleted, instance);
        }

        void OnActionCanceled(const InputActionInstance& instance) override
        {
            Call(FN_OnActionCanceled, instance);
        }
    };
}
