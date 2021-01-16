#ifndef RAYTRACER_PRINTABLE_H
#define RAYTRACER_PRINTABLE_H

namespace rt {
    struct Printable {
        virtual void print(std::ostream& stream, int indent) const = 0;
        friend std::ostream& operator<<(std::ostream& stream, Printable const& printable) {
            printable.print(stream, 0);
            return stream;
        }
    };
}

#endif //RAYTRACER_PRINTABLE_H
