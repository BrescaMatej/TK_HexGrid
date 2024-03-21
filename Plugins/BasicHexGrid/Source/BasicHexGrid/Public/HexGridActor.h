// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>

#include "HexCommon.h"
#include "HexGridActor.generated.h"

class AHexTileActor;

/*
* An actual hex grid using Cube/Axial coordinates
* Implementation is inspired by https://www.redblobgames.com/grids/hexagons/
*
* Currently it's a signle Array of Hex Row structure and methods for cleanup and initialization.
* Motivation for the grid actor is to handle non visual grid logic.
*/

UCLASS()
class BASICHEXGRID_API AHexGridActor : public AActor
{
	GENERATED_BODY()

public:
	AHexGridActor();

	UFUNCTION(BlueprintCallable, Category = "BasicHexGrid|HexGrid")
	void InitializeHexGrid(TArray<FHexRow> GridMap);

	UFUNCTION(BlueprintCallable, Category = "BasicHexGrid|HexGrid")
	void CleanupHexGrid();

	UFUNCTION(BlueprintPure, Category = "BasicHexGrid|HexGrid")
	TArray<FHexRow> GetHexGridMap() { return HexGridMap; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHexTileActor> HexTileTemplate = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FHexRow> HexGridMap = {};
};
