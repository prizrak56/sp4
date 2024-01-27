#pragma once
#include <iostream>

using namespace std::literals::string_literals;

struct Document {
    Document() = default;

    Document(int id, double relevance, int rating)
        : id(id)
        , relevance(relevance)
        , rating(rating) {
    }

    int id = 0;
    double relevance = 0.0;
    int rating = 0;
};

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};

template <typename Iterator>
std::ostream& operator<<(std::ostream& out, const Document& range) {
    out << "{ document_id = " << range.id << ", relevance = "s << range.relevance << ", rating = "s << range.rating << " }"s;
    return out;
}