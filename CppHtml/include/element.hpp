#include <vector>
#include <string>
#include <unordered_map>

namespace CppHtml {
    class Element {
    public:
        Element(const std::string& tag) : tag(tag) {}

        Element* AddChild(Element* child) {
            children.push_back(child);
            return this;
        }

        Element* SetAttribute(const std::string& attr, const std::string& value) {
            attributes[attr] = value;
            return this;
        }

        Element* SetAttribute(const std::string& attr) {
            attributes[attr] = "";
            return this;
        }

        Element* SetAttributes(const std::unordered_map<std::string, std::string>& attributes) {
            this->attributes = attributes;
            return this;
        }

        Element* AddAttributes(const std::unordered_map<std::string, std::string>& attributes) {
            this->attributes.insert(attributes.begin(), attributes.end());
            return this;
        }

        Element* SetText(const std::string& text) {
            this->text = text;
            return this;
        }

        std::string ToString() {
            std::string result = "<" + tag;
            for (const auto& [key, val] : attributes) {
                if (val.empty()) {
                    result += " " + key;
                    continue;
                }

                result += " " + key + "=\"" + val + "\"";
            }
            result += ">";
            if (!text.empty()) {
                result += text;
            }
            for (Element* child : children) {
                result += child->ToString();
            }
            result += "</" + tag + ">";
            return result;
        }

        std::string ToString(bool indent) {
            if (indent == false) {
                return ToString();
            }

            int indentLevel = 0;

            std::string result = std::string(indentLevel, ' ') + "<" + tag;
            for (const auto& [key, val] : attributes) {
                if (val.empty()) {
                    result += " " + key;
                    continue;
                }

                result += " " + key + "=\"" + val + "\"";
            }

            result += ">";

            if (!text.empty()) {
                result += '\n' + std::string(indentLevel + 4, ' ') + text;
            }

            for (Element* child : children) {
                result += "\n" + child->ToString(indent, indentLevel + 4);
            }
            result += "\n" + std::string(indentLevel, ' ') + "</" + tag + ">";
            return result;
        }

        std::string ToString(bool indent, int indentLevel) {
            if (indent == false) {
                return ToString();
            }

            std::string result = std::string(indentLevel, ' ') + "<" + tag;
            for (const auto& [key, val] : attributes) {
                if (val.empty()) {
                    result += " " + key;
                    continue;
                }

                result += " " + key + "=\"" + val + "\"";
            }

            result += ">";

            if (!text.empty()) {
                result += '\n' + std::string(indentLevel + 4, ' ') + text;
            }

            for (Element* child : children) {
                result += "\n" + child->ToString(indent, indentLevel + 4);
            }
            result += "\n" + std::string(indentLevel, ' ') + "</" + tag + ">";
            return result;
        }

    private:
        std::string tag;
        std::string text;
        std::unordered_map<std::string, std::string> attributes;
        std::vector<Element*> children;
    };
};