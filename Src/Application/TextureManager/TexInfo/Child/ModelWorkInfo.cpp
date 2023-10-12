#include "ModelWorkInfo.h"

void ModelWorkInfo::SetTex()
{
	m_texture->SetModelData(m_path);
}

void ModelWorkInfo::SetData(const json11::Json a_jsonObj)
{

	if (a_jsonObj["Name"].string_value().c_str() != "")SetName(a_jsonObj["Name"].string_value());

	if (a_jsonObj["Path"].string_value().c_str() != "")
	{
		SetPath(a_jsonObj["Path"].string_value());
		SetTex();
	}
}

shared_ptr<KdModelWork> ModelWorkInfo::GetTex() const
{
	return m_texture;
}
