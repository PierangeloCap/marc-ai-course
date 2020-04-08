#ifndef GENERICSTATE_H
#define GENERICSTATE_H

#include "State.h"

#include "../Utils/Exceptions/IncompatibleStateTypeException.h"

namespace Modeling {

    class Problem;

    template <class StateType>
    class GenericState : public virtual State {

    protected:
        std::unique_ptr<StateType> value;

    public:
        const StateType& getValue() const;

        explicit GenericState<StateType>(std::unique_ptr<StateType> val);

        virtual bool operator== (const State& a) override;

    };

    template<class StateType>
    const StateType& GenericState<StateType>::getValue() const {
        return *(this->value);
    }

    template <class StateType>
    GenericState<StateType>::GenericState(std::unique_ptr<StateType> val) : value(std::move(val)) { }

    template<class StateType>
    bool GenericState<StateType>::operator==(const State& a) {
        const auto* genState = dynamic_cast<const GenericState<StateType> *>(&a);
        if (genState == nullptr) throw IncompatibleStateTypeException();
        return this->getValue() == genState->getValue();
    }

}

#endif /* GENERICSTATE_H */

