#include "FWeaponBase.h"
#include "Components/SphereComponent.h"  // 包含球体碰撞组件
#include "Components/WidgetComponent.h"  // 包含UI小部件组件
#include "Animation/AnimationAsset.h"  // 动画资源相关
#include "Components/SkeletalMeshComponent.h"  // 骨骼网格组件
#include "BlasterLearing/AFragLib/Character/FCharacter.h"

// 武器基类的构造函数
AFWeaponBase::AFWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);  
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); 
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);  

	
	//ui
	PickUpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUpWidget"));
	SetRootComponent(PickUpWidget);
	
}

// 游戏开始时调用
void AFWeaponBase::BeginPlay()
{
	if (HasAuthority())
    {
		AreaSphere ->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	 	AreaSphere ->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	 	AreaSphere ->OnComponentBeginOverlap.AddDynamic(this,&AFWeaponBase::OnSphereOverlap);
		AreaSphere -> OnComponentEndOverlap.AddDynamic(this,&AFWeaponBase::OnSphereEndOverlap);
    }
}

// 每帧更新函数（已禁用）
void AFWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFWeaponBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFCharacter* character = Cast<AFCharacter>(OtherActor);
	if (character && PickUpWidget)
	{
		character->SetOverlappingWeapon(this);  // 显示拾取UI
	}
}

void AFWeaponBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFCharacter* character = Cast<AFCharacter>(OtherActor);
	if (character && PickUpWidget)
	{
		character->SetOverlappingWeapon(nullptr);  // 显示拾取UI
	}
}
