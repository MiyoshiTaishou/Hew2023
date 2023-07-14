#include	<functional>
#include	<thread>

// 指定時間後にスレッドを起動
void Invoke(std::function<void()> Function, int Time)
{
	std::thread([=]()
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(Time));
	//			Sleep(Time);
	Function();
		}).detach();
}

