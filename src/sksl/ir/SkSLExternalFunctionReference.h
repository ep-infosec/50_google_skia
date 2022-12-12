/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKSL_EXTERNALFUNCTIONREFERENCE
#define SKSL_EXTERNALFUNCTIONREFERENCE

#include "src/sksl/ir/SkSLExpression.h"
#include "src/sksl/ir/SkSLExternalFunction.h"

namespace SkSL {

/**
 * Represents an identifier referring to an ExternalFunction. This is an intermediate value:
 * ExternalFunctionReferences are always eventually replaced by ExternalFunctionCalls in valid
 * programs.
 */
class ExternalFunctionReference final : public Expression {
public:
    inline static constexpr Kind kIRNodeKind = Kind::kExternalFunctionReference;

    ExternalFunctionReference(Position pos, const ExternalFunction* ef)
        : INHERITED(pos, kIRNodeKind, &ef->type())
        , fFunction(*ef) {}

    const ExternalFunction& function() const {
        return fFunction;
    }

    std::string description(OperatorPrecedence) const override {
        return std::string(this->function().name());
    }

    std::unique_ptr<Expression> clone(Position pos) const override {
        return std::make_unique<ExternalFunctionReference>(pos, &this->function());
    }

private:
    const ExternalFunction& fFunction;

    using INHERITED = Expression;
};

}  // namespace SkSL

#endif
