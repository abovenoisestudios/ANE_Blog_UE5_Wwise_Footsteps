// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AkComponent.h" // Include this directive to access Ak Component.
#include "AkSwitchValue.h" // Include this directive to access Ak Switch Value.
#include "PhysicalMaterials/PhysicalMaterial.h" // Include this directive to work with Physical Materials.

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyUE5ProjectCharacter.generated.h"

UCLASS(config=Game)
class AMyUE5ProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	UQuartzSubsystem* Clock;

	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMyUE5ProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:
	
	#pragma region Wwise Footsteps Switch Declarations
	
	/** Ak Audio Component. Created in the class constructor. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Audio")
	UAkComponent* AkAudioComponent;

	/** A map data structure. Holds Physical Materials as keys and Ak Switch Values as values.
	 *	These values will set the correct switch in Wwise */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Audio")
	TMap<UPhysicalMaterial*, UAkSwitchValue*> PhysicalMaterialMap;
	
	/** Boolean property that sets AddOnScreenDebugMessage function on and makes the line trace visible in game. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Audio")
	bool bPrintDebug;

	/** Defines how long the line trace extends from our Character's location on the Z vector.
	 *	Positive numbers up vector, negative numbers down vector. -150cm set as default */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Audio")
	float Offset = -150;
	
	/**
	 * @brief Gets a reference of the floor's Physical Material with a Line trace.
	 * @param OffsetZ How far the line trace extends from our Character's center.
	 * @param bDebug Sets visibility for the Line trace. true: Visible, false: Not Visible
	 * @return A Physical Material reference
	 */
	UFUNCTION(BlueprintCallable, Category="Audio")
	UPhysicalMaterial* GetPhysicalMaterialByLineTrace(const float &OffsetZ, const bool &bDebug);

	/**
	 * @brief Gets a Physical Material reference and sets the appropriate Ak Switch value in Wwise. 
	 * @param HitPhysicalMaterial A Physical Material Reference
	 * @param bDebug Sets visibility for printing the current Physical Material to the screen. true: Visible, false: Not Visible
	 * @param DefaultAkSwitchValue Default Ak Switch value.
	 */
	UFUNCTION(BlueprintCallable, Category="Audio")
	void SetFootstepsSwitch(const UPhysicalMaterial* HitPhysicalMaterial, const bool &bDebug, const UAkSwitchValue* DefaultAkSwitchValue);

	#pragma endregion
	
	/** In case you want to implement On Landing Sounds. Callable from Blueprints*/
    UFUNCTION(BlueprintCallable)
    virtual void Landed(const FHitResult& Hit) override;
	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

