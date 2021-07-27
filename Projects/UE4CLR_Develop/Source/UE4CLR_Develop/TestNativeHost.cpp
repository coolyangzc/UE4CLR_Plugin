// Fill out your copyright notice in the Description page of Project Settings.


#include "TestNativeHost.h"
#include "UE4CLRLibrary.h"

#define LOGONSCREEN GEngine->AddOnScreenDebugMessage

// Sets default values for this component's properties
UTestNativeHost::UTestNativeHost()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestNativeHost::BeginPlay()
{
	Super::BeginPlay();

	//Initialize and start the .NET Core runtime
	UE_LOG(LogTemp, Warning, TEXT("Before Init()"));
	UUE4CLRLibrary::Init();
	UE_LOG(LogTemp, Warning, TEXT("After Init()"));

	// Test calling managed functions
	UE_LOG(LogTemp, Warning, TEXT("Calling Lib.Square(x) in ManagedLib.dll: 0.2^2 = %f"), UUE4CLRLibrary::Square(0.2));
	LOGONSCREEN(-1, 20.f, FColor::Yellow, 
		FString::Printf(TEXT("Calling Lib.Square(x) in ManagedLib.dll: 0.2^2 = %f"), UUE4CLRLibrary::Square(0.2)));
	UE_LOG(LogTemp, Warning, TEXT("Calling Lib.Square(x) in ManagedLib.dll: 0.4^2 = %f"), UUE4CLRLibrary::Square(0.4));
	LOGONSCREEN(-1, 20.f, FColor::Yellow,
		FString::Printf(TEXT("Calling Lib.Square(x) in ManagedLib.dll: 0.4^2 = %f"), UUE4CLRLibrary::Square(0.4)));
	
	UUE4CLRLibrary::lib_args send_args
	{
		0,
		L"Sent Message",
		10
	};
	UUE4CLRLibrary::lib_args recv_args = UUE4CLRLibrary::PassAndReturnStruct(send_args);

	FString output_msg = FString::Printf(TEXT("Calling Lib.FunctionReturnStruct(lib_args) in ManagedLib.dll: \
		send args(0, \"Sent Message\", 10);   returned args: (%d, \"%s\", %lld)"),
		recv_args.number, recv_args.message, recv_args.longnumber);
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *output_msg);
	LOGONSCREEN(-1, 20.f, FColor::Yellow, output_msg);
}


// Called every frame
void UTestNativeHost::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

