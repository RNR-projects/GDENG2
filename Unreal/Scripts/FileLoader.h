// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FileLoader.generated.h"

/**
 * 
 */
UCLASS()
class GDENG_FINAL_API UFileLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = ".level files")
		static void LoadFile(FString filePath, TArray<FString>& OutNames, TArray<int>& OutTypes, TArray<FVector>& OutPositions, TArray<FRotator>& OutRotations,
			TArray<FVector>& OutScales, TArray<int>& OutHasRigidBodies);

	UFUNCTION(BlueprintCallable, Category = ".level files")
		static void SaveFile(FString filePath, TArray<AActor*> cubes, TArray<AActor*> planes, TArray<AActor*> spheres, TArray<AActor*> capsules);
};
