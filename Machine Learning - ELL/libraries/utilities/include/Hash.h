/**
 * Microsoft - Modern Information Technology
 * https://github.com/Microsoft/ELL/blob/master/libraries/utilities/include/Hash.h
 *
 *  Created on: Mar 28, 2019
 *  Student (MIG Virtual Developer): Tung Dang
 */

#pragma once 

#include "Unused.h"

#include <tuple>
#include <utility>
#include <vector>
#include <map>
#include <iostream>

namespace ell 
{
    namespace utilities
    {
        #define HashTableTemplateList class KeyType, class ElementType, class CAllocatorType
        #define CHashTableType        CHashTable<KeyType, ElementType, CAllocatorType>

        namespace detail
        {
            inline void HashCombineImpl(size_t& seed, size_t value)
            {
                seed ^= value + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }

        template <typename T>
        inline void HashCombine(size_t& seed, const T& t);

        template <class Iterator>
        inline void HashRange(size_t& seed, Iterator first, Iterator last);

        template <class Iterator>
        [[nodiscard]] inline size_t HashRange(Iterator first, Iterator last);

        template <typename T>
        [[nodiscard]] auto HashValue(const T& t) -> decltype(std::hash<T>{}(t))
        {
            return std::hash<T>{}(t);
        }

        template <typename T, size_t N>
        [[nodiscard]] auto HashValue(const T (&a)[N])
        {
            return HashRange(a, a + N);
        }

        template <typename T, size_t N>
        [[nodiscard]] auto HashValue(T (&a)[N])
        {
            return HashRange(a, a + N);
        }

        template <typename T, typename Alloc>
        [[nodiscard]] auto HashValue(const std::vector<T, Alloc>& v)
        {
            size_t seed = 0;
            HashCombine(seed, v.size());
            HashRange(seed, v.begin(), v.end());
            return seed;
        }

        namespace detail
        {
            template <size_t Idx, typename Tuple>
            void HashTupleImpl(size_t& seed, const Tuple& tuple)
            {
                    HashCombine(seed, std::get<Idx>(tuple));
                    HashTupleImpl<Idx + 1>(seed, tuple);
            }

            template <typename Tuple>
            [[nodiscard]] size_t HashTuple(const Tuple& tuple)
            {
                size_t seed = 0;
                HashTupleImpl<0>(seed, tuple);
                return seed;
            }
        } 
        
        template <typename... Ts>
        [[nodiscard]] auto HashValue(const std::tuple<Ts...>& tuple)
        {
            return detail::HashTuple(tuple);
        }

        template <HashTableTemplateList>
        class CHashTable 
        {
            public:
                class CHashKey
                {
                    public:     
                        CHashKey(void);
                        CHashKey(const KeyType &keyValue);
                        CHashKey(const KeyType &keyValue, const unsigned long hashNode);
                        CHashKey(const CHashKey &hashKey);
                        virtual ~CHashKey(void);

                        unsigned long GetHashCode(void) const;
                        const KeyType& GetKeyValue(void) const;
                        bool operator == (const CHashKey &hashKey) const;

                    protected:
                        KeyType m_KeyValue;
                        unsigned long m_HashCode;
                };

                CHashTable(const unsigned long size);
                virtual ~CHashTable(void);

                bool Add(const KeyType &key, const ElementType& element);
                bool Get(const KeyType &key, ElementType& element);
                bool Remove(const KeyType& key, ElementType &element);
                bool Remove(const ElementType& element);

                bool Add(const CHashKey &hashKey, const ElementType& element);
                bool Get(const CHashKey &hashKey, ElementType &element) const;
                bool Remove(const CHashKey &hashKey, ElementType &element);  

                bool IsEmpty(void) const;
                unsigned long GetCount(void) const;
                void DebugPrint(void) const;

            protected: 
                class CHashNode
                {
                    public:     
                        CHashNode (const CHashKey &hashKey, const ElementType &element);
                        virtual ~CHashNode(void);

                        const CHashKey &GetHashKey(void) const;
                        ElementType GetElement(void) const;

                    protected:  
                        CHashKey m_HashKey;
                        ElementType m_Element;
                };
        };

        template <typename ElementType>
        class HashAlgorithms
        {
        public:
            class PrintBinaryTreeMap 
            {
                public:
                    struct Node
                    {
                        int key;
                        Node *left;
                        Node *right;
                    };

                    struct Node* newNode(int key)
                    {
                        struct Node* root = new Node;
                        root->key = key;
                        root->left = NULL;
                        root->right = NULL;
                    };
                    void GetVerticalOrder(Node* root, int hd, std::map<int, std::vector<int>> &map);
                    void printVerticalOrder();
            };
        };
    }
}

#pragma region implementation

namespace ell 
{
    namespace utilities 
    {
        template <typename T>
        inline void HashCombine(size_t& seed, const T& t)
        {
            detail::HashCombineImpl(seed, HashValue(t));
        }

        template <class Iterator>
        inline void HashRange(size_t& seed, Iterator first, Iterator last)
        {
            for (; first != last; ++first)
            {
                HashCombine<typename std::iterator_traits<Iterator>::value_type>(seed, *first);
            }
        }

        template <class Iterator>
        [[nodiscard]] inline size_t HashRange(Iterator first, Iterator last)
        {
            size_t seed = 0;
            HashRange(seed, first, last);
            return seed;
        }

        template <typename ElementType>
        void HashAlgorithms<ElementType>::PrintBinaryTreeMap::GetVerticalOrder(Node* root, 
                                            int hd, std::map<int, std::vector<int>> &map) 
        {
            if (root == NULL)
            {
                return;
            }
            map[hd].push_back(root->key);
            GetVerticalOrder(root->left, hd-1, map);
            GetVerticalOrder(root->right, hd+1, map);
        }

        template <typename ElementType>
        void HashAlgorithms<ElementType>::PrintBinaryTreeMap::printVerticalOrder()
        {
            Node* root = newNode(1);
            root->left = newNode(2);
            root->right = newNode(3);
            root->left->left = newNode(4); 
            root->left->right = newNode(5); 
            root->right->left = newNode(6); 
            root->right->right = newNode(7); 
            root->right->left->right = newNode(8); 
            root->right->right->right = newNode(9); 

            std::map<int, std::vector<int>> map;
            int hd = 0;
            GetVerticalOrder(root, hd, map);
            std::map<int, std::vector<int>>::iterator it;
            for (it=map.begin(); it!=map.end(); it++)
            {
                for (size_t i=0; i<it->second.size(); ++i)
                {
                    std::cout << it->second[i] << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

#pragma endregion implementation
