#include "Model2D.h"

Model2D::Model2D(const std::vector<Vector2D>& vertices, const std::vector<int> indices) : m_vertices(vertices),	m_indices(indices)
{
}

Model2D::Model2D(const std::string path, double dX, double dY)
{
	Loader loader(path);
	if (loader.isLoad())
	{
		m_vertices = loader.vertices();
		m_indices = loader.indices();
		fillMatrix(dX, dY);
	}
}

void Model2D::draw(const HDC& hdc)
{
	POINT* vertices = getPoints();

	Polygon(hdc, vertices, m_vertices.size());
	delete[] vertices;
}

void Model2D::apply(Matrix<> transformMat)
{
	m_modelMatrix = transformMat * m_modelMatrix;
}

pair<double, double> Model2D::getFirstCoordinate()
{
	return pair<double, double>(m_modelMatrix(0, 0), m_modelMatrix(1, 0));
}

void Model2D::fillMatrix(double dX, double dY)
{
	Matrix<> matrix(3, m_vertices.size());
	for (int i = 0; i < m_indices.size() - 1; i++)
	{
		matrix.setValue(0, i, m_vertices[m_indices[i]].x() + dX);
		matrix.setValue(1, i, m_vertices[m_indices[i]].y() + dY);
		matrix.setValue(2, i, 1);
	}
	m_modelMatrix = matrix;
}

POINT* Model2D::getPoints()
{
	POINT* result = new POINT[m_vertices.size()];
	for (int i = 0; i < m_vertices.size(); i++)
	{
		result[i].x = round(m_modelMatrix(0, i) / m_modelMatrix(2, i));
		result[i].y = round(m_modelMatrix(1, i) / m_modelMatrix(2, i));
	}
	return result;
}
