// ===== PERSON 1 =====
// Gates.h - the two primitive gates (NAND, NOR) and every other gate built from them.
#pragma once
#include "Component.h"

// ------------------------- primitives -------------------------------------
class NandGate final : public Gate {
public:
    NandGate(std::string name, Wire* a, Wire* b, Wire* out = nullptr)
        : Gate(std::move(name), a, b, out) { initOutput(); }
    bool compute() const override { return !(a_->get() && b_->get()); }
};

class NorGate final : public Gate {
public:
    NorGate(std::string name, Wire* a, Wire* b, Wire* out = nullptr)
        : Gate(std::move(name), a, b, out) { initOutput(); }
    bool compute() const override { return !(a_->get() || b_->get()); }
};

// ------------------------- derived gates ----------------------------------
// A LogicBlock is a Circuit with one output wire.
class LogicBlock : public Circuit {
public:
    explicit LogicBlock(std::string name) : Circuit(std::move(name)) {}
    Wire* out() const { return out_; }
protected:
    Wire* out_ = nullptr;
};

// ---- built from NAND only ----
class NotGate : public LogicBlock {           // NOT a = NAND(a,a)
public:
    NotGate(const std::string& name, Wire* a, Wire* out = nullptr) : LogicBlock(name) {
        out_ = add<NandGate>(name + ".nand", a, a, out)->out();
    }
};

class AndGate : public LogicBlock {           // AND = NOT(NAND)
public:
    AndGate(const std::string& name, Wire* a, Wire* b) : LogicBlock(name) {
        auto* n = add<NandGate>(name + ".nand", a, b);
        out_ = add<NotGate>(name + ".not", n->out())->out();
    }
};

class OrGate : public LogicBlock {            // OR = NAND(NOT a, NOT b)
public:
    OrGate(const std::string& name, Wire* a, Wire* b) : LogicBlock(name) {
        auto* na = add<NotGate>(name + ".na", a);
        auto* nb = add<NotGate>(name + ".nb", b);
        out_ = add<NandGate>(name + ".nand", na->out(), nb->out())->out();
    }
};

class XorGate : public LogicBlock {           // classic 4-NAND XOR
public:
    XorGate(const std::string& name, Wire* a, Wire* b) : LogicBlock(name) {
        auto* n1 = add<NandGate>(name + ".n1", a, b);
        auto* n2 = add<NandGate>(name + ".n2", a, n1->out());
        auto* n3 = add<NandGate>(name + ".n3", b, n1->out());
        out_ = add<NandGate>(name + ".n4", n2->out(), n3->out())->out();
    }
};

class XnorGate : public LogicBlock {          // XNOR = NOT(XOR)
public:
    XnorGate(const std::string& name, Wire* a, Wire* b) : LogicBlock(name) {
        auto* x = add<XorGate>(name + ".xor", a, b);
        out_ = add<NotGate>(name + ".not", x->out())->out();
    }
};

// ---- built from NOR only ----
class NotNorGate : public LogicBlock {        // NOT a = NOR(a,a)
public:
    NotNorGate(const std::string& name, Wire* a) : LogicBlock(name) {
        out_ = add<NorGate>(name + ".nor", a, a)->out();
    }
};

class OrNorGate : public LogicBlock {         // OR = NOT(NOR)
public:
    OrNorGate(const std::string& name, Wire* a, Wire* b) : LogicBlock(name) {
        auto* n = add<NorGate>(name + ".nor", a, b);
        out_ = add<NotNorGate>(name + ".not", n->out())->out();
    }
};

class AndNorGate : public LogicBlock {        // AND = NOR(NOT a, NOT b)
public:
    AndNorGate(const std::string& name, Wire* a, Wire* b) : LogicBlock(name) {
        auto* na = add<NotNorGate>(name + ".na", a);
        auto* nb = add<NotNorGate>(name + ".nb", b);
        out_ = add<NorGate>(name + ".nor", na->out(), nb->out())->out();
    }
};

class XorNorGate : public LogicBlock {        // XOR from 5 NORs
public:
    XorNorGate(const std::string& name, Wire* a, Wire* b) : LogicBlock(name) {
        auto* n1 = add<NorGate>(name + ".n1", a, b);
        auto* n2 = add<NorGate>(name + ".n2", a, n1->out());
        auto* n3 = add<NorGate>(name + ".n3", b, n1->out());
        auto* xn = add<NorGate>(name + ".xnor", n2->out(), n3->out());
        out_ = add<NorGate>(name + ".n5", xn->out(), xn->out())->out();
    }
};
