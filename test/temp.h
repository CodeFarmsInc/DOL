class A {
    ZZ_EXT_A
    int a;
public:
    A(){}
    A(int i);
    void prt();
};
class B {
    ZZ_EXT_B
    int b;
public:
    B(){}
    B(int i);
    void prt();
};
ZZ_HYPER_SINGLE_AGGREGATE(aggr,B,A);
ZZ_HYPER_NAME(aName,A);
ZZ_HYPER_UTILITIES(util);
