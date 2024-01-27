#include "request_queue.h"

std::ostream& operator << (std::ostream& os, const std::vector<Document>& obj) {

    os << "{ document_id = " << obj[0].id << ", relevance = " << obj[0].relevance << ", rating = " << obj[0].rating << " }";
    if (obj.size() > 1) {
        os << "{ document_id = " << obj[1].id << ", relevance = " << obj[1].relevance << ", rating = " << obj[1].rating << " }";
    }

    return os;
}

int main() {
    SearchServer search_server("and in at");
    RequestQueue request_queue(search_server);
    search_server.AddDocument(1, "curly cat curly tail", DocumentStatus::ACTUAL, { 7, 2, 7 });
    search_server.AddDocument(2, "curly dog and fancy collar", DocumentStatus::ACTUAL, { 1, 2, 3 });
    search_server.AddDocument(3, "big cat fancy collar ", DocumentStatus::ACTUAL, { 1, 2, 8 });
    search_server.AddDocument(4, "big dog sparrow Eugene", DocumentStatus::ACTUAL, { 1, 3, 2 });
    search_server.AddDocument(5, "big dog sparrow Vasiliy", DocumentStatus::ACTUAL, { 1, 1, 1 });
    // 1439 �������� � ������� �����������
    for (int i = 0; i < 1439; ++i) {
        request_queue.AddFindRequest("empty request");
    }
    // ��� ��� 1439 �������� � ������� �����������
    request_queue.AddFindRequest("curly dog");
    // ����� �����, ������ ������ ������, 1438 �������� � ������� �����������
    request_queue.AddFindRequest("big collar");
    // ������ ������ ������, 1437 �������� � ������� �����������
    request_queue.AddFindRequest("sparrow");
    std::cout << "Total empty requests: " << request_queue.GetNoResultRequests() << std::endl;
    return 0;
}