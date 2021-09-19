// Fill out your copyright notice in the Description page of Project Settings.


#include "FileLoader.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UFileLoader::LoadFile(FString filePath, TArray<FString>& OutNames, TArray<int>& OutTypes, TArray<FVector>& OutPositions, TArray<FRotator>& OutRotations,
							TArray<FVector>& OutScales, TArray<int>& OutHasRigidBodies)
{
	FString OutText;
	TArray<FString> OutArray;
	if (FFileHelper::LoadFileToString(OutText, *filePath))
	{
		OutText.ParseIntoArray(OutArray, TEXT("\n"));
		TArray<FString> rowContents;

		int index = 0;

		for (int i = 0; i < OutArray.Num(); i++)
		{
			if (index == 0)
			{
				OutNames.Add(OutArray[i]);
				index++;
			}
			else if (index == 1)
			{
				OutArray[i].ParseIntoArray(rowContents, TEXT(" "));
				OutTypes.Add(FCString::Atoi(*rowContents[1]));
				index++;
			}
			else if (index == 2)
			{
				OutArray[i].ParseIntoArray(rowContents, TEXT(" "));
				OutPositions.Add(FVector(FCString::Atof(*rowContents[1]), -FCString::Atof(*rowContents[3]), FCString::Atof(*rowContents[2])));
				index++;
			}
			else if (index == 3)
			{
				OutArray[i].ParseIntoArray(rowContents, TEXT(" "));
				OutRotations.Add(FRotator::MakeFromEuler(FVector(FMath::RadiansToDegrees(FCString::Atof(*rowContents[1])),
					FMath::RadiansToDegrees(FCString::Atof(*rowContents[3])), FMath::RadiansToDegrees(FCString::Atof(*rowContents[2])))));
				index++;
			}
			else if (index == 4)
			{
				OutArray[i].ParseIntoArray(rowContents, TEXT(" "));
				OutScales.Add(FVector(FCString::Atof(*rowContents[1]), FCString::Atof(*rowContents[3]), FCString::Atof(*rowContents[2])));
				index++;
			}
			else if (index == 5)
			{
				OutArray[i].ParseIntoArray(rowContents, TEXT(" "));
				OutHasRigidBodies.Add(FCString::Atoi(*rowContents[1]));
				index = 0;
			}
		}
	}
}

