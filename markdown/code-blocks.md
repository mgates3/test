No ticks, no c++ (this has some styling in bitbucket, but not full c++)

    //-----
    // Some comments about enum Foo.
    enum class Foo {
        A,
        B,
    };

    //-----
    // Some comments about class Bob.
    class Bob {
    public:
        Bob();
    };

    //-----
    // Some comments about this function.
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }

No ticks, with she-bang c++ (this works in bitbucket)

    #!c++
    //-----
    // Some comments about enum Foo.
    enum class Foo {
        A,
        B,
    };

    //-----
    // Some comments about class Bob.
    class Bob {
    public:
        Bob();
    };

    //-----
    // Some comments about this function.
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }

No ticks, with she-bang cpp (this works in bitbucket)

    #!cpp
    //-----
    // Some comments about enum Foo.
    enum class Foo {
        A,
        B,
    };

    //-----
    // Some comments about class Bob.
    class Bob {
    public:
        Bob();
    };

    //-----
    // Some comments about this function.
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }

With ticks, no c++ (no styling on bitbucket)
```
    //-----
    // Some comments about enum Foo.
    enum class Foo {
        A,
        B,
    };

    //-----
    // Some comments about class Bob.
    class Bob {
    public:
        Bob();
    };

    //-----
    // Some comments about this function.
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }
```

With ticks cpp (this works in chrome preview and bitbucket)
```cpp
    //-----
    // Some comments about enum Foo.
    enum class Foo {
        A,
        B,
    };

    //-----
    // Some comments about class Bob.
    class Bob {
    public:
        Bob();
    };

    //-----
    // Some comments about this function.
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }
```

With ticks c++ (this works in chrome preview and bitbucket)
```c++
    //-----
    // Some comments about enum Foo.
    enum class Foo {
        A,
        B,
    };

    //-----
    // Some comments about class Bob.
    class Bob {
    public:
        Bob();
    };

    //-----
    // Some comments about this function.
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }
```

With ticks, she-bang cpp (no styling on bitbucket; shows she-bang)
```
    #!cpp
    //-----
    // Some comments about enum Foo.
    enum class Foo {
        A,
        B,
    };

    //-----
    // Some comments about class Bob.
    class Bob {
    public:
        Bob();
    };

    //-----
    // Some comments about this function.
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }
```

With ticks, she-bang c++ (no styling on bitbucket; shows she-bang)
```
    #!c++
    //-----
    // Some comments about enum Foo.
    enum class Foo {
        A,
        B,
    };

    //-----
    // Some comments about class Bob.
    class Bob {
    public:
        Bob();
    };

    //-----
    // Some comments about this function.
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }
```
