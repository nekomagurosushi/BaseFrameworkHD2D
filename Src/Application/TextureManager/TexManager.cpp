#include "Application/TextureManager/TexManager.h"
#include "Application/TextureManager/TexInfo/Child/SqPolyInfo.h"
#include "Application/TextureManager/TexInfo/Child/2DTexInfo.h"
#include "Application/TextureManager/TexInfo/Child/ModelInfo.h"
#include "Application/TextureManager/TexInfo/Child/ModelWorkInfo.h"
/*
	１：画像名
	２：パス名
	３：X方向画像表示サイズ
	４：Y方向画像表示サイズ
	５：X方向当たり判定サイズ
	６：Y方向当たり判定サイズ
	７：Z方向当たり判定サイズ
	８：X方向サイズ
	９：Y方向サイズ
	１０：Z方向サイズ
*/

void TexManager::JsonLoad(const string a_filename)
{
	ifstream ifs(a_filename);
	string str, filed;
	if (!ifs)
	{
		cout << "ファイルのオープンに失敗";
		return;
	}

	//文字列として読込
	string strJson((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());

	//文字列のJSONを解析（パース）する
	string err;
	json11::Json jsonObj = json11::Json::parse(strJson, err);
	if (err.size() > 0) { assert(0 && "読み込んだファイルのJson変換に失敗"); };


	auto& dataList=jsonObj["ModelWork"].array_items();
	for (auto&& data : dataList)
	{

		//ここの途中でデータの種類によって↓のDataNameの型を決め、キャストする
		istringstream iss(str);
		shared_ptr<ModelWorkInfo> dataName = make_shared<ModelWorkInfo>();

		dataName->SetData(data);

		m_modelWorkInfoList.push_back(dataName);

	}
	dataList = jsonObj["Model"].array_items();
	for (auto&& data : dataList)
	{

		//ここの途中でデータの種類によって↓のDataNameの型を決め、キャストする
		istringstream iss(str);
		shared_ptr<ModelInfo> dataName = make_shared<ModelInfo>();

		dataName->SetData(data);

		m_modelInfoList.push_back(dataName);

	}
	dataList = jsonObj["PlaneTex"].array_items();
	for (auto&& data : dataList)
	{

		//ここの途中でデータの種類によって↓のDataNameの型を決め、キャストする
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
//		cout << "ファイルのオープンに失敗";
//		return;
//	}
//
//	//一行目のタグ読み飛ばし
//	getline(ifs, str);
//
//	while (getline(ifs, str))
//	{
//
//		//ここの途中でデータの種類によって↓のDataNameの型を決め、キャストする
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
//		cout << "ファイルのオープンに失敗";
//		return;
//	}
//
//	//一行目のタグ読み飛ばし
//	getline(ifs, str);
//
//	while (getline(ifs, str))
//	{
//
//		//ここの途中でデータの種類によって↓のDataNameの型を決め、キャストする
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
//		cout << "ファイルのオープンに失敗";
//		return;
//	}
//
//	//一行目のタグ読み飛ばし
//	getline(ifs, str);
//
//	while (getline(ifs, str))
//	{
//
//		//ここの途中でデータの種類によって↓のDataNameの型を決め、キャストする
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
//		cout << "ファイルのオープンに失敗";
//		return;
//	}
//
//	//文字列として読込
//	string strJson((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
//
//	//文字列のJSONを解析（パース）する
//	string err;
//	json11::Json jsonObj = json11::Json::parse(strJson,err);
//	if (err.size() > 0) { assert(0 && "読み込んだファイルのJson変換に失敗"); };
//
//	auto& dataList = jsonObj["DataList"].array_items();
//	for(auto&& data:dataList)
//	{
//
//		//ここの途中でデータの種類によって↓のDataNameの型を決め、キャストする
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
