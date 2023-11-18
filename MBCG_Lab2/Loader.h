#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Vector2D.h"

class Loader
{
private:
	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;

	std::string m_path;

public:
	Loader(const std::string& path);
	~Loader();

	bool isLoad();
	std::vector<Vector2D> vertices() const;
	std::vector<int> indices() const;
};
