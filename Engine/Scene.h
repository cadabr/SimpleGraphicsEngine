#pragma once
#include "Object.h"
#include "MultiIndex.h"

class Scene {
public:
    void addObject(std::shared_ptr<Object> obj) {
        objects.insert(std::move(obj));
    }

    template <ComponentType Type>
    auto rangeForComponent() const {
        return objects.get<typename tag_for_type<Type>::type>().equal_range(true);
    }
    
private:
    MultiIndex objects;
};
