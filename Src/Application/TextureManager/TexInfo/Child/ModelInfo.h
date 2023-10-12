#pragma once
#include "Application/TextureManager/TexInfo/Base/TexInfo.h"
class ModelInfo :public TexInfo
{
public:
	ModelInfo():
		m_texture(make_shared<KdModelData>()),
		TexInfo()
	{}
	void SetTex()override;
	void SetData(const json11::Json a_jsonObj)override;

	//�摜�{�̃Q�b�^�[
	shared_ptr<const KdModelData>GetTex()const;
private:
	//�摜�|�C���^�[
	shared_ptr<KdModelData> m_texture;
};