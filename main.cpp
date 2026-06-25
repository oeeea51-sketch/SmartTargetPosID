#include <Geode/Geode.hpp>
#include <Geode/modify/SetupMovePopup.hpp>

using namespace geode::prelude;

class $modify(MySetupMovePopup, SetupMovePopup) {
public:
    bool init(EffectGameObject* trigger, cocos2d::CCArray* objects) {
        if (!SetupMovePopup::init(trigger, objects))
            return false;

        auto confirmSpr = ButtonSprite::create(
            "Confirm",
            60,
            true,
            "goldFont.fnt",
            "GJ_button_02.png", 
            25.0f,
            0.5f
        );

        auto confirmBtn = CCMenuItemSpriteExtra::create(
            confirmSpr,
            this,
            menu_selector(MySetupMovePopup::onConfirmID)
        );

        confirmBtn->setPosition({0.f, -115.f});

        if (auto menu = this->m_mainLayer->getChildByID("main-menu")) {
            menu->addChild(confirmBtn);
        } else if (auto menu = this->m_buttonMenu) {
            menu->addChild(confirmBtn);
        }

        return true;
    }

    void onConfirmID(cocos2d::CCObject*) {
        auto editorLayer = LevelEditorLayer::get();
        if (!editorLayer) return;

        auto objects = editorLayer->m_objects;
        if (!objects || objects->count() < 2) return;

        GameObject* targetObj = nullptr;
        for (int i = objects->count() - 1; i >= 0; --i) {
            auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
            if (obj && obj != m_gameObject && obj->m_groupCount > 0) {
                targetObj = obj;
                break;
            }
        }

        if (!targetObj) return;

        int groupID = targetObj->getGroupID(0);
        if (groupID <= 0) return;

        if (this->m_targetGroupInput) {
            this->m_targetGroupInput->setString(std::to_string(groupID).c_str());
        }

        if (this->m_gameObject) {
            this->m_gameObject->m_targetGroupID = groupID;
        }
    }
};
