#include "SqPolyInfo.h"

void SqPolyInfo::SetTex()
{
	m_texture->SetMaterial(m_path);
}

void SqPolyInfo::SetData(const json11::Json a_jsonObj)
{
	static int x_split, y_split;
	if (a_jsonObj["Name"].string_value().c_str() != "")SetName(a_jsonObj["Name"].string_value());

	if (a_jsonObj["Path"].string_value().c_str() != "")
	{
		SetPath(a_jsonObj["Path"].string_value());
		SetTex();
	}
	/*switch (a_id)
	{
	case TexInfoId::NAME:
		if (a_string != "")SetName(a_string);
		break;
	case TexInfoId::PATH:
		if (a_string != "")
		{
			SetPath(a_string);
			SetTex();
		}
		break;
	case TexInfoId::RECT_X:
		if (stoi(a_string) != NULL)SetRectX(stoi(a_string));
		break;
	case TexInfoId::RECT_Y:
		if (stoi(a_string) != NULL)SetRectY(stoi(a_string));
		break;
	case TexInfoId::COLI_X:
		if (stoi(a_string) != NULL)SetColiX(stoi(a_string));
		break;
	case TexInfoId::COLI_Y:
		if (stoi(a_string) != NULL)SetColiY(stoi(a_string));
		break;
	case TexInfoId::COLI_Z:
		if (stoi(a_string) != NULL)SetColiZ(stoi(a_string));
		break;
	case TexInfoId::SIZE_X:
		if (stoi(a_string) != NULL)SetSizeX(stof(a_string));
		break;
	case TexInfoId::SIZE_Y:
		if (stoi(a_string) != NULL)SetSizeY(stof(a_string));
		break;
	case TexInfoId::SIZE_Z:
		if (stoi(a_string) != NULL)SetSizeZ(stof(a_string));
		break;
	case TexInfoId::STARTPOINT:
		if (a_string != (""))SetPivot(KdSquarePolygon::PivotType((stoi(a_string))));
		break;
	case TexInfoId::SPLIT_X:
		if (a_string != (""))x_split=stoi(a_string);
		break;
	case TexInfoId::SPLIT_Y:
		if (a_string != (""))y_split = stoi(a_string);
		break;
	}
	if (!x_split || !y_split)return;
	m_texture->SetSplit(x_split,y_split);*/
}

void SqPolyInfo::SetRectX(const int a_rectX)
{
	m_rectX = a_rectX;
}

void SqPolyInfo::SetRectY(const int a_rectY)
{
	m_rectY = a_rectY;
}

void SqPolyInfo::SetColiX(const int a_coliX)
{
	m_collisionX = a_coliX;
}

void SqPolyInfo::SetColiY(const int a_coliY)
{
	m_collisionY = a_coliY;
}

void SqPolyInfo::SetColiZ(const int a_coliZ)
{
	m_collisionZ = a_coliZ;
}

void SqPolyInfo::SetSizeX(const float a_sizeX)
{
	m_sizeX = a_sizeX;
}

void SqPolyInfo::SetSizeY(const float a_sizeY)
{
	m_sizeY = a_sizeY;
}

void SqPolyInfo::SetSizeZ(const float a_sizeZ)
{
	m_sizeZ = a_sizeZ;
}

void SqPolyInfo::SetPivot(const KdSquarePolygon::PivotType a_startPoint)
{
	m_texture->SetPivot(a_startPoint);
}

void SqPolyInfo::SetUVRect(UINT index)
{
	m_texture->SetUVRect(index);
}

shared_ptr<KdSquarePolygon> SqPolyInfo::GetTex()const
{
	return m_texture;
}

const int SqPolyInfo::GetRectX()const
{
	return m_rectX;
}

const int SqPolyInfo::GetRectY()const
{
	return m_rectY;
}

const int SqPolyInfo::GetColiX()const
{
	return m_collisionX;
}

const int SqPolyInfo::GetColiY()const
{
	return m_collisionY;
}

const int SqPolyInfo::GetColiZ()const
{
	return m_collisionZ;
}

const float SqPolyInfo::GetSizeX()const
{
	return m_sizeX;
}

const float SqPolyInfo::GetSizeY()const
{
	return m_sizeY;
}

const float SqPolyInfo::GetSizeZ()const
{
	return m_sizeZ;
}