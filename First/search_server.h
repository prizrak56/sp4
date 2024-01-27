#pragma once
#include "document.h"
#include "string_processing.h"
#include <map>
#include <vector>
#include <algorithm>

const int MAX_RESULT_DOCUMENT_COUNT = 5;

class SearchServer {
public:

    template <typename StringContainer>
    explicit SearchServer(const StringContainer& stop_words) : stop_words_(MakeUniqueNonEmptyStrings(stop_words))
    {
        if (!all_of(stop_words_.begin(), stop_words_.end(), IsValidWord)) {
            throw std::invalid_argument("Some of stop words are invalid");
        }
    }

    // Êîíñòðóêòîð, ïðèíèìàþùèé òåêñò ñòîï-ñëîâ
    explicit SearchServer(const std::string& stop_words_text);

    // Ìåòîä äëÿ äîáàâëåíèÿ äîêóìåíòà
    void AddDocument(int document_id, const std::string& document, DocumentStatus status, const std::vector<int>& ratings);

    // Øàáëîííûé ìåòîä äëÿ ïîèñêà äîêóìåíòîâ ïî çàïðîñó
    template <typename DocumentPredicate>
    std::vector<Document> FindTopDocuments(const std::string& raw_query, DocumentPredicate document_predicate) const;

    // Ìåòîä äëÿ ïîèñêà äîêóìåíòîâ ïî çàïðîñó è ñòàòóñó
    std::vector<Document> FindTopDocuments(const std::string& raw_query, DocumentStatus status) const;

    // Ìåòîä äëÿ ïîèñêà äîêóìåíòîâ ïî çàïðîñó ñ ó÷åòîì ñòàòóñà ACTUAL
    std::vector<Document> FindTopDocuments(const std::string& raw_query) const;

    // Ìåòîä äëÿ ïîëó÷åíèÿ îáùåãî êîëè÷åñòâà äîêóìåíòîâ
    size_t GetDocumentCount() const;

    // Ìåòîä äëÿ ïîëó÷åíèÿ èäåíòèôèêàòîðà äîêóìåíòà ïî èíäåêñó
    int GetDocumentId(int index) const;

    // Ìåòîä äëÿ ïîèñêà ñîâïàäåíèé ñëîâ â çàïðîñå äëÿ óêàçàííîãî äîêóìåíòà
    std::tuple<std::vector<std::string>, DocumentStatus> MatchDocument(const std::string& raw_query, int document_id) const;

private:
    // Ñòðóêòóðà äàííûõ äëÿ õðàíåíèÿ èíôîðìàöèè î äîêóìåíòå
    struct DocumentData {
        int rating;
        DocumentStatus status;
    };
    const std::set<std::string> stop_words_;
    std::map<std::string, std::map<int, double>> word_to_document_freqs_;
    std::map<int, DocumentData> documents_;
    std::vector<int> document_ids_;

    // Ìåòîä äëÿ ïðîâåðêè, ÿâëÿåòñÿ ëè ñëîâî ñòîï-ñëîâîì
    bool IsStopWord(const std::string& word) const;

    // Ïðîâåðêà, ÿâëÿåòñÿ ëè ñëîâî äîïóñòèìûì (íå ñîäåðæèò ñïåöñèìâîëîâ)
    static bool IsValidWord(const std::string& word);

    // Ðàçäåëåíèå òåêñòà íà ñëîâà, èñêëþ÷àÿ ñòîï-ñëîâà è ïðîâåðÿÿ èõ äîïóñòèìîñòü
    std::vector<std::string> SplitIntoWordsNoStop(const std::string& text) const;

    // Âû÷èñëåíèå ñðåäíåãî ðåéòèíãà ïî âåêòîðó ðåéòèíãîâ
    static int ComputeAverageRating(const std::vector<int>& ratings);

    // Ñòðóêòóðà äëÿ ïðåäñòàâëåíèÿ ñëîâà èç çàïðîñà
    struct QueryWord {
        std::string data;
        bool is_minus;
        bool is_stop;
    };

    // Àíàëèç ñëîâà èç çàïðîñà
    QueryWord ParseQueryWord(const std::string& text) const;

    // Ñòðóêòóðà äëÿ ïðåäñòàâëåíèÿ çàïðîñà
    struct Query {
        std::set<std::string> plus_words;
        std::set<std::string> minus_words;
    };
    // Àíàëèç çàïðîñà
    Query ParseQuery(const std::string& text) const;

    // Âû÷èñëåíèå îáðàòíîé ÷àñòîòû äîêóìåíòîâ äëÿ ñëîâà
    double ComputeWordInverseDocumentFreq(const std::string& word) const;

    // Ïîèñê âñåõ äîêóìåíòîâ, ñîîòâåòñòâóþùèõ çàïðîñó ñ ó÷åòîì ïðåäèêàòà
    template <typename DocumentPredicate>
    std::vector<Document> FindAllDocuments(const Query& query, DocumentPredicate document_predicate) const;

};