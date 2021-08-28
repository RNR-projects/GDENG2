#pragma once
#include "AUIScreen.h"
class InspectorScreen : public AUIScreen
{
public:
	InspectorScreen();
	~InspectorScreen();

	// Inherited via AUIScreen
	virtual void drawUI() override;

private:
	void updatePosition();
	void updateRotation();
	void updateScale();

	class AGameObject* selectedObject;

	float pos[3];
	float rot[3];
	float scale[3];
};

