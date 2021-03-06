////////////////////////////////////////
// RenderController.hpp
// 
// Class that wraps the scene node and model of a game object
////////////////////////////////////////

#pragma once

#include "Core.h"
#include "Constants.h"
#include "SceneNode.h"
#include "Drawable.h"
#include "DrawableUI.h"
#include "HealthBar.h"
#include "TextUI.h"


class Scene; //  put declaration here to sidestep header issues

struct z_compare {
    bool operator() (const SceneNode* lhs, const SceneNode* rhs) const {
        return lhs->transform[3].z < rhs->transform[3].z;
    }
};

struct HealthBarSetting {
    const char* iconFile;
    float translateY;
    float initFilledFraction;
    glm::vec3 barColor;

    HealthBarSetting(const char* iconFile, float translateY, float initFilledFraction, glm::vec3 barColor)
        : iconFile(iconFile), translateY(translateY), initFilledFraction(initFilledFraction), barColor(barColor) {}
};

class RenderController {
public:
    RenderController() {}

    virtual ~RenderController() {
    }

    SceneNode* rootNode;
    SceneNode* modelNode;


    virtual void update(GameObject* gameObject, Scene* scene) {};

    /* Helpers */

    // Init the healthbar object and add its node to the scene graph and the uiNode vector
    std::pair<HealthBar*, SceneNode*> createHealthBar(HealthBarSetting barSetting, Scene* scene) {
        HealthBar* barObject = new HealthBar(
            scene->getShaderID(ShaderType::HEALTH_BAR),
            barSetting.iconFile, barSetting.translateY, barSetting.initFilledFraction, barSetting.barColor
        );
        SceneNode* barNode = barObject->createSceneNodes(rootNode->objectId);
        this->rootNode->addChild(barNode);
        uiNodes.push_back(barNode);

        return std::pair<HealthBar*, SceneNode*>(barObject, barNode);
    }

    // Init the healthbar object and add its node to the scene graph and the uiNode vector
    std::pair<TextUI*, SceneNode*> createTextUI(FontType font, glm::vec3 color, glm::mat4 model, Scene* scene) {
        TextUI* textObject = new TextUI(scene->getShaderID(ShaderType::TEXT), font, color, "", model);
        SceneNode* textNode = textObject->createSceneNodes(rootNode->objectId);
        rootNode->addChild(textNode);
        uiNodes.push_back(textNode);

        return std::pair<TextUI*, SceneNode*>(textObject, textNode);
    }

    // Always return nullptr which should be assigned to the original barNode class member
    SceneNode* deleteUiNode(SceneNode* uiNode) {
        if (uiNode) {
            uiNodes.erase(std::find(uiNodes.begin(), uiNodes.end(), uiNode));
        }
        return nullptr;
    }

    void updateChat(Player* player, TextUI* chatText) {
        // change the text content, if player object has a valid chatId
        int chatId = player->currChat;
        if (chatId != Player::NO_CHAT) {
            chatText->shouldDisplay = true;
            chatText->alphaValue = chatText->maxAlpha;
            // reset timer
            chatText->maxAlphaStartTime = std::chrono::system_clock::now(); // to allow new text be rendered for awhile
            chatText->reservedText = chatMessages[chatId];
        }

        // Update the effect of textUI: 
        // should be handled by DrawableUI::update() when autoFadeOff turned on
    }

    /* Static */

    static std::vector<SceneNode*> uiNodes;

    static void drawUI(const glm::mat4& viewProjMtx) {
        std::sort(uiNodes.begin(), uiNodes.end(), z_compare());
        DrawableUI::isDrawUiMode = true;
        for (SceneNode* uiNode : uiNodes) {
            uiNode->draw(viewProjMtx);
        }
        DrawableUI::isDrawUiMode = false;
    }

    const static std::string chatMessages[16];

private:
};

std::vector<SceneNode*> RenderController::uiNodes;

const std::string RenderController::chatMessages[16] = {
    "You suck", "Water", "Shovel", "Pesticide", "Fertilizer", // 0~4
    "Come on", "Help", "I'm so dead", "Thanks", "Good job", // 5~9
    "Thank you for the quarter!", // secret
    "Thank you for the quarter!", // alex Zhu
    "Thank you for the quarter!", // arun sUgUmar
    "Thank you for the quarter!", // Joyaan
    "Thank you for the quarter!", // Mingqi
    "Thank you for the quarter!" // Yang
};