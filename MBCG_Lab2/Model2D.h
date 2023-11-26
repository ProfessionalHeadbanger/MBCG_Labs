#pragma once
#include <vector>
#include <Windows.h>
#include "Vector2D.h"
#include "Matrix.h"
#include "AffineTransform.h"
#include "Loader.h"

# define M_PI 3.14159265358979323846

class Model2D
{
private:
	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;
	double rotation_angle = M_PI / 2;

	Matrix<> m_modelMatrix;
	void fillMatrix(double dX, double dY);
	POINT* getPoints();

public:
	Model2D() = default;
	Model2D(const std::string path, double dX, double dY);

	void draw(const HDC& hdc);

	void Shift(double x, double y);
	void RotateRight();
	void RotateLeft();
	void Scale(double k);
	void ReflectX();
	void ReflectY();
	void ReflectXY();

	void SetRotation(double grad);

	pair<double, double> getFirstCoordinate();
};