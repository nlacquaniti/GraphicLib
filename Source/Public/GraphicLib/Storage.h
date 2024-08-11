#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <tuple>

namespace GraphicLib {
template <typename... Types> struct Storage {
    using EntryKey = std::size_t;
    using EntryType = std::tuple<std::pair<Types, unsigned int>...>;

    template <typename Type>
    using AllocType =
#ifndef STORAGE_ALLOCATOR
        std::allocator<Type>;
#else
        STORAGE_ALLOCATOR(Type);
#endif

    std::unordered_map<EntryKey,
        EntryType,
        std::hash<std::size_t>,
        std::equal_to<std::size_t>,
        AllocType<std::pair<const std::size_t, EntryType>>>
        Entries;
    std::vector<EntryKey, AllocType<std::size_t>> UnusedEntryKeys;
    std::size_t NextEntryKey = 0;
};

template <typename... Types> auto GetNextEntryKey(Storage<Types...>& storage) {
    typename Storage<Types...>::EntryKey nextEntryKey;

    if (!storage.UnusedEntryKeys.empty()) {
        nextEntryKey = storage.UnusedEntryKeys.back();
        storage.UnusedEntryKeys.pop_back();
    } else {
        nextEntryKey = storage.NextEntryKey;
        ++storage.NextEntryKey;
    }

    return nextEntryKey;
}

template <typename... Types>
[[nodiscard]] auto AddStorageEntry(
    Storage<Types...>& storage, const typename Storage<Types...>::EntryType& entry) {
    const auto entryKey = GetNextEntryKey(storage);
    storage.Entries.insert(std::make_pair(entryKey, entry));
    return entryKey;
}

template <typename... Types>
void RemoveStorageEntry(Storage<Types...>& storage, std::size_t entryId) {
    const auto entryToEraseIt = storage.Entries.find(entryId);
    if (entryToEraseIt == storage.Entries.cend()) {
        assert(false);
        return;
    }

    storage.Entries.erase(entryToEraseIt);
    storage.unusedEntryKeys.push_back(entryId);
}

template <typename... Types>
const typename Storage<Types...>::EntryType* FindStorageEntry(
    Storage<Types...>& storage, std::size_t entryId) {
    const auto entryToFindIt = storage.Entries.find(entryId);
    if (entryToFindIt == storage.Entries.cend()) {
        assert(false);
        return;
    }

    return &entryToFindIt->second;
}
} // namespace GraphicLib