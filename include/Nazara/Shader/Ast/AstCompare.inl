// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Shader module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Shader/Ast/AstCompare.hpp>
#include <stdexcept>
#include <Nazara/Shader/Debug.hpp>

namespace Nz::ShaderAst
{
	inline bool Compare(const Expression& lhs, const Expression& rhs)
	{
		if (lhs.GetType() != rhs.GetType())
			return false;

		switch (lhs.GetType())
		{
		case NodeType::None: break;

#define NAZARA_SHADERAST_EXPRESSION(Node) case NodeType::Node: return Compare(static_cast<const Node&>(lhs), static_cast<const Node&>(lhs));
#include <Nazara/Shader/Ast/AstNodeList.hpp>

		default: throw std::runtime_error("unexpected node type");
		}

		return true;
	}

	inline bool Compare(const Statement& lhs, const Statement& rhs)
	{
		if (lhs.GetType() != rhs.GetType())
			return false;

		switch (lhs.GetType())
		{
		case NodeType::None: break;

#define NAZARA_SHADERAST_STATEMENT(Node) case NodeType::Node: return Compare(static_cast<const Node&>(lhs), static_cast<const Node&>(lhs));
#include <Nazara/Shader/Ast/AstNodeList.hpp>

		default: throw std::runtime_error("unexpected node type");
		}

		return false;
	}

	template<typename T>
	bool Compare(const T& lhs, const T& rhs)
	{
		return lhs == rhs;
	}

	template<typename T, std::size_t S>
	bool Compare(const std::array<T, S>& lhs, const std::array<T, S>& rhs)
	{
		for (std::size_t i = 0; i < S; ++i)
		{
			if (!Compare(lhs[i], rhs[i]))
				return false;
		}

		return true;
	}

	template<typename T>
	bool Compare(const std::vector<T>& lhs, const std::vector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		for (std::size_t i = 0; i < lhs.size(); ++i)
		{
			if (!Compare(lhs[i], rhs[i]))
				return false;
		}

		return true;
	}

	template<typename T>
	bool Compare(const AttributeValue<T>& lhs, const AttributeValue<T>& rhs)
	{
		if (!Compare(lhs.HasValue(), rhs.HasValue()))
			return false;

		if (!Compare(lhs.IsResultingValue(), rhs.IsResultingValue()))
			return false;

		if (!Compare(lhs.IsExpression(), rhs.IsExpression()))
			return false;

		if (lhs.IsExpression())
		{
			if (!Compare(lhs.GetExpression(), rhs.GetExpression()))
				return false;
		}
		else if (lhs.IsResultingValue())
		{
			if (!Compare(lhs.GetResultingValue(), rhs.GetResultingValue()))
				return false;
		}

		return true;
	}

	inline bool Compare(const BranchStatement::ConditionalStatement& lhs, const BranchStatement::ConditionalStatement& rhs)
	{
		if (!Compare(lhs.condition, rhs.condition))
			return false;

		if (!Compare(lhs.statement, rhs.statement))
			return false;

		return true;
	}

	inline bool Compare(const DeclareExternalStatement::ExternalVar& lhs, const DeclareExternalStatement::ExternalVar& rhs)
	{
		if (!Compare(lhs.bindingIndex, rhs.bindingIndex))
			return false;

		if (!Compare(lhs.bindingSet, rhs.bindingSet))
			return false;

		if (!Compare(lhs.name, rhs.name))
			return false;

		if (!Compare(lhs.type, rhs.type))
			return false;

		return true;
	}

	inline bool Compare(const DeclareFunctionStatement::Parameter& lhs, const DeclareFunctionStatement::Parameter& rhs)
	{
		if (!Compare(lhs.name, rhs.name))
			return false;

		if (!Compare(lhs.type, rhs.type))
			return false;

		return true;
	}

	inline bool Compare(const StructDescription& lhs, const StructDescription& rhs)
	{
		if (!Compare(lhs.layout, rhs.layout))
			return false;

		if (!Compare(lhs.name, rhs.name))
			return false;

		if (!Compare(lhs.members, rhs.members))
			return false;

		return true;
	}

