#pragma once
#include "Application/TextureManager/TexInfo/Base/TexInfo.h"
class PlaneTexInfo:public TexInfo
{
public:
	PlaneTexInfo():
		m_texture(make_shared<KdTexture>()),
		m_pos(Math::Vector2::Zero),
		m_size(Math::Vector2::Zero),
		m_rectX(),
		m_rectY(),
		m_color(),
		TexInfo()
	{}
	void SetTex()override;
	void SetData(const json11::Json a_jsonObj)override;

	void SetPos(Math::Vector2 a_pos);
	void SetSize(Math::Vector2 a_size);
	//画像のX方向画像表示のセッター
	void SetRectX(const int a_rectX);
	//画像のY方向画像表示のセッター
	void SetRectY(const int a_rectY);

	void SetColor(Math::Color a_color);
	//画像本体ゲッター
	shared_ptr<KdTexture>GetTex()const;
	Math::Vector2 GetPos();
	Math::Vector2 GetSize();
	//画像のX方向画像表示のゲッター
	const int GetRectX()const;
	//画像のY方向画像表示のゲッター
	const int GetRectY()const;

	const Math::Color GetColor()const;
private:
	//画像ポインター
	shared_ptr<KdTexture> m_texture;
	Math::Vector2 m_size;
	Math::Vector2 m_pos;
	//画像X方向表示サイズ
	int m_rectX;
	//画像Y方向表示サイズ
	int m_rectY;

	Math::Color m_color;
};