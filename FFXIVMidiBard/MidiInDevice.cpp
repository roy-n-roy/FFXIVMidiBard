#include "MidiInDevice.h"

namespace FFXIVMidiBard {

	static HMIDIIN _midi_in_handle;
	static UINT _device_id;
	static WCHAR errmsg[MAXERRORLENGTH];
	static char errmsg_buff[MAXERRORLENGTH];
	static KeyCombination _keyCombi;
	void CALLBACK MidiInProc(
		HMIDIIN midi_in_handle,
		UINT wMsg,
		DWORD dwInstance,
		DWORD dwParam1,
		DWORD dwParam2
	)
	{
		switch (wMsg)
		{
		case MIM_OPEN:
#ifdef _DEBUG
			Debug::WriteLine("MIDI device was opened.");
#endif
			break;
		case MIM_CLOSE:
#ifdef _DEBUG
			Debug::WriteLine("MIDI device was closed.");
#endif
			break;
		case MIM_DATA:
		{
			unsigned char status_byte = (dwParam1 & 0x000000ff);
			bool is_noteon_event = status_byte == 0x90;
			bool is_noteoff_event = status_byte == 0x80;
			if (!is_noteon_event && !is_noteoff_event)
			{
				break;
			}
			unsigned char velocity = (dwParam1 & 0x00ff0000) >> 16;
			bool is_pressed = velocity != 0;
			if (!is_pressed)
			{
				break;
			}
			unsigned char note = (dwParam1 & 0x0000ff00) >> 8;

			if (!NeteToKeyMapper::Instance()->ContainsKey(note)) {
				break;
			}

			KeyCombination keyCombi = NeteToKeyMapper::Instance()[note];

			// when noteon
			if (is_noteon_event) {
				if (_keyCombi.key != 0) {
					keybd_event(_keyCombi.key, 0, KEYEVENTF_KEYUP, 0);
					if (_keyCombi.ctrl) {
						keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					}
					if (_keyCombi.shift) {
						keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					}
				}

				if (keyCombi.ctrl) {
					keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
					Sleep(20);
				}
				if (keyCombi.shift) {
					keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
					Sleep(20);
				}

				keybd_event(keyCombi.key, 0, 0, 0);
				_keyCombi = keyCombi;
			}

			// when noteoff
			if (is_noteoff_event) {
				if (keyCombi.ctrl == _keyCombi.ctrl && keyCombi.shift == _keyCombi.shift && keyCombi.key == _keyCombi.key) {
					if (_keyCombi.key != 0) {
						keybd_event(_keyCombi.key, 0, KEYEVENTF_KEYUP, 0);
						if (_keyCombi.ctrl) {
							keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
						}
						if (_keyCombi.shift) {
							keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
						}
					}
					_keyCombi = { false, false, 0 };
				}
			}
#ifdef _DEBUG
			Debug::WriteLine("MIM_DATA: wMsg={0:X}, p1={1:X}, p2={2:X}", wMsg, dwParam1, dwParam2);
			if (is_noteon_event) {
				Debug::WriteLine("note on = {0:D}, velocity = {1:D}", note, velocity);

			} else if (is_noteoff_event) {
				Debug::WriteLine("note off = {0:D}, velocity = {1:D}", note, velocity);
			}
#endif
		}
		break;
		case MIM_LONGDATA:
		case MIM_ERROR:
		case MIM_LONGERROR:
		case MIM_MOREDATA:
		default:
			break;
		}
	}

	void MidiInDevice::Stop() {
		MMRESULT res;

		res = midiInStop(_midi_in_handle);
		if (res != MMSYSERR_NOERROR) {
#ifdef _DEBUG
			Debug::WriteLine("MIDI input device {0:D} stop failed.", _device_id);
#endif
			return;
		}

		res = midiInReset(_midi_in_handle);
		if (res != MMSYSERR_NOERROR) {
#ifdef _DEBUG
			Debug::WriteLine("MIDI input device {0:D} reset failed.", _device_id);
#endif
			return;
		}

		res = midiInClose(_midi_in_handle);
		if (res != MMSYSERR_NOERROR) {
#ifdef _DEBUG
			Debug::WriteLine("MIDI input device {0:D} close failed.", _device_id);
#endif
			return;
		}
	}

	void MidiInDevice::Start(UINT device_id) {
		MMRESULT res;
		_device_id = device_id;

		res = midiInOpen(&_midi_in_handle, _device_id, (DWORD_PTR)MidiInProc, 0, CALLBACK_FUNCTION);
		if (res != MMSYSERR_NOERROR) {
#ifdef _DEBUG
			Debug::WriteLine("Cannot open MIDI input device {0:D}.", _device_id);
#endif
			return;
		}

#ifdef _DEBUG
		Debug::WriteLine("Successfully opened a MIDI input device {0:D}.", _device_id);
#endif
		res = midiInStart(_midi_in_handle);
		if (res != MMSYSERR_NOERROR) {
#ifdef _DEBUG
			Debug::WriteLine("MIDI input device {0:D} start failed.", _device_id);
#endif
			return;
		}
	}

	cli::array<System::String^>^ MidiInDevice::GetNames() {
		UINT deviceCount = midiInGetNumDevs();
		cli::array<System::String^>^ midiDeviceNameArray;
		if (deviceCount == 0) {
			midiDeviceNameArray = gcnew cli::array<System::String^>(1);
			midiDeviceNameArray[0] = "MIDI Input Device not found.";
			return midiDeviceNameArray;
		}

		MIDIINCAPS midiInCaps;

		midiDeviceNameArray = gcnew cli::array<System::String^>(deviceCount);

		for (UINT i = 0; i < deviceCount; i++) {
			midiInGetDevCaps(i, &midiInCaps, sizeof(midiInCaps));
			midiDeviceNameArray[i] = marshal_as<System::String^>(midiInCaps.szPname);
		}

		return midiDeviceNameArray;
	}

}