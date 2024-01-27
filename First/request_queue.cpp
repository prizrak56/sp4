#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server) : search_request_(search_server) {
}

template<typename DocumentPredicate>
void RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {}
void RequestQueue::AddFindRequest(const std::string& raw_query, DocumentStatus status) {}
void RequestQueue::AddFindRequest(const std::string& raw_query)
{
    if (requests_.empty() || requests_.size() < min_in_day_) {
        auto a = search_request_.FindTopDocuments(raw_query);
        if (a.empty() || a.size() == 0) {
            empty_req_ += 1;
            requests_.push_back(false);

        }
        else {
            requests_.push_back(true);
        }
    }
    else {
        if (requests_.front() == false) {
            empty_req_ -= 1;
        }
        requests_.pop_front();

        auto a = search_request_.FindTopDocuments(raw_query);
        if (a.empty() || a.size() == 0) {
            requests_.push_back(false);
            empty_req_ += 1;
        }
        else {
            requests_.push_back(true);
        }
    }
}

int RequestQueue::GetNoResultRequests() const
{
    return empty_req_;
}