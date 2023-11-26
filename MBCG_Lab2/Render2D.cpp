#include "Render2D.h"

Render2D::~Render2D()
{
	for (const auto& object : m_objects)
	{
		if (object)
		{
			delete object;
		}
	}
}

void Render2D::draw(const HDC& hdc)
{
	HBRUSH oldBrush = NULL;
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (i == selectIndex)
		{
			oldBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
		}

		if (m_objects[i])
		{
			m_objects[i]->draw(hdc);
		}

		if (i == selectIndex)
		{
			DeleteObject(SelectObject(hdc, oldBrush));
		}
	}
}

void Render2D::addObject(Model2D* model)
{
	m_objects.push_back(model);
}

Model2D* Render2D::getObject()
{
	return m_objects[selectIndex];
}

void Render2D::nextObject()
{
	selectIndex = (selectIndex + 1) % m_objects.size();
}