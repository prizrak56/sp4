﻿#include "request_queue.h"

using namespace std::literals::string_literals;

int main() {
    SearchServer search_server("and in at"s);
    RequestQueue request_queue(search_server);
    search_server.AddDocument(1, "curly cat curly tail"s, DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "curly dog and fancy collar"s, DocumentStatus::ACTUAL, { 1, 2, 3 });
    search_server.AddDocument(3, "big cat fancy collar "s, DocumentStatus::ACTUAL, { 1, 2, 8 });
    search_server.AddDocument(4, "big dog sparrow Eugene"s, DocumentStatus::ACTUAL, { 1, 3, 2 });
    search_server.AddDocument(5, "big dog sparrow Vasiliy"s, DocumentStatus::ACTUAL, { 1, 1, 1 });
    // 1439 çàïðîñîâ ñ íóëåâûì ðåçóëüòàòîì
    for (int i = 0; i < 1439; ++i) {
        request_queue.AddFindRequest("empty request"s);
    }
    // âñå åùå 1439 çàïðîñîâ ñ íóëåâûì ðåçóëüòàòîì
    request_queue.AddFindRequest("curly dog"s);
    // íîâûå ñóòêè, ïåðâûé çàïðîñ óäàëåí, 1438 çàïðîñîâ ñ íóëåâûì ðåçóëüòàòîì
    request_queue.AddFindRequest("big collar"s);
    // ïåðâûé çàïðîñ óäàëåí, 1437 çàïðîñîâ ñ íóëåâûì ðåçóëüòàòîì
    request_queue.AddFindRequest("sparrow"s);
    std::cout << "Total empty requests: "s << request_queue.GetNoResultRequests() << std::endl;
    return 0;
}