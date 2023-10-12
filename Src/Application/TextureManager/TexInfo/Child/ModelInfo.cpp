#include "ModelInfo.h"

void ModelInfo::SetTex()
{
	m_texture->Load(m_path);
}

void ModelInfo::SetData(const json11::Json a_jsonObj)
{
	if (a_jsonObj["Name"].string_value().c_str() != "")SetName(a_jsonObj["Name"].string_value());

	if (a_jsonObj["Path"].string_value().c_str() != "")
	{
		SetPath(a_jsonObj["Path"].string_value());
		SetTex();
	}
}

shared_ptr<const KdModelData> ModelInfo::GetTex() const
{
	return m_texture;
}
