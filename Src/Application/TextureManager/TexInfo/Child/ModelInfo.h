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

	//画像本体ゲッター
	shared_ptr<const KdModelData>GetTex()const;
private:
	//画像ポインター
	shared_ptr<KdModelData> m_texture;
};