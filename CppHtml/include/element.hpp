#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

namespace CppHtml {
    class Element {
    public:
        Element(const std::string& tag) : tag(tag) {}

        Element* GetParent() {
            return parent;
        }

        Element* AddChild(Element* child) {
            children.push_back(child);
            return this;
        }

        Element* AddChildren(const std::vector<Element*>& children) {
            this->children.insert(this->children.end(), children.begin(), children.end());
            return this;
        }

        Element* SetTag(const std::string& tag) {
            this->tag = tag;
            return this;
        }

        Element* GetChild(int index) {
            return children[index];
        }

        std::vector<Element*> GetChildren() {
            return children;
        }

        std::string GetTag() {
            return tag;
        }

        std::string GetText() {
            return text;
        }

        std::string GetAttribute(const std::string& attr) {
            return attributes[attr];
        }

        std::unordered_map<std::string, std::string> GetAttributes() {
            return attributes;
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
        Element* parent;
    };
};

std::string operator<<(std::string str, CppHtml::Element element) {
    return str + element.ToString();
}

std::ostream& operator<<(std::ostream& os, CppHtml::Element element) {
    os << element.ToString();
    return os;
}

std::string operator<<(CppHtml::Element element, int indentLevel) {
    return element.ToString(true, indentLevel);
}