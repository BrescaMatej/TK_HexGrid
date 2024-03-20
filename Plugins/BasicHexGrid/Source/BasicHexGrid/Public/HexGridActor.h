// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <CoreMinimal.h>

#include "HexTileActor.h"

#include <GameFramework/Actor.h>
#include "HexGridActor.generated.h"

UCLASS()
class BASICHEXGRID_API AHexGridActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHexGridActor();

	UFUNCTION(BlueprintCallable)
	void InitializeHexGrid(TArray<FHexRow> GridMap);

	UFUNCTION(BlueprintCallable)
	void CleanupHexGrid();

protected:
	UFUNCTION(BlueprintCallable)
	TArray<FHexRow> GenerateRectangleMap(int left = 0, int right = 10, int top = 0, int bottom = 8)
	{
		TArray<FHexRow> Out_;
		for (int r = top; r <= bottom; r++)
		{
			TArray<FCubeHex> OutHex_;
			int rOffset = FMath::Floor(r / 2.0f);
			for (int q = left - rOffset; q <= right - rOffset; q++)
			{
				OutHex_.Add(FCubeHex(q, r));
			}
			Out_.Add(OutHex_);
		}
		return Out_;
	}

	UFUNCTION(BlueprintCallable)
	TArray<FHexRow> GenerateHexMap(int Spread = 1)
	{
		TArray<FHexRow> Out_;
		for (int q = -Spread; q <= Spread; q++)
		{			
			TArray<FCubeHex> OutHex_;
			int r1 = FMath::Max(-Spread, -q - Spread);
			int r2 = FMath::Min(Spread, -q + Spread);
			for (int r = r1; r <= r2; r++)
			{
				OutHex_.Add(FCubeHex(r, q));
			}
			Out_.Add(OutHex_);
		}
		return Out_;
	}

	UFUNCTION(BlueprintCallable)
	TArray<FHexRow> GenerateRhombusMap(int NumRows, int RowLength)
	{
		TArray<FHexRow> Out_;
		for (int q = 0; q < NumRows; q++)
		{
			TArray<FCubeHex> OutHex_;
			for (int r = 0; r < RowLength; r++)
			{
				OutHex_.Add(FCubeHex(r, q));
			}
			Out_.Add(OutHex_);
		}
		return Out_;
	}


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHexTileActor> HexTileTemplate = nullptr;

	// For test purposes
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<FHexRow> HexagonMap
	//{
	//	FHexRow({FCubeHex(3,0), FCubeHex(4,0), FCubeHex(5,0), FCubeHex(6,0)}),
	//	FHexRow({FCubeHex(2,1), FCubeHex(3,1), FCubeHex(4,1), FCubeHex(5,1), FCubeHex(6,1)}),
	//	FHexRow({FCubeHex(1,2), FCubeHex(2,2), FCubeHex(3,2), FCubeHex(4,2), FCubeHex(5,2), FCubeHex(6,2)}),
	//	FHexRow({FCubeHex(0,3), FCubeHex(1,3), FCubeHex(2,3), FCubeHex(3,3), FCubeHex(4,3), FCubeHex(5,3), FCubeHex(6,3)}),
	//	FHexRow({FCubeHex(0,4), FCubeHex(1,4), FCubeHex(2,4), FCubeHex(3,4), FCubeHex(4,4), FCubeHex(5,4)}),
	//	FHexRow({FCubeHex(0,5), FCubeHex(1,5), FCubeHex(2,5), FCubeHex(3,5), FCubeHex(4,5)}),
	//	FHexRow({ FCubeHex(0,6), FCubeHex(1,6), FCubeHex(2,6), FCubeHex(3,6) })
	//};
};
