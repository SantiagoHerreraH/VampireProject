// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProyectoVampiroCharacter.h"
#include "ProyectoVampiro/Widgets/LifeBar.h"
#include "ProyectoVampiro/Widgets/ExperienceBar.h"

#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AProyectoVampiroCharacter

AProyectoVampiroCharacter::AProyectoVampiroCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create life component & widget.
	m_LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));
	m_LifeComponent->maxLife = { 100.f };

	LifeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LifeBar"));
	LifeWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Create experience widget
	ExperienceBarClass=nullptr;
	XPBar=nullptr;

	
}
void AProyectoVampiroCharacter::BeginPlay() 
{
	Super::BeginPlay();

	ULifeBar* LifeBar = Cast<ULifeBar>(LifeWidgetComponent->GetUserWidgetObject());
	LifeBar->SetOwnerCharacter(this);
	
	this->m_LifeComponent->OnKillEntity.BindUObject(this, &AProyectoVampiroCharacter::KillPlayer);

	if(IsLocallyControlled() && ExperienceBarClass)
	{
		XPBar = CreateWidget<UExperienceBar>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ExperienceBarClass);
		XPBar->AddToViewport();
		XPBar->SetExperienceBar(currentXP,maxXP,currentLevel);
	}
}

const float AProyectoVampiroCharacter::GetCurrentLife()
{
	return this->m_LifeComponent->currentLife;
}

const float AProyectoVampiroCharacter::GetMaxLife()
{
	return this->m_LifeComponent->maxLife;
}

void AProyectoVampiroCharacter::ReduceLife_Implementation(float amount)
{
	this->m_LifeComponent->ReduceLife(amount);
}

void AProyectoVampiroCharacter::RestoreLife_Implementation(float amount)
{
	this->m_LifeComponent->RestoreLife(amount);
}

void AProyectoVampiroCharacter::StartDamageOverTime_Implementation(float damage, float time)
{
	this->m_LifeComponent->StartDamageOverTime(damage, time);
}

void AProyectoVampiroCharacter::StopDamageOverTime_Implementation()
{
	this->m_LifeComponent->StopDamageOverTime();
}

void AProyectoVampiroCharacter::AddExperience_Implementation(float xp)
{
	if(currentLevel==maxLevel)
		return;
	
	this->currentXP += xp;
	if (this->currentXP >= this->maxXP) {
		this->LevelUp();
	}
	XPBar->SetExperienceBar(currentXP,maxXP,currentLevel);
}

void AProyectoVampiroCharacter::LevelUp_Implementation()
{
	currentXP = 0.f;
	maxXP+=maxXP*0.2f;
	if (this->currentLevel < this->maxLevel) 
	{
		this->currentLevel++;
	}

	XPBar->SetExperienceBar(currentXP,maxXP,currentLevel);
}


void AProyectoVampiroCharacter::KillPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("Muertisimo"));
	DisableInput(GetWorld()->GetFirstPlayerController());
	GetMesh()->SetSimulatePhysics(true);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProyectoVampiroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AProyectoVampiroCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AProyectoVampiroCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	/*PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AProyectoVampiroCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AProyectoVampiroCharacter::LookUpAtRate);*/

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AProyectoVampiroCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AProyectoVampiroCharacter::TouchStopped);
}

void AProyectoVampiroCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AProyectoVampiroCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AProyectoVampiroCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AProyectoVampiroCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AProyectoVampiroCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AProyectoVampiroCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
