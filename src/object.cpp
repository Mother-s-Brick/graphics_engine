#include "object.h"
#include "utils.h"

#define DEFAULT_PRIMITIVE_Z 1


SceneObject* object::getHelicopter(float scale) {

    SceneObject* propeller = new SceneObject("propeller", getPropeller());
    SceneObject* smallPropeller = new SceneObject("small_propeller", getPropeller());
    SceneObject* body = new SceneObject("body", getHelicopterBody());

    smallPropeller->transform.translation.x = -1.72f;
    smallPropeller->transform.scale = 0.3f;

    body->appendChild(propeller);
    body->appendChild(smallPropeller);
    body->transform.scale = scale;
   
    propeller->physicsBody.angularVelocity = 0.005f;
    smallPropeller->physicsBody.angularVelocity = -0.005f;

    body->physicsBody.forwardVelocity= 0.0001f;
    body->physicsBody.angularVelocity= 0.0001f;

	return body;
}

SceneObject* object::getSpinner() {
    SceneObject* prop1 = new SceneObject("p1", getPropeller());
    SceneObject* prop2 = new SceneObject("p2", getPropeller({ 0, 255, 0 }, 0.1f, 3));
    SceneObject* prop3 = new SceneObject("p2", getPropeller());
    SceneObject* shaft = new SceneObject("shaft", { { getPolygon(4, PI / 4, {0,0,0}, {0.7f, 0.05f}), GL_TRIANGLE_FAN, {255, 255, 255} } });

    prop1->transform.translation.x = 0.5f;
    prop2->transform.translation.x = -0.5f;
    prop3->transform.translation.x = 1;
    prop1->transform.scale = 0.5;
    prop2->transform.scale = 0.5;
    prop3->transform.scale = 0.5;

    shaft->physicsBody.angularVelocity = 0.0001f;
    prop1->physicsBody.angularVelocity = -0.001f;
    prop2->physicsBody.angularVelocity = 0.001f;
    prop3->physicsBody.angularVelocity = 0.001f;

    shaft->appendChild(prop1);
    shaft->appendChild(prop2);
    prop2->appendChild(prop3);

    return shaft;
}

std::vector<Primitive> object::getHelicopterBody() {

    float scale = 1;

    Primitive cockpit(getPolygon(4, PI / 4, { 0, 0 }, { 0.5f, 0.3f }), GL_TRIANGLE_FAN, {0, 0, 255});
    Primitive topGlass(getPolygon(3, 0, { 0.44f, 0 }, { 0.175f, 0.25f }), GL_TRIANGLE_FAN, { 255, 0, 0 });
    Primitive tail(getPolygon(4, PI / 4, { -1, 0 }, { 1, 0.05f }), GL_TRIANGLE_FAN, { 0, 255, 0 });

    return { cockpit, topGlass, tail };
}

std::vector<Primitive> object::getPropeller(Vector3 color, float width, int nPropellers) {
    std::vector<Primitive> prop;

    float stepAngle = 2 * PI / nPropellers;

    for (int i = 0; i < nPropellers; i++) {
        prop.push_back(Primitive(
            getRectangle(width, 1, i * stepAngle),
            GL_TRIANGLE_FAN,
            color
        ));
    }

    return prop;
}

std::vector<Vector3> object::getPolygon(int n, float rotation, Vector3 offset, Vector2 scale) {
    std::vector<Vector3> polygon(n);

    float angleStep = 2 * PI / n;
    for (int i = 0; i < n; i++) {
        polygon[i].x = scale.x * cos(angleStep * i + rotation) + offset.x;
        polygon[i].y = scale.y * sin(angleStep * i + rotation) + offset.y;
        polygon[i].z = DEFAULT_PRIMITIVE_Z;
    }

    return polygon;
}

std::vector<Vector3> object::getRectangle(float width, float length, float rotation) {
    std::vector<Vector3> rectangle(4);

    rectangle[0] = { 0.0f, width / 2, DEFAULT_PRIMITIVE_Z};
    rectangle[1] = { 0.0f, -width / 2, DEFAULT_PRIMITIVE_Z};
    rectangle[2] = { length, -width / 2, DEFAULT_PRIMITIVE_Z};
    rectangle[3] = { length, width / 2, DEFAULT_PRIMITIVE_Z};

    for (auto& vertex : rectangle) {
        float x = vertex.x, y = vertex.y;
        vertex.x = cos(rotation) * x - sin(rotation) * y;
        vertex.y = sin(rotation) * x + cos(rotation) * y;
        vertex.z = DEFAULT_PRIMITIVE_Z;
    }

    return rectangle;
}
