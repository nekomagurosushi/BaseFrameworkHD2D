#pragma once
/*
	0=NAME
	1=PATH
	2=RECT_X
	3=RECT_Y
	4=COLI_X
	5=COLI_Y
	6=COLI_Z
	7=SIZE_X
	8=SIZE_Y
	9=SIZE_Z
	10=STARTPOINT
*/
enum TexInfoId
{
	NAME,
	PATH,
	RECT_X,
	RECT_Y,
	COLI_X,
	COLI_Y,
	COLI_Z,
	SIZE_X,
	SIZE_Y,
	SIZE_Z,
	STARTPOINT,
	SPLIT_X,
	SPLIT_Y
};
using namespace std;

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
class TexInfo
{
public:
	
	TexInfo() :
	m_name(""),
	m_path("")
	{};
	~TexInfo() {};

	//セッター
	/*
	画像本体セッター
	引数に指定がない場合、自身の持つパスから見込む
	*/
	virtual void SetTex()=0;
	//画像の名前のセッター
	void SetName(const string a_name);
	//画像のパスのセッター
	void SetPath(const string a_path);
	
	//データセッター
	virtual void SetData(const json11::Json a_string)=0;

	//ゲッター
	//画像の名前のゲッター
	const string GetName() const;
	//画像のパスのゲッター
	const string GetPath()const;
	
protected:
	//画像の名前
	string m_name;
	//画像パス
	string m_path;
};
