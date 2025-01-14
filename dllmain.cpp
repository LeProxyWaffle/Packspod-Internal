#include <Includes.h>
#include <fstream>
#include <ostream>
#include <string>
#include <Windows.h>
#include <process.h>
#include <tchar.h>
#include <vector>

bool isF7Pressed = false;

bool ifimfortnite()
{
    char processPath[MAX_PATH];
    GetModuleFileNameA(NULL, processPath, MAX_PATH);

    if (strstr(processPath, "FortniteClient-Win64-Shipping.exe") != NULL)
    {
        return true;
    }

    return false;
}

unsigned __stdcall CheckF7Pressed(void* lpParam)
{
    while (true)
    {
        if (GetAsyncKeyState(VK_F7) & 0x8000)
        {
            isF7Pressed = true;
            Beep(250, 250);
            break;
        }
        Sleep(100);
    }
    FortniteClientWin64Shipping = reinterpret_cast<uintptr_t>(GetModuleHandleA(0));

    if (SDK::UWorld* World = SDK::UObject::FindObject<SDK::UWorld*>(L"Frontend", reinterpret_cast<SDK::UObject*>(-1)))
    {
        SDK::MathLibrary = SDK::UObject::FindObject<SDK::UKismetMathLibrary*>(L"Engine.Default__KismetMathLibrary");

        // MessageBoxA(0, "Found MathLibrary", 0, 0);

        SDK::GameplayStatics = SDK::UObject::FindObject<SDK::UGameplayStatics*>(L"Engine.Default__GameplayStatics");

        // MessageBoxA(0, "Found GameplayStatics", 0, 0);

        SDK::FortLibrary = SDK::UObject::FindObject<SDK::UFortKismetLibrary*>(L"FortniteGame.Default__FortKismetLibrary");

        // MessageBoxA(0, "Found FortLibrary", 0, 0);

        SDK::SystemLibrary = SDK::UObject::FindObject<SDK::UKismetSystemLibrary*>(L"Engine.Default__KismetSystemLibrary");

        // MessageBoxA(0, "Found SystemLibrary", 0, 0);

        SDK::StringLibrary = SDK::UObject::FindObject<SDK::UKismetStringLibrary*>(L"Engine.Default__KismetStringLibrary");

       // MessageBox(0, L"Found Libraries", 0, 0);

        Implementation::Font = SDK::UObject::FindObject<SDK::UFont*>(L"Engine/EngineFonts/Roboto.Roboto", reinterpret_cast<SDK::UObject*>(-1));
        Implementation::Player = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.FortPlayerPawnAthena");
        Implementation::Weapon = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.FortWeaponRanged");
        Implementation::SupplyDrop = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.FortAthenaSupplyDrop");
        Implementation::Pickup = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.FortPickup");
        Implementation::Container = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.BuildingContainer");
        Implementation::Weakspot = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.BuildingWeakSpot");
        Implementation::Vehicle = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.FortAthenaVehicle");
        Implementation::Building = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.BuildingTrap");
        Implementation::Pickaxe = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.FortWeaponPickaxeAthena");
        Implementation::Projectile = SDK::UObject::FindObject<SDK::UObject*>(L"FortniteGame.FortProjectileBase");

        //MessageBox(0, L"Found Player Shit", 0, 0);

        Implementation::Material = SDK::UObject::FindObject<SDK::UObject*>(L"Engine.Material");
        Implementation::LeftShift = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName(L"LeftShift") }, 0 };
        Implementation::F8 = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName(L"F8") }, 0 };
        Implementation::RightMouseButton = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName(L"RightMouseButton") }, 0 };
        Implementation::LeftMouseButton = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName(L"LeftMouseButton") }, 0 };
        Implementation::Insert = SDK::FKey{ SDK::FName{ SDK::StringLibrary->Conv_StringToName(L"Insert") }, 0 };

        //MessageBox(0, L"Found Buttons", 0, 0);

        SDK::UGameInstance* OwningGameInstance = World->OwningGameInstance();
        //MessageBox(0, L"OwningGameInstance", 0, 0);
        SDK::ULocalPlayer* LocalPlayer = OwningGameInstance->LocalPlayers()[0];
        //MessageBox(0, L"LocalPlayer", 0, 0);
        SDK::UGameViewportClient* ViewportClient = LocalPlayer->ViewportClient();
        //MessageBox(0, L"ViewportClient", 0, 0);

        ViewportClientHook.Hook(ViewportClient, 115, DrawTransition, &DrawTransitionOriginal);
    }
    return 0;
}

BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {

        if (ifimfortnite()) {

            uintptr_t hThread = _beginthreadex(NULL, 0, CheckF7Pressed, NULL, 0, NULL);

            CloseHandle((HANDLE)hThread);


            return 0;
        }
        else
        {
            return 1;
        }
    }

    return TRUE;
}