	inline bool Compare(const StructDescription::StructMember& lhs, const StructDescription::StructMember& rhs)
	{
		if (!Compare(lhs.builtin, rhs.builtin))
			return false;

		if (!Compare(lhs.cond, rhs.cond))
			return false;

		if (!Compare(lhs.locationIndex, rhs.locationIndex))
			return false;

		if (!Compare(lhs.name, rhs.name))
			return false;

		if (!Compare(lhs.type, rhs.type))
			return false;

		return true;
	}

	inline bool Compare(const AccessIdentifierExpression& lhs, const AccessIdentifierExpression& rhs)
	{
		if (!Compare(*lhs.expr, *rhs.expr))
			return false;

		if (!Compare(lhs.identifiers, rhs.identifiers))
			return false;

		return true;
	}

	inline bool Compare(const AccessIndexExpression& lhs, const AccessIndexExpression& rhs)
	{
		if (!Compare(*lhs.expr, *rhs.expr))
			return false;

		if (!Compare(lhs.indices, rhs.indices))
			return false;

		return true;
	}

	inline bool Compare(const AssignExpression& lhs, const AssignExpression& rhs)
	{
		if (!Compare(lhs.op, rhs.op))
			return false;

		if (!Compare(lhs.left, rhs.left))
			return false;

		if (!Compare(lhs.right, rhs.right))
			return false;

		return true;
	}

	inline bool Compare(const BinaryExpression& lhs, const BinaryExpression& rhs)
	{
		if (!Compare(lhs.op, rhs.op))
			return false;

		if (!Compare(lhs.left, rhs.left))
			return false;

		if (!Compare(lhs.right, rhs.right))
			return false;

		return true;
	}

	inline bool Compare(const CallFunctionExpression& lhs, const CallFunctionExpression& rhs)
	{
		if (!Compare(lhs.targetFunction, rhs.targetFunction))
			return false;

		if (!Compare(lhs.parameters, rhs.parameters))
			return false;

		return true;
	}

	inline bool Compare(const CallMethodExpression& lhs, const CallMethodExpression& rhs)
	{
		if (!Compare(lhs.methodName, rhs.methodName))
			return false;

		if (!Compare(lhs.object, rhs.object))
			return false;

		if (!Compare(lhs.parameters, rhs.parameters))
			return false;

		return true;
	}

	inline bool Compare(const CastExpression& lhs, const CastExpression& rhs)
	{
		if (!Compare(lhs.targetType, rhs.targetType))
			return false;

		if (!Compare(lhs.expressions, rhs.expressions))
			return false;

		return true;
	}

	inline bool Compare(const ConditionalExpression& lhs, const ConditionalExpression& rhs)
	{
		if (!Compare(lhs.condition, rhs.condition))
			return false;

		if (!Compare(lhs.truePath, rhs.truePath))
			return false;

		if (!Compare(lhs.falsePath, rhs.falsePath))
			return false;

		return true;
	}

	inline bool Compare(const ConstantExpression& lhs, const ConstantExpression& rhs)
	{
		if (!Compare(lhs.constantId, rhs.constantId))
			return false;

		return true;
	}

	inline bool Compare(const ConstantValueExpression& lhs, const ConstantValueExpression& rhs)
	{
		if (!Compare(lhs.value, rhs.value))
			return false;

		return true;
	}

	inline bool Compare(const IdentifierExpression& lhs, const IdentifierExpression& rhs)
	{
		if (!Compare(lhs.identifier, rhs.identifier))
			return false;

		return true;
	}

	inline bool Compare(const IntrinsicExpression& lhs, const IntrinsicExpression& rhs)
	{
		if (!Compare(lhs.intrinsic, rhs.intrinsic))
			return false;

		if (!Compare(lhs.parameters, rhs.parameters))
			return false;

		return true;
	}

	inline bool Compare(const SwizzleExpression& lhs, const SwizzleExpression& rhs)
	{
		if (!Compare(lhs.componentCount, rhs.componentCount))
			return false;

		if (!Compare(lhs.expression, rhs.expression))
			return false;

		if (!Compare(lhs.components, rhs.components))
			return false;

		return true;
	}

	inline bool Compare(const VariableExpression& lhs, const VariableExpression& rhs)
	{
		if (!Compare(lhs.variableId, rhs.variableId))
			return false;

		return true;
	}

	inline bool Compare(const UnaryExpression& lhs, const UnaryExpression& rhs)
	{
		if (!Compare(lhs.op, rhs.op))
			return false;

		if (!Compare(lhs.expression, rhs.expression))
			return false;

		return true;
	}

