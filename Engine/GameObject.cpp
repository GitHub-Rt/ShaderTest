#include "GameObject.h"
#include "SphereCollider.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	dead_(false), pParent_(parent), objectName_(name), pCollider_(nullptr)
{
	childList_.clear();
	if (parent)
	{
		transform_.pParent_ = &parent->transform_;
	}
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();

	RoundRobin(GetRootJob());

	//UpdateSub�̌Ăяo��(�C�e���[�^�[)
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	//ReleaseSub�̌Ăяo��(�C�e���[�^�[)
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->dead_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
	Release();
}

XMMATRIX GameObject::GetWorldMatrix()
{
	return transform_.GetWorldMatrix();
}

void GameObject::KillMe()
{
	dead_ = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

XMFLOAT3 GameObject::GetPosition(GameObject* pTarget)
{
	return pTarget->transform_.position_;
}


//�q�I�u�W�F�N�g�̒T��
GameObject* GameObject::FindChildObject(std::string objectName)
{
	if (objectName_ == objectName)
	{
		return this;
	}
	else
	{
		for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		{
			GameObject* obj = (*itr)->FindChildObject(objectName);
			if (obj != nullptr)
			{
				return obj;
			}
		}
	}
	return nullptr;
}


//�e�̎擾
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}
	return pParent_->GetRootJob();
}

//�e�I�u�W�F�N�g����q���X�g�̒T��
GameObject* GameObject::FindObject(std::string objectName)
{
	return GetRootJob()->FindChildObject(objectName);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

//�����蔻��
void GameObject::Collision(GameObject* pTarget)
{
	if (this == pTarget || pTarget->pCollider_ == nullptr)
	{
		return;
	}
	float x = transform_.position_.x - pTarget->transform_.position_.x;
	float y = transform_.position_.y - pTarget->transform_.position_.y;
	float z = transform_.position_.z - pTarget->transform_.position_.z;

	float radiusSum = pCollider_->GetRadius() + pTarget->pCollider_->GetRadius();


	if (x * x + y * y + z * z <= radiusSum * radiusSum)
	{
		OnCollision(pTarget);
	}
}

//�I�u�W�F�N�g�̑�������
void GameObject::RoundRobin(GameObject* pTarget)
{
	if (pCollider_ == nullptr)
	{
		return;
	}

	if (pTarget->pCollider_)
	{
		Collision(pTarget);
	}

	for (auto i = pTarget->childList_.begin(); i != pTarget->childList_.end(); i++)
	{
		RoundRobin(*i);
	}
}