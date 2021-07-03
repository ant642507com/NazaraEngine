// Copyright (C) 2020 Jérôme Leclercq
// This file is part of the "Nazara Development Kit"
// For conditions of distribution and use, see copyright notice in Prerequisites.hpp

#pragma once

#ifndef NDK_COMPONENTS_COLLISIONCOMPONENT3D_HPP
#define NDK_COMPONENTS_COLLISIONCOMPONENT3D_HPP

#include <Nazara/Physics3D/Collider3D.hpp>
#include <Nazara/Physics3D/RigidBody3D.hpp>
#include <NazaraSDK/Component.hpp>
#include <memory>

namespace Ndk
{
	class CollisionComponent3D;

	using CollisionComponent3DHandle = Nz::ObjectHandle<CollisionComponent3D>;

	class NDK_API CollisionComponent3D : public Component<CollisionComponent3D>
	{
		friend class PhysicsSystem3D;

		public:
			CollisionComponent3D(std::shared_ptr<Nz::Collider3D> geom = std::shared_ptr<Nz::Collider3D>());
			CollisionComponent3D(const CollisionComponent3D& collision);
			~CollisionComponent3D() = default;

			const std::shared_ptr<Nz::Collider3D>& GetGeom() const;

			void SetGeom(std::shared_ptr<Nz::Collider3D> geom);

			CollisionComponent3D& operator=(std::shared_ptr<Nz::Collider3D> geom);
			CollisionComponent3D& operator=(CollisionComponent3D&& collision) = delete;

			static ComponentIndex componentIndex;

		private:
			void InitializeStaticBody();
			Nz::RigidBody3D* GetStaticBody();

			void OnAttached() override;
			void OnComponentAttached(BaseComponent& component) override;
			void OnComponentDetached(BaseComponent& component) override;
			void OnDetached() override;
			void OnEntityDisabled() override;
			void OnEntityEnabled() override;

			std::unique_ptr<Nz::RigidBody3D> m_staticBody;
			std::shared_ptr<Nz::Collider3D> m_geom;
			bool m_bodyUpdated;
	};
}

#include <NazaraSDK/Components/CollisionComponent3D.inl>

#endif // NDK_COMPONENTS_COLLISIONCOMPONENT3D_HPP