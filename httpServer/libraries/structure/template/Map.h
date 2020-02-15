//
// Created by root on 10-02-20.
//

#ifndef STRUCTURE_TEMPLATE_MAP_H
#define STRUCTURE_TEMPLATE_MAP_H


namespace Template {

    template<class K, class V>
    class Map {

        class Chain;

        class Pair {
            K m_key;
            V m_value;
        public:
            Pair(const K &key);

            Pair(const K &key, V value);

            Pair(const Pair &pair);

            ~Pair();

            friend class Item;

            friend class Chain;
        };

        class Item {
            Pair m_data;
            Item *m_next;
        public:
            Item(const Pair &pair);

            friend class Chain;
        };

        class Chain {
            Item *m_head;
            Item *m_tail;
        public:
            Chain(const Pair &data);

            ~Chain();

            V *insert(const Pair &data);

            V *find(const K &key);

            V *getLastInserted();
        };

        Chain **m_value;
        unsigned int m_capacity;
        unsigned int m_length;

        int hash(const K &key) const;

    public:
        Map();

        ~Map();

        V const operator[](const K& key) const;

        V &operator[](const K& key);

        void clear();

        unsigned int length();

        bool exist(const K &key) const;

    };


    template<class K, class V>
    Map<K, V>::Map() :
            m_value(0),
            m_capacity(100),
            m_length(0) {
        m_value = new Chain *[m_capacity]();
        for (int index = 0; index < m_capacity; index++) {
            m_value[index] = 0;
        }
    }

    template<class K, class V>
    Map<K, V>::~Map() {
        clear();
        delete [] m_value;
        m_value = 0;
    }

    template<class K, class V>
    int Map<K, V>::hash(const K &key) const {
        unsigned int hash = key.getHash();

        return hash % m_capacity;
    }

    template<class K, class V>
    V const Map<K, V>::operator[](const K &key) const {
        int index = hash(key);

        return *m_value[index]->find(key);
    }

    template<class K, class V>
    V &Map<K, V>::operator[](const K &key) {
        int index = hash(key);

        if (!m_value[index]) {
            Pair pair(key);
            m_value[index] = new Chain(pair);

            V* value = m_value[index]->getLastInserted();
            m_length++;
            return *value;
        } else {

            V* value = m_value[index]->find(key);
            if (!value) {
                Pair pair(key);
                m_length++;
                value = m_value[index]->insert(pair);
            }

            return *value;
        }
    }

    template<class K, class V>
    void Map<K, V>::clear() {
        if (!m_length || !m_value) {
            return;
        }

        for (int index = 0; index < m_capacity; index++) {
            if (m_value[index]) {
                delete m_value[index];
                m_value[index] = 0;
            }
        }

        m_length = 0;
    }

    template<class K, class V>
    unsigned int Map<K, V>::length() {
        return m_length;
    }

    template<class K, class V>
    bool Map<K, V>::exist(const K &key) const {
        int index = hash(key);

        if (!m_value[index]) {
            return false;
        }

        return m_value[index]->find(key) != 0;
    }

////////////////////////////////////////////

    template<class K, class V>
    Map<K, V>::Pair::Pair(const K &key) {
        m_key = key;
    }

    template<class K, class V>
    Map<K, V>::Pair::Pair(const K &key, V value) {
        m_key = key;
        m_value = value;
    }

    template<class K, class V>
    Map<K, V>::Pair::Pair(const Pair &pair) {
        m_key = pair.m_key;
        m_value = pair.m_value;
    }

    template<class K, class V>
    Map<K, V>::Pair::~Pair() {
    }

    template<class K, class V>
    Map<K, V>::Item::Item(const Pair &pair) : m_data(pair) {
        m_next = 0;
    }

    template<class K, class V>
    Map<K, V>::Chain::Chain(const Pair &data) {
        m_head = new Item(data);
        m_tail = m_head;
    }

    template<class K, class V>
    Map<K, V>::Chain::~Chain() {
        m_tail = m_head;
        while (m_tail) {
            m_tail = m_tail->m_next;
            delete m_head;
            m_head = m_tail;
        }
    }

    template<class K, class V>
    V *Map<K, V>::Chain::insert(const Pair &data) {
        Item *ptr = new Item(data);
        m_tail->m_next = ptr;
        m_tail = ptr;

        return &m_tail->m_data.m_value;
    }

    template<class K, class V>
    V *Map<K, V>::Chain::find(const K &key) {
        Item *ptr = m_head;
        while (ptr) {
            if (ptr->m_data.m_key == key) {

                return &ptr->m_data.m_value;
            }
            ptr = ptr->m_next;
        }

        return 0;
    }

    template<class K, class V>
    V *Map<K, V>::Chain::getLastInserted() {
        return &m_tail->m_data.m_value;
    }

}

#endif //STRUCTURE_TEMPLATE_MAP_H