#pragma once
#include "Component.h"

template <ComponentType Type>
struct has_component {
    using result_type = bool;
    bool operator()(const std::shared_ptr<Object>& obj) const {
        return obj->hasComponent(Type);
    }
};

template <ComponentType Type>
struct component_tag {};

struct by_graphics   {};
struct by_kinematics {};
struct by_transform  {};

namespace bmi = boost::multi_index;

template <typename StoredClass>
using MultiIndex = boost::multi_index_container<
    StoredClass,
    bmi::indexed_by<
        bmi::hashed_non_unique<
            bmi::tag<by_graphics>,
            has_component<ComponentType::Graphics>
        >,
        bmi::hashed_non_unique<
            bmi::tag<by_kinematics>,
            has_component<ComponentType::Kinematics>
        >,
        bmi::hashed_non_unique<
            bmi::tag<by_transform>,
            has_component<ComponentType::Transform>
        >
    >
>;

template <ComponentType Type>
struct tag_for_type;

template <> struct tag_for_type<ComponentType::Graphics>   { using type = by_graphics;   };
template <> struct tag_for_type<ComponentType::Kinematics> { using type = by_kinematics; };
template <> struct tag_for_type<ComponentType::Transform>  { using type = by_transform;  };
