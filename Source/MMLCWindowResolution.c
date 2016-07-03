/*
    MMLCWindowResolution: A program to change the window size of the Mega Man Legacy Collection.

    Copyright (C) 2016  Lucas Cota (BrasileiroGamer)
    lucasbrunocota@live.com
    <http://www.github.com/BrasileiroGamer/>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _WIN32_WINNT 0x0500
#include <time.h>
#include <stdio.h>
#include <windows.h>

int main()
{
	int FirstRun; //Run Control
	int WindowWidth; //Width Size
	int WindowHeight; //Height Size
	HWND WindowHandle; //Window Handle

	int TimeLimit; //FindWindow() Limit
	clock_t TimeStart; //FindWindow() Start

	//Checking INI
	FILE *MMLCWindowResolution = fopen("./MMLCWindowResolution.ini", "r");
	FirstRun = GetPrivateProfileInt("Global", "FirstRun", -1, "./MMLCWindowResolution.ini");
	TimeLimit = GetPrivateProfileInt("Global", "TimeLimit", -1, "./MMLCWindowResolution.ini");
	WindowWidth = GetPrivateProfileInt("Window", "WindowWidth", -1, "./MMLCWindowResolution.ini");
	WindowHeight = GetPrivateProfileInt("Window", "WindowHeight", -1, "./MMLCWindowResolution.ini");

	if(MMLCWindowResolution == NULL || FirstRun == 1 || FirstRun == -1 || TimeLimit == -1 || WindowWidth == -1 || WindowHeight == -1)
	{
		MMLCWindowResolution = fopen("./MMLCWindowResolution.ini", "w");

		//Getting Configurations
		system("cls");
		printf("\n MMLCWindowResolution Tool v2016.3\n\n");
		printf(" Well, it looks like it's the first time you're running MMLCWindowResolution.\n");
		printf(" 'WindowWidth' is the value of the width of the window (eg: 1920).\n");
		printf(" 'WindowHeight' is the value of the height of the window (eg: 1080).\n");
		printf(" Please enter values for configuration:\n\n");

		printf(" WindowWidth: ");
		scanf("%i", &WindowWidth); fflush(stdin);
		printf(" WindowHeight: ");
		scanf("%i", &WindowHeight); fflush(stdin);

		ShowWindow(GetConsoleWindow(), SW_HIDE); //Hiding Console

		//Writing Configurations
		fprintf(MMLCWindowResolution, "[Global]\n");
		fprintf(MMLCWindowResolution, "# Verifies that the program has already been set.\n");
		fprintf(MMLCWindowResolution, "FirstRun=0\n\n");

		fprintf(MMLCWindowResolution, "# Is the limit of time (in seconds) that the program will look for the game window.\n");
		fprintf(MMLCWindowResolution, "# Decrease this only when necessary, if you put a very small amount, it may be the program does not find the game window.\n");
		fprintf(MMLCWindowResolution, "TimeLimit=60\n\n");

		fprintf(MMLCWindowResolution, "[Window]\n");
		fprintf(MMLCWindowResolution, "# Is the value of the width of the window (eg: 1920).\n");
		fprintf(MMLCWindowResolution, "WindowWidth=%i\n\n", WindowWidth);

		fprintf(MMLCWindowResolution, "# Is the value of the height of the window (eg: 1080).\n");
		fprintf(MMLCWindowResolution, "WindowHeight=%i\n", WindowHeight);
		fclose(MMLCWindowResolution);

		MessageBox(NULL, "You can view this prompt again by setting 'FirstRun=1' in 'MMLCWindowResolution.ini' or deleting it. You can also edit the information manually in 'MMLCWindowResolution.ini'.\n\nPress OK to continue.", "MMLCWindowResolution Tool", MB_ICONINFORMATION);
	}
	else
	{
		fclose(MMLCWindowResolution);
		ShowWindow(GetConsoleWindow(), SW_HIDE); //Hiding Console
	}

	//Reading INI
	TimeLimit = GetPrivateProfileInt("Global", "TimeLimit", -1, "./MMLCWindowResolution.ini");
	WindowWidth = GetPrivateProfileInt("Window", "WindowWidth", -1, "./MMLCWindowResolution.ini");
	WindowHeight = GetPrivateProfileInt("Window", "WindowHeight", -1, "./MMLCWindowResolution.ini");

	system("START steam://rungameid/363440"); //Starting Game
	WindowHandle = FindWindow(NULL, "Mega Man Legacy Collection"); //Getting Handling

	TimeStart = clock(); //Countdown Start
	TimeLimit = TimeLimit + ((TimeLimit * 100) / 1000); //Countdown Limit (Compensating 100 ms)

	//Fiding Window
	while(WindowHandle == NULL && ((clock() - TimeStart) / (double) CLOCKS_PER_SEC) <= TimeLimit)
	{
		Sleep(100);
		WindowHandle = FindWindow(NULL, "Mega Man Legacy Collection");
	}

	if(WindowHandle == NULL)
	{
		MessageBox(NULL, "Could not find the Mega Man Legacy Collection window!\n\nThe program will close, press OK to continue.", "MMLCWindowResolution Tool", MB_ICONERROR);
		return 1;
	}
	else
	{
		//Applying Resolution
		Sleep(5000);
		SetWindowPos(WindowHandle, NULL, ((GetSystemMetrics(SM_CXSCREEN) - WindowWidth) / 2), ((GetSystemMetrics(SM_CYSCREEN) - WindowHeight) / 2), WindowWidth, WindowHeight, SWP_SHOWWINDOW);
	}
	return 0;
}
