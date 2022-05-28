#ifndef API_CLIENT_REPORT_HENDLER_H
#define API_CLIENT_REPORT_HENDLER_H

#include "interfaces_handlers.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace calmgram::api_client::network {

    class ReportHandler : public IReportAboutMark{
    private:
        std::string request_;
        
    public:
        ReportHandler() = default;
        ~ReportHandler() = default;
        
        bool Execute(std::string msg, bool is_marked, std::string const& token) override;

        bool DataToRequest(std::string msg, bool is_marked, std::string const& token);
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_REPORT_HENDLER_H