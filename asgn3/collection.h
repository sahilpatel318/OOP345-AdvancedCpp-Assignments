#pragma once
/*
  Name : SAHIL HARESHBHAI PATEL
  Email: shpatel27@myseneca.ca
  Student ID: 173793225
  Date: July 18, 2025

  I declare that this submission is the result of my own work and I only copied the code that my professor provided to complete my assignments.
  This submitted piece of work has not been shared with any other student or 3rd party content provider.
*/

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "mediaItem.h"
#include <string>
#include <vector>

namespace seneca
{
    /*
     * Collection class manages a dynamic collection of MediaItem pointers.
     * It supports item addition, sorting, quote removal, and observer callbacks.
     */
    class Collection
    {
        std::string m_name;                         // Name of the collection
        std::vector<MediaItem *> m_items;           // Vector storing pointers to MediaItems
        void (*m_observer)(const Collection &, const MediaItem &);  // Function pointer for observer callback

    public:
        /*
         * Constructor - initializes the collection with a given name.
         * @param name : name of the collection
         */
        Collection(const std::string &name);

        // Rule of 5 - Deleted copy and move operations to prevent shallow copying
        Collection(const Collection &other) = delete;
        Collection &operator=(const Collection &other) = delete;
        Collection(Collection &&other) noexcept = delete;
        Collection &operator=(Collection &&other) noexcept = delete;

        /*
         * Destructor - deallocates all dynamically allocated MediaItem pointers.
         */
        ~Collection();

        /*
         * Returns the name of the collection.
         */
        const std::string &name() const;

        /*
         * Returns the number of items currently in the collection.
         */
        size_t size() const;

        /*
         * Sets an observer function that is called whenever a new item is successfully added.
         * @param observer : function pointer to observer callback
         */
        void setObserver(void (*observer)(const Collection &, const MediaItem &));

        /*
         * Adds a new MediaItem pointer to the collection (if not already present).
         * Notifies observer if one is set.
         * @param item : pointer to dynamically allocated MediaItem
         * @return reference to the current Collection
         */
        Collection &operator+=(MediaItem *item);

        /*
         * Provides access to a MediaItem by index with bounds checking.
         * @param idx : index of the item
         * @return pointer to the MediaItem
         */
        MediaItem *operator[](size_t idx) const;

        /*
         * Searches for a MediaItem by title.
         * @param title : title of the item to search
         * @return pointer to the matching MediaItem, or nullptr if not found
         */
        MediaItem *operator[](const std::string &title) const;

        /*
         * Removes leading and trailing quotes from all item titles and summaries.
         */
        void removeQuotes();

        /*
         * Sorts the collection based on a given field: "title", "summary", or "year".
         * @param field : name of the field to sort by
         */
        void sort(const std::string &field);
    };

    /*
     * Overloads the stream insertion operator to display the contents of a collection.
     * @param os : output stream
     * @param collection : Collection to display
     * @return output stream with all items displayed
     */
    std::ostream &operator<<(std::ostream &os, const Collection &collection);

} // namespace seneca

#endif // SENECA_COLLECTION_H
