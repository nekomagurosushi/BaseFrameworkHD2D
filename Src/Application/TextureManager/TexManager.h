#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<vector>

using namespace std;
class SqPolyInfo;
class PlaneTexInfo;
class ModelInfo;
class ModelWorkInfo;
class TexManager
{
private:
	//�摜�̏����܂Ƃ߂����X�g
	vector<shared_ptr<SqPolyInfo>> m_sqPolyInfoList;
	vector<shared_ptr<PlaneTexInfo>> m_planeTexInfoList;
	vector<shared_ptr<const ModelInfo>> m_modelInfoList;
	vector<shared_ptr<ModelWorkInfo>> m_modelWorkInfoList;

public:
	void JsonLoad(const string a_filename);
	//�t�@�C�������w�肷��΂�������f�[�^���f�[�^���X�g�ɕۑ�
	//void CSVSqPolyLoad(const string a_filename);
	////�t�@�C�������w�肷��΂�������f�[�^���f�[�^���X�g�ɕۑ�
	//void CSVPlaneTexLoad(const string a_filename);
	////�t�@�C�������w�肷��΂�������f�[�^���f�[�^���X�g�ɕۑ�
	//void CSVModelLoad(const string a_filename);
	////�t�@�C�������w�肷��΂�������f�[�^���f�[�^���X�g�ɕۑ�
	//void CSVModelWorkLoad(const string a_filename);

	//���߂�ꂽ�摜�̖��O��n���A���̖��O�����X�g�ɂ���΁A�Y������TexInfo�^�̃f�[�^��߂�l�Ƃ��ēn��
	shared_ptr<SqPolyInfo> LoadSqPolyInfo(const string a_name)const;
	shared_ptr<PlaneTexInfo> LoadPlaneTexInfo(const string a_name)const;
	shared_ptr<const ModelInfo> LoadModelInfo(const string a_name)const;
	shared_ptr<ModelWorkInfo> LoadModelWorkInfo(const string a_name)const;
};