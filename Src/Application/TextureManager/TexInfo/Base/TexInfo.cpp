#include "Application/TextureManager/TexInfo/Base/TexInfo.h"

void TexInfo::SetName(const string a_name)
{
	m_name = a_name;
}

void TexInfo::SetPath(const string a_path)
{
	m_path = a_path;
}

const string TexInfo::GetName()const
{
	return m_name;
}

const string TexInfo::GetPath()const
{
	return m_path;
}
