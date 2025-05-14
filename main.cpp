#include <iostream>
#include <memory>
#include <limits>

// Цвета ANSI
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

// Базовый класс
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

// Квадрат
class Square : public Shape {
    int size;
public:
    Square(int s) : size(s) {}
    void draw() const override {
        std::cout << GREEN << "+";
        for (int i = 0; i < size * 2; ++i) std::cout << "-";
        std::cout << "+\n";

        for (int i = 0; i < size; ++i) {
            std::cout << "|" << RESET;
            for (int j = 0; j < size; ++j) std::cout << GREEN << "* " << RESET;
            std::cout << GREEN << "|\n" << RESET;
        }

        std::cout << GREEN << "+";
        for (int i = 0; i < size * 2; ++i) std::cout << "-";
        std::cout << "+\n" << RESET;
    }
};

// Прямоугольник
class Rectangle : public Shape {
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    void draw() const override {
        std::cout << CYAN << "+";
        for (int i = 0; i < width * 2; ++i) std::cout << "-";
        std::cout << "+\n";

        for (int i = 0; i < height; ++i) {
            std::cout << "|" << RESET;
            for (int j = 0; j < width; ++j) std::cout << CYAN << "* " << RESET;
            std::cout << CYAN << "|\n" << RESET;
        }

        std::cout << CYAN << "+";
        for (int i = 0; i < width * 2; ++i) std::cout << "-";
        std::cout << "+\n" << RESET;
    }
};

// Треугольник
class Triangle : public Shape {
    int height;
public:
    Triangle(int h) : height(h) {}
    void draw() const override {
        std::cout << YELLOW << "+-- Triangle --+\n" << RESET;
        for (int i = 1; i <= height; ++i) {
            std::cout << YELLOW << "|" << RESET;
            for (int j = 0; j < i; ++j) std::cout << YELLOW << "* " << RESET;
            std::cout << YELLOW << "|\n" << RESET;
        }
        std::cout << YELLOW << "+--------------+\n" << RESET;
    }
};

// Круг
class Circle : public Shape {
    int radius;
public:
    Circle(int r) : radius(r) {}
    void draw() const override {
        std::cout << RED << "+-- Circle --+\n" << RESET;
        for (int y = -radius; y <= radius; ++y) {
            std::cout << RED << "|" << RESET;
            for (int x = -radius; x <= radius; ++x) {
                if (x * x + y * y <= radius * radius)
                    std::cout << RED << "*" << RESET;
                else
                    std::cout << " ";
            }
            std::cout << RED << "|\n" << RESET;
        }
        std::cout << RED << "+-------------+\n" << RESET;
    }
};

// Очистка ввода в случае ошибки
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    while (true) {
        std::cout << "\nChoose a shape to draw:\n";
        std::cout << "1. Square\n2. Rectangle\n3. Triangle\n4. Circle\n0. Exit\n> ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 0) break;

        std::unique_ptr<Shape> shape;

        if (choice == 1) {
            int size;
            std::cout << "Enter side length: ";
            std::cin >> size;
            shape = std::make_unique<Square>(size);
        } else if (choice == 2) {
            int w, h;
            std::cout << "Enter width and height: ";
            std::cin >> w >> h;
            shape = std::make_unique<Rectangle>(w, h);
        } else if (choice == 3) {
            int h;
            std::cout << "Enter height: ";
            std::cin >> h;
            shape = std::make_unique<Triangle>(h);
        } else if (choice == 4) {
            int r;
            std::cout << "Enter radius: ";
            std::cin >> r;
            shape = std::make_unique<Circle>(r);
        } else {
            std::cout << "Unknown option.\n";
            continue;
        }

        if (std::cin.fail()) {
            clearInput();
            std::cout << "Invalid parameters. Try again.\n";
            continue;
        }

        std::cout << "\n";
        shape->draw();
    }

    std::cout << "Goodbye!\n";

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;
}
