#pragma once
#include <stdio.h>
#include <windows.h> 
#include <mmsystem.h> 
#include <msclr/marshal_cppstd.h>
#include "NeteToKeyMapper.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")

namespace FFXIVMidiBard {
	using namespace msclr::interop;

#ifdef _DEBUG
	using namespace System::Diagnostics;
#endif
	static class MidiInDevice {
	public:
		static void Start(UINT device_id);
		static void Stop();
		static cli::array<System::String^>^ GetNames();
	};
}

