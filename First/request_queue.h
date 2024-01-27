#pragma once
#include "search_server.h"
#include <deque>

class RequestQueue {
public:

    explicit RequestQueue(const SearchServer& search_server);

    // сделаем "обёртки" для всех методов поиска, чтобы сохранять результаты для нашей статистики
    template <typename DocumentPredicate>
    void AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
    void AddFindRequest(const std::string& raw_query, DocumentStatus status);
    void AddFindRequest(const std::string& raw_query);
    int GetNoResultRequests() const;

private:

    struct QueryResult {
        bool actual;
    };
    std::deque<bool> requests_;
    int empty_req_;
    const static int min_in_day_ = 1440;
    const SearchServer& search_request_;
};
