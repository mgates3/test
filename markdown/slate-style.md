[TOC]

Introduction
================================================================================

Much of this guide quotes or paraphrases the
[Python style guide (PEP 8)](https://www.python.org/dev/peps/pep-0008/).

Code is read much more often than
it is written. The guidelines provided here are intended to improve
the readability of code and make it consistent across
SLATE, as an important part of SLATE's sustainability.

A style guide is about consistency. Consistency with this style guide
is important. Consistency within a project is more important.
Consistency within one module or function is the most important.

However, know when to be inconsistent -- sometimes style guide
recommendations just aren't applicable. When in doubt, use your best
judgment. Look at other examples and decide what looks best. And
don't hesitate to ask!

In particular: do not break backwards compatibility just to comply with
this style guide!

Some other good reasons to ignore a particular guideline:

1. When applying the guideline would make the code less readable, even
   for someone who is used to reading code that follows this style guide.

2. To be consistent with surrounding code that also breaks it (maybe
   for historic reasons) -- although this is also an opportunity to
   clean up someone else's mess (in true extreme programming style).

3. Because the code in question predates the introduction of the
   guideline and there is no other reason to be modifying that code.



Code Formatting
================================================================================

SLATE largely follows
[K&R](https://en.wikipedia.org/wiki/Indentation_style#K&R_style)
and
[Stroustrup style](https://en.wikipedia.org/wiki/Indentation_style#Variant:_Stroustrup).

Indentation
--------------------------------------------------------------------------------

Use 4 spaces per indentation level
(class, enum, function, if, while, switch, case, etc.).
However, namespaces do not add an indentation level.
Also, `public`, `protected`, and `private` keywords are not indented.

Never use tabs. (Makefiles of course must use tabs for recipes.)

Braces
--------------------------------------------------------------------------------

For functions, place the opening brace on a line by itself.
This visually separates the parameters from the code inside the function.

Yes:
```c++
    void longFunctionName(
        param1,
        param2)
    {
        code();
    }
```

No:
```c++
    void longFunctionName(
        param1,
        param2) {
        code();
    }
```

For other blocks, place the opening brace at the end of its statement line
("cuddled"). This saves significant vertical space.

Yes:
```c++
    namespace slate {
    namespace internal {

    //------------------------------------------------------------------------------
    enum class Values {
        A,
        B,
    };

    //==============================================================================
    class FooBar {
    public:
        FooBar(int m, int n)
            : number_rows_(m),
              number_cols_(n)
        {
            code();
        }

    private:
        int num_rows_, num_cols_;
    };

    //------------------------------------------------------------------------------
    void longFunctionName()
    {
        if (condition) {
            code();
        }
        else if (condition) {
            code();
        }
        else {
            code();
        }

        for (int i = 0; i < n; ++i) {
            code();
        }

        while (condition) {
            code();
        }

        do {
            code();
        } while (condition);

        switch (value) {
            case 1:
                break;
            default:
                break;
        }
    }

    }  // namespace internal
    }  // namespace slate
```

No:
```c++
    // Don't indent namespaces.
    namespace slate {
        namespace internal {
            class FooBar {
            };
        }
    }

    // Don't use more than 4 spaces.
    class FooBar {
            member;
    };

    // Don't use less than 4 spaces.
    void longFunctionName()
    {
      if (condition) {
        for (...) {
        }
      }
    }

    // Don't skip indenting cases inside switch.
    switch (value) {
    case 1:
        code();
        break;
    default:
        code();
        break;
    }

    // Don't cuddle else.
    if (condition) {
        code();
    } else if (condition) {
        code();
    } else {
        code();
    }

    // Don't uncuddle braces (with some exceptions below).
    if (condition)
    {
        code();
    }
    else
    {
        code();
    }
```

The closing brace usually goes on a line by itself.
The exception is an empty block, such as an empty constructor or empty loop.
```c++
    class Foo {
        Foo()
        {}
    };

    while (progress.at(sweep-1).load() < depend) {}
```

Don't make an empty loop using just a semi-colon. Make it *obvious* that it
is empty.
```c++
    No:  while (progress.at(sweep-1).load() < depend);
```

Braces may be used, but are not required, on short one *line* `if`, `for`, and
`while` blocks. However, if a single *statement* spans multiple *lines*, braces
should be added. If one block in an `if-then-else` has braces, put braces on all
its blocks.

Yes:
```c++
    // Braces not required.
    if (condition)
        one-line;
    else
        one-line;

    // Braces may be used.
    if (condition) {
        one-line;
    }
    else {
        one-line;
    }

    // Braces required for a single multi-line statement.
    if (condition) {
        longFunctionName(
            args,
            args);
    }

    // `else` block requires braces, so use braces for both blocks.
    if (condition) {
        one-line;
    }
    else {
        code();
        code();
    }
```

No:
```c++
    // Braces required for a multi-line statement.
    if (condition)
        longFunctionName(
            args,
            args);

    // `else` block requires braces, so use braces for both blocks.
    if (condition)
        one-line;
    else {
        code();
        code();
    }
```

However, do not duplicate the opening brace if using an `#ifdef`. Doing so often
confuses text editors, since they see an unbalanced opening brace. In this
(hopefully rare) case, put the brace on a line by itself (Allman style):

Yes:
```c++
    #ifdef MACRO
        while (condition)
    #else
        while (other-condition)
    #endif
        {
            code();
        }
```

No:
```c++
    #ifdef MACRO
        while (condition) {
    #else
        while (other-condition) {
    #endif
            code();
        }
```

OpenMP pragmas must also have the brace after the pragma:
```c++
    #pragma omp task
    {
        code();
    }
```

Whitespace
--------------------------------------------------------------------------------

Put one space between `if`, `for`, `while`, `do`, `switch` and its opening
parenthesis or brace.
Put one space before an opening brace, except for a function.
No spaces inside the parenthesis.
```c++
    //     +-----------+--- spaces
    //     | ,......., | .. no spaces
    //     V x       x v
    Yes: if (condition) {
    No:  if(condition){
    No:  if( condition ){

    //      +-----------------------+--- spaces
    //      | ,..................., | .. no spaces
    //      V x                   x v
    Yes: for (int i = 0; i < n; ++i) {
    No:  for(int i = 0; i < n; ++i){
    No:  for( int i = 0; i < n; ++i ){

              +-----------+--- spaces
              | ,......., | .. no spaces
              V x       x v
    Yes: while (condition) {
    No:  while(condition){
    No:  while( condition ){

    //     +---------------- space
    //     |
    //     V
    Yes: do {
             code();
         } while(condition);
    //    ^      x       x
    //    |      '.......'.. no spaces
    //    +----------------- space

    No:  do{
             code();
         }while(condition);
```

Avoid extraneous whitespace in the following situations:

- **Question:** Immediately inside parentheses, brackets or braces.
```c++
    Yes: spam(ham[1], {eggs: 2})
    No:  spam( ham[ 1 ], { eggs: 2 } )
```

  I tend to put spaces inside function parenthesis, to avoid long runs without
  spaces. LAPACK also puts spaces inside parenthesis.
```c++
    long_function_name(long_first_argument(long_inner_argument))
    vs.
    long_function_name( long_first_argument( long_inner_argument ) )
```

- Immediately before a comma, semicolon, or colon:
```c++
    Yes: for (int i = 0; i < n; ++i)
    No:  for (int i = 0 ; i < n ; ++i)

    Yes: function(a, b, c);
    No:  function(a , b , c);
```

- Immediately before the open parenthesis that starts the argument
  list of a function call:
```c++
    Yes: spam(1)
    No:  spam (1)
```

- Immediately before the open brace that starts an indexing:
```c++
    Yes: mymap["key"] = mylist[index]
    No:  mymap ["key"] = mylist [index]
```

- Excessive space around an assignment (or other) operator to
  align it with another. Small amounts of extra space (say, ≤ 4 spaces)
  to align items to improve readability and vertical editing are acceptable;
  use discretion.

  Yes:
```c++
    x = 1;
    y = 2;
    long_variable = 3;

    // One extra space to align = signs.
    m  = 1;
    n  = 2;
    nb = 40;
```

  No:
```c++
    x                   = 1;
    y                   = 2;
    extra_long_variable = 3;
```

- Always surround these binary and ternary operators with a single space on
  either side, and a single space after unary `!`:

    - assignment (`=`)
    - augmented assignment (`+=`, `-=`, etc.)
    - comparison operators (`==`, `<`, `>`, `!=`, `<=`, `>=`)
    - boolean operators (`&&`, `||`, `!`)
    - ternary operator (`? :`)

  Examples:
```c++
    Yes: i = j;
    No:  i=j;

    Yes: if (i < n)
    No:  if (i<n)       //>

    Yes: if (i == j && diag == Unit)
    No:  if (i==j&&diag==Unit)

    Yes: if (! row_major)
    No:  if (!row_major)

    Yes: condition ? value-if-true : value-if-false
    No:  condition?value-if-true:value-if-false
```

  **Question:** for default arguments, space or no space?
```c++
    function(argument=default)
    function(argument = default)

    template <typename type=default>
    template <typename type = default>
```

- If operators with different priorities are used, consider adding
  whitespace around the lowest priority operators. Use
  your own judgment; however, never use more than one space, and
  always have the same amount of whitespace on both sides of a binary
  operator.

  Yes:
```c++
    x = x*2 - 1
    hypot2 = x*x + y*y
    c = (a + b)*(a - b)
```

  Rather not:
```c++
    x = x*2-1
    x = x * 2 - 1
    hypot2 = x * x + y * y
    c = (a + b) * (a - b)
```

  Definitely not:
```c++
    x = x *2 - 1
    x = x*2 -1
```

Maximum Line Length
--------------------------------------------------------------------------------

Soft limit goal is 80 characters.
Hard limit is 85 characters.

**Rationale:**
Limiting the required editor window width makes it possible to have
several files open side-by-side, and works well when using code
review tools that present the two versions in adjacent columns.
Having a soft limit avoids awkward wrapping just because 1-2 characters exceed
the soft limit, and to avoid the need to rewrap code that *did* fit into 80
characters, but was later indented one more level. Don't be pedantic about it,
but don't stretch a line to 100 characters, either!

Line Continuation
--------------------------------------------------------------------------------

For statements that continue onto multiple lines, align lines either:

1. Vertically after open parenthesis, or
2. Using hanging indent, with no arguments on the first line. Add an extra level
   of indentation if needed to clearly distinguish it as a continuation line.
   **Question:** add 2 levels?

Yes:
```c++
    // 1. Align with opening parenthesis.
    foo = long_function_name(var_one, var_two,
                             var_three, var_four)

    // 2. Hanging indent adds a level (4 spaces).
    foo = long_function_name(
        var_one, var_two,
        var_three, var_four);

    // Question: add 2 levels (8 spaces)?
    foo = long_function_name(
            var_one, var_two,
            var_three, var_four);
```

No:
```c++
    // Arguments on first line forbidden when not using vertical alignment.
    foo = long_function_name(var_one, var_two,
        var_three, var_four)
```

### Multi-line if-statements

When an `if` condition extends across multiple lines, the
`if (` creates a natural 4-space indent for the
subsequent lines of the multi-line conditional, which can produce a visual
conflict with the code inside the `if`-statement,
which is also indented by 4 spaces.

**Question:** Should SLATE take a position on this? (PEP 8 does not.)

Acceptable options in this situation include, but are not limited to:
```c++
    // No extra indentation.
    if (this_is_one_thing
        && that_is_another_thing) {
        do_something();
    }

    // Add a blank line.
    if (this_is_one_thing
        && that_is_another_thing) {

        do_something();
    }

    // Move opening brace to next line.
    if (this_is_one_thing
        && that_is_another_thing)
    {
        do_something();
    }

    // Add a comment, which will provide some distinction in editors
    // supporting syntax highlighting.
    if (this_is_one_thing
        && that_is_another_thing) {
        // Since both conditions are true, we can frobnicate.
        do_something();
    }

    // Add some extra indentation on the conditional continuation line.
    if (this_is_one_thing
            && that_is_another_thing) {
        do_something();
    }
```

(Also see the discussion of whether to break before or after binary
operators below.)

### Indent of Member Initializers

In class constructors, the colon for initializing member variables is indented 4
spaces; the actual member variables are thus indented 6 spaces. This is to avoid
the visual conflict between parameters (with hanging indent) and member
initializers. Initializers are listed one per line.

Yes:
```c++
    MyClass::MyClass(
        param1,
        param2)
        : member1_(),
          member2_()
    {}
```

No:
```c++
    MyClass::MyClass(
        param1,
        param2)
        : member1_(), member2_()
    {}

    MyClass::MyClass(
        param1,
        param2):
        member1_(),
        member2_()
    {}
```

### Indent of Closing Braces

The closing brace/bracket/parenthesis on multi-line constructs may
be lined up under the first character of the line that
starts the multi-line construct, as in:
```c++
    int my_list[] = {
        1, 2, 3,
        4, 5, 6
    };
```

### Line Break Before Binary and Ternary Operators

Consistent with math publishing convention,
break continued lines before binary and ternary operators.
Where applicable, align operator under assignment = sign.
Short ternary operators may be on one line.

Yes: easy to match operators with operands
```c++
    income = gross_wages
           + taxable_interest
           + (dividends - qualified_dividends)
           - ira_deduction
           - student_loan_interest

    if (foo
        && bar
        && baz) {
        code();
    }

    // ternary operator
    result = condition ? value-if-true : value-if-false;
    result = long-condition
           ? long-value-if-true
           : long-value-if-false;
```

No: operators sit far away from their operands
```c++
    income = gross_wages +
             taxable_interest +
             (dividends - qualified_dividends) -
             ira_deduction -
             student_loan_interest

    if (foo &&
        bar &&
        baz) {
        code();
    }

    result = condition ?
             value-if-true :
             value-if-false;
```

**Rationale:**
[See PEP008](https://www.python.org/dev/peps/pep-0008/#should-a-line-break-before-or-after-a-binary-operator).
This is the convention followed in mathematics and advocated by Knuth. It
highlights the operators, makes them all line up, and is clearer what is
being operated on.

This is a change from PLASMA and SLATE's original style sheet, which placed
boolean operators (&& and ||) at the end of lines.

**Question:** what about lining up clauses for readability:
```c++
    // new style
    if (A.op() == Op::NoTrans
        || A.op() == Op::Trans)

vs.

    // new style + extra spaces
    if (   A.op() == Op::NoTrans
        || A.op() == Op::Trans)

vs.

    // old style
    if (A.op() == Op::NoTrans ||
        A.op() == Op::Trans)
```

**Question:** should ternary operators be enclosed in parenthesis?
```c++
    result = (condition ? value-if-true : value-if-false);
    result = (condition
           ? value-if-true
           : value-if-false);
```

### Compound statements

Multiple statements on the same line are generally discouraged.

  Yes:
```c++
    if (foo == "blah")
        do_blah_thing();

    do_one();
    do_two();
    do_three();
```

  Rather not:
```c++
    if (foo == "blah") do_blah_thing();

    do_one(); do_two(); do_three();
```

  Definitely not:
```c++
    if (foo == "blah") do_blah_thing();
    else do_non_blah_thing();

    try { something(); }
    catch (Exception const& ex) { cleanup(); }

    do_one(); do_two(); do_three(long, argument,
                                 list, like, this)

    if (foo == "blah") { one(); two(); three(); }
```

Blank lines
--------------------------------------------------------------------------------

Surround function definitions and classes by a single blank line.
Blank lines may be omitted between a bunch of related one-liners
(although probably not if properly documented with Doxygen).

Use blank lines in functions, sparingly, to indicate logical sections.
Think of this like paragraphs in a paper.

Yes:
```c++
    //==============================================================================
    class Foo {
    public:
        Foo()
        {}

        Foo(param)
        {
            code();
        }

        // No blanks needed between prototypes, only between definitions.
        void member1();
        void member2();
        void member3();

        // May skip blank lines for one-liners.
        int m()  const { return m_; }
        int n()  const { return n_; }
        int mt() const { return mt_; }
        int nt() const { return nt_; }
    };

    //------------------------------------------------------------------------------
    void function1()
    {
        code();
    }

    //------------------------------------------------------------------------------
    void function2()
    {
        code();
    }
```

Trailing Whitespace
--------------------------------------------------------------------------------

Never include trailing whitespace.

**Rationale:**
Changes in trailing whitespace needlessly complicate diff and merges.
Some editors can be set to automatically delete trailing whitespace on save.

- In BBEdit, Preferences > Text Files > Strip trailing whitespace.

Files should end with exactly one newline.

**Rationale:**
Omitting the newline complicates diff, merges, grep, and some editors will
complain. Having multiple newlines causes needless changes.

Trailing Commas
--------------------------------------------------------------------------------

Trailing commas are okay and encouraged in enum lists (since C++11).
Including a trailing comma helps to avoid merge conflicts, where 2 different
changes both add a new item and thus both add a comma to the previous line.

Yes:
```c++
    enum class Foo {
        A,
        B,
        C,
    };
```

The same rationale is used for line continuation (`\`) in Makefile lists.
Be sure to include a blank line after the list, since the first blank
is part of the list itself.
```makefile
    src = \
        file1.cc \
        file2.cc \

    next = ...
```



Comments
================================================================================

Comments that contradict the code are worse than no comments. Always
make a priority of keeping the comments up-to-date when the code
changes!

Use C++ style `//` comments.
For Doxygen, use `///` comments.
For explanatory comments, always put one space after `//` or `///`.
For commenting out code, a space is not required.

Comment your code heavily, so a reader later can understand what you are
did, but do not state the obvious.

If a comment is a sentence, start with a capital letter
(unless it is an identifier -- never alter the case of identifiers!),
and end with a period. Use one space between sentences.
Consider using backticks \`...\` around identifiers.

If a comment is not a sentence, start with a small letter and do not end with
a period.

Write all comments in English.

Yes:
```c++
    //----------------------------------------
    /// Solves a complex problem.
    ///
    /// @param[in] n
    ///     Array size.
    ///
    /// @param[out] result
    ///     Output data.
    ///
    void function(int n, int* result)
    {
        // Do some work.
        code();

        // block size
        int nb = 32;

        // No space required to comment out code.
        //int mb = 64;
    }
```

No:
```c++
    //Solves a complex problem.   # Missing initial space.
    // solves a complex problem.  # Missing initial capital.
    // Solves a complex problem   # Missing final period.
```

Comment the function *definition*, not the function *prototype*.
Duplicated comments diverge.

Start each file with the copyright boilerplate.

Use `A^H` and `A^T` rather than Matlab `A'` notation. The explicit
conjugate-transpose or transpose is more explicit, easier to see, and will
format nicely in Doxygen.

In Doxygen, use Latex-style markup: `$...$` and `\[...\]` for equations.

Block comments
--------------------------------------------------------------------------------

Block comments generally apply to some (or all) code that follows
them, and are indented to the same level as that code. Each line of a
block comment starts with `//` or `///`, and a single space (unless it is
indented text inside the comment).

Paragraphs inside a block comment are separated by a line containing only `//`
or `///`. Do not indent paragraphs.

Yes:
```c++
    /// Computes an LU factorization of a general m-by-n matrix $A$
    /// using partial pivoting with row interchanges.
    ///
    /// The factorization has the form
    /// \[
    ///     A = P L U
    /// \]
    /// where $P$ is a permutation matrix, $L$ is lower triangular with unit
    /// diagonal elements (lower trapezoidal if m > n), and $U$ is upper
    /// triangular (upper trapezoidal if m < n).
```

Inline comments
--------------------------------------------------------------------------------

An inline comment is a comment on the same line as a statement.
Use inline comments sparingly. They make it harder to fit within 80 characters,
and can lead to lines changing when only the comment changed, not the code.
Inline comments should be separated by at least two spaces from the
statement. They should start with `//` and a single space.

If they state the obvious, inline comments are unnecessary and in fact
distracting. Don't do this:
```c++
    x = x + 1;  // Increment x.
```

But sometimes, this is useful:
```c++
    x = x + 1;  // Compensate for border.
```

Inline comments using Doxygen's `///<` can be useful to document enum values
and member variables:
```c++
    int64_t mt_;  ///< Number of block rows in this view.
    int64_t nt_;  ///< Number of block cols in this view.
```

Horizontal Rules
--------------------------------------------------------------------------------

Use horizontal rule lines consisting of dashes or equal signs to separate
major sections of code. Note these use `//`, not Doxygen's `///`, which would
add extra rule lines to Doxygen's output.

Before a class, use an 80 character line of `//` and equals:
```c++
    //==============================================================================
    /// Class documentation.
    class Foo {
    };
```

Before a function definition or enum, use an 80 character line of `//` and
dashes:
```c++
    //------------------------------------------------------------------------------
    /// Function documentation.
    void function() {
    }
```

Inside a function, major sections can be marked by lines such as these,
which have 40, 20, and 10 dashes, respectively:
```c++
    //----------------------------------------
    // Section.

    //--------------------
    // Sub-section.

    //----------
    // Sub-sub-section.
```

**Rationale:**
Instead of fixed length rules, as above, some prefer making the rule line fit
the length of the comment text. However, this requires changing the rule line
whenever the comment changes, and prevents a hierarchy of sections.

Testers use 3 boilerplate comments to quickly identify where the
actual routine calls are, amidst all the matrix setup:
```c++
    //==================================================
    // Run SLATE test.
    //==================================================

    //==================================================
    // Check results.
    //==================================================

    //==================================================
    // Run ScaLAPACK reference routine.
    //==================================================
```



Naming Conventions
================================================================================

- Enum values      are UpperCamelCase:  `enum class MatrixType`
- Classes          are UpperCamelCase:  `class SymmetricMatrix`
- Member functions are lowerCamelCase:  `Matrix::tileGet()`
- Global functions are lowerCamelCase:  `gesvMixed()`
- Variables        are snake\_case:     `my_awesome_variable`
- Constants        are snake\_case:     `max_life`
- Namespaces       are lowercase:       `namespace slate {...}`
  Namespaces should be short, so hopefully they are one word, not two words
  needing lowerCamelCase or snake_case.

- Private variables have underscore suffix: `int mt_, nt_;`
  Note that leading underscores are reserved by C++: `_mt` is illegal.

**Question:**
Should private routines be named differently, to clearly distinguish them? I
guess not, since C++ will enforce private/public, and we may want to change a
private routine to public.

Note: When using acronyms in CamelCase, capitalize all the
letters of the acronym. Thus HTTPServerError is better than
HttpServerError.

[PLASMA's style guide](https://bitbucket.org/icl/plasma/wiki/Conventions),
which SLATE's guide was originally based on, uses
snake\_case for functions. Hence TestSweeper, BLAS++, and LAPACK++ use
snake\_case. Since LAPACK itself uses snake\_case (`ssytrs_aa_2stage`), that
works well. A few functions in SLATE use snake\_case, but should be converted to
lowerCamelCase, with the snake\_case version being deprecated (but not
immediately deleted, for backwards compatibility).

Headers that an application needs (i.e., that would be included via slate.hh)
go in include/slate. Strictly internal headers go in src.

SLATE library (`-lslate`) source files go in src. Underneath src, directories
group similar files. Ideally, directories would be based on namespaces, like
`src/internal` for the `slate::internal` namespace. Currently some directories
differ from that practice.

Never have 2 files
with the same name in different directories, since this causes an issue building
a static library. For instance, **do not** have `src/gemm.cc` and
`src/internal/gemm.cc`, which would make two different `gemm.o` files to add to
`libslate.a`. In this case, repeat the namespace in the filename:
```
    src/gemm.cc                                 // slate::gemm
    src/internal/internal_gemm.cc               // slate::internal::gemm
```

Names to Use
--------------------------------------------------------------------------------

Follow common mathematical conventions, including:
- For matrices, use capital `A`, `B`, `C`, etc.
- For vectors, use lowercase `x`, `y`, `z`, etc.
- For vector of eigenvalues, use `Lambda`.
  For vector of singular values, use `Sigma`.
- For scalars, use lowercase Greek `alpha`, `beta`, etc.

- For number of block rows and cols, use `mt` and `nt`, respectively.
- For number of individual rows and cols, use `m` and `n`, respectively.

- For block row and col loop counters, use `i` and `j`, respectively.
  This differs from PLASMA, which used `m` and `n`.
- For 3rd loop counter, use `k`.

- For individual row and col loop counters, use `ii` and `jj`, respectively.

- For tile block size, use `mb` (rows) and `nb` (cols).
- Use `ib` for *inner blocking*.
- For truncated tile size, use `ib` and `jb`, as in LAPACK.
  E.g., `ib = min( nb, m - i )` and `jb = min( nb, n - j );`.
  This creates a conflict with inner blocking, but SLATE doesn't need to
  refer to the truncated tile size very often.

Constants
--------------------------------------------------------------------------------

Declare constants near the top of the function. Use these names:
```c++
    // scalar (real or complex)
    const scalar_t zero  = 0.0;
    const scalar_t half  = 0.5;
    const scalar_t one   = 1.0;

    // real
    const real_t   rzero = 0.0;
    const real_t   rhalf = 0.5;
    const real_t   rone  = 1.0;

    // integer
    const int64_t  izero = 0;
    const int64_t  ione  = 1;
```

Negative values can be expressed using those names, such as `-one`, instead of
`negative_one`, `neg_one`, or worse, `mone`.

Yes:
```c++
    gemm(-one, A, B, zero, C);
```

Older, deprecated style:
```c++
    gemm(scalar_t(-1.0), A, B, scalar_t(0.0), C);
```

For clarity, instead of passing an ambiguous constant like 0 or 1 for an
argument, name the constant:
```c++
    const int priority_zero = 0;
    const int priority_one  = 1;

    internal::gemm(..., priority_one);
```

Names to Avoid
--------------------------------------------------------------------------------

Never use the characters 'l' (lowercase letter el), 'O' (uppercase
letter oh), or 'I' (uppercase letter eye) as single character variable
names.

**Rationale:**
In some fonts, these characters are indistinguishable from the
numerals one and zero. When tempted to use 'l', use 'L' instead.



C++ Features
================================================================================

Loops
--------------------------------------------------------------------------------

Declare loop variables in the loop itself.
```c++
    for (int i = 0; i < n; ++i) {
        ...
    }

    auto end = container.end();
    for (auto iter = container.begin(); iter != end; ++iter) {
        int value = *iter;
    }
```

Prefer pre-increment to post-increment.
```c++
    Yes: for (int i = 0; i < n; ++i)
    No:  for (int i = 0; i < n; i++)
```

**Rationale:**
For int, these are essentially equivalent, but for iterators, `i++` creates an
extra temporary variable to return, thus being inherently less inefficient,
while `++i` doesn't create a temporary.

**Question:** preferred spacing for range loop colon?

Where applicable, use C++11 range loop (note spaces before and after : operator).
```c++
    for (int value : container) {
        ...
    }
```

For an infinite loop, use `while (true)`.
Do not use `for ( ; ; )`, which is a weird C++ idiom.
```c++
    while (true) {
        ...
        if (condition)
            break;
        ...
    }
```

Exceptions
--------------------------------------------------------------------------------

Catch exceptions as const reference, and name it `ex`:
```c++
    try {
        ...
    }
    catch (Exception const& ex) {
        ...
    }
```

Additionally, for all try/except clauses, limit the ``try`` clause
to the absolute minimum amount of code necessary. This
avoids masking bugs.

Miscellaneous
--------------------------------------------------------------------------------

Stuff to write up.

Generally SLATE requires C++11, plus tuple fix { ... } that may require C++17.

Self-contained headers

#define guards

C libraries have extern guards

Order of includes:
1. SLATE headers
2. standard C++ headers
3. standard C   headers
4. other library headers

**Rationale:**
This ensures that SLATE headers are including everything they need,
and not accidentally getting it from a previously included C++ header.
It is the order advocated by Google [verify].

All code is in `slate` namespace

Avoid global variables

Data members private, unless static const

Use `auto` for long type names

Rule of 3 or 5
Either need all 3: destructor, copy constructor, assignment, or none of them.
Generally need all 3 when memory is being allocated with new.
For C++11, rule of 5:
destructor, copy constructor, move constructor, assignment, move assignment.
There are some variations with the swap routine, copy-and-swap idiom.

Do not use `volatile` without reading
*Item 4: Use `std::atomic` for concurrency, `volatile` for special memory*
in Scott Meyer's book *Effective Modern C++*. You probably want to use `atomic`.

Dead Code
--------------------------------------------------------------------------------

Avoid dead code. In general, do not leave dead code commented out. Doing so
raises the question of what that code is doing there. Instead, simply delete it.
The original code is maintained in hg/git if ever needed again. This also
reduces the number of commits and work to cleanup codes later on.

The only time to leave dead code in is if it is a feature that isn't yet
implemented, or isn't fully working. For instance, pivoting to the left in LU
during the factorization. Then the experimental code can be left commented out,
with a comment explaining why it is commented out.

Pet peeves
----------------------------------------

Don't compare boolean values to true or false using ==.
```c++
    Yes: if (row_major)
    No:  if (row_major == true)

    Yes: if (! row_major)
    No:  if (row_major == false)
```

Preprocessor and Pragmas
------------------------

Many style guides, and some auto formatting tools like clang-format, insist that
preprocessor directives `#define`, `#if`, `#else`, `#endif` occur without any
indentation. This makes little sense. Without indent, the preprocessor
directives disrupt the visual flow of the code, making it difficult to tell what
is inside a loop or `if` block. The code is much easier to read if the
preprocessor directives are indented along with the code, and add their own
level of indentation. Thankfully, SLATE has fewer `#ifdef` than previous
libraries such as PLASMA and MAGMA, due to templating.

Yes:
```c++
    #ifndef BLAS_FORTRAN_NAME
        #if defined(FORTRAN_UPPER)
            #define BLAS_FORTRAN_NAME( lower, UPPER ) UPPER
        #elif defined(FORTRAN_LOWER)
            #define BLAS_FORTRAN_NAME( lower, UPPER ) lower
        #else
            #define BLAS_FORTRAN_NAME( lower, UPPER ) lower ## _
        #endif
    #endif

        if (k > 1) {
            #pragma omp task
            {
                #if CONDITION
                    slate::internal::gemmW(...);
                #else
                    slate::internal::gemmA(...);
                #endif
            }
        }
```

Rather not. If the code inside the `#if` is multiple lines, it is hard to find
where the `#if` ends:
```c++
        if (k > 1) {
            #pragma omp task
            {
                #if CONDITION
                slate::internal::gemmW(...);
                #else
                slate::internal::gemmA(...);
                #endif
            }
        }
```

No:
```c++
    #ifndef BLAS_FORTRAN_NAME
    #if defined(FORTRAN_UPPER)
    #define BLAS_FORTRAN_NAME( lower, UPPER ) UPPER
    #elif defined(FORTRAN_LOWER)
    #define BLAS_FORTRAN_NAME( lower, UPPER ) lower
    #else
    #define BLAS_FORTRAN_NAME( lower, UPPER ) lower ## _
    #endif
    #endif

        if (k > 1) {
    #pragma omp task
            {
    #if CONDITION
                slate::internal::gemmW(...);
    #else
                slate::internal::gemmA(...);
    #endif
            }
        }
```
