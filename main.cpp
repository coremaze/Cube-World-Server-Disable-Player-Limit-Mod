#include <windows.h>
unsigned int base;

extern "C" __declspec(dllexport) bool APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {

        case DLL_PROCESS_ATTACH:
            base = (unsigned int)GetModuleHandle(NULL);

            BYTE* location = (BYTE*)(base + 0x025859);

            DWORD dwOldProtection;
            VirtualProtect(location, 2, PAGE_EXECUTE_READWRITE, &dwOldProtection);
            location[0] = 0x90; //NOP
            location[1] = 0x90; //NOP
            VirtualProtect(location, 2, dwOldProtection, &dwOldProtection);

            break;

    }
    return true;
}
