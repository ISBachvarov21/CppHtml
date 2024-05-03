#include <iostream>
#include "../include/element.hpp"

using namespace CppHtml;

int main() {
    Element html("html");
    Element head("head");
    Element body("body");
    Element title("title");
    Element h1("h1");
    Element p("p");

    html.AddChild(&head);
    html.AddChild(&body);
    head.AddChild(&title);
    body.AddChild(&h1);
    body.AddChild(&p);

    title.SetText("Hello, World!");
    h1.SetText("Hello, World!");
    p.SetText("This is a paragraph.");

    std::cout << html.ToString(true) << std::endl;

    std::cin >> std::ws;

    return 0;
}