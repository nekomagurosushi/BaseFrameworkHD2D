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
	//�摜��X�����摜�\���̃Z�b�^�[
	void SetRectX(const int a_rectX);
	//�摜��Y�����摜�\���̃Z�b�^�[
	void SetRectY(const int a_rectY);
	//�摜��X���������蔻��i���a�j�̃Z�b�^�[
	void SetColiX(const int a_coliX);
	//�摜��Y���������蔻��i���a�j�̃Z�b�^�[
	void SetColiY(const int a_coliY);
	//�摜��Z���������蔻��i���a�j�̃Z�b�^�[
	void SetColiZ(const int a_coliZ);
	//�摜��X�����T�C�Y�̃Z�b�^�[
	void SetSizeX(const float a_sizeX);
	//�摜��Y�����T�C�Y�̃Z�b�^�[
	void SetSizeY(const float a_sizeY);
	//�摜��Z�����T�C�Y�̃Z�b�^�[
	void SetSizeZ(const float a_sizeZ);
	//�摜���_�ʒu�̖��̃Z�b�^�[
	void SetPivot(const KdSquarePolygon::PivotType a_startPoint);
	void SetUVRect(UINT index);

	//�摜�{�̃Q�b�^�[
	shared_ptr<KdSquarePolygon>GetTex()const;
	//�摜��X�����摜�\���̃Q�b�^�[
	const int GetRectX()const;
	//�摜��Y�����摜�\���̃Q�b�^�[
	const int GetRectY()const;
	//�摜��X���������蔻��i���a�j�̃Q�b�^�[
	const int GetColiX()const;
	//�摜��Y���������蔻��i���a�j�̃Q�b�^�[
	const int GetColiY()const;
	//�摜��Z���������蔻��i���a�j�̃Q�b�^�[
	const int GetColiZ()const;
	//�摜��X�����T�C�Y�̃Q�b�^�[
	const float GetSizeX()const;
	//�摜��Y�����T�C�Y�̃Q�b�^�[
	const float GetSizeY()const;
	//�摜��Z�����T�C�Y�̃Q�b�^�[
	const float GetSizeZ()const;
private:
	//�摜�|�C���^�[
	shared_ptr<KdSquarePolygon> m_texture;
	//�摜X�����\���T�C�Y
	int m_rectX;
	//�摜Y�����\���T�C�Y
	int m_rectY;
	//X���������蔻��i���a�j
	int m_collisionX;
	//Y���������蔻��i���a�j
	int m_collisionY;
	//Z���������蔻��i���a�j
	int m_collisionZ;
	//X�����T�C�Y
	float m_sizeX;
	//Y�����T�C�Y
	float m_sizeY;
	//Z�����T�C�Y
	float m_sizeZ;
};