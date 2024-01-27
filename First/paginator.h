#pragma once
#include "document.h"
#include "search_server.h"

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) : begin_(begin), end_(end), page_size_(page_size) {


        size_p = distance(begin, end);
        if (size_p % page_size != 0) {
            size_p = size_p / page_size;
            size_p += 1;
        }
        else {
            size_p = size_p / page_size;
        }

        docsort_.resize(size_p);
        while (begin != end) {

            alldoc_.push_back(*begin);
            ++begin;

        }


    }

    auto Sort() {
        int x = 0;
        int lists = 0;
        int convert_pageS = static_cast<int>(page_size_);
        for (int i = 0; i < alldoc_.size(); i++) {
            if (x < convert_pageS) {
                docsort_[lists].insert(docsort_[lists].begin() + x, alldoc_[i]);
                ++x;
            }
            if (x == convert_pageS) {
                x = 0;
                lists += 1;
            }
        }
        return docsort_;
    }

    auto GetAllDoc() {
        return alldoc_;
    }



private:
    int size_p = 0;
    Document last;
    std::vector<Document> alldoc_;
    std::vector<std::vector<Document>> docsort_;
    Iterator begin_, end_;
    size_t page_size_ = 0, page_count_ = 0;
};

template <typename Container>
auto Paginate(const Container& c, size_t page_size) {
    Paginator ret = Paginator(c.begin(), c.end(), page_size);

    return ret.Sort();
}