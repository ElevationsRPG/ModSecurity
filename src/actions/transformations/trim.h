/*
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 - 2021 Trustwave Holdings, Inc. (http://www.trustwave.com/)
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

#ifndef SRC_ACTIONS_TRANSFORMATIONS_TRIM_H_
#define SRC_ACTIONS_TRANSFORMATIONS_TRIM_H_

#include "transformation.h"

namespace modsecurity::actions::transformations {

class Trim : public Transformation {
 public:
    explicit Trim(const std::string &action);

    bool transform(std::string &value, const Transaction *trans) const override;

    static std::string *ltrim(std::string *s);
    static std::string *rtrim(std::string *s);
    static std::string *trim(std::string *s);
};

}  // namespace modsecurity::actions::transformations

#endif  // SRC_ACTIONS_TRANSFORMATIONS_TRIM_H_
