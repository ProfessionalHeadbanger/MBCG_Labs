#pragma once
#include <vector>
#include <Windows.h>
#include "Vector2D.h"
#include "Matrix.h"
#include "Loader.h"

class Model2D
{
private:
	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;

	Matrix<> m_modelMatrix;
	void fillMatrix(double dX, double dY);
	POINT* getPoints();

public:
	Model2D() = default;
	Model2D(const std::vector<Vector2D> &vertices, const std::vector<int> indices);
	Model2D(const std::string path, double dX, double dY);

	void draw(const HDC& hdc);
	void apply(Matrix<> transformMatrix);
	pair<double, double> getFirstCoordinate();
};
