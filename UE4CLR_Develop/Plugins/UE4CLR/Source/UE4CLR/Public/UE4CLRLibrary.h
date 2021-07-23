#pragma once
#include "CoreMinimal.h"
#include "UE4CLRLibrary.generated.h"

UCLASS(MinimalAPI)
class UUE4CLRLibrary : public UObject
{
	GENERATED_BODY()

public:
	UE4CLR_API static int Init();
	UE4CLR_API static float Square(float x = 0);
};