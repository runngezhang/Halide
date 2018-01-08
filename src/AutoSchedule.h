#ifndef HALIDE_INTERNAL_AUTO_SCHEDULE_H
#define HALIDE_INTERNAL_AUTO_SCHEDULE_H

/** \file
 *
 * Defines the method that does automatic scheduling of Funcs within a pipeline.
 */

#include "Function.h"
#include "Target.h"

namespace Halide {

/** A struct representing the machine parameters to generate the auto-scheduled
 * code for. */
struct MachineParams {
    /** Maximum level of parallelism avalaible. */
    int parallelism;
    /** Size of the last-level cache (in KB). */
    int last_level_cache_size;
    /** Indicates how much more expensive is the cost of a load compared to
     * the cost of an arithmetic operation at last level cache. */
    int balance;

    explicit MachineParams(int32_t parallelism, int32_t llc, int32_t balance)
        : parallelism(parallelism), last_level_cache_size(llc), balance(balance) {}

    /** Convert the MachineParams into canonical string form. */
    EXPORT std::string to_string() const;

    /** Reconstruct a MachineParams from canonical string form. */
    EXPORT explicit MachineParams(const std::string &s);
};

namespace Internal {

/** Generate schedules for Funcs within a pipeline. The Funcs should not already
 * have specializations or schedules as the current auto-scheduler does not take
 * into account user-defined schedules or specializations. This applies the
 * schedules and returns a string representation of the schedules. The target
 * architecture is specified by 'target'. */
EXPORT std::string generate_schedules(const std::vector<Function> &outputs,
                                      const Target &target,
                                      const MachineParams &arch_params);

}
}

#endif
