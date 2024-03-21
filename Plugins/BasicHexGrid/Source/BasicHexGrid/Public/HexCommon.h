#pragma once
#include "CoreMinimal.h"
#include "HexCommon.generated.h"

UENUM(BlueprintType)
enum class EPointyHexDirection : uint8 {
	EE	UMETA(DisplayName = "East"),
	NE	UMETA(DisplayName = "North-East"),
	NW	UMETA(DisplayName = "North-West"),
	WW	UMETA(DisplayName = "West"),
	SW	UMETA(DisplayName = "South-Wast"),
	SE	UMETA(DisplayName = "South-East")
};

UENUM(BlueprintType)
enum class EPointyHexDiagonal : uint8 {
	NE	UMETA(DisplayName = "North-East"),
	NN	UMETA(DisplayName = "North"),
	NW	UMETA(DisplayName = "North-West"),
	SW	UMETA(DisplayName = "South-Wast"),
	SS	UMETA(DisplayName = "South"),
	SE	UMETA(DisplayName = "South-East")
};

/* Data structures*/
#pragma region STRUCTURES

/*
	Represents a single Cube coordinate hex.
	Initialized by q and r , s is calculated from (-q - r)
*/
USTRUCT(BlueprintType)
struct BASICHEXGRID_API FHex
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int q = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int r = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int s = 0;

	FHex() {}
	// Axial constructor
	FHex(int _q, int _r) : q(_q), r(_r), s(-_q - _r)
	{
	}

	// Cube constrcutor
	FHex(int _q, int _r, int _s) : q(_q), r(_r), s(_s)
	{
		check(q + r + s == 0); // Valid cube coords must sum back to 0
	}
};

/* Operator overloading for custom hex math */
#pragma region OPERATOR_OVERLOADS

FORCEINLINE bool operator == (const FHex& a, const FHex& b)
{
	return a.q == b.q && a.r == b.r && a.s == b.s;
}

FORCEINLINE bool operator!= (const FHex& a, const FHex& b)
{
	return !(a == b);
}

FORCEINLINE FHex operator + (const FHex& a, const FHex& b)
{
	return FHex(a.q + b.q, a.r + b.r);
}

FORCEINLINE FHex operator += (const FHex& a, const FHex& b)
{
	return a + b;
}

FORCEINLINE FHex operator - (const FHex& a, const FHex& b)
{
	return FHex(a.q - b.q, a.r - b.r);
}

FORCEINLINE FHex operator -= (const FHex& a, const FHex& b)
{
	return a - b;
}

FORCEINLINE FHex operator *= (const FHex& a, const FHex& b)
{
	return FHex(a.q * b.q, a.r * b.r);
}

#pragma endregion OPERATOR_OVERLOADS


/* Represents a single row of Hex cells */
USTRUCT(BlueprintType)
struct BASICHEXGRID_API FHexRow
{
	GENERATED_USTRUCT_BODY()

	FHexRow() {}
	FHexRow(TArray<FHex> InArr) : HexArr(InArr) 
	{
		check(IsValidRow());
	}

	const TArray<FHex> GetArr()
	{
		return HexArr;
	}

	int FindHex(FHex Hex)
	{
		int i = 0;
		for (FHex H : HexArr)
		{
			if (Hex == H)
			{
				return i;
			}
			i++;
		}
		return -1;
	}

	bool ContainsHex(FHex Hex)
	{
		return FindHex(Hex) >= 0;
	}

	bool IsValidRow()
	{
		if (HexArr.Num() <= 0) return false;
		FHex first = HexArr[0];
		for (FHex H : HexArr)
		{
			if (H.r != first.r) return false;
		}
		return true;
	}
private:
	TArray<FHex> HexArr{};
};


#pragma endregion STRUCTURES


/* Utility functions */
#pragma region UTILITIES

static FVector GetHexTilePositionWorldSpace(FHex Hex, float HexRadius = 50.0f, float ZOffset = 0.0f)
{
	float PosX = HexRadius * (FMath::Sqrt(3.0f) * Hex.q + FMath::Sqrt(3.0) / 2 * Hex.r);
	float PosY = HexRadius * 3.0 / 2 * Hex.r;
	return FVector(PosX, PosY, ZOffset);
}

