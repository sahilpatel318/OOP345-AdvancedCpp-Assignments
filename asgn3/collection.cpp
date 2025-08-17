/*
 Name : SAHIL HARESHBHAI PATEL
 Email: shpatel27@myseneca.ca
 Student ID: 173793225
 Date: July 18, 2025

 I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
 This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#include "collection.h"
#include "mediaItem.h"
#include <algorithm>

namespace seneca
{
    // Constructor initializes collection with a name and null observer
    Collection::Collection(const std::string &name)
        : m_name{name}, m_observer{nullptr} {}

    // Destructor to deallocate all MediaItem pointers
    Collection::~Collection()
    {
        for (auto item : m_items)
        {
            delete item;  // Avoid memory leak
        }
    }

    // Returns the name of the collection
    const std::string &Collection::name() const { return m_name; }

    // Returns the number of items in the collection
    size_t Collection::size() const { return m_items.size(); }

    // Sets a function pointer as observer to notify when an item is added
    void Collection::setObserver(void (*observer)(const Collection &, const MediaItem &))
    {
        m_observer = observer;
    }

    // Adds a new MediaItem to the collection if it doesn't already exist
    Collection &Collection::operator+=(MediaItem *item)
    {
        for (auto m_item : m_items)
        {
            if (m_item->getTitle() == item->getTitle())
            {
                delete item;  // Prevent memory leak for duplicate
                return *this; // Ignore duplicates
            }
        }

        m_items.push_back(item);  // Add to collection
        if (m_observer)
        {
            m_observer(*this, *item);  // Notify observer
        }

        return *this;
    }

    // Overloaded subscript operator for index-based access
    MediaItem *Collection::operator[](size_t idx) const
    {
        if (idx >= m_items.size())
        {
            std::string msg = "Bad index " + std::to_string(idx) + " Collection has " +
                              std::to_string(m_items.size()) + " items.";
            throw std::out_of_range(msg);  // Safe bounds checking
        }
        return m_items[idx];
    }

    // Overloaded subscript operator for title-based search
    MediaItem *Collection::operator[](const std::string &title) const
    {
        auto it = std::find_if(m_items.begin(), m_items.end(), [title](MediaItem *item)
                               { return item->getTitle() == title; });
        return it != m_items.end() ? *it : nullptr;
    }

    // Helper function to remove quotes from beginning and end of a string
    void trimQuotes(std::string &str)
    {
        if (str.front() == '\"')
        {
            str = str.substr(1, str.size() - 1);  // Remove first quote
        }
        if (str.back() == '\"')
        {
            str = str.substr(0, str.size() - 1);  // Remove last quote
        }
    }

    // Removes quotes from the title and summary of each MediaItem in the collection
    void Collection::removeQuotes()
    {
        std::for_each(m_items.begin(), m_items.end(), [](MediaItem *item)
                      {
            // Clean title
            std::string title = item->getTitle();
            trimQuotes(title);
            item->setTitle(title);

            // Clean summary
            std::string summary = item->getSummary();
            trimQuotes(summary);
            item->setSummary(summary); });
    }

    // Sorts the collection based on the field: "title", "summary", or "year"
    void Collection::sort(const std::string &field)
    {
        if (field == "title")
        {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem *a, MediaItem *b)
                      { return a->getTitle() < b->getTitle(); });
        }
        else if (field == "summary")
        {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem *a, MediaItem *b)
                      { return a->getSummary() < b->getSummary(); });
        }
        else if (field == "year")
        {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem *a, MediaItem *b)
                      { return a->getYear() < b->getYear(); });
        }
    }

    // Stream insertion operator to display all items in the collection
    std::ostream &operator<<(std::ostream &os, const Collection &collection)
    {
        for (size_t i = 0; i < collection.size(); i++)
        {
            collection[i]->display(os);  // Use polymorphic display function
        }

        return os;
    }

} // namespace seneca
