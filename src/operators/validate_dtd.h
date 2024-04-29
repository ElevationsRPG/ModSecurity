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

#ifndef SRC_OPERATORS_VALIDATE_DTD_H_
#define SRC_OPERATORS_VALIDATE_DTD_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#ifdef WITH_LIBXML2
#include <libxml/xmlschemas.h>
#include <libxml/xpath.h>
#endif
#include <string>
#include <memory>
#include <utility>

#include "src/operators/operator.h"


namespace modsecurity {
namespace operators {

#ifdef WITH_LIBXML2
class XmlDtdPtrManager {
 public:
    /** @ingroup ModSecurity_Operator */
    explicit XmlDtdPtrManager(xmlDtdPtr dtd)
        : m_dtd(dtd) { }
    ~XmlDtdPtrManager() {
        if (m_dtd != NULL) {
            xmlFreeDtd(m_dtd);
            m_dtd = NULL;
        }
    }
    xmlDtdPtr get() const {return m_dtd;}
 private:
    xmlDtdPtr m_dtd; // The resource being managed
};
#endif

class ValidateDTD : public Operator {
 public:
    /** @ingroup ModSecurity_Operator */
    explicit ValidateDTD(std::unique_ptr<RunTimeString> param)
        : Operator("ValidateDTD", std::move(param)) { }
#ifdef WITH_LIBXML2
    bool evaluate(Transaction *transaction, const std::string  &str) override;
    bool init(const std::string &file, std::string *error) override;


    static void error_runtime(void *ctx, const char *msg, ...) {
        const Transaction *t = reinterpret_cast<Transaction *>(ctx);
        char buf[1024];
        std::string s;
        va_list args;

        va_start(args, msg);
        int len = vsnprintf(buf, sizeof(buf), msg, args);
        va_end(args);

        if (len > 0) {
            s = "XML Error: " + std::string(buf);
        }
        ms_dbg_a(t, 4, s);
    }


    static void warn_runtime(void *ctx, const char *msg, ...) {
        const Transaction *t = reinterpret_cast<Transaction *>(ctx);
        char buf[1024];
        std::string s;
        va_list args;

        va_start(args, msg);
        int len = vsnprintf(buf, sizeof(buf), msg, args);
        va_end(args);

        if (len > 0) {
            s = "XML Warning: " + std::string(buf);
        }
        ms_dbg_a(t, 4, s);
    }


    static void null_error(void *ctx, const char *msg, ...) { // cppcheck-suppress[constParameterPointer,constParameterCallback]
    }

 private:
    std::string m_resource;
#endif
};

}  // namespace operators
}  // namespace modsecurity


#endif  // SRC_OPERATORS_VALIDATE_DTD_H_
