#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>

namespace seneca {
    enum class PartOfSpeech {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };

    struct Word {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary {
        Word* m_words;
        size_t m_count;
        
    public:
        Dictionary();
        Dictionary(const char* filename);
        ~Dictionary();
        
        // Copy operations
        Dictionary(const Dictionary& other);
        Dictionary& operator=(const Dictionary& other);
        
        // Move operations
        Dictionary(Dictionary&& other) noexcept;
        Dictionary& operator=(Dictionary&& other) noexcept;
        
        void searchWord(const char* word);
        
    private:
        PartOfSpeech getPartOfSpeech(const std::string& pos_str) const;
        void cleanup();
        void copy(const Dictionary& other);
    };
}

#endif