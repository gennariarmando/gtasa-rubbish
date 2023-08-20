#include "plugin.h"

#include "Rubbish.h"
plugin::ThiscallEvent<AddressList<0x53EAD3, H_CALL>, PRIORITY_BEFORE, ArgPickNone, void()> movingThingsEvent;

using namespace plugin;

class RubbishSA {
public:
    RubbishSA() {
        plugin::Events::initRwEvent += []() {
            CRubbish::Init();
        };

        plugin::Events::gameProcessEvent += []() {
            CRubbish::Update();
        };

        movingThingsEvent += []() {
            CRubbish::Render();
        };

        plugin::Events::shutdownRwEvent += []() {
            CRubbish::Shutdown();
        };

        plugin::ThiscallEvent <plugin::AddressList<0x6B19F9, plugin::H_CALL>, plugin::PRIORITY_AFTER, plugin::ArgPickN<CAutomobile*, 0>, void(CAutomobile*)> onProcessControl;
        onProcessControl += [](CAutomobile* _this) {
            CRubbish::StirUp(_this);
        };

        patch::RedirectJump(0x7204C0, CRubbish::SetVisibility);
    }
} rubbishSA;
