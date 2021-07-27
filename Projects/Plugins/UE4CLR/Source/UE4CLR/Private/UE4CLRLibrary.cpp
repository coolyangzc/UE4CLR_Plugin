#include "UE4CLRLibrary.h"

// Standard headers
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>

#include "coreclr_delegates.h"
#include "hostfxr.h"
#include "nethost.h"

#include "Windows/WindowsHWrapper.h"

#define STR(s) L ## s
#define CH(c) L ## c
#define DIR_SEPARATOR L'\\'
#define LOGONSCREEN GEngine->AddOnScreenDebugMessage

namespace globals
{
    bool been_loaded = false;
    std::basic_string<char_t> lib_path;
	hostfxr_initialize_for_runtime_config_fn init_fptr;
	hostfxr_get_runtime_delegate_fn get_delegate_fptr;
	hostfxr_close_fn close_fptr;
	load_assembly_and_get_function_pointer_fn load_assembly_and_get_function_pointer = nullptr;
}

void* load_library(const char_t* path)
{
    HMODULE h = ::LoadLibraryW(path);
    assert(h != nullptr);
    return (void*)h;
}
void* get_export(void* h, const char* name)
{
    void* f = ::GetProcAddress((HMODULE)h, name);
    assert(f != nullptr);
    return f;
}

bool load_hostfxr()
{
    FString hostfxr_path = FPaths::ProjectPluginsDir() + TEXT("UE4CLR/Runtime/Win64/host/fxr/5.0.7/hostfxr.dll");
    UE_LOG(LogTemp, Warning, TEXT("hostfxr_path: %s"), *hostfxr_path);
    LOGONSCREEN(-1, 10.f, FColor::White, FString::Printf(TEXT("hostfxr_path: %s"), *hostfxr_path));
    // Load hostfxr and get desired exports

    void* lib = load_library(*hostfxr_path);
    globals::init_fptr = (hostfxr_initialize_for_runtime_config_fn)get_export(lib, "hostfxr_initialize_for_runtime_config");
    globals::get_delegate_fptr = (hostfxr_get_runtime_delegate_fn)get_export(lib, "hostfxr_get_runtime_delegate");
    globals::close_fptr = (hostfxr_close_fn)get_export(lib, "hostfxr_close");

    return (globals::init_fptr && globals::get_delegate_fptr && globals::close_fptr);
}

load_assembly_and_get_function_pointer_fn get_dotnet_load_assembly(const char_t* config_path)
{
    // Load .NET Core
    void* load_assembly_and_get_function_pointer = nullptr;
    hostfxr_handle cxt = nullptr;
    int rc = globals::init_fptr(config_path, nullptr, &cxt);
    if (rc != 0 || cxt == nullptr)
    {
        std::cerr << "Init failed: " << std::hex << std::showbase << rc << std::endl;
        globals::close_fptr(cxt);
        return nullptr;
    }

    // Get the load assembly function pointer
    rc = globals::get_delegate_fptr(
        cxt,
        hdt_load_assembly_and_get_function_pointer,
        &load_assembly_and_get_function_pointer);
    if (rc != 0 || load_assembly_and_get_function_pointer == nullptr)
        std::cerr << "Get delegate failed: " << std::hex << std::showbase << rc << std::endl;

    globals::close_fptr(cxt);
    return (load_assembly_and_get_function_pointer_fn)load_assembly_and_get_function_pointer;
}

int UUE4CLRLibrary::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("In Init()"));

    if (!globals::been_loaded)
    {
        if (!load_hostfxr())
        {
            assert(false && "Failure: load_hostfxr()");
            return EXIT_FAILURE;
        }
        UE_LOG(LogTemp, Warning, TEXT("After load_hostfxr()"));

        FString config_path = FPaths::ProjectDir() + TEXT("Managed/Build/ManagedLib.runtimeconfig.json");
        UE_LOG(LogTemp, Warning, TEXT("config_path: %s"), *config_path);
        LOGONSCREEN(-1, 10.f, FColor::White, FString::Printf(TEXT("config_path: %s"), *config_path));

        globals::load_assembly_and_get_function_pointer = get_dotnet_load_assembly(*config_path);
        assert(globals::load_assembly_and_get_function_pointer != nullptr && "Failure: get_dotnet_load_assembly()");
        
        globals::lib_path = *(FPaths::ProjectDir() + TEXT("Managed/Build/ManagedLib.dll"));
        globals::been_loaded = true;
    }
    UE_LOG(LogTemp, Warning, TEXT("lib_path: %s"), globals::lib_path.c_str());
    LOGONSCREEN(-1, 10.f, FColor::White, FString::Printf(TEXT("lib_path: %s"), globals::lib_path.c_str()));
    
    return EXIT_SUCCESS;
}

float UUE4CLRLibrary::Square(float x)
{
    typedef float (CORECLR_DELEGATE_CALLTYPE* square_entry_point_fn)(float x);
    square_entry_point_fn square = nullptr;
    int rc = globals::load_assembly_and_get_function_pointer(
        globals::lib_path.c_str(),
        STR("ManagedLib.Lib, ManagedLib"),
        STR("Square"), //method_name
        STR("ManagedLib.Lib+SquareDelegate, ManagedLib"), //delegate_type_name
        nullptr,
        (void**)&square);
    assert(rc == 0 && print_messages != nullptr && "Failure: load_assembly_and_get_function_pointer()");
    return square(x);
}

UUE4CLRLibrary::lib_args UUE4CLRLibrary::PassAndReturnStruct(UUE4CLRLibrary::lib_args args)
{
    typedef lib_args(CORECLR_DELEGATE_CALLTYPE* func_return_struct_entry_point_fn)(lib_args x);
    func_return_struct_entry_point_fn func_return_struct = nullptr;
    int rc = globals::load_assembly_and_get_function_pointer(
        globals::lib_path.c_str(),
        STR("ManagedLib.Lib, ManagedLib"),
        STR("FunctionReturnStruct"), //method_name
        STR("ManagedLib.Lib+FunctionReturnStructDelegate, ManagedLib"), //delegate_type_name
        nullptr,
        (void**)&func_return_struct);
    assert(rc == 0 && square != nullptr && "Failure: load_assembly_and_get_function_pointer()");
    return func_return_struct(args);
}