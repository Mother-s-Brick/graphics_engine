﻿#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "application/Color.h"

#include "engine/SceneObject.h"
#include "engine/PhysicsBody.h"
#include "engine/Scene.h"
#include "engine/Renderable.h"
#include "engine/Window.h"
#include "engine/FirstPersonController.h"

#include "graphics/MeshLoader.h"
#include "misc/utils.h"


Scene* setupScene() {
    Scene* scene = new Scene();

    SceneObject* mainCam = new SceneObject("mainCam");
    mainCam->addComponent<Camera>();
    mainCam->addComponent<FirstPersonController>();
    scene->setMainCamera(mainCam->getComponent<Camera>());

    SceneObject* box = new SceneObject("box");
    RenderData* renderData = MeshLoader::loadMesh("assets/box.obj", "assets/caixa.jpg");
    box->addComponent<Renderable>(renderData);
    //box->transform.setTranslation({ 0, 0, -10 });
    box->transform.setScale(20);

    mainCam->transform.setTranslation({ 0, 0, 0 });

    scene->addRootObject(box);
    scene->addRootObject(mainCam);
    return scene;
}

int main() {

    Window* window = new Window();
    window->show();

    Scene* scene = setupScene();
    glm::vec3 backgroundColor = Color::CYAN;

    scene->start();
    while (!window->shouldClose()) {
        window->pollEvents();
        Window::clearBuffers();
        Window::setColor(backgroundColor);

        Component::deltaTime = Window::getDeltaTime();
        scene->update();
        scene->render();

        window->display();
    }

    window->close();
    Window::terminate();

    std::cout << "Terminating..." << std::endl;
    return EXIT_SUCCESS;
}
