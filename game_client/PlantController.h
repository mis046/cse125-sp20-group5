////////////////////////////////////////
// PlantController.h
// 
// Class that wraps and controls the rendering attributes of Plant
////////////////////////////////////////

#pragma once

#include "RenderController.h"
#include <Plant.hpp>
#include "HealthBar.h" //TODO to be removed
#include "Scene.h"


class PlantController : public RenderController {
public:
    PlantController(uint objectId, Scene* scene) {
        // init node
        rootNode = new SceneNode(NULL, "PlantRootEmptyNode", objectId);
        modelNode = scene->getModel(ModelType::SEED)->createSceneNodes(objectId);
        modelNode->scaler = SEED_SCALER;

        rootNode->addChild(modelNode);
        scene->getGroundNode()->addChild(rootNode); 
        currGrowStage = Plant::GrowStage::SEED;


        // init growth bar
        float barTranslateY = 1.3f;
        float initBarFilledFraction = 1.0f;
        glm::vec3 barColor = glm::vec3(0.1, 0.9, 1.0);
        growthBar = new HealthBar(
            scene->getShaderID(ShaderType::HEALTH_BAR),
            "texture/water_icon.png", 
            barTranslateY, initBarFilledFraction, barColor
        ); 
        barNode = growthBar->createSceneNodes(rootNode->objectId);
        rootNode->addChild(barNode);
    }

    ~PlantController() {
        // TODO: NOT relaly tho ideally we would need this but then we have to refactor particle group and growthbar and sceneNode
        // as of right now we need a new model for each instance which isn't great but eh what can you do?
        delete growthBar;
        delete pGroup;
    }

    void update(GameObject * gameObject, Scene* scene) override {
        update(((Plant*)gameObject), scene);
    }

    void update(Plant* plant, Scene* scene) {
        // Update grown plant model
        if (currGrowStage != plant->growStage) {
            updatePlantModel(plant, scene);
            currGrowStage = plant->growStage;
        }

        // Load new data provided by server
        rootNode->loadGameObject(plant);

        // Update growth bar
        if (plant->growStage == Plant::GrowStage::GROWN) {
            barNode->removeSelf();
        }
        else if (plant->growProgressTime == 0.0f) {
            growthBar->resetBar(0.0f);
        }
        else {
            growthBar->updateBar(plant->growProgressTime / plant->growExpireTime);
        }
    }

    void updatePlantModel(Plant* plant, Scene* scene) {
        // Delete old model node
        delete modelNode;

        // Switch to new model
        uint objectId = plant->objectId;
        switch (plant->growStage) {
            case Plant::GrowStage::SEED:
                modelNode = scene->getModel(ModelType::SEED)->createSceneNodes(objectId);
                modelNode->scaler = SEED_SCALER;
                break;
            case Plant::GrowStage::SAPLING:
                modelNode = scene->getModel(ModelType::SAPLING)->createSceneNodes(objectId);
                modelNode->scaler = SAPLING_SCALER;
                break;
            case Plant::GrowStage::BABY:
                if (plant->plantType == Plant::PlantType::CORN) {
                    modelNode = scene->getModel(ModelType::BABY_CORN)->createSceneNodes(objectId);
                    modelNode->scaler = BABY_CORN_SCALER;
                }
                break;
            case Plant::GrowStage::GROWN:
                if (plant->plantType == Plant::PlantType::CORN) {
                    modelNode = scene->getModel(ModelType::CORN)->createSceneNodes(objectId);
                    modelNode->scaler = CORN_SCALER;
                    float attackRange = plant->range->rangeDistance;
                    pGroup = scene->getParticleFactory()->getCornAttackParticleGroup(glm::vec3(0, 0, 0), attackRange);
                    particleNode = pGroup->createSceneNodes(plant->objectId);
                    particleNode->position = glm::vec3(0, 2, 0); // TODO MAKE CONSTANT
                    rootNode->addChild(particleNode);
                }
                break;
        }
        rootNode->addChild(modelNode);
    }
    
private:
    HealthBar* growthBar;

    SceneNode* barNode;
    SceneNode* particleNode;
    ParticleGroup* pGroup; 
    Plant::GrowStage currGrowStage;
};