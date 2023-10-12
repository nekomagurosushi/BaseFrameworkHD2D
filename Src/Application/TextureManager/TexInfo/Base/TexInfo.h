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
class TexInfo
{
public:
	
	TexInfo() :
	m_name(""),
	m_path("")
	{};
	~TexInfo() {};

	//�Z�b�^�[
	/*
	�摜�{�̃Z�b�^�[
	�����Ɏw�肪�Ȃ��ꍇ�A���g�̎��p�X���猩����
	*/
	virtual void SetTex()=0;
	//�摜�̖��O�̃Z�b�^�[
	void SetName(const string a_name);
	//�摜�̃p�X�̃Z�b�^�[
	void SetPath(const string a_path);
	
	//�f�[�^�Z�b�^�[
	virtual void SetData(const json11::Json a_string)=0;

	//�Q�b�^�[
	//�摜�̖��O�̃Q�b�^�[
	const string GetName() const;
	//�摜�̃p�X�̃Q�b�^�[
	const string GetPath()const;
	
protected:
	//�摜�̖��O
	string m_name;
	//�摜�p�X
	string m_path;
};