static FHex GetHexDirectionVector(EPointyHexDirection Direction = EPointyHexDirection::EE)
{
	switch (Direction)
	{
	case EPointyHexDirection::EE:
		return FHex(1, 0, -1);
		break;
	case EPointyHexDirection::NE:
		return FHex(1, -1, 0);
		break;
	case EPointyHexDirection::NW:
		return FHex(0, -1, 1);
		break;
	case EPointyHexDirection::WW:
		return FHex(-1, 0, 1);
		break;
	case EPointyHexDirection::SW:
		return FHex(-1, 1, 0);
		break;
	case EPointyHexDirection::SE:
		return FHex(0, 1, -1);
		break;
	default:
		return FHex(0, 0, 0);
		break;
	};
}

static FHex GetHexNeighbor(FHex Hex, EPointyHexDirection Direction = EPointyHexDirection::EE)
{
	return Hex + GetHexDirectionVector(Direction);
}

static FHex GetHexDiagonalVector(EPointyHexDiagonal Direction = EPointyHexDiagonal::NE)
{
	switch (Direction)
	{
	case EPointyHexDiagonal::NE:
		return FHex(2, -1, -1);
		break;
	case EPointyHexDiagonal::NN:
		return FHex(1, -2, 1);
		break;
	case EPointyHexDiagonal::NW:
		return FHex(-1, -1, 2);
		break;
	case EPointyHexDiagonal::SW:
		return FHex(-2, 1, 1);
		break;
	case EPointyHexDiagonal::SS:
		return FHex(-1, 2, -1);
		break;
	case EPointyHexDiagonal::SE:
		return FHex(1, 1, -2);
		break;
	default:
		return FHex(0, 0, 0);
		break;
	};
}

static FHex GetHexDiagonal(FHex Hex, EPointyHexDiagonal Direction = EPointyHexDiagonal::NE)
{
	return Hex + GetHexDiagonalVector(Direction);
}

static int GetHexTileDistance(FHex a, FHex b)
{
	FHex vec = a - b;
	return (FMath::Abs(vec.q) + FMath::Abs(vec.q + vec.r) + FMath::Abs(vec.r)) / 2;
}

#pragma endregion UTILITIES


/* Example hex grid map generators */
#pragma region GRID_MAP_GENERATORS

static TArray<FHexRow> GenerateRectangleMap(int left = 0, int right = 10, int top = 0, int bottom = 8)
{
	TArray<FHexRow> Out_;
	for (int r = top; r <= bottom; r++)
	{
		TArray<FHex> OutHex_;
		int rOffset = FMath::Floor(r / 2.0f);
		for (int q = left - rOffset; q <= right - rOffset; q++)
		{
			OutHex_.Add(FHex(q, r));
		}
		Out_.Add(OutHex_);
	}
	return Out_;
}

static TArray<FHexRow> GenerateHexMap(int Spread = 1)
{
	TArray<FHexRow> Out_;
	for (int q = -Spread; q <= Spread; q++)
	{
		TArray<FHex> OutHex_;
		int r1 = FMath::Max(-Spread, -q - Spread);
		int r2 = FMath::Min(Spread, -q + Spread);
		for (int r = r1; r <= r2; r++)
		{
			OutHex_.Add(FHex(r, q));
		}
		Out_.Add(OutHex_);
	}
	return Out_;
}

static TArray<FHexRow> GenerateRhombusMap(int NumRows, int RowLength)
{
	TArray<FHexRow> Out_;
	for (int q = 0; q < NumRows; q++)
	{
		TArray<FHex> OutHex_;
		for (int r = 0; r < RowLength; r++)
		{
			OutHex_.Add(FHex(r, q));
		}
		Out_.Add(OutHex_);
	}
	return Out_;
}

#pragma endregion GRID_MAP_GENERATORS


/* Sanity checks */
#pragma region TEST

// Handwritten map For test purposes
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

#pragma endregion TEST


