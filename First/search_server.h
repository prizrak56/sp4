#pragma once
#include "document.h"
#include "string_processing.h"
#include <map>
#include <vector>

const int MAX_RESULT_DOCUMENT_COUNT = 5;

class SearchServer {
public:

    template <typename StringContainer>
    explicit SearchServer(const StringContainer& stop_words);

    //  онструктор, принимающий текст стоп-слов
    explicit SearchServer(const std::string& stop_words_text);

    // ћетод дл€ добавлени€ документа
    void AddDocument(int document_id, const std::string& document, DocumentStatus status,const std::vector<int>& ratings);

    // Ўаблонный метод дл€ поиска документов по запросу
    template <typename DocumentPredicate>
    std::vector<Document> FindTopDocuments(const std::string& raw_query,DocumentPredicate document_predicate) const;

    // ћетод дл€ поиска документов по запросу и статусу
    std::vector<Document> FindTopDocuments(const std::string& raw_query, DocumentStatus status) const;

    // ћетод дл€ поиска документов по запросу с учетом статуса ACTUAL
    std::vector<Document> FindTopDocuments(const std::string& raw_query) const;

    // ћетод дл€ получени€ общего количества документов
    size_t GetDocumentCount() const;

    // ћетод дл€ получени€ идентификатора документа по индексу
    int GetDocumentId(int index) const;

    // ћетод дл€ поиска совпадений слов в запросе дл€ указанного документа
    std::tuple<std::vector<std::string>, DocumentStatus> MatchDocument(const std::string& raw_query,int document_id) const;

private:
    // —труктура данных дл€ хранени€ информации о документе
    struct DocumentData {
        int rating;
        DocumentStatus status;
    };
    const std::set<std::string> stop_words_;
    std::map<std::string, std::map<int, double>> word_to_document_freqs_;
    std::map<int, DocumentData> documents_;
    std::vector<int> document_ids_;

    // ћетод дл€ проверки, €вл€етс€ ли слово стоп-словом
    bool IsStopWord(const std::string& word) const;

    // ѕроверка, €вл€етс€ ли слово допустимым (не содержит спецсимволов)
    static bool IsValidWord(const std::string& word);

    // –азделение текста на слова, исключа€ стоп-слова и провер€€ их допустимость
    std::vector<std::string> SplitIntoWordsNoStop(const std::string& text) const;

    // ¬ычисление среднего рейтинга по вектору рейтингов
    static int ComputeAverageRating(const std::vector<int>& ratings);

    // —труктура дл€ представлени€ слова из запроса
    struct QueryWord {
        std::string data;
        bool is_minus;
        bool is_stop;
    };

    // јнализ слова из запроса
    QueryWord ParseQueryWord(const std::string& text) const;

    // —труктура дл€ представлени€ запроса
    struct Query {
        std::set<std::string> plus_words;
        std::set<std::string> minus_words;
    };
    // јнализ запроса
    Query ParseQuery(const std::string& text) const;

    // ¬ычисление обратной частоты документов дл€ слова
    double ComputeWordInverseDocumentFreq(const std::string& word) const;

    // ѕоиск всех документов, соответствующих запросу с учетом предиката
    template <typename DocumentPredicate>
    std::vector<Document> FindAllDocuments(const Query& query, DocumentPredicate document_predicate) const;
    
};
