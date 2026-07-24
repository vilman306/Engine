#ifndef JSONEXTENSIONS_HPP_INCLUDED
#define JSONEXTENSIONS_HPP_INCLUDED

#include <nlohmann/json.hpp>
#include <type_traits>

namespace JsonUtils
{

// Returns the value of type T at key 'p_Key' in the JSON 'p_Json'.
template <typename T>
T GetFromJson(const nlohmann::json& p_Json, const std::string& p_Key)
{
    // Make sure the key is in the json
    if (!p_Json.contains(p_Key))
        throw std::runtime_error("ERROR: Missing key '" + p_Key + "' in " + p_Json.dump());

    const nlohmann::json& value = p_Json[p_Key];

    if constexpr (std::is_same_v<T, std::string>) {
        if (!value.is_string())
            throw std::runtime_error("ERROR: Value at key '" + p_Key + "' is not a string. In: " + p_Json.dump());
        return value.get<std::string>();
    }
    else if constexpr (std::is_same_v<T, int>) {
        if (!value.is_number_integer())
            throw std::runtime_error("ERROR: Value at key '" + p_Key + "' is not an integer. In: " + p_Json.dump());
        return value.get<int>();
    }
    else if constexpr (std::is_same_v<T, float>) {
        if (!value.is_number())
            throw std::runtime_error("ERROR: Value at key '" + p_Key + "' is not a number. In: " + p_Json.dump());
        return value.get<float>();
    }
    else if constexpr (std::is_same_v<T, double>) {
        if (!value.is_number())
            throw std::runtime_error("ERROR: Value at key '" + p_Key + "' is not a number. In: " + p_Json.dump());
        return value.get<double>();
    }
    else if constexpr (std::is_same_v<T, nlohmann::json>) {
        return value;
    }
    else if constexpr (std::is_same_v<T, bool>) {
        if (!value.is_boolean())
            throw std::runtime_error("ERROR: Value at key '" + p_Key + "' is not a boolean. In: " + p_Json.dump());
        return value.get<bool>();
    }
    else if constexpr (std::is_same_v< T, std::vector<int> >) {
        if (!value.is_array())
            throw std::runtime_error("ERROR: Value at key '" + p_Key + "' is not an array. In: " + p_Json.dump());
        std::vector<int> out;
        for (auto& element : value) {
            if (!element.is_number_integer())
                throw std::runtime_error("ERROR: Element in array at key '" + p_Key + "' is not an integer In: " + p_Json.dump());
            out.push_back(element.get<int>());
        }
        return out;
    }
    else if constexpr (std::is_same_v< T, std::vector<float> >) {
        if (!value.is_array())
            throw std::runtime_error("ERROR: Value at key '" + p_Key + "' is not an array. In: " + p_Json.dump());
        std::vector<float> out;
        for (auto& element : value) {
            if (!element.is_number())
                throw std::runtime_error("ERROR: Element in array at key '" + p_Key + "' is not a number. In: " + p_Json.dump());
            out.push_back(element.get<float>());
        }
        return out;
    }
    else if constexpr (std::is_same_v< T, std::vector<double> >) {
        if (!value.is_array())
            throw std::runtime_error("ERROR: Value at key '" + p_Key + "' is not an array. In: " + p_Json.dump());
        std::vector<double> out;
        for (auto& element : value) {
            if (!element.is_number())
                throw std::runtime_error("ERROR: Element in array at key '" + p_Key + "' is not a number. In: " + p_Json.dump());
            out.push_back(element.get<double>());
        }
        return out;
    }
    else {
        throw std::runtime_error("ERROR: Unsupported type in function GetFromJson");
    }
}

// Returns the "child JSON" inside the JSON 'p_Json' that contains the key value pair 'p_Key' : 'p_Value'.
// T is the type of p_Value.
// Example: GetChildJsonFromKeyValuePair<std::string>('gameObjectsJson', "Name", "TestSprite2") will return 'testSprite2Json'
//    "GameObjects": [
//        {
//            "Prefab":"Sprite",
//            "Name":"TestSprite",
//            "Overrides": {
//                "Texture":"testimage.png",
//                "Transform": {
//                    "Position":[300,300,0]
//                }
//            }
//        },
//        {
//            "Prefab":"Sprite",
//            "Name":"TestSprite2",
//            "Defaults": {
//                "Texture":"testimage2.png",
//                "Transform": {
//                    "Position":[600,600,0]
//                }
//            }
//        }
//    ]
template <typename T>
nlohmann::json GetChildJsonFromKeyValuePair(const nlohmann::json& p_Json, const std::string& p_Key, const T& p_Value)
{
    // Make sure only one child json contains the key value pair
    bool pairFound = false;
    nlohmann::json out;
    for (const nlohmann::json& childJson : p_Json)
    {
        if (childJson.contains(p_Key) && childJson[p_Key].get<T>() == p_Value)
        {
            if (!pairFound)
            {
                pairFound = true;
                out = childJson;
                break;
            }
            // Here, the json has been found more than once
            throw std::runtime_error("ERROR: The provided key value pair exists in multiple child JSONs in " + p_Json.dump());
        }
    }
    if (!pairFound)
        throw std::runtime_error("ERROR: The provided key value pair does not exist in any child JSON in " + p_Json.dump());
    return out;
}


}
#endif // JSONEXTENSIONS_HPP_INCLUDED
