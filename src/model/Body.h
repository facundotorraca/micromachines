#ifndef MICROMACHINES_BODY_H
#define MICROMACHINES_BODY_H


class Body {
    public:
        virtual void collide(Body* other_body) = 0;

        virtual int32_t get_ID() = 0;
};


#endif //MICROMACHINES_BODY_H
