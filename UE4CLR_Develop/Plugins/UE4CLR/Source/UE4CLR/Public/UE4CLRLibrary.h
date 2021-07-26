#pragma once

#include "nethost.h"

#include "CoreMinimal.h"
#include "UE4CLRLibrary.generated.h"


UCLASS(MinimalAPI)
class UUE4CLRLibrary : public UObject
{
	GENERATED_BODY()

public:
	//Initialize and start the .NET Core runtime
	UE4CLR_API static int Init();

	//Call managed functions
	UE4CLR_API static float Square(float x = 0);
	struct lib_args
	{
		int number;
		const char_t* message;
		int64_t longnumber;
	};
	UE4CLR_API static lib_args PassAndReturnStruct(lib_args args);
};