#pragma once

namespace FFXIVMidiBard {
	using namespace System::Collections::Generic;

	public value struct KeyCombination {
	public:
		bool ctrl;
		bool shift;
		unsigned char key;
	};


	static ref class NeteToKeyMapper
	{
	private:
		static Dictionary<unsigned char, KeyCombination>^ _instance = nullptr;

	public:
		static Dictionary<unsigned char, KeyCombination>^ Instance() {
			if (_instance == nullptr) {
				_instance = gcnew Dictionary<unsigned char, KeyCombination>(38);

				_instance[(unsigned char)48] = KeyCombination { true, false, 'Q' };
				_instance[(unsigned char)49] = KeyCombination { true, false, '2' };
				_instance[(unsigned char)50] = KeyCombination { true, false, 'W' };
				_instance[(unsigned char)51] = KeyCombination { true, false, '3' };
				_instance[(unsigned char)52] = KeyCombination { true, false, 'E' };
				_instance[(unsigned char)53] = KeyCombination { true, false, 'R' };
				_instance[(unsigned char)54] = KeyCombination { true, false, '5' };
				_instance[(unsigned char)55] = KeyCombination { true, false, 'T' };
				_instance[(unsigned char)56] = KeyCombination { true, false, '6' };
				_instance[(unsigned char)57] = KeyCombination { true, false, 'Y' };
				_instance[(unsigned char)58] = KeyCombination { true, false, '7' };
				_instance[(unsigned char)59] = KeyCombination { true, false, 'U' };
				_instance[(unsigned char)60] = KeyCombination { false, false, 'Q' };
				_instance[(unsigned char)61] = KeyCombination { false, false, '2' };
				_instance[(unsigned char)62] = KeyCombination { false, false, 'W' };
				_instance[(unsigned char)63] = KeyCombination { false, false, '3' };
				_instance[(unsigned char)64] = KeyCombination { false, false, 'E' };
				_instance[(unsigned char)65] = KeyCombination { false, false, 'R' };
				_instance[(unsigned char)66] = KeyCombination { false, false, '5' };
				_instance[(unsigned char)67] = KeyCombination { false, false, 'T' };
				_instance[(unsigned char)68] = KeyCombination { false, false, '6' };
				_instance[(unsigned char)69] = KeyCombination { false, false, 'Y' };
				_instance[(unsigned char)70] = KeyCombination { false, false, '7' };
				_instance[(unsigned char)71] = KeyCombination { false, false, 'U' };
				_instance[(unsigned char)72] = KeyCombination { false, true, 'Q' };
				_instance[(unsigned char)73] = KeyCombination { false, true, '2' };
				_instance[(unsigned char)74] = KeyCombination { false, true, 'W' };
				_instance[(unsigned char)75] = KeyCombination { false, true, '3' };
				_instance[(unsigned char)76] = KeyCombination { false, true, 'E' };
				_instance[(unsigned char)77] = KeyCombination { false, true, 'R' };
				_instance[(unsigned char)78] = KeyCombination { false, true, '5' };
				_instance[(unsigned char)79] = KeyCombination { false, true, 'T' };
				_instance[(unsigned char)80] = KeyCombination { false, true, '6' };
				_instance[(unsigned char)81] = KeyCombination { false, true, 'Y' };
				_instance[(unsigned char)82] = KeyCombination { false, true, '7' };
				_instance[(unsigned char)83] = KeyCombination { false, true, 'U' };
				_instance[(unsigned char)84] = KeyCombination { false, true, 'I' };
			}
			return _instance;
		};
	};
}