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


	UE_LOG(LogTemp, Warning, TEXT("Before Init"));
	UUE4CLRLibrary::Init();
	UE_LOG(LogTemp, Warning, TEXT("After Init"));

	// Test calling managed functions
	UE_LOG(LogTemp, Warning, TEXT("Calling Lib.square(x) in ManagedLib.dll: 0.2^2 = %f"), UUE4CLRLibrary::Square(0.2));
	LOGONSCREEN(-1, 10.f, FColor::Yellow, 
		FString::Printf(TEXT("Calling Lib.square(x) in ManagedLib.dll: 0.2^2 = %f"), UUE4CLRLibrary::Square(0.2)));
	UE_LOG(LogTemp, Warning, TEXT("Calling Lib.square(x) in ManagedLib.dll: 0.4^2 = %f"), UUE4CLRLibrary::Square(0.4));
	LOGONSCREEN(-1, 10.f, FColor::Yellow,
		FString::Printf(TEXT("Calling Lib.square(x) in ManagedLib.dll: 0.4^2 = %f"), UUE4CLRLibrary::Square(0.4)));
	// ...
	
}


// Called every frame
void UTestNativeHost::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

