#include	<functional>
#include	<thread>

// �w�莞�Ԍ�ɃX���b�h���N��
void Invoke(std::function<void()> Function, int Time)
{
	std::thread([=]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(Time));
	//			Sleep(Time);
	Function();
		}).detach();
}

