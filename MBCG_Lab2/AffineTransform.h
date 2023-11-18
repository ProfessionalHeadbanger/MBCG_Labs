#pragma once
#include "Matrix.h"

Matrix<> Translation(double x, double y);

Matrix<> Identity();

Matrix<> Scaling(double kx, double ky);

Matrix<> ReflectOX();

Matrix<> ReflectOY();

Matrix<> Rotation(double grad);

Matrix<> ReflectAll();