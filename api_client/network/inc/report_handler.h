#ifndef API_CLIENT_REPORT_HENDLER_H
#define API_CLIENT_REPORT_HENDLER_H

#include "interfaces_handlers.h"

namespace calmgram::api_client::network {

    class ReportHandler : public IReportAboutMark{
    private:
        std::string request_;
        
    public:
        ReportHandler() = default;
        ~ReportHandler() = default;
        
        bool Execute(std::string msg, bool is_marked) override;

        bool DataToRequest(std::string msg, bool is_marked);
    };

} // namespace calmgram::api_client::network

#endif //API_CLIENT_REPORT_HENDLER_H