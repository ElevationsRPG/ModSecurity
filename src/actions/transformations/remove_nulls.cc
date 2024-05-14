/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 - 2023 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */

#include "remove_nulls.h"


namespace modsecurity::actions::transformations {


bool RemoveNulls::transform(std::string &val, const Transaction *trans) const {
    size_t i = 0;
    std::string transformed_value;
    transformed_value.reserve(val.size());

    while (i < val.size()) {
        if (val.at(i) == '\0') {
            // do nothing; continue on to next char in original val
        } else {
            transformed_value += val.at(i);
        }
        i++;
    }

    const auto changed = transformed_value != val;
    val = transformed_value;
    return changed;
}


}  // namespace modsecurity::actions::transformations
