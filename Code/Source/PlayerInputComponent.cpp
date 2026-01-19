/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <EnhancedInput/PlayerInputComponent.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace EnhancedInput
{
    class PlayerInputNotificationBusHandler
        : public PlayerInputNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(PlayerInputNotificationBusHandler, "{BACBDCDE-F012-3456-789A-BCDEF0123456}", AZ::SystemAllocator,
            OnInputActionTriggered,
            OnInputActionStarted,
            OnInputActionOngoing,
            OnInputActionCompleted,
            OnInputActionCanceled);

        void OnInputActionTriggered(const AZStd::string& actionName, const InputActionInstance& instance) override
        {
            Call(FN_OnInputActionTriggered, actionName, instance);
        }

        void OnInputActionStarted(const AZStd::string& actionName, const InputActionInstance& instance) override
        {
            Call(FN_OnInputActionStarted, actionName, instance);
        }

        void OnInputActionOngoing(const AZStd::string& actionName, const InputActionInstance& instance) override
        {
            Call(FN_OnInputActionOngoing, actionName, instance);
        }

        void OnInputActionCompleted(const AZStd::string& actionName, const InputActionInstance& instance) override
        {
            Call(FN_OnInputActionCompleted, actionName, instance);
        }

        void OnInputActionCanceled(const AZStd::string& actionName, const InputActionInstance& instance) override
        {
            Call(FN_OnInputActionCanceled, actionName, instance);
        }
    };

    void PlayerInputComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<PlayerInputComponent, AZ::Component>()
                ->Version(1)
                ->Field("SubscribedActions", &PlayerInputComponent::m_subscribedActions);

            if (auto editContext = serializeContext->GetEditContext())
            {
                editContext->Class<PlayerInputComponent>("Player Input", "Receives enhanced input action events for this entity")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "Enhanced Input")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Editor/Icons/Components/PlayerInput.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ->DataElement(AZ::Edit::UIHandlers::Default, &PlayerInputComponent::m_subscribedActions, "Subscribed Actions", "List of action names to listen for");
            }
        }

        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<PlayerInputComponent>("PlayerInputComponent")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Method("SubscribeToAction", &PlayerInputComponent::SubscribeToAction)
                ->Method("UnsubscribeFromAction", &PlayerInputComponent::UnsubscribeFromAction)
                ->Method("UnsubscribeFromAllActions", &PlayerInputComponent::UnsubscribeFromAllActions);

            behaviorContext->EBus<PlayerInputNotificationBus>("PlayerInputNotificationBus")
                ->Attribute(AZ::Script::Attributes::Category, "EnhancedInput")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Handler<PlayerInputNotificationBusHandler>()
                ->Event("OnInputActionTriggered", &PlayerInputNotifications::OnInputActionTriggered)
                ->Event("OnInputActionStarted", &PlayerInputNotifications::OnInputActionStarted)
                ->Event("OnInputActionOngoing", &PlayerInputNotifications::OnInputActionOngoing)
                ->Event("OnInputActionCompleted", &PlayerInputNotifications::OnInputActionCompleted)
                ->Event("OnInputActionCanceled", &PlayerInputNotifications::OnInputActionCanceled);
        }
    }

    void PlayerInputComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("PlayerInputService"));
    }

    void PlayerInputComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("PlayerInputService"));
    }

    void PlayerInputComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void PlayerInputComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    void PlayerInputComponent::Init()
    {
    }

    void PlayerInputComponent::Activate()
    {
        for (const auto& actionName : m_subscribedActions)
        {
            EnhancedInputNotificationBus::MultiHandler::BusConnect(actionName);
        }
    }

    void PlayerInputComponent::Deactivate()
    {
        EnhancedInputNotificationBus::MultiHandler::BusDisconnect();
    }

    void PlayerInputComponent::SubscribeToAction(const AZStd::string& actionName)
    {
        if (AZStd::find(m_subscribedActions.begin(), m_subscribedActions.end(), actionName) == m_subscribedActions.end())
        {
            m_subscribedActions.push_back(actionName);
            EnhancedInputNotificationBus::MultiHandler::BusConnect(actionName);
        }
    }

    void PlayerInputComponent::UnsubscribeFromAction(const AZStd::string& actionName)
    {
        auto it = AZStd::find(m_subscribedActions.begin(), m_subscribedActions.end(), actionName);
        if (it != m_subscribedActions.end())
        {
            EnhancedInputNotificationBus::MultiHandler::BusDisconnect(actionName);
            m_subscribedActions.erase(it);
        }
    }

    void PlayerInputComponent::UnsubscribeFromAllActions()
    {
        EnhancedInputNotificationBus::MultiHandler::BusDisconnect();
        m_subscribedActions.clear();
    }

    void PlayerInputComponent::OnActionTriggered(const InputActionInstance& instance)
    {
        if (instance.m_action)
        {
            PlayerInputNotificationBus::Event(GetEntityId(), &PlayerInputNotifications::OnInputActionTriggered, instance.m_action->GetName(), instance);
        }
    }

    void PlayerInputComponent::OnActionStarted(const InputActionInstance& instance)
    {
        if (instance.m_action)
        {
            PlayerInputNotificationBus::Event(GetEntityId(), &PlayerInputNotifications::OnInputActionStarted, instance.m_action->GetName(), instance);
        }
    }

    void PlayerInputComponent::OnActionOngoing(const InputActionInstance& instance)
    {
        if (instance.m_action)
        {
            PlayerInputNotificationBus::Event(GetEntityId(), &PlayerInputNotifications::OnInputActionOngoing, instance.m_action->GetName(), instance);
        }
    }

    void PlayerInputComponent::OnActionCompleted(const InputActionInstance& instance)
    {
        if (instance.m_action)
        {
            PlayerInputNotificationBus::Event(GetEntityId(), &PlayerInputNotifications::OnInputActionCompleted, instance.m_action->GetName(), instance);
        }
    }

    void PlayerInputComponent::OnActionCanceled(const InputActionInstance& instance)
    {
        if (instance.m_action)
        {
            PlayerInputNotificationBus::Event(GetEntityId(), &PlayerInputNotifications::OnInputActionCanceled, instance.m_action->GetName(), instance);
        }
    }

} // namespace EnhancedInput
