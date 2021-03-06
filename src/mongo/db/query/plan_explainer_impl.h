/**
 *    Copyright (C) 2020-present MongoDB, Inc.
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the Server Side Public License, version 1,
 *    as published by MongoDB, Inc.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    Server Side Public License for more details.
 *
 *    You should have received a copy of the Server Side Public License
 *    along with this program. If not, see
 *    <http://www.mongodb.com/licensing/server-side-public-license>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the Server Side Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#pragma once

#include "mongo/db/exec/plan_stage.h"
#include "mongo/db/query/plan_explainer.h"

namespace mongo {
/**
 * A PlanExplainer implementation for classic execution plans.
 *
 * For classic execution plans all information required to generate explain output in various
 * formats is stored in the execution tree itself, so having access to the root stage of the
 * execution tree this PlanExplainer should obtain all plan details and execution stats.
 */
class PlanExplainerImpl final : public PlanExplainer {
public:
    PlanExplainerImpl(PlanStage* root) : _root{root} {}

    bool isMultiPlan() const final;
    std::string getPlanSummary() const final;
    void getSummaryStats(PlanSummaryStats* statsOut) const final;
    PlanStatsDetails getWinningPlanStats(ExplainOptions::Verbosity verbosity) const final;
    std::vector<PlanStatsDetails> getRejectedPlansStats(
        ExplainOptions::Verbosity verbosity) const final;
    std::vector<PlanStatsDetails> getCachedPlanStats(const PlanCacheEntry::DebugInfo&,
                                                     ExplainOptions::Verbosity) const final;

private:
    PlanStage* const _root;
};

/**
 * Retrieves the first stage of a given type from the plan tree, or nullptr if no such stage is
 * found.
 */
PlanStage* getStageByType(PlanStage* root, StageType type);
}  // namespace mongo
