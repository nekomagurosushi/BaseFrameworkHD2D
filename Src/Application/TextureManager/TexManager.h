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
	//画像の情報をまとめたリスト
	vector<shared_ptr<SqPolyInfo>> m_sqPolyInfoList;
	vector<shared_ptr<PlaneTexInfo>> m_planeTexInfoList;
	vector<shared_ptr<const ModelInfo>> m_modelInfoList;
	vector<shared_ptr<ModelWorkInfo>> m_modelWorkInfoList;

public:
	void JsonLoad(const string a_filename);
	//ファイル名を指定すればそこからデータをデータリストに保存
	//void CSVSqPolyLoad(const string a_filename);
	////ファイル名を指定すればそこからデータをデータリストに保存
	//void CSVPlaneTexLoad(const string a_filename);
	////ファイル名を指定すればそこからデータをデータリストに保存
	//void CSVModelLoad(const string a_filename);
	////ファイル名を指定すればそこからデータをデータリストに保存
	//void CSVModelWorkLoad(const string a_filename);

	//決められた画像の名前を渡し、その名前がリストにあれば、該当するTexInfo型のデータを戻り値として渡す
	shared_ptr<SqPolyInfo> LoadSqPolyInfo(const string a_name)const;
	shared_ptr<PlaneTexInfo> LoadPlaneTexInfo(const string a_name)const;
	shared_ptr<const ModelInfo> LoadModelInfo(const string a_name)const;
	shared_ptr<ModelWorkInfo> LoadModelWorkInfo(const string a_name)const;
};