	inline bool Compare(const BranchStatement& lhs, const BranchStatement& rhs)
	{
		if (!Compare(lhs.isConst, rhs.isConst))
			return false;

		if (!Compare(lhs.elseStatement, rhs.elseStatement))
			return false;

		if (!Compare(lhs.condStatements, rhs.condStatements))
			return false;

		return true;
	}

	inline bool Compare(const DeclareConstStatement& lhs, const DeclareConstStatement& rhs)
	{
		if (!Compare(lhs.name, rhs.name))
			return false;

		if (!Compare(lhs.type, rhs.type))
			return false;

		if (!Compare(lhs.expression, rhs.expression))
			return false;

		return true;
	}

	inline bool Compare(const DeclareExternalStatement& lhs, const DeclareExternalStatement& rhs)
	{
		if (!Compare(lhs.bindingSet, rhs.bindingSet))
			return false;

		if (!Compare(lhs.externalVars, rhs.externalVars))
			return false;

		return true;
	}

	inline bool Compare(const DeclareFunctionStatement& lhs, const DeclareFunctionStatement& rhs)
	{
		if (!Compare(lhs.depthWrite, rhs.depthWrite))
			return false;

		if (!Compare(lhs.earlyFragmentTests, rhs.earlyFragmentTests))
			return false;

		if (!Compare(lhs.entryStage, rhs.entryStage))
			return false;

		if (!Compare(lhs.name, rhs.name))
			return false;

		if (!Compare(lhs.parameters, rhs.parameters))
			return false;

		if (!Compare(lhs.returnType, rhs.returnType))
			return false;

		if (!Compare(lhs.statements, rhs.statements))
			return false;

		return true;
	}

	inline bool Compare(const DeclareOptionStatement& lhs, const DeclareOptionStatement& rhs)
	{
		if (!Compare(lhs.optName, rhs.optName))
			return false;

		if (!Compare(lhs.optType, rhs.optType))
			return false;

		if (!Compare(lhs.defaultValue, rhs.defaultValue))
			return false;

		return true;
	}

	inline bool Compare(const DeclareStructStatement& lhs, const DeclareStructStatement& rhs)
	{
		if (!Compare(lhs.description, rhs.description))
			return false;

		return true;
	}

	inline bool Compare(const DeclareVariableStatement& lhs, const DeclareVariableStatement& rhs)
	{
		if (!Compare(lhs.varName, rhs.varName))
			return false;

		if (!Compare(lhs.varType, rhs.varType))
			return false;

		if (!Compare(lhs.initialExpression, rhs.initialExpression))
			return false;

		return true;
	}

	inline bool Compare(const DiscardStatement& /*lhs*/, const DiscardStatement& /*rhs*/)
	{
		return true;
	}

	inline bool Compare(const ExpressionStatement& lhs, const ExpressionStatement& rhs)
	{
		if (!Compare(lhs.expression, rhs.expression))
			return false;

		return true;
	}

	bool Compare(const ForEachStatement& lhs, const ForEachStatement& rhs)
	{
		if (!Compare(lhs.varName, rhs.varName))
			return false;

		if (!Compare(lhs.unroll, rhs.unroll))
			return false;

		if (!Compare(lhs.expression, rhs.expression))
			return false;

		if (!Compare(lhs.statement, rhs.statement))
			return false;

		return true;
	}

	inline bool Compare(const MultiStatement& lhs, const MultiStatement& rhs)
	{
		if (!Compare(lhs.statements, rhs.statements))
			return false;

		return true;
	}

	inline bool Compare(const NoOpStatement& /*lhs*/, const NoOpStatement& /*rhs*/)
	{
		return true;
	}

	inline bool Compare(const ReturnStatement& lhs, const ReturnStatement& rhs)
	{
		if (!Compare(lhs.returnExpr, rhs.returnExpr))
			return false;

		return true;
	}

	inline bool Compare(const WhileStatement& lhs, const WhileStatement& rhs)
	{
		if (!Compare(lhs.unroll, rhs.unroll))
			return false;

		if (!Compare(lhs.condition, rhs.condition))
			return false;

		if (!Compare(lhs.body, rhs.body))
			return false;

		return true;
	}
}

#include <Nazara/Shader/DebugOff.hpp>