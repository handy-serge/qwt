// sandbox.cpp : main project file.

#include "stdafx.h"
#include "MainWindow.h"

using namespace sandbox;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
    System::Windows::Forms::Form^ mainWindow = gcnew MainWindow();
	Application::Run(mainWindow);

	return 0;
}
