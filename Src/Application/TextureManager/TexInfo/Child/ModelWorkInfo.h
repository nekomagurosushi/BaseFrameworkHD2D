#pragma once
#include "Application/TextureManager/TexInfo/Base/TexInfo.h"
class ModelWorkInfo :public TexInfo
{
public:
	ModelWorkInfo() :
		m_texture(make_shared<KdModelWork>()),
		TexInfo()
	{}
	void SetTex()override;
	void SetData( const json11::Json a_jsonObj)override;

	//�摜�{�̃Q�b�^�[
	shared_ptr<KdModelWork>GetTex()const;
private:
	//�摜�|�C���^�[
	shared_ptr<KdModelWork> m_texture;
};