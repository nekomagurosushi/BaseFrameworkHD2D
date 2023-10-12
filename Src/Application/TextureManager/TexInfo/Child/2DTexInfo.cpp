#include "2DTexInfo.h"

void PlaneTexInfo::SetTex()
{
	m_texture->Load(m_path);
}

void PlaneTexInfo::SetData(const json11::Json a_jsonObj)
{

	if (a_jsonObj["Name"].string_value().c_str() != "")SetName(a_jsonObj["Name"].string_value());

	if (a_jsonObj["Path"].string_value().c_str() != "")
	{
		SetPath(a_jsonObj["Path"].string_value());
		SetTex();
	}
	if (a_jsonObj["Rect"].array_items().size() > 0)
	{
		int rectX = a_jsonObj["Rect"].array_items()[0].number_value();
		int rectY = a_jsonObj["Rect"].array_items()[1].number_value();
		SetRectX(rectX);
		SetRectY(rectY);
	}
	if (a_jsonObj["Pos"].array_items().size() > 0)
	{
		Math::Vector2 pos = {
			float(a_jsonObj["Pos"].array_items()[0].number_value()),
			float(a_jsonObj["Pos"].array_items()[1].number_value()) 
		};
		SetPos(pos);
	}
	if (a_jsonObj["Size"].array_items().size() > 0)
	{
		Math::Vector2 size = {
			float(a_jsonObj["Size"].array_items()[0].number_value()),
			float(a_jsonObj["Size"].array_items()[1].number_value())
		};
		SetSize(size);
	}
	if (!a_jsonObj["Color"].array_items().empty())
	{
		Math::Color color = {
			float(a_jsonObj["Color"].array_items()[0].number_value()),
			float(a_jsonObj["Color"].array_items()[1].number_value()),
			float(a_jsonObj["Color"].array_items()[2].number_value()),
			float(a_jsonObj["Color"].array_items()[3].number_value())
		};
		SetColor(color);
	}
}

void PlaneTexInfo::SetPos(Math::Vector2 a_pos)
{
	m_pos= a_pos;
}

void PlaneTexInfo::SetSize(Math::Vector2 a_size)
{
	m_size = a_size;
}

void PlaneTexInfo::SetRectX(const int a_rectX)
{
	m_rectX = a_rectX;
}

void PlaneTexInfo::SetRectY(const int a_rectY)
{
	m_rectY = a_rectY;
}

void PlaneTexInfo::SetColor(Math::Color a_color)
{
	m_color = a_color;
}

shared_ptr<KdTexture> PlaneTexInfo::GetTex()const
{
	return m_texture;
}

Math::Vector2 PlaneTexInfo::GetPos()
{
	return m_pos;
}

Math::Vector2 PlaneTexInfo::GetSize()
{
	return m_size;
}

const int PlaneTexInfo::GetRectX()const
{
	return m_rectX;
}

const int PlaneTexInfo::GetRectY()const
{
	return m_rectY;
}

const Math::Color PlaneTexInfo::GetColor() const
{
	return m_color;
}
