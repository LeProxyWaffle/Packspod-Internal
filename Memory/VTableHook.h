#pragma once
#include <Windows.h>

class ShadowVMT
{
public:
	template <typename Type>
    bool Hook(SDK::UObject* Address, int Index, void* Function, Type* Original)
    {
        //MessageBoxW(0, L"Starting Hook function", L"Debug", MB_OK);

        this->VirtualTable = *(uintptr_t**)(Address);
        //MessageBoxW(0, L"VirtualTable acquired", L"Debug", MB_OK);

        if (this->LastHookedFunctionAddress && this->LastHookedFunctionIndex)
        {
            if (this->LastHookedFunctionAddress == this->VirtualTable[this->LastHookedFunctionIndex])
            {
                //MessageBoxW(0, L"Already hooked, skipping", L"Debug", MB_OK);
                return false;
            }
        }

        if (reinterpret_cast<void*>(this->VirtualTable[Index]) != Function)
        {
            //MessageBoxW(0, L"Checking VirtualTable Index for mismatch", L"Debug", MB_OK);

            while (this->VirtualTable[this->VTableSize])
            {
                this->VTableSize++;
            }
           // MessageBoxW(0, (L"VTable size: " + std::to_wstring(this->VTableSize)).c_str(), L"Debug", MB_OK);

            if (Index < this->VTableSize)
            {
                //MessageBoxW(0, L"Allocating new VTable", L"Debug", MB_OK);
                this->AllocatedVTable = reinterpret_cast<uintptr_t*>(SDK::FMemory::Malloc(this->VTableSize * sizeof(uintptr_t), 0x10));

                for (int i = 0; i < this->VTableSize; i++)
                {
                    this->AllocatedVTable[i] = this->VirtualTable[i];
                }
                //MessageBoxW(0, L"Copied old VTable to new VTable", L"Debug", MB_OK);

                *Original = reinterpret_cast<Type>(this->VirtualTable[Index]);
                //MessageBoxW(0, L"Original function stored", L"Debug", MB_OK);

                this->AllocatedVTable[Index] = reinterpret_cast<uintptr_t>(Function);
                //MessageBoxW(0, L"Hook function set in VTable", L"Debug", MB_OK);

                *(uintptr_t**)(Address) = this->AllocatedVTable;
                //MessageBoxW(0, L"VTable replaced", L"Debug", MB_OK);

                this->LastHookedFunctionAddress = reinterpret_cast<uintptr_t>(Function);
                this->LastHookedFunctionIndex = Index;
                MessageBoxW(0, L"Press OK in lobby.", L"Debug", MB_OK);

                return true;
            }
        }
        MessageBoxW(0, L"Hook failed, either already hooked or invalid index", L"Debug", MB_OK);
        return false;
    }
 
	template <typename Type>
	void Unhook( SDK::UObject* Address , Type* Original )
	{
		if ( this->VirtualTable && this->LastHookedFunctionIndex )
		{
			uintptr_t* VirtualTable = *( uintptr_t** ) ( Address );

			VirtualTable[ this->LastHookedFunctionIndex ] = reinterpret_cast< uintptr_t >( *Original );

			*( uintptr_t** ) Address = VirtualTable;

			SDK::FMemory::Free( VirtualTable );

			this->LastHookedFunctionAddress = 0x0;
			this->LastHookedFunctionIndex = -1;
		}
	}

private:
	uintptr_t* VirtualTable;
	uintptr_t* AllocatedVTable;
	int VTableSize;

	uintptr_t LastHookedFunctionAddress;
	int LastHookedFunctionIndex;
};