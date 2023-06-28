namespace slate {

class Foo {
    Foo():
        member1_(),
        member2_()
    {}
    
    ~Foo()
    {}
};

}

namespace blas {

void function() {
    try {
        code();
    } catch (std::exception const& ex) {
        code();
    }
    
    if (cond) {
        code();
    } else if (cond) {
        code();
    } else {
        code();
    }
    
    while (true) {
        code();
    }
    
    for (int i = 0; i < n; ++i) {
        code();
    }
    
    switch (variable) {
        case 1:
            code();
            break;
        case 2:
            code();
            break;
        default:
            code();
            break;
    }
    
    switch (variable) {
        case 1: {
            code();
            break;
        }
        case 2: {
            code();
            break;
        }
        default: {
            code();
            break;
        }
    }
    
    return 0;
}

}

int main(int argc, char** argv)
{
    function();
    return 0;
}
