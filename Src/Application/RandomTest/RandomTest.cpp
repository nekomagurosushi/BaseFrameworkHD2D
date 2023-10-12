#include "Application/RandomTest/RandomTest.h"

void RandomTest::Init()
{
	int randRest[10] = {};
	/*
	srand((unsigned)time(NULL));

	for (int i = 0; i < 100; i++)
	{
		int temp = rand() % 10000;
		int idx = temp / 1000;
		randRest[idx]++;
	}

	OutputDebugStringA("--------------------------------------\n");
	for (int i = 0; i < 10; i++)
	{
		std::stringstream ss;
		ss << "�擾�����l��" << i * 1000 << "�`" <<(i+1)*1000<<
			"�̌���:\t"<<randRest[i]<<"\n";
		std::string str = ss.str();
		OutputDebugStringA(str.c_str());
	}
	OutputDebugStringA("--------------------------------------\n");
	*///�����Z���k�E�c�C�X�^
	/*std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<int> intRand(0, 9999);
	for (int i = 0; i < 100000000; i++)
	{
		int temp = intRand(mt);
		int idx = temp / 1000;
		randRest[idx]++;
	}*/

	//OutputDebugStringA("--------------------------------------\n");
	//for (int i = 0; i < 10; i++)
	//{
	//	std::stringstream ss;
	//	ss << "�擾�����l��" << i * 1000 << "�`" << (i + 1) * 1000 <<
	//		"�̌���:\t" << randRest[i] << "\n";
	//	std::string str = ss.str();
	//	
	//}
	//OutputDebugStringA("--------------------------------------\n");

	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<int> intRand(0, 999);
	OutputDebugStringA("--------------------------------------\n");
	std::stringstream ss;
	for (int i = 0; i < 1000; i++)
	{
		if (intRand(mt) < 5)
		{
			ss << "���A�J�[�h�擾�I" << "\n";
		}
		else if (intRand(mt)<500)
		{
			ss << "S���A�J�[�h�擾�I" << "\n";
		}
		else
		{
			ss << "�R�����J�[�h�擾�I" << "\n";
		}
	}
	std::string str = ss.str();
	OutputDebugStringA(str.c_str());
	
	OutputDebugStringA("--------------------------------------\n");
}
