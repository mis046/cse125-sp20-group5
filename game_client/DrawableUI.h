#pragma once

// TODO: the code for HealthBar and TextUI are not the best implementation 
// as they use static instead of a controller; I would say the best implementation
// is to let derived class of scene node become the controller for different types 
// of model, although requires plenty of refactoring

#include "Core.h"
#include "Constants.h"
#include "SceneNode.h"
#include "Drawable.h"
#include "stb_image.h"

class DrawableUI : public Drawable {
public:
    // Used to postpone drawing to the last for the sake of blending
    static bool isDrawUiMode;

    // Bar rendering var
    bool shouldDisplay = true;
    bool alphaEffectOn = false;
    static constexpr float MAX_ALPHA = 0.8f;
    float alphaValue = MAX_ALPHA;
    float alphaStep = 0.05f;

    virtual ~DrawableUI() {}


    bool canDraw();
    void loadTexture(const char* textureFile, GLuint* textureID);

    SceneNode* createSceneNodes(uint objectId) override;

private:
};
