#ifndef API_CLIENT_REPORT_H
#define API_CLIENT_REPORT_H

#include "interfaces_handlers.h"

#include <iostream>

namespace calmgram::api_client::local {

    class ReportHandler : public network::IReportAboutMark { 
    public:
        ReportHandler() = default;
        ~ReportHandler() = default;
        
        bool Execute(std::string msg, bool is_marked, std::string const& token) override {
            std::cout << "msg: " << msg;
            if (is_marked) {
                std::cout << " must be censored" << std::endl;
            } else {
                std::cout << " must be uncensored" << std::endl;
            }
            return true;
        }
    };

} // namespace calmgram::api_client::local

#endif //API_CLIENT_REPORT_H