void UFileLoader::SaveFile(FString filePath, TArray<AActor*> cubes, TArray<AActor*> planes, TArray<AActor*> spheres, TArray<AActor*> capsules)
{
	FString output = "";
	for (int i = 0; i < cubes.Num(); i++)
	{
		output += cubes[i]->GetActorLabel() + "\n";
		FVector pos = cubes[i]->GetActorLocation();
		FVector rot = cubes[i]->GetActorRotation().Euler();
		FVector scale = cubes[i]->GetActorScale();

		output += "Type: 1\n";
		output += "Position: " + FString::SanitizeFloat(pos.X / 100.0f) + " " + FString::SanitizeFloat(pos.Z / 100.0f) + " " + 
			FString::SanitizeFloat(-pos.Y / 100.0f) + "\n";
		output += "Rotation: " + FString::SanitizeFloat(FMath::DegreesToRadians(rot.X)) + " " + 
			FString::SanitizeFloat(FMath::DegreesToRadians(rot.Z)) + " " + FString::SanitizeFloat(FMath::DegreesToRadians(rot.Y)) + "\n";
		output += "Scale: " + FString::SanitizeFloat(scale.X) + " " + FString::SanitizeFloat(scale.Z) + " " + FString::SanitizeFloat(scale.Y) + "\n";

		if (cubes[i]->GetActorEnableCollision())
		{
			output += "HasRigidBody: 1\n";
		}
		else
		{
			output += "HasRigidBody: 0\n";
		}
	}
	for (int i = 0; i < planes.Num(); i++)
	{
		output += planes[i]->GetActorLabel() + "\n";
		FVector pos = planes[i]->GetActorLocation();
		FVector rot = planes[i]->GetActorRotation().Euler();
		FVector scale = planes[i]->GetActorScale();

		output += "Type: 2\n";
		output += "Position: " + FString::SanitizeFloat(pos.X / 100.0f) + " " + FString::SanitizeFloat(pos.Z / 100.0f) + " " +
			FString::SanitizeFloat(pos.Y / 100.0f) + "\n";
		output += "Rotation: " + FString::SanitizeFloat(FMath::DegreesToRadians(rot.X)) + " " +
			FString::SanitizeFloat(FMath::DegreesToRadians(rot.Z)) + " " + FString::SanitizeFloat(FMath::DegreesToRadians(rot.Y)) + "\n";
		output += "Scale: " + FString::SanitizeFloat(scale.X) + " " + FString::SanitizeFloat(scale.Z) + " " + FString::SanitizeFloat(scale.Y) + "\n";

		if (planes[i]->GetActorEnableCollision())
		{
			output += "HasRigidBody: 1\n";
		}
		else
		{
			output += "HasRigidBody: 0\n";
		}
	}
	for (int i = 0; i < spheres.Num(); i++)
	{
		output += spheres[i]->GetActorLabel() + "\n";
		FVector pos = spheres[i]->GetActorLocation();
		FVector rot = spheres[i]->GetActorRotation().Euler();
		FVector scale = spheres[i]->GetActorScale();

		output += "Type: 3\n";
		output += "Position: " + FString::SanitizeFloat(pos.X / 100.0f) + " " + FString::SanitizeFloat(pos.Z / 100.0f) + " " +
			FString::SanitizeFloat(pos.Y / 100.0f) + "\n";
		output += "Rotation: " + FString::SanitizeFloat(FMath::DegreesToRadians(rot.X)) + " " +
			FString::SanitizeFloat(FMath::DegreesToRadians(rot.Z)) + " " + FString::SanitizeFloat(FMath::DegreesToRadians(rot.Y)) + "\n";
		output += "Scale: " + FString::SanitizeFloat(scale.X) + " " + FString::SanitizeFloat(scale.Z) + " " + FString::SanitizeFloat(scale.Y) + "\n";

		if (spheres[i]->GetActorEnableCollision())
		{
			output += "HasRigidBody: 1\n";
		}
		else
		{
			output += "HasRigidBody: 0\n";
		}
	}
	for (int i = 0; i < capsules.Num(); i++)
	{
		output += capsules[i]->GetActorLabel() + "\n";
		FVector pos = capsules[i]->GetActorLocation();
		FVector rot = capsules[i]->GetActorRotation().Euler();
		FVector scale = capsules[i]->GetActorScale();

		output += "Type: 4\n";
		output += "Position: " + FString::SanitizeFloat(pos.X / 100.0f) + " " + FString::SanitizeFloat(pos.Z / 100.0f) + " " +
			FString::SanitizeFloat(pos.Y / 100.0f) + "\n";
		output += "Rotation: " + FString::SanitizeFloat(FMath::DegreesToRadians(rot.X)) + " " +
			FString::SanitizeFloat(FMath::DegreesToRadians(rot.Z)) + " " + FString::SanitizeFloat(FMath::DegreesToRadians(rot.Y)) + "\n";
		output += "Scale: " + FString::SanitizeFloat(scale.X) + " " + FString::SanitizeFloat(scale.Z) + " " + FString::SanitizeFloat(scale.Y) + "\n";

		if (capsules[i]->GetActorEnableCollision())
		{
			output += "HasRigidBody: 1\n";
		}
		else
		{
			output += "HasRigidBody: 0\n";
		}
	} 

	if (filePath.StartsWith("C:\\"))
		FFileHelper::SaveStringToFile(output, *filePath);
	else
		FFileHelper::SaveStringToFile(output, *(FPaths::ProjectSavedDir() + filePath));
}
