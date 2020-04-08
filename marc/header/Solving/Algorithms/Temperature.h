#ifndef TEMPERATURE_H
#define TEMPERATURE_H


namespace Solving::Algorithms {

    class Temperature {

    protected:
        [[nodiscard]] double virtual temperature(const unsigned int step) const = 0;

    public:
        double operator[](const unsigned int step) {
            return this->temperature(step);
        }

    };

}


#endif /* CODE_C___TEMPERATURE_H */
