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
	//�摜��X�����摜�\���̃Z�b�^�[
	void SetRectX(const int a_rectX);
	//�摜��Y�����摜�\���̃Z�b�^�[
	void SetRectY(const int a_rectY);

	void SetColor(Math::Color a_color);
	//�摜�{�̃Q�b�^�[
	shared_ptr<KdTexture>GetTex()const;
	Math::Vector2 GetPos();
	Math::Vector2 GetSize();
	//�摜��X�����摜�\���̃Q�b�^�[
	const int GetRectX()const;
	//�摜��Y�����摜�\���̃Q�b�^�[
	const int GetRectY()const;

	const Math::Color GetColor()const;
private:
	//�摜�|�C���^�[
	shared_ptr<KdTexture> m_texture;
	Math::Vector2 m_size;
	Math::Vector2 m_pos;
	//�摜X�����\���T�C�Y
	int m_rectX;
	//�摜Y�����\���T�C�Y
	int m_rectY;

	Math::Color m_color;
};