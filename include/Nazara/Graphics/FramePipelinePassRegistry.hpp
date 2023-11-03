// Copyright (C) 2023 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_GRAPHICS_FRAMEPIPELINEPASSREGISTRY_HPP
#define NAZARA_GRAPHICS_FRAMEPIPELINEPASSREGISTRY_HPP

#include <NazaraUtils/Prerequisites.hpp>
#include <Nazara/Graphics/FramePipelinePass.hpp>
#include <NazaraUtils/Algorithm.hpp>
#include <functional>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

namespace Nz
{
	class ParameterList;

	class FramePipelinePassRegistry
	{
		public:
			using Factory = std::function<std::unique_ptr<FramePipelinePass>(FramePipelinePass::PassData& passData, std::string passName, const ParameterList& parameters)>;

			FramePipelinePassRegistry() = default;
			FramePipelinePassRegistry(const FramePipelinePassRegistry&) = default;
			FramePipelinePassRegistry(FramePipelinePassRegistry&&) = default;
			~FramePipelinePassRegistry() = default;

			inline std::unique_ptr<FramePipelinePass> BuildPass(std::size_t passIndex, FramePipelinePass::PassData& passData, std::string passName, const ParameterList& parameters) const;

			inline std::size_t GetPassIndex(std::string_view passName) const;

			template<typename T> std::size_t RegisterPass(std::string passName);
			inline std::size_t RegisterPass(std::string passName, Factory factory);

			FramePipelinePassRegistry& operator=(const FramePipelinePassRegistry&) = default;
			FramePipelinePassRegistry& operator=(FramePipelinePassRegistry&&) = default;

		private:
			std::list<std::string> m_passNames; //< in order to allow std::string_view as a key in C++17 (keep std::string stable as well because of SSO)
			std::unordered_map<std::string_view, std::size_t> m_passIndex;
			std::vector<Factory> m_passFactories;
	};
}

#include <Nazara/Graphics/FramePipelinePassRegistry.inl>

#endif // NAZARA_GRAPHICS_FRAMEPIPELINEPASSREGISTRY_HPP