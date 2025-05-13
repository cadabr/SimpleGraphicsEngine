#pragma once

#include "Object.h"

// Теги для доступа к индексам по имени
struct by_id {};
struct by_name {};
struct by_age {};
struct by_composite {};
struct by_sequence {};
struct by_random {};
struct by_hash_id {};
struct by_hash_name {};

namespace bmi = boost::multi_index;

using SceneContainer = boost::multi_index_container<
    Object,
    bmi::indexed_by<
        bmi::ordered_unique<bmi::tag<by_id>, bmi::member<Person, int, &Person::id>>,

        // 2. Упорядоченный неуникальный индекс по имени
        bmi::ordered_non_unique<bmi::tag<by_name>, bmi::member<Person, std::string, &Person::name>>,

        // 3. Упорядоченный неуникальный индекс по возрасту
        bmi::ordered_non_unique<bmi::tag<by_age>, bmi::member<Person, int, &Person::age>>,

        // 4. Композитный ключ (name + age)
        bmi::ordered_non_unique<
            bmi::tag<by_composite>,
            bmi::composite_key<
                Person,
                bmi::member<Person, std::string, &Person::name>,
                bmi::member<Person, int, &Person::age>
            >
        >,

        // 5. Последовательный доступ (как list)
        bmi::sequenced<bmi::tag<by_sequence>>,

        // 6. Случайный доступ (как vector)
        bmi::random_access<bmi::tag<by_random>>,

        // 7. Хешированный уникальный индекс по id
        bmi::hashed_unique<bmi::tag<by_hash_id>, bmi::member<Person, int, &Person::id>>,

        // 8. Хешированный неуникальный индекс по имени
        bmi::hashed_non_unique<bmi::tag<by_hash_name>, bmi::member<Person, std::string, &Person::name>>
    >
>;

class Scene {
};
