// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "HexCommon.h"
#include "BasicHexBlueprintFunctionLibrary.generated.h"

/**
 * General blueprint function library for Basic Hex plugin
 */
UCLASS()
class BASICHEXGRID_API UBasicHexBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/* blueprint math operator overloads */
#pragma region HEX MATH BLUEPRINT NODE

	/** Adds two Hex coordinates (A + B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Hex + Hex", CompactNodeTitle = "+", ScriptMethod = "HexPlusHex", ScriptOperator = "+;+=", Keywords = "add combine + plus"), Category = "BasicHexGrid|Math")
	static FHex K2_Add_HexHex(FHex a, FHex b)
	{ return a + b; }

	/** Subtracts Two hex coordinates (A - B) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Hex - Hex", CompactNodeTitle = "-", ScriptMethod = "HexMinusHex", ScriptOperator = "-;-=", Keywords = "subtract minus - "), Category = "BasicHexGrid|Math")
	static FHex K2_Subtract_HexHex(FHex a, FHex b)
	{ return a - b; }

#pragma endregion HEX MATH BLUEPRINT NODE


	/* Utilities */
#pragma region HEX UTILITIES
	
	/*
	Returns a FVector of world-space XY coordinate of the Hex tile.
	The radius is a length of the regular Hex edge. 
	The Z offset is arbitrary value that can be passed in by the user.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BasicHexGrid|Utility")
	static FVector K2_GetHexTilePositionWorldSpace(FHex Hex, float HexRadius = 50.0f, float ZOffset = 0.0f)
	{
		return GetHexTilePositionWorldSpace(Hex, HexRadius , ZOffset);
	}

	/** Returns the direction vector in Hex units*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BasicHexGrid|Utility")
	static FHex K2_GetHexDirectionVector(EPointyHexDirection Direction = EPointyHexDirection::EE)
	{
		return GetHexDirectionVector(Direction);
	}

	/** Returns the Neighbour of the Hex in the provided direction*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BasicHexGrid|Utility")
	static FHex K2_GetHexNeighbor(FHex Hex, EPointyHexDirection Direction = EPointyHexDirection::EE)
	{
		return GetHexNeighbor(Hex, Direction);
	}

	/** Returns a diagonal vector in Hex units */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BasicHexGrid|Utility")
	static FHex K2_GetHexDiagonalVector(EPointyHexDiagonal Direction = EPointyHexDiagonal::NE)
	{
		return GetHexDiagonalVector(Direction);
	}

	/** Returns a diagonal Hex neighbor in the provided direction */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BasicHexGrid|Utility")
	static FHex K2_GetHexDiagonal(FHex Hex, EPointyHexDiagonal Direction = EPointyHexDiagonal::NE)
	{
		return GetHexDiagonal(Hex, Direction);
	}

	/** Returns a distance between two Hex tiles */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "BasicHexGrid|Utility")
	static int K2_GetHexTileDistance(FHex a, FHex b)
	{
		return GetHexTileDistance(a, b);
	}

#pragma endregion HEX UTILITIES


	/* map grid generators */
#pragma region HEX MAP GRID GENERATOR BLUEPRINT NODES
	
	/** Generates a rectangular Hex map from given offsets */
	UFUNCTION(BlueprintCallable, Category = "BasicHexGrid|Generator")
	static TArray<FHexRow> K2_GenerateRectangleMap(int left = 0, int right = 10, int top = 0, int bottom = 8)
	{
		return GenerateRectangleMap(left, right, top, bottom);
	}

	/** Generates a hexagonal map spreading from center hex using Spread parameter as tile unit radius. */
	UFUNCTION(BlueprintCallable, Category = "BasicHexGrid|Generator")
	static TArray<FHexRow> K2_GenerateHexMap(int Spread = 1)
	{
		return GenerateHexMap(Spread);
	}

	/** Generates a rhombus map using number of rows and row length. */
	UFUNCTION(BlueprintCallable, Category = "BasicHexGrid|Generator")
	static TArray<FHexRow> K2_GenerateRhombusMap(int NumRows, int RowLength)
	{
		return GenerateRhombusMap(NumRows, RowLength);
	}

#pragma endregion HEX MAP GRID GENERATOR BLUEPRINT NODES



};