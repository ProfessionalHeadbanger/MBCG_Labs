#pragma once
#include "Model2D.h"
#include <wtypes.h>
#include "AffineTransform.h"

class Render2D
{
private:
	std::vector<Model2D*> m_objects;
	int selectIndex = 0;

public:
	Render2D() = default;
	~Render2D();

	void draw(const HDC& hdc);
	void addObject(Model2D* model);
	void applyToObject(Matrix<> transformMatrix);
	void nextObject();
};
