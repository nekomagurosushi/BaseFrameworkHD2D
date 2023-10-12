#pragma once
#include "Application/TextureManager/TexInfo/Base/TexInfo.h"
class SqPolyInfo :public TexInfo
{
public:
	SqPolyInfo():
		m_texture(make_shared<KdSquarePolygon>()),
		m_rectX(),
		m_rectY(),
		m_collisionX(),
		m_collisionY(),
		m_collisionZ(),
		m_sizeX(),
		m_sizeY(),
		m_sizeZ(),
		TexInfo()
	{}
	void SetTex()override;
	void SetData(const json11::Json a_jsonObj)override;
	//画像のX方向画像表示のセッター
	void SetRectX(const int a_rectX);
	//画像のY方向画像表示のセッター
	void SetRectY(const int a_rectY);
	//画像のX方向当たり判定（半径）のセッター
	void SetColiX(const int a_coliX);
	//画像のY方向当たり判定（半径）のセッター
	void SetColiY(const int a_coliY);
	//画像のZ方向当たり判定（半径）のセッター
	void SetColiZ(const int a_coliZ);
	//画像のX方向サイズのセッター
	void SetSizeX(const float a_sizeX);
	//画像のY方向サイズのセッター
	void SetSizeY(const float a_sizeY);
	//画像のZ方向サイズのセッター
	void SetSizeZ(const float a_sizeZ);
	//画像原点位置の名称セッター
	void SetPivot(const KdSquarePolygon::PivotType a_startPoint);
	void SetUVRect(UINT index);

	//画像本体ゲッター
	shared_ptr<KdSquarePolygon>GetTex()const;
	//画像のX方向画像表示のゲッター
	const int GetRectX()const;
	//画像のY方向画像表示のゲッター
	const int GetRectY()const;
	//画像のX方向当たり判定（半径）のゲッター
	const int GetColiX()const;
	//画像のY方向当たり判定（半径）のゲッター
	const int GetColiY()const;
	//画像のZ方向当たり判定（半径）のゲッター
	const int GetColiZ()const;
	//画像のX方向サイズのゲッター
	const float GetSizeX()const;
	//画像のY方向サイズのゲッター
	const float GetSizeY()const;
	//画像のZ方向サイズのゲッター
	const float GetSizeZ()const;
private:
	//画像ポインター
	shared_ptr<KdSquarePolygon> m_texture;
	//画像X方向表示サイズ
	int m_rectX;
	//画像Y方向表示サイズ
	int m_rectY;
	//X方向当たり判定（半径）
	int m_collisionX;
	//Y方向当たり判定（半径）
	int m_collisionY;
	//Z方向当たり判定（半径）
	int m_collisionZ;
	//X方向サイズ
	float m_sizeX;
	//Y方向サイズ
	float m_sizeY;
	//Z方向サイズ
	float m_sizeZ;
};