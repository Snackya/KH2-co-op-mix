#ifndef MEMORYLIB
#define MEMORYLIB

#pragma once    // added by Snackya

#include <windows.h>
#include <iostream>
#include <string>
#include <psapi.h>
#include "TlHelp32.h"
#include <vector>

using namespace std;


// from fork https://github.com/Snackya/LuaBackend
class MemoryLib
{
    private:
        static inline STARTUPINFOA _sInfo;
        static inline PROCESS_INFORMATION _pInfo;
        static inline uint64_t _execAddress;
        static inline bool _bigEndian = false;

    public:
        static inline uint64_t BaseAddress;
        static inline DWORD PIdentifier = NULL;
        static inline HANDLE PHandle = NULL;
        static inline char PName[MAX_PATH];

    static HMODULE FindBaseAddr(HANDLE InputHandle, string InputName)
    {
        HMODULE hMods[1024];
        DWORD cbNeeded;
        unsigned int i;

        if (EnumProcessModules(InputHandle, hMods, sizeof(hMods), &cbNeeded))
        {
            for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
            {
                TCHAR szModName[MAX_PATH];
                if (GetModuleFileNameEx(InputHandle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
                {
                    wstring wstrModName = szModName;
                    wstring wstrModContain = wstring(InputName.begin(), InputName.end());

                    if (wstrModName.find(wstrModContain) != string::npos)
                        return hMods[i];
                }
            }
        }

        return nullptr;
    }

    static DWORD FindProcessId(const std::wstring& processName)
    {
        PROCESSENTRY32 processInfo;
        processInfo.dwSize = sizeof(processInfo);

        HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (processesSnapshot == INVALID_HANDLE_VALUE)
            return 0;

        Process32First(processesSnapshot, &processInfo);
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }

        while (Process32Next(processesSnapshot, &processInfo))
        {
            if (!processName.compare(processInfo.szExeFile))
            {
                CloseHandle(processesSnapshot);
                return processInfo.th32ProcessID;
            }
        }

        CloseHandle(processesSnapshot);
        return 0;
    }

    static void ExecuteProcess(string InputName, uint64_t InputAddress, bool InputEndian)
    {
        ZeroMemory(&_sInfo, sizeof(_sInfo)); _sInfo.cb = sizeof(_sInfo);
        ZeroMemory(&_pInfo, sizeof(_pInfo));

        CreateProcessA(InputName.c_str(), NULL, NULL, NULL, TRUE, 0, NULL, NULL, &_sInfo, &_pInfo);

        BaseAddress = InputAddress;
        _bigEndian = InputEndian;
    };

    // added by Snackya. idea from Tommadness/TrevorLuckey
    static void SetPCSX2BaseAddress()
    {
        // over the horizon (valor form ability) address and expected value
        uint32_t oth_addr = 0x032EE36;
        uint16_t oth_val = 0x80F6;
        uint16_t val;

        // check multiple offsets until the read value matches the expected one.
        for (int i = 1; i < 8; ++i)
        {
            BaseAddress = 0x10000000 * i;
            vector<uint8_t> _buffer(2);
            ReadProcessMemory(PHandle, (void*)(BaseAddress + oth_addr), _buffer.data(), 2, 0);
            val = (_buffer[1] << 8) | _buffer[0];
            if (val == oth_val) break;
        }
    }

    // added by Snackya
    static bool AttachToGameVersion(string version)
    {
        string _exec;
        if (version == "PC") _exec = "KINGDOM HEARTS II FINAL MIX.exe";
        else if (version == "PS2") _exec = "pcsx2.exe";

        PIdentifier = FindProcessId(wstring(_exec.begin(), _exec.end()));
        PHandle = OpenProcess(PROCESS_ALL_ACCESS, false, PIdentifier);

        if (version == "PC" && PHandle != NULL)
        {
            BaseAddress = (uint64_t)FindBaseAddr(PHandle, _exec);
            return true;
        }
        else if (version == "PS2" && PHandle != NULL)
        {
            SetPCSX2BaseAddress();
            return true;
        }
        else return false;
    }

    static bool LatchProcess(string InputName, uint64_t InputAddress, bool InputEndian)
    {
        ZeroMemory(&_sInfo, sizeof(_sInfo)); _sInfo.cb = sizeof(_sInfo);
        ZeroMemory(&_pInfo, sizeof(_pInfo));

        PIdentifier = FindProcessId(wstring(InputName.begin(), InputName.end()));
        PHandle = OpenProcess(PROCESS_ALL_ACCESS, false, PIdentifier);

        GetProcessImageFileNameA(MemoryLib::PHandle, PName, MAX_PATH);
        BaseAddress = InputAddress;

        _execAddress = (uint64_t)FindBaseAddr(PHandle, PName);
        _bigEndian = InputEndian;

        if (PHandle == NULL)
            return false;

        return true;
    };

    static void ExternProcess(DWORD InputID, HANDLE InputH, uint64_t InputAddress)
    {
        PIdentifier = InputID;
        PHandle = InputH;

        GetProcessImageFileNameA(MemoryLib::PHandle, PName, MAX_PATH);

        BaseAddress = InputAddress;
        _execAddress = (uint64_t)FindBaseAddr(PHandle, PName);
    };

    static uint8_t ReadByte(uint64_t Address) { return ReadBytes(Address, 1)[0]; }
    static vector<uint8_t> ReadBytes(uint64_t Address, int Length)
    {
        vector<uint8_t> _buffer;
        _buffer.resize(Length);

        ReadProcessMemory(PHandle, (void*)(Address + BaseAddress), _buffer.data(), Length, 0);
        return _buffer;
    }
    static uint16_t ReadShort(uint64_t Address)
    {
        auto _buffer = ReadBytes(Address, 2);

        if (_bigEndian)
            return (_buffer[0] << 8) | _buffer[1];
        else
            return (_buffer[1] << 8) | _buffer[0];
    }
    static uint32_t ReadInt(uint64_t Address)
    {
        auto _buffer = ReadBytes(Address, 4);

        if (_bigEndian)
            return (_buffer[0] << 24) | (_buffer[1] << 16) | (_buffer[2] << 8) | (_buffer[3]);
        else
            return (_buffer[3] << 24) | (_buffer[2] << 16) | (_buffer[1] << 8) | (_buffer[0]);
    }
    static uint64_t ReadLong(uint64_t Address)
    {
        auto _buffer = ReadBytes(Address, 8);

        if (_bigEndian)
            return ((uint64_t)_buffer[0] << 56) | ((uint64_t)_buffer[1] << 48) | ((uint64_t)_buffer[2] << 40) | ((uint64_t)_buffer[3] << 32) | ((uint64_t)_buffer[4] << 24) | ((uint64_t)_buffer[5] << 16) | ((uint64_t)_buffer[6] << 8) | ((uint64_t)_buffer[7]);

        else
            return ((uint64_t)_buffer[7] << 56) | ((uint64_t)_buffer[6] << 48) | ((uint64_t)_buffer[5] << 40) | ((uint64_t)_buffer[4] << 32) | ((uint64_t)_buffer[3] << 24) | ((uint64_t)_buffer[2] << 16) | ((uint64_t)_buffer[1] << 8) | ((uint64_t)_buffer[0]);
    }
    static float ReadFloat(uint64_t Address)
    {
        auto _value = ReadInt(Address);
        auto _return = *reinterpret_cast<float*>(&_value);
        return _return;
    }
    static bool ReadBool(uint64_t Address)
    {
        auto _value = ReadByte(Address);
        return _value == 0 ? false : true;
    }
    static string ReadString(uint64_t Address, int Length)
    {
        auto _value = ReadBytes(Address, Length);
        string _output(_value.begin(), _value.end());
        return _output;
    }
    
    static void WriteByte(uint64_t Address, uint8_t Input) { WriteProcessMemory(PHandle, (void*)(Address + BaseAddress), &Input, 1, 0); }
    static void WriteBytes(uint64_t Address, vector<uint8_t> Input)
    {
        WriteProcessMemory(PHandle, (void*)(Address + BaseAddress), Input.data(), Input.size(), 0);
    }
    static void WriteShort(uint64_t Address, uint16_t Input)
    {
        vector<uint8_t> _write(2);

        for (uint64_t i = 0; i < 2; i++)
        {
            if (_bigEndian)
                _write[1 - i] = (Input >> (i * 8)) & 0xFF;

            else
                _write[i] = (Input >> (i * 8)) & 0xFF;
        }

        WriteBytes(Address, _write);
        _write.clear();
    }
    static void WriteInt(uint64_t Address, uint32_t Input)
    {
        vector<uint8_t> _write(4);

        for (uint64_t i = 0; i < 4; i++)
        {
            if (_bigEndian)
                _write[3 - i] = (Input >> (i * 8)) & 0xFF;

            else
                _write[i] = (Input >> (i * 8)) & 0xFF;
        }

        WriteBytes(Address, _write);
        _write.clear();
    }
    static void WriteLong(uint64_t Address, uint64_t Input)
    {
        vector<uint8_t> _write(8);

        for (uint64_t i = 0; i < 8; i++)
        {
            if (_bigEndian)
                _write[1 - i] = (Input >> (i * 8)) & 0xFF;

            else
                _write[i] = (Input >> (i * 8)) & 0xFF;
        }

        WriteBytes(Address, _write);
        _write.clear();
    }
    static void WriteFloat(uint64_t Address, float Input)
    {
        auto _value = *reinterpret_cast<uint32_t*>(&Input);
        WriteInt(Address, _value);
    }
    static void WriteBool(uint64_t Address, bool Input) { Input == true ? WriteByte(Address, 1) : WriteByte(Address, 0); }
    static void WriteString(uint64_t Address, string Input)
    {
        vector<uint8_t> _value(Input.begin(), Input.end());
        WriteBytes(Address, _value);
    }

    static uint8_t ReadByteAbsolute(uint64_t Address) { return ReadBytesAbsolute(Address, 1)[0]; }
    static vector<uint8_t> ReadBytesAbsolute(uint64_t Address, int Length)
    {
        vector<uint8_t> _buffer;
        _buffer.resize(Length);

        ReadProcessMemory(PHandle, (void*)(Address), _buffer.data(), Length, 0);
        return _buffer;
    }
    static uint16_t ReadShortAbsolute(uint64_t Address)
    {
        auto _buffer = ReadBytesAbsolute(Address, 2);

        if (_bigEndian)
            return (_buffer[0] << 8) | _buffer[1];

        else
            return (_buffer[1] << 8) | _buffer[0];
    }
    static uint32_t ReadIntAbsolute(uint64_t Address)
    {
        auto _buffer = ReadBytesAbsolute(Address, 4);

        if (_bigEndian)
            return (_buffer[0] << 24) | (_buffer[1] << 16) | (_buffer[2] << 8) | (_buffer[3]);

        else
            return (_buffer[3] << 24) | (_buffer[2] << 16) | (_buffer[1] << 8) | (_buffer[0]);
    }
    static uint64_t ReadLongAbsolute(uint64_t Address)
    {
        auto _buffer = ReadBytesAbsolute(Address, 8);

        if (_bigEndian)
            return ((uint64_t)_buffer[0] << 56) | ((uint64_t)_buffer[1] << 48) | ((uint64_t)_buffer[2] << 40) | ((uint64_t)_buffer[3] << 32) | ((uint64_t)_buffer[4] << 24) | ((uint64_t)_buffer[5] << 16) | ((uint64_t)_buffer[6] << 8) | ((uint64_t)_buffer[7]);

        else
            return ((uint64_t)_buffer[7] << 56) | ((uint64_t)_buffer[6] << 48) | ((uint64_t)_buffer[5] << 40) | ((uint64_t)_buffer[4] << 32) | ((uint64_t)_buffer[3] << 24) | ((uint64_t)_buffer[2] << 16) | ((uint64_t)_buffer[1] << 8) | ((uint64_t)_buffer[0]);
    }
    static float ReadFloatAbsolute(uint64_t Address)
    {
        auto _value = ReadIntAbsolute(Address);
        auto _return = *reinterpret_cast<float*>(&_value);
        return _return;
    }
    static bool ReadBoolAbsolute(uint64_t Address)
    {
        auto _value = ReadByteAbsolute(Address);
        return _value == 0 ? false : true;
    }
    static string ReadStringAbsolute(uint64_t Address, int Length)
    {
        auto _value = ReadBytesAbsolute(Address, Length);
        string _output(_value.begin(), _value.end());
        return _output;
    }

    static void WriteByteAbsolute(uint64_t Address, uint8_t Input)
    {
        WriteProcessMemory(PHandle, (void*)(Address), &Input, 1, 0);
    }
    static void WriteBytesAbsolute(uint64_t Address, vector<uint8_t> Input)
    {
        WriteProcessMemory(PHandle, (void*)(Address), Input.data(), Input.size(), 0);
    }
    static void WriteShortAbsolute(uint64_t Address, uint16_t Input)
    {
        vector<uint8_t> _write(2);

        for (uint64_t i = 0; i < 2; i++)
        {
            if (_bigEndian)
                _write[1 - i] = (Input >> (i * 8)) & 0xFF;

            else
                _write[i] = (Input >> (i * 8)) & 0xFF;
        }

        WriteBytesAbsolute(Address, _write);
        _write.clear();
    }
    static void WriteIntAbsolute(uint64_t Address, uint32_t Input)
    {
        vector<uint8_t> _write(4);

        for (uint64_t i = 0; i < 4; i++)
        {
            if (_bigEndian)
                _write[1 - i] = (Input >> (i * 8)) & 0xFF;

            else
                _write[i] = (Input >> (i * 8)) & 0xFF;
        }

        WriteBytesAbsolute(Address, _write);
        _write.clear();
    }
    static void WriteLongAbsolute(uint64_t Address, uint64_t Input)
    {
        vector<uint8_t> _write(8);

        for (uint64_t i = 0; i < 8; i++)
        {
            if (_bigEndian)
                _write[1 - i] = (Input >> (i * 8)) & 0xFF;

            else
                _write[i] = (Input >> (i * 8)) & 0xFF;
        }

        WriteBytesAbsolute(Address, _write);
        _write.clear();
    }
    static void WriteFloatAbsolute(uint64_t Address, float Input)
    {
        auto _value = *reinterpret_cast<uint32_t*>(&Input);
        WriteIntAbsolute(Address, _value);
    }
    static void WriteBoolAbsolute(uint64_t Address, bool Input) { Input == true ? WriteByteAbsolute(Address, 1) : WriteByteAbsolute(Address, 0); }
    static void WriteStringAbsolute(uint64_t Address, string Input)
    {
        vector<uint8_t> _value(Input.begin(), Input.end());
        WriteBytesAbsolute(Address, _value);
    }
    
    static void WriteExec(uint64_t Address, vector<uint8_t> Input)
    {
        WriteProcessMemory(PHandle, (void*)(Address + _execAddress), Input.data(), Input.size(), 0);
    }

    static uint64_t GetPointer(uint64_t Address, uint64_t Offset)
    {
        uint64_t _temp = ReadLong(Address);
        return _temp + Offset;
    }
    static uint64_t GetPointerAbsolute(uint64_t Address, uint64_t Offset)
    {
        uint64_t _temp = ReadLongAbsolute(Address);
        return _temp + Offset;
    }
};
#endif

/*
MIT License

Copyright (c) 2021 TopazTK

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/