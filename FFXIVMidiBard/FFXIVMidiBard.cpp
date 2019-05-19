#include <Windows.h>
#include "MainWindow.h"

namespace FFXIVMidiBard {

	[STAThreadAttribute]
	int main()
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);
		Application::Run(gcnew FFXIVMidiBard::MainWindow());

		return 0;
	}
}