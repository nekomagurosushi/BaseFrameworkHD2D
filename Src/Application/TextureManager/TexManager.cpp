#include "Application/TextureManager/TexManager.h"
#include "Application/TextureManager/TexInfo/Child/SqPolyInfo.h"
#include "Application/TextureManager/TexInfo/Child/2DTexInfo.h"
#include "Application/TextureManager/TexInfo/Child/ModelInfo.h"
#include "Application/TextureManager/TexInfo/Child/ModelWorkInfo.h"
/*
	�P�F�摜��
	�Q�F�p�X��
	�R�FX�����摜�\���T�C�Y
	�S�FY�����摜�\���T�C�Y
	�T�FX���������蔻��T�C�Y
	�U�FY���������蔻��T�C�Y
	�V�FZ���������蔻��T�C�Y
	�W�FX�����T�C�Y
	�X�FY�����T�C�Y
	�P�O�FZ�����T�C�Y
*/

void TexManager::JsonLoad(const string a_filename)
{
	ifstream ifs(a_filename);
	string str, filed;
	if (!ifs)
	{
		cout << "�t�@�C���̃I�[�v���Ɏ��s";
		return;
	}

	//������Ƃ��ēǍ�
	string strJson((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

	//�������JSON����́i�p�[�X�j����
	string err;
	json11::Json jsonObj = json11::Json::parse(strJson, err);
	if (err.size() > 0) { assert(0 && "�ǂݍ��񂾃t�@�C����Json�ϊ��Ɏ��s"); };


	auto& dataList=jsonObj["ModelWork"].array_items();
	for (auto&& data : dataList)
	{

		//�����̓r���Ńf�[�^�̎�ނɂ���ā���DataName�̌^�����߁A�L���X�g����
		istringstream iss(str);
		shared_ptr<ModelWorkInfo> dataName = make_shared<ModelWorkInfo>();

		dataName->SetData(data);

		m_modelWorkInfoList.push_back(dataName);

	}
	dataList = jsonObj["Model"].array_items();
	for (auto&& data : dataList)
	{

		//�����̓r���Ńf�[�^�̎�ނɂ���ā���DataName�̌^�����߁A�L���X�g����
		istringstream iss(str);
		shared_ptr<ModelInfo> dataName = make_shared<ModelInfo>();

		dataName->SetData(data);

		m_modelInfoList.push_back(dataName);

	}
	dataList = jsonObj["PlaneTex"].array_items();
	for (auto&& data : dataList)
	{

		//�����̓r���Ńf�[�^�̎�ނɂ���ā���DataName�̌^�����߁A�L���X�g����
		istringstream iss(str);
		shared_ptr<PlaneTexInfo> dataName = make_shared<PlaneTexInfo>();

		dataName->SetData(data);

		m_planeTexInfoList.push_back(dataName);

	}
	//auto& dataList = jsonObj["DataList"].array_items();

	ifs.close();
}

//void TexManager::CSVSqPolyLoad(const string a_filename)
//{
//	ifstream ifs(a_filename);
//	string str, filed;
//	if (!ifs)
//	{
//		cout << "�t�@�C���̃I�[�v���Ɏ��s";
//		return;
//	}
//
//	//��s�ڂ̃^�O�ǂݔ�΂�
//	getline(ifs, str);
//
//	while (getline(ifs, str))
//	{
//
//		//�����̓r���Ńf�[�^�̎�ނɂ���ā���DataName�̌^�����߁A�L���X�g����
//		istringstream iss(str);
//		shared_ptr<SqPolyInfo> dataName = make_shared<SqPolyInfo>();
//		int i = TexInfoId::NAME;
//		while (getline(iss, filed, ','))
//		{
//			dataName->SetData(TexInfoId(i), filed);
//			i++;
//		}
//		m_sqPolyInfoList.push_back(dataName);
//	}
//	ifs.close();
//}
//
//void TexManager::CSVPlaneTexLoad(const string a_filename)
//{
//	ifstream ifs(a_filename);
//	string str, filed;
//	if (!ifs)
//	{
//		cout << "�t�@�C���̃I�[�v���Ɏ��s";
//		return;
//	}
//
//	//��s�ڂ̃^�O�ǂݔ�΂�
//	getline(ifs, str);
//
//	while (getline(ifs, str))
//	{
//
//		//�����̓r���Ńf�[�^�̎�ނɂ���ā���DataName�̌^�����߁A�L���X�g����
//		istringstream iss(str);
//		shared_ptr<PlaneTexInfo> dataName = make_shared<PlaneTexInfo>();
//	
//		int i = TexInfoId::NAME;
//		while (getline(iss, filed, ','))
//		{
//			dataName->SetData(TexInfoId(i), filed);
//			i++;
//		}
//		m_planeTexInfoList.push_back(dataName);
//
//	}
//	ifs.close();
//}
//
//void TexManager::CSVModelLoad(const string a_filename)
//{
//	ifstream ifs(a_filename);
//	string str, filed;
//	if (!ifs)
//	{
//		cout << "�t�@�C���̃I�[�v���Ɏ��s";
//		return;
//	}
//
//	//��s�ڂ̃^�O�ǂݔ�΂�
//	getline(ifs, str);
//
//	while (getline(ifs, str))
//	{
//
//		//�����̓r���Ńf�[�^�̎�ނɂ���ā���DataName�̌^�����߁A�L���X�g����
//		istringstream iss(str);
//		shared_ptr<ModelInfo> dataName = make_shared<ModelInfo>();
//		int i = TexInfoId::NAME;
//		while (getline(iss, filed, ','))
//		{
//			dataName->SetData(TexInfoId(i), filed);
//			i++;
//		}
//		m_modelInfoList.push_back(dataName);
//
//	}
//	ifs.close();
//}
//
//void TexManager::CSVModelWorkLoad(const string a_filename)
//{
//	ifstream ifs(a_filename);
//	string str, filed;
//	if (!ifs)
//	{
//		cout << "�t�@�C���̃I�[�v���Ɏ��s";
//		return;
//	}
//
//	//������Ƃ��ēǍ�
//	string strJson((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
//
//	//�������JSON����́i�p�[�X�j����
//	string err;
//	json11::Json jsonObj = json11::Json::parse(strJson,err);
//	if (err.size() > 0) { assert(0 && "�ǂݍ��񂾃t�@�C����Json�ϊ��Ɏ��s"); };
//
//	auto& dataList = jsonObj["DataList"].array_items();
//	for(auto&& data:dataList)
//	{
//
//		//�����̓r���Ńf�[�^�̎�ނɂ���ā���DataName�̌^�����߁A�L���X�g����
//		istringstream iss(str);
//		shared_ptr<ModelWorkInfo> dataName = make_shared<ModelWorkInfo>();
//		
//		dataName->SetData(data);
//
//		m_modelWorkInfoList.push_back(dataName);
//
//	}
//	ifs.close();
//}

shared_ptr<SqPolyInfo> TexManager::LoadSqPolyInfo(const string a_name) const
{
	for (shared_ptr<SqPolyInfo> texinfo : m_sqPolyInfoList)
	{
		if (texinfo == nullptr)
		{
			continue;
		}
		if (texinfo->GetName() != a_name);
		else
		{
			return texinfo;
		}
	}
	return nullptr;
}

shared_ptr<PlaneTexInfo> TexManager::LoadPlaneTexInfo(const string a_name) const
{
	for (shared_ptr<PlaneTexInfo> texinfo : m_planeTexInfoList)
	{
		if (texinfo == nullptr)
		{
			continue;
		}
		if (texinfo->GetName() != a_name);
		else
		{
			return texinfo;
		}
	}
	return nullptr;
}

shared_ptr<const ModelInfo> TexManager::LoadModelInfo(const string a_name) const
{
	for (shared_ptr<const ModelInfo> texinfo : m_modelInfoList)
	{
		if (texinfo == nullptr)
		{
			continue;
		}
		if (texinfo->GetName() != a_name);
		else
		{
			return texinfo;
		}
	}
	return nullptr;
}

shared_ptr<ModelWorkInfo> TexManager::LoadModelWorkInfo(const string a_name) const
{
	for (shared_ptr<ModelWorkInfo> texinfo : m_modelWorkInfoList)
	{
		if (texinfo == nullptr)
		{
			continue;
		}
		if (texinfo->GetName() != a_name);
		else
		{
			return texinfo;
		}
	}
	return nullptr;